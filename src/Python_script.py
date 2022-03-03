import fft
import time
import numpy as np

N = 4092
x = np.linspace(-np.pi,np.pi,N)
x_cpp =fft.VecDouble(x)
y =fft.VecCompdouble()

tic = time.perf_counter()
fft.fft(x_cpp,y,N)
toc = time.perf_counter()
print("took",toc - tic,"seconds")