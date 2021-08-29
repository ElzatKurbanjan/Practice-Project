#!/bin/bash
date=`TZ='Asia/Shanghai' date +%Y-%m-%d__%H:%M:%S`
#echo $date
mem_info_string=`free -m | head -n2 | tail -n1 | sed 's/  */ /g'`
total_mem=`echo $mem_info_string | cut -d' ' -f2`
#echo ${total_mem}m
free_mem=`echo $mem_info_string | cut -d' ' -f4`
#echo ${free_mem}m
used_mem=`echo $mem_info_string | cut -d' ' -f3`
#echo ${used_mem}m

used_rate=$(echo "scale=3;${used_mem} / ${total_mem}" | bc)
used_rate=$(echo "scale=1;${used_rate} * 100 / 1" | bc)
#echo $used_rate

last_dynamic_average_used_memory=$1
if [ -z ${last_dynamic_average_used_memory} ];then
    last_dynamic_average_used_memory=0
fi
current_dynamic_average_used_memory=$(echo "scale=1;0.7 * ${last_dynamic_average_used_memory} + 0.3 * ${used_rate}" | bc)
#echo ${current_dynamic_average_used_memory}

echo ${date}" "${total_mem}M" "${free_mem}M" "${used_rate}%" "${current_dynamic_average_used_memory}%