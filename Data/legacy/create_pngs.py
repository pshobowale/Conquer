import pickle
import matplotlib.pyplot as plt
import numpy as np
import numpngw

Pixel2Label,BackgroundMask,Label2Pixel,AdjacencyDict=pickle.load(open("data.bin","rb"))

plt.show()

S=pickle.load(open("SegMap-24-01-2021_15_34_16.seg","rb"))
#Bosborus Hack
c=plt.imread("Nuts2.png")[:,1150:,:3]
print(c.shape)

#Remove Errors from Region Growing
c[np.where((c != (1,1,1)).all(axis=2))] = (0,0,0)
c[c[:,:,0]!=c[:,:,1]]=(0,0,0)
c[c[:,:,1]!=c[:,:,2]]=(0,0,0)
c=c[:,:,0]

S[c==1]=0

#plt.imshow(S)
#plt.show()

S=S[:Pixel2Label.shape[0],:Pixel2Label.shape[1]]>0
Pixel2Label[S==0]=0
Pixel2Label[Pixel2Label==129]=0#Russia Hack
S=np.dstack((S,S,S,S)).astype(float)
plt.imsave("Background.png",S,cmap="gray")


numpngw.write_png("Pixel2Label.png",Pixel2Label.astype(np.uint16))



borders=255*(plt.imread("map_borders.png")[:,:,0]==0)-(Pixel2Label==0)*255
borders=borders>0
borders=borders.astype(float)
borders=np.dstack((borders*0.1,borders*0.1,borders*0.1,borders))
#print(np.min(borders),np.max(borders))
#plt.imshow(borders>0,"gray")
#plt.show()
plt.imsave("Borders.png", borders,cmap="gray")


