// Demo of sending data via temporary files.  The default is to send data to gnuplot directly
// through stdin.
//
// Compile it with:
//   g++ -o example-tmpfile example-tmpfile.cc -lboost_iostreams -lboost_system -lboost_filesystem

#include <map>
#include <vector>
#include <cmath>

#include "gnuplot-iostream.h"

using namespace std;

typedef double (*R_fun)(double); //R_fun standds for Real function (f : R-> R)

void circle(vector<pair<double, double>>* xy_pts){
    for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
		double theta = alpha*2.0*3.14159;
		xy_pts->push_back(make_pair(cos(theta), sin(theta)));
	}
}

void create_point_vector(vector<pair<double, double>>* vec, R_fun f,int n, double x_min, double x_max){
    for(double x= x_min; x<x_max; x+=(x_max-x_min)/(float)n) {
		double y = f(x);
		vec->push_back(make_pair(x, y));
	}
}

int main() {
	Gnuplot gp;

    int n = 1024;

	vector<pair<double, double> > xy_pts_sin;
	create_point_vector(&xy_pts_sin,&sin,n,-M_PI,M_PI);

	gp << "set xrange [-4:4]\nset yrange [-1:1]\n";
	// Data will be sent via a temporary file.  These are erased when you call
	// gp.clearTmpfiles() or when gp goes out of scope.  If you pass a filename
	// (e.g. "gp.file1d(pts, 'mydata.dat')"), then the named file will be created
	// and won't be deleted (this is useful when creating a script).
	gp << "plot" << gp.file1d(xy_pts_sin) << "with lines title 'cubic'"<< endl;

}