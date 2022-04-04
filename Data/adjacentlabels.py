import pickle
import numpy

_,_,Label2Pixel,AdjacencyDict=pickle.load(open("data.bin","rb"))


print("label,[sorted adjacent labels]")
for i,element in enumerate(AdjacencyDict):
    if len(element)==0:
        print("{},".format(i))
        continue
    else:
        print(i,end=",")
        element=sorted(list(element))
        n=len(element)-1
        for j in range(n):
            print(element[j],end=",")
        print(element[n])
