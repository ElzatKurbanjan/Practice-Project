import numpy as np
from sklearn.decomposition import PCA
import datetime
from sklearn.neighbors import KNeighborsClassifier

print("a")

# pca=PCA(n_components=100)

# def mk_dataset(train_matrix_path,train_vector_path):
#     fin = open(train_matrix_path,'rb')
#     line=fin.readline().decode('utf-8').strip('\r\n').strip('[').strip(']')
#     count=1;
#     train_matrix=[]
#     while line:
#         line=line.split(',')
#         vector=[]
#         for ch in line:
#             vector.append(int(ch))
#         train_matrix.append(vector)
#         if(count %5000 ==0):
#             print(count)
#         count=count+1
#         line = fin.readline().decode('utf-8').strip('\r\n').strip('[').strip(']')

#     fin = open (train_vector_path,'rb')
#     line=fin.readline().decode('utf-8').strip('\r\n')
#     train_vector=[]
#     while line:
#         train_vector.append(int(line))
#         line = fin.readline().decode('utf-8').strip('\r\n')
#     fin.close()

#     print('训练集特征矩阵行数：' ,train_matrix.__len__())
#     print('训练集标签维数：',train_vector.__len__())

#     st=datetime.datetime.now()
#     print('训练集pca开始',st)
#     train_matrix=pca.fit_transform(train_matrix)
#     et=datetime.datetime.now()
#     print('训练集pca结束',et,'time cost: ',(et-st).seconds)

#     print('pca后训练集每个向量维度', len(train_matrix[0]))
#     print('pca后训练集总长度', len(train_matrix))

#     train_matrix=np.array(train_matrix)
#     train_vector=np.array(train_vector)
#     return train_matrix,train_vector


# def mk_testset(test_matrix_path):
#     fin = open(test_matrix_path, 'rb')
#     line = fin.readline().decode('utf-8').strip('\r\n').strip('[').strip(']')
#     count = 1;
#     test_matrix = []
#     while line:
#         line=line.split(',')
#         vector = []
#         for ch in line:
#             vector.append(int(ch))
#         test_matrix.append(vector)
#         if (count % 5000 == 0):
#             print(count)
#         count = count + 1
#         line = fin.readline().decode('utf-8').strip('\r\n').strip('[').strip(']')
#     fin.close()

#     st = datetime.datetime.now()
#     print('测试集pca开始', st)
#     test_matrix=pca.transform(test_matrix)
#     et = datetime.datetime.now()
#     print('测试集pca结束', et, 'time cost: ', (et - st).seconds)

#     print('pca后测试集每个向量维度',len(test_matrix[0]))
#     print('pca后测试集总长度',len(test_matrix))

#     test_matrix=np.array(test_matrix)
#     return test_matrix

# block_index=1
# suffix='.txt'

# train_x,train_y=mk_dataset('..\\..\\data\\occurancy_matrix\\Matrix'+str(block_index)+suffix ,'..\\..\\data\\blocks_solution\\solution' + str(block_index)+suffix )

# st=datetime.datetime.now()
# print('开始训练 ','start time:',st)

# knn = KNeighborsClassifier()
# knn.fit(train_x, train_y)

# et=datetime.datetime.now()
# print('训练结束',' end time:' ,et,' time cost:',(et-st).seconds)


# test_data=mk_testset('..\\..\\data\\occurancy_matrix_test\\Matrix' + str(block_index)+suffix )
# st=datetime.datetime.now()
# print('开始预测',st)
# y_pred = knn.predict(test_data)
# et=datetime.datetime.now()
# print('预测结束',et,'time cost :',(et-st).seconds)

# f_result_out= open('..\\..\\data\\solution_KNN_Odistance\\solution' + str(block_index)+suffix , 'wb')
# for r in y_pred:
#     f_result_out.write((str(r)+'\r\n').encode('utf-8'))
# f_result_out.close()
