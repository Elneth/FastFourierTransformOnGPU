#include "../include/fft.hpp"

using namespace std;

void Cooley_Tukey_hat(vector<double> vec_in, vector<double>* vec_out, int n){
    for (int i = 0; i < n; i++) {
		vec_out->push_back(vec_in[i]);
	}
    Cooley_Tukey_rec(vec_out,n);
}

void Cooley_Tukey_rec(vector<double>* vec, int n){
    if (n <= 1){
        return;
    }
    //odds and even (size n/2)
    vector<double> vec_even;
    vector<double> vec_odd;

    //filling even and odd
    for (int i=0;i<n/2;i++){
        vec_even.push_back( (*vec)[2*i] );
        vec_odd.push_back( (*vec)[2*i+1] );
    }
}