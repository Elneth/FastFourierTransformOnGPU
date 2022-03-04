# FastFourierTransformOnGPU
Exploring ways to parallelize the fft

Dependencies :

If gnuplot-iostream is not installed :
> sudo apt-get install libgnuplot-iostream-dev


Compiling and running the cpp code :
in src :
> make run

Using SWIG to generate a python library (to be used in wavelet project)
in src:
> g++ -c -fPIC fft.cpp
> swig -c++ -python fft.i
> g++ -c -fPIC fft_wrap.cxx  path/to/python3.x 	 usually : -I/usr/include/python3.8
> g++ -shared -Wl,-soname,_fft.so -o _fft.so fft.o fft_wrap.o
> python3 Python_script.py

