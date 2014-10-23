import numpy as np
import matplotlib.pyplot as plt
import sys

data = np.loadtxt(open(str(sys.argv[1]),"rb"),delimiter=",",skiprows=1)
print data[1][:]

