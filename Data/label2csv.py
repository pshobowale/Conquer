import pickle

Pixel2Label,BackgroundMask,Label2Pixel,AdjacencyDict=pickle.load(open("data.bin","rb"))


print("label,x0,y0,dx,dy")
for i,element in enumerate(Label2Pixel[:]):
    if len(element)==0:
        print("{},,,,,".format(i))
        continue
    else:
        mask,(x0,y0)=element[0]
        print("{},{},{},{},{}".format(i,x0,y0,mask.shape[0],mask.shape[1]))

