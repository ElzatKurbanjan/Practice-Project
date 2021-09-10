#!/bin/sh

date=`TZ='Asia/Shanghai' date +%Y-%m-%d__%H:%M:%S`

# print the whole disk
df --total | tail -n1 | awk -v dt=${date} '{
    printf("%s 0 disk %sk %sk %s\n", dt, $2, $4, $5);
}'

df -k | awk -v dt=${date} '
    {
        if ( NR > 1) {
            printf("%s 1 %s %sk %sk %s\n", dt, $6, $2, $4, $5);
        }
    }
'