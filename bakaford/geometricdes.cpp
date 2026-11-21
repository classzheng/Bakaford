#include "geometricdes.hpp"
#include <iostream>
#include <iomanip>

int main(void) {
	using namespace Bakaford;
    Circle<realtype> circle(Point<realtype>(0.L,0.L),Point<realtype>(1.L,0.L));
    Point<realtype> a=circle.semifreepoint();
    Point<realtype> b=circle.semifreepoint();
    Point<realtype> c=circle.semifreepoint();
    Point<realtype> p=circle.semifreepoint();

    Point<realtype> x=p.foot(Line<realtype>(a,b));
    Point<realtype> y=p.foot(Line<realtype>(c,b));
    Point<realtype> z=p.foot(Line<realtype>(a,c));

    std::complex<realtype> u=y.data-x.data, v=z.data-x.data;
    realtype error=u.real()*v.imag()-u.imag()*v.real();

    std::cout << std::setprecision(12)
              << "Simson line feet:\n"
              << x.data << '\n' << y.data << '\n' << z.data << '\n'
              << "Collinearity error: " << error << '\n';
	return 0;
}
