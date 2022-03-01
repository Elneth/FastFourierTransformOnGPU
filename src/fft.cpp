#include "../include/fft.hpp"

void fft(std::vector<double> x_in,
	std::vector<std::complex<double>> *x_out,
	int N) {
	
	// Make copy of array and apply window
	
	for (int i = 0; i < N; i++) {
		x_out->push_back(std::complex<double>(x_in[i], 0));
	}

	// Start recursion
	fft_rec(x_out, N);
}

void fft_rec(std::vector<std::complex<double>> *x, int N) {
	// Check if it is splitted enough
	if (N <= 1) {
		return;
	}

	// Split even and odd
	std::vector<std::complex<double>> odd;
	std::vector<std::complex<double>> even;
	for (int i = 0; i < N / 2; i++) {
		even.push_back((*x)[i*2]);
		odd.push_back((*x)[i*2+1]);
	}

	// Split on tasks
	fft_rec(&even, N/2);
	fft_rec(&odd, N/2);


	// Calculate DFT
	for (int k = 0; k < N / 2; k++) {
		std::complex<double> t = exp(std::complex<double>(0, -2 * M_PI * k / N)) * odd[k];
		(*x)[k] = even[k] + t;
		(*x)[N / 2 + k] = even[k] - t;
	}
}
