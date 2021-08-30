#!/bin/bash
cpu_used_rate_thresh=50
mem_used_rate_thresh=50

eval `ps aux | awk -v mth=${mem_used_rate_thresh} -v cth=${cpu_used_rate_thresh} -v i=0 '
    {
        if($4>mth || $3>cth) {
            printf("suspicious_process_pid[%d]=\"%s\"\n", i, $2);
            ++i;
        }
    }
    '`

if [ ${#suspicious_process_pid[*]} -gt 0 ]; then
    sleep 5
    date=`TZ='Asia/Shanghai' date +%Y-%m-%d" "%H:%M:%S`
    ps aux | awk -v spp_string="${suspicious_process_pid[*]}" -v mth=${mem_used_rate_thresh} -v cth=${cpu_used_rate_thresh} -v dt="${date}" '
        BEGIN {
            spp_arr_len=split(spp_string, pid_arr, " ");
        }
        {
            if($4>mth || $3>cth) {
                for (i = 1; i <= spp_arr_len; i++) {
                    if ($2 == pid_arr[i]) {
                        print dt, $11, $2, $1, $3"%", $4"%";
                    }
                }
            }
        }
    '
fi


