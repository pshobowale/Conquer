import matplotlib.pyplot as plt
import numpy as np


country=plt.imread("mapchart/countrys_nuts2.png")[:,:,:3]
nuts2=plt.imread("mapchart/nuts2.png")[:,:,:3]
nuts3=plt.imread("mapchart/nuts3.png")[:,:,:3]

print(country.shape)
plt.imshow(country)
plt.show()