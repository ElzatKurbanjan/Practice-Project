for line in `cat test_data`;do
	echo expr: ${line}
	echo ${line} | ./a.out
	echo
	#echo expected: ${line} = $((${line}))
done
