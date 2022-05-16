import pickle
import matplotlib.pyplot as plt
import numpy as np

Pixel2Label,BackgroundMask,Label2Pixel,AdjacencyDict=pickle.load(open("data.bin","rb"))#
S=pickle.load(open("SegMap-24-01-2021_15_34_16.seg","rb"))
#Bosborus Hack
S[S==63]=0
#plt.imshow(S)
#plt.show()
S=S[:Pixel2Label.shape[0],:Pixel2Label.shape[1]]>0
S=np.dstack((S,S,S,S)).astype(float)

plt.imsave("Background.png",S,cmap="gray")

Pixel2Label[Pixel2Label==63]=0
borders=255*(plt.imread("map_borders.png")[:,:,0]==0)-(Pixel2Label==0)*255
borders=borders>0
borders=borders.astype(float)
borders=np.dstack((borders*0.1,borders*0.1,borders*0.1,borders))
#print(np.min(borders),np.max(borders))
#plt.imshow(borders>0,"gray")
#plt.show()
plt.imsave("Borders.png", borders,cmap="gray")


