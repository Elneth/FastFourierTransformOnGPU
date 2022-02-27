// Demo of sending data via temporary files.  The default is to send data to gnuplot directly
// through stdin.
//
// Compile it with:
//   g++ -o example-tmpfile example-tmpfile.cc -lboost_iostreams -lboost_system -lboost_filesystem

#include <map>
#include <vector>
#include <cmath>

#include "gnuplot-iostream.h"

#include "../include/fft.hpp"

using namespace std;

typedef double (*R_fun)(double); //R_fun standds for Real function (f : R-> R)


void linspace(vector<double>* X, double x_min, double x_max, int n){
	for(double x= x_min; x < x_max; x+= (x_max-x_min)/n) {
		X->push_back(x);
	}
}

void create_vector_from_fun(vector<double> x,vector<double>* y, R_fun f,int n){
    for(int i= 0; i<n; i++) {
		y->push_back(f(x[i]));
	}
}

void create_point_vector_from_vecs(vector<pair<double, double>>* vec,vector<double> x, vector<double> y,int n){
    for(int i= 0; i<n; i++) {
		vec->push_back(make_pair(x[i], y[i]));
	}
}

int main() {
	Gnuplot gp;

    int n = 1024;

	vector<double> x;
	vector<double> y;
	vector<double> y_hat;

	vector<pair<double, double> > xy_pts;

	linspace(&x, -M_PI, M_PI, n);
	create_vector_from_fun(x,&y,&sin,n);
	create_point_vector_from_vecs(&xy_pts, x, y, n);

	Cooley_Tukey_hat(y, &y_hat, n);

	double min_x = *min_element(x.begin(),x.end());
	double max_x = *max_element(x.begin(),x.end());
	double min_y = *min_element(y.begin(),y.end());
	double max_y = *max_element(y.begin(),y.end());

	gp << "set xrange ["<<min_x<<":"<<max_x<<"]\nset yrange ["<<min_y<<":"<<max_y<<"]\n";
	// Data will be sent via a temporary file.  These are erased when you call
	// gp.clearTmpfiles() or when gp goes out of scope.  If you pass a filename
	// (e.g. "gp.file1d(pts, 'mydata.dat')"), then the named file will be created
	// and won't be deleted (this is useful when creating a script).
	gp << "plot" << gp.file1d(xy_pts) << "with lines title 'cubic'"<< endl;

}