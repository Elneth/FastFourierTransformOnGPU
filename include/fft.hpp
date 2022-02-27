#ifndef FFT_H
#define FFT_H

#include <map>
#include <vector>
#include <cmath>

/*Inspiration soursces 
https://gist.github.com/lukicdarkoo/3f0d056e9244784f8b4a

*/

// FFT algorithm
void Cooley_Tukey_hat(std::vector<double> vec_in, std::vector<double>* vec_out, int n);
void Cooley_Tukey_rec(std::vector<double>* vec, int n);

#endif