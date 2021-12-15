import heapq

import numpy as np
from sklearn.decomposition import PCA
import datetime
from sklearn.metrics.pairwise import cosine_similarity

pca=PCA(n_components=100)

def mk_dataset(train_matrix_path,train_vector_path):
    fin = open(train_matrix_path,'rb')
    line=fin.readline().decode('utf-8').strip('\r\n').strip('[').strip(']')
    count=1;
    train_matrix=[]
    while line:
        line=line.split(',')
        vector=[]
        for ch in line:
            vector.append(int(ch))
        train_matrix.append(vector)
        if(count %5000 ==0):
            print(count)
        count=count+1
        line = fin.readline().decode('utf-8').strip('\r\n').strip('[').strip(']')

    fin = open (train_vector_path,'rb')
    line=fin.readline().decode('utf-8').strip('\r\n')
    train_vector=[]
    while line:
        train_vector.append(int(line))
        line = fin.readline().decode('utf-8').strip('\r\n')
    fin.close()

    print('训练集特征矩阵行数：' ,train_matrix.__len__())
    print('训练集标签维数：',train_vector.__len__())

    st=datetime.datetime.now()
    print('训练集pca开始',st)
    train_matrix=pca.fit_transform(train_matrix)
    et=datetime.datetime.now()
    print('训练集pca结束',et,'time cost: ',(et-st).seconds)

    print('pca后训练集每个向量维度', len(train_matrix[0]))
    print('pca后训练集总长度', len(train_matrix))

    train_matrix=np.array(train_matrix)
    train_vector=np.array(train_vector)
    return train_matrix,train_vector


def mk_testset(test_matrix_path,start,end):
    fin = open(test_matrix_path, 'rb')
    line = fin.readline().decode('utf-8').strip('\r\n').strip('[').strip(']')
    count = 0;
    test_matrix = []
    while line:
        if (count>=start and count<end):
            line=line.split(',')
            vector = []
            for ch in line:
                vector.append(int(ch))
            test_matrix.append(vector)
        count = count + 1
        line = fin.readline().decode('utf-8').strip('\r\n').strip('[').strip(']')
    fin.close()

    st = datetime.datetime.now()
    print('测试集pca开始', st)
    test_matrix=pca.transform(test_matrix)
    et = datetime.datetime.now()
    print('测试集pca结束', et, 'time cost: ', (et - st).seconds)

    print('pca后测试集每个向量维度',len(test_matrix[0]))
    print('pca后测试集总长度',len(test_matrix))

    test_matrix=np.array(test_matrix)
    return test_matrix


def cos_knn(k, test_data,  stored_data, stored_target):
    # 找到test_data中每个点与stored_data中每个其他点之间的余弦相似度。
    cosim = cosine_similarity(test_data, stored_data)

    # 获取stored_data中与任何给定test_data点最相似的图像的前k个索引。
    top = [(heapq.nlargest((k), range(len(i)), i.take)) for i in cosim]

    # 使用存储的目标值将索引转换为具体值。
    top = [[stored_target[j] for j in i[:k]] for i in top]

    # 投票，并返回test_data中每个图像的预测
    pred = [max(set(i), key=i.count) for i in top]

    return pred





block_index=1
suffix='.txt'

train_x,train_y=mk_dataset('..\\..\\data\\occurancy_matrix\\Matrix'+str(block_index)+suffix ,'..\\..\\data\\blocks_solution\\solution' + str(block_index)+suffix )


for i in range(0,200):
    test_data=mk_testset('..\\..\\data\\occurancy_matrix_test\\Matrix' + str(block_index)+suffix ,i*1000,(i+1)*1000)

    st=datetime.datetime.now()
    print('第',i,'部分开始预测：',st)
    y_pred = cos_knn(5,test_data,train_x,train_y)
    et=datetime.datetime.now()
    print( '第',i,'部分预测结束：',et,'time cost :',(et-st).seconds)

    if(i==0):
        f_result_out = open('..\\..\\data\\solution_KNN_CosDistance\\solution' + str(block_index) + suffix , 'wb')
    else:
        f_result_out = open('..\\..\\data\\solution_KNN_CosDistance\\solution' + str(block_index) + suffix , 'ab')

    for r in y_pred:
        f_result_out.write((str(r)+'\r\n').encode('utf-8'))
    f_result_out.close()
