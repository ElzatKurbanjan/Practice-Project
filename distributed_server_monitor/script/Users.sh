#!/bin/bash
date=`TZ='Asia/Shanghai' date +%Y-%m-%d__%H:%M:%S`

UserCount=$(cat /etc/passwd | awk -F: '
    BEGIN {
        count=0;
    }
    {
        if ($3 >= 1000 && $1 != "nobody") {
            count+=1;
        }
    }
    END {
        printf("%d\n", count);
    }
')

RecentUsers=$(last | head -n3 | awk '
    BEGIN {
        i = 1;
        printf("[");
    }
    {
        if (i != 3) {
            printf("%s,", $1);
        } else {
            printf("%s", $1);
        }
        ++i;
    }
    END {
        printf("]\n");
    }
')

SudoUsers=[`cat /etc/group | grep sudo | cut -d: -f4`]

WLineCount=$(w | wc -l)
LogonUsers=$(w | awk -v count=${WLineCount} '
    BEGIN {
        printf("[");
    }
    {
        if (NR > 2 && NR != count) {
            printf("%s_%s_%s,", $1, $3, $2);
        }
        if (NR == count) {
            printf("%s_%s_%s", $1, $3, $2);
        }
    }
    END {
        printf("]");
    }
')

echo ${date} ${UserCount} ${RecentUsers} ${SudoUsers} ${LogonUsers}