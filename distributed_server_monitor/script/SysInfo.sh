#!/bin/sh

date=`TZ='Asia/Shanghai' date +%Y-%m-%d__%H:%M:%S`

dev_info=$(uname -a | awk '
    {
        printf("%s %s/%s", $2, $4, $3);
    }
')

login_info=$(uptime | awk '
    {
        login_time_str = $5
        split(login_time_str, login_time, ":");
        hours = login_time[1];
        minites_str = login_time[2];
        split(minites_str, minites_arr, ",");
        minites=minites_arr[1];
        printf("%s_%s_%s_%s_hours,_%s_minutes %s %s %s\n", $2, $3, $4, hours, minites, $10, $11, $12);   
    }')


disk_info=$(df --total | tail -n1 | awk '{
    printf("%sk %s\n", $2, $5);
}')

mem_info=$(./MemLog.sh | awk '{print $2" "$4}')

disk_alert=$(echo ${disk_info} | awk '{
    if ($2 < 80) {
        printf("normal");
    } else if ($2 < 90) {
        printf("note");
    } else {
        printf("warning");
    }
}')

mem_alert=$(echo ${mem_info} | awk '{
    if ($2 < 70) {
        printf("normal");
    } else if ($2 < 80) {
        printf("note");
    } else {
        printf("warning");
    }
}')


echo ${date} ${dev_info} ${login_info} ${disk_info} ${mem_info} ${disk_alert} ${mem_alert}

