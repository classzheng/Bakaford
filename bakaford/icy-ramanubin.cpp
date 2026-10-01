#include "icy-ramanubin.hpp"
using namespace Bakaford;
int main(){
    Ramanubin<realtype> rb;
    rb.allocate({M_PI, M_E, std::sqrt(M_PI), std::pow(M_PI, 9), 1.14514L});
    std::vector<realtype> coef=rb.run();
    realtype resd=rb.residual();
    for(auto& is:coef) std::cout << is << " ";
    std::cout << "with residual " << resd;
    return 0;
}
