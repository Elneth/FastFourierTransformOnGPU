#include "../include/fft.hpp"

using namespace std;

void fft(vector<double> x_in,
	vector<complex<double>> *x_out,
	int N) {
	
	// Make copy of array and apply window
	
	for (int i = 0; i < N; i++) {
		x_out->push_back(complex<double>(x_in[i], 0));
	}

	// Start recursion
	fft_rec(x_out, N);
}

void fft_rec(vector<complex<double>> *x, int N) {
	// Check if it is splitted enough
	if (N <= 1) {
		return;
	}

	// Split even and odd
	vector<complex<double>> odd;
	vector<complex<double>> even;
	for (int i = 0; i < N / 2; i++) {
		even.push_back((*x)[i*2]);
		odd.push_back((*x)[i*2+1]);
	}

	// Split on tasks
	fft_rec(&even, N/2);
	fft_rec(&odd, N/2);


	// Calculate DFT
	for (int k = 0; k < N / 2; k++) {
		complex<double> t = exp(complex<double>(0, -2 * M_PI * k / N)) * odd[k];
		(*x)[k] = even[k] + t;
		(*x)[N / 2 + k] = even[k] - t;
	}
}
