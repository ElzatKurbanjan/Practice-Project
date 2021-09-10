#!/bin/bash

date=`TZ='Asia/Shanghai' date +%Y-%m-%d__%H:%M:%S`

load=$(cat /proc/loadavg | awk '{printf("%.2f %.2f %.2f", $1, $2, $3)}')

cpu_time1=$(cat /proc/stat | head -n1 | awk '
    BEGIN {
        total_cpu_time = 0;
        used_cpu_time = 0;
    }
    {
        total_cpu_time = $2 + $3 + $4 + $5 + $6 + $7 + $8 + $9 + $10 + $11;
        used_cpu_time = $2 + $3 + $4 + $7 + $8 + $9 + $10 + $11;
    }
    END {
        printf("%s,%s", used_cpu_time, total_cpu_time);
    }')

sleep 0.5

cpu_used_rate=$(cat /proc/stat | head -n1 | awk -v last_cpu_time_str=${cpu_time1} '
    BEGIN {
        split(last_cpu_time_str, last_cpu_time, ",");
        last_used_cpu_time = last_cpu_time[1];
        last_total_cpu_time = last_cpu_time[2];
        used_cpu_time = 0;
        total_cpu_time = 0;
    }
    {
        total_cpu_time = $2 + $3 + $4 + $5 + $6 + $7 + $8 + $9 + $10 + $11;
        used_cpu_time = $2 + $3 + $4 + $7 + $8 + $9 + $10 + $11;
    }
    END {
        time_interval = total_cpu_time - last_total_cpu_time;
        used_time = used_cpu_time - last_used_cpu_time;
        printf("%.2f%%", used_time / time_interval * 100);
    }')

echo ${date} ${load} ${cpu_used_rate}