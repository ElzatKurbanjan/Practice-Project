for line in `cat test_data`;do
	echo ${line} | ./a.out
	echo expected: ${line} = $((${line}))
done
