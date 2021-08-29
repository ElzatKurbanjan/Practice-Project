#!/bin/bash
date=`TZ='Asia/Shanghai' date +%Y-%m-%d__%H:%M:%S`
echo $date
mem_info_string=`free -m | head -n2 | tail -n1 | sed 's/  */ /g'`
total_mem=`echo $mem_info_string | cut -d' ' -f2`
echo ${total_mem}m
free_mem=`echo $mem_info_string | cut -d' ' -f4`
echo ${free_mem}m
used_mem=`echo $mem_info_string | cut -d' ' -f3`
echo ${used_mem}m

used_rate=$(echo "scale=1;${used_mem} / ${total_mem} * 100" | bc)
echo $used_rate

tmp=${last_dynamic_average_used_memory}
echo tmp:${tmp}
if [ -z ${tmp} ];then
    echo "first time!!!"
    tmp=0
fi
current_dynamic_average_used_memory=$(echo "scale=1;0.7 * ${tmp} + 0.3 * ${used_rate}" | bc)
echo ${current_dynamic_average_used_memory}
last_dynamic_average_used_memory=${current_dynamic_average_used_memory}
echo ${last_dynamic_average_used_memory}
#export last_dynamic_average_used_memory