import pickle
import matplotlib.pyplot as plt
import numpy as np

Pixel2Label,BackgroundMask,Label2Pixel,AdjacencyDict=pickle.load(open("data.bin","rb"))#

#plt.imshow(Pixel2Label>0)
#plt.show()
plt.imsave("Background.png",Pixel2Label>0,cmap="gray")

borders=255*(plt.imread("map_borders.png")[:,:,0]==0)-(Pixel2Label==0)*255
print(np.min(borders),np.max(borders))
plt.imshow(borders>0,"gray")
plt.show()
plt.imsave("Borders.png", borders>0,cmap="gray")


