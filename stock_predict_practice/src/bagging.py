def get_vote(str):
    '''
    ind_pre=str.find('previous')
    if(ind_pre!=-1):
        return 1;
    else:
        return 2
    '''
    return 1

def bagging(result_set_path):
    matrix=[]
    path=result_set_path[0]
    vote=get_vote(path)
    print(vote)
    fin = open(path, 'rb')
    line = fin.readline().decode().strip('\r\n')
    while line:
        vector = dict()
        num = vector.get(int(line), 0)
        vector.update({int(line): num + vote})
        matrix.append(vector)
        line = fin.readline().decode().strip('\r\n')
    fin.close()

    for findex in range (1,len(result_set_path)):
        fin = open(result_set_path[findex], 'rb')
        vote = get_vote(result_set_path[findex])
        print(vote)
        line = fin.readline().decode().strip('\r\n')
        count=0
        while line:
            vector = matrix[count]
            num = vector.get(int(line), 0)
            vector.update({int(line): num + vote})
            count+=1
            line = fin.readline().decode().strip('\r\n')
        fin.close()

    return matrix

pre_base_path='..\\..\\data\\previous_data\\'
o_base_path='..\\..\\data\\solution_KNN_Odistance\\solution'
cos_base_path='..\\..\\data\\solution_KNN_CosDistance\\solution'
svm_base_path='..\\..\\data\\solution_SVM\\solution'
output_base_path='..\\..\\data\\bagging\\solution_'
suffix='.txt'

path_set=[]
for i in range (1,11):
    path_set.append(svm_base_path + str(i) + suffix)
    path_set.append(cos_base_path + str(i) + suffix)
    path_set.append(o_base_path + str(i) + suffix)
    path_set.append(pre_base_path+'previous_KNN_CosDistance\\solution'+str(i)+suffix)
    path_set.append(pre_base_path + 'previous_KNN_Odistance\\solution' + str(i) + suffix)
    path_set.append(pre_base_path + 'previous_SVM\\solution' + str(i) + suffix)



vector_set = bagging(path_set)
vector_set_ordered=[]
for v in vector_set:
    vector=sorted(v.items(),key= lambda item:item[1],reverse=True)
    vector_set_ordered.append(vector)

fout=open(output_base_path+'mix_60'+suffix,'wb')
for vso in vector_set_ordered:
    tuple=vso[0]
    fout.write((str(tuple[0])+'\r\n').encode('utf-8'))
fout.close()