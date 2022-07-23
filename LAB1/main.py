from sklearn.neighbors import NearestNeighbors
import time

def createDataSet(nombre):
    data = open(nombre,"r")
    dataset = []
    for line in data:
        coordenadaX = line.split(" ",1)[0]
        coordenadaY = line.split(" ",1)[1].split('\n')[0]
        dataset.append([coordenadaX,coordenadaY])
    return dataset

#query = [2,2]
def findKNN(query,k,dataSet):
    result = NearestNeighbors(n_neighbors=k,algorithm="ball_tree").fit(dataSet)
    distances,indices = result.kneighbors([query])
    neighbors = []
    print(indices[0])
    for x in range(k):
        value = dataSet[indices[0][x]]
        neighbors.append(value)
    return(neighbors)

def takeTime(function):
        start = time.time()
        function_output = function()
        execution_time = time.time() - start
        return function_output, execution_time

DatasetA = createDataSet("dataSetA.txt")
DatasetB = createDataSet("dataSetB.txt")
DatasetC = createDataSet("dataSetC.txt")
findKNN([302,150],3,DatasetA)


# print(
#     "DatasetA",
#     takeTime(lambda:findKNN([302,150],1000,DatasetA))[1],
#     takeTime(lambda:findKNN([704,200],5000,DatasetA))[1],
#     takeTime(lambda:findKNN([106,629],10000,DatasetA))[1],
#     takeTime(lambda:findKNN([739,401],15000,DatasetA))[1]
# )

# print(
#     "DatasetB",
#     takeTime(lambda:findKNN([204,629],1000,DatasetB))[1],
#     takeTime(lambda:findKNN([589,358],5000,DatasetB))[1],
#     takeTime(lambda:findKNN([639,888],10000,DatasetB))[1],
#     takeTime(lambda:findKNN([529,440],15000,DatasetB))[1]
# )

# print(
#     "DatasetC",
#     takeTime(lambda:findKNN([200,294],1000,DatasetC))[1],
#     takeTime(lambda:findKNN([3,2],5000,DatasetC))[1],
#     takeTime(lambda:findKNN([110,382],10000,DatasetC))[1],
#     takeTime(lambda:findKNN([22,444],15000,DatasetC))[1]
# )  