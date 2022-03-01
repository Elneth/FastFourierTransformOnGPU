#ifndef FFT_H
#define FFT_H

#include <vector>
#include <complex>

/*Inspiration soursces 
https://gist.github.com/lukicdarkoo/3f0d056e9244784f8b4a

*/

// FFT algorithm
void fft(std::vector<double> x_in,
	std::vector<std::complex<double>> *x_out,
	int N);
void fft_rec(std::vector<std::complex<double>> *x, int N);

#endif
