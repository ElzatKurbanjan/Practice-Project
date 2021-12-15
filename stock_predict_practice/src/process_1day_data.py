import os

fin_data=open("../data/jhw.txt",'rb')

fout_data=open("../data/jhw_processed.txt",'wb')

line_data=fin_data.readline().decode('utf-8')

count=0
line_count_need_to_delete = 2
last_output_line = ""
while line_data:
    # 处理空行
    if(line_data == '\r\n'):
        line_data = fin_data.readline().decode('utf-8')
        continue

    # 前n行参考价值较小，处理前n行
    count += 1
    if (count <= line_count_need_to_delete):
        line_data = fin_data.readline().decode('utf-8')
        continue
    
    if (count % 10 == 0):
        print(count)

    # 先将本行的涨跌幅作为上一行的结果贴到上一行的最后，并写入文件
    words=line_data.split();
    output_line = last_output_line + words[5].strip("%") + '\r\n'
    fout_data.write(output_line.encode('utf-8'))

    # 处理本行的其他列
    last_output_line = ""
    for i in range(len(words)):
        if (i == 0 or i == 4 or i == 8):
            continue
        if (i == 5 or i == 6):
            words[i] = words[i].strip("%")
        last_output_line +=  words[i] + "\t\t\t"
    line_data = fin_data.readline().decode('utf-8')

# 此处为需要预测行的数据
print(last_output_line)

fin_data.close()
fout_data.close()

os.system("pause")