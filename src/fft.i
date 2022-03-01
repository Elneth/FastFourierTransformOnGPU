%module fft
%{
#include "../include/fft.hpp"
%}
%include "std_vector.i"
%include "std_complex.i"
namespace std {

  /* On a side note, the names VecDouble and VecVecdouble can be changed, but the order of first the inner vector matters! */
  %template(VecDouble) vector<double>;
  %template(CompDouble) complex<double>;
  %template(VecCompdouble) vector< complex<double> >;
}

%include "../include/fft.hpp"