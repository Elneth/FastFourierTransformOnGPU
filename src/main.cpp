// Demo of sending data via temporary files.  The default is to send data to gnuplot directly
// through stdin.
//
// Compile it with:
//   g++ -o example-tmpfile example-tmpfile.cc -lboost_iostreams -lboost_system -lboost_filesystem

#include <complex>
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

void create_point_vector_from_vecs_bis(vector<pair<double, double>>* vec,vector<double> x, vector<double> y,int n){
	for(int i= 0; i<n; i++) {
		if (i<n/2)
		{
			vec->push_back(make_pair(x[i], y[n/2+i]));
		} else {
			vec->push_back(make_pair(x[i], y[i-n/2]));
		}
	}
}

double test_fun(double x){
	return sin(2*x*M_PI)+sin(4*M_PI*x);
}

double test_fun_2(double x) {
	if (abs(x)<0.5) {
		return 1;
	} else {
		return 0;
	}
}

double test_fun_3(double x) {
	return sin(2*M_PI*x*x);
}

int main() {
	Gnuplot gp;

	int n = 256;

	vector<double> x;
	vector<double> y;
	vector<complex<double>> y_hat;

	vector<pair<double, double> > xy_pts;

	linspace(&x, -M_PI, M_PI, n);
	create_vector_from_fun(x,&y,&test_fun_3,n);
	create_point_vector_from_vecs(&xy_pts, x, y, n);

	fft(y, &y_hat, n);

	vector<double> y_hat_abs;
	for (int i=0;i<n;i++) {
		y_hat_abs.push_back(abs(y_hat[i]));
	}

	vector<pair<double, double>> xy_fft;
	vector<double> x_fft;
	linspace(&x_fft, -n/2.0, n/2.0, n);

	create_point_vector_from_vecs_bis(&xy_fft, x_fft, y_hat_abs, n);

	/*double min_x = *min_element(x.begin(),x.end());
	double max_x = *max_element(x.begin(),x.end());
	double min_y = *min_element(y.begin(),y.end());
	double max_y = *max_element(y.begin(),y.end());*/

	gp << "set xrange ["<<-n/2<<":"<<n/2<<"]\nset yrange ["<<-1<<":"<<n<<"]\n";
	//gp << "set xrange ["<<min_x<<":"<<max_x<<"]\nset yrange ["<<min_y<<":"<<max_y<<"]\n";
	// Data will be sent via a temporary file.  These are erased when you call
	// gp.clearTmpfiles() or when gp goes out of scope.  If you pass a filename
	// (e.g. "gp.file1d(pts, 'mydata.dat')"), then the named file will be created
	// and won't be deleted (this is useful when creating a script).
	gp << "plot" << gp.file1d(xy_pts) << "with lines title 'sine'"<< ",";

	//gp << "set xrange ["<<-n/2<<":"<<n/2<<"]\nset yrange ["<<-1<<":"<<n<<"]\n";

	gp << gp.file1d(xy_fft) << "with points title 'fft'" << endl;

}