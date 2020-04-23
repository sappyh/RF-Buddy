import numpy as np
from matplotlib import pyplot as plt

a=np.fromfile('capture', dtype=np.complex64)
plt.plot(a)
plt.show()