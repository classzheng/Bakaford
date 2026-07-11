#include "hottreasoner.hpp"
using namespace Bakaford;
int main(void) {
    Reasoner r;
    Element A("A",&Universe,CustomType);
    Element B("B",&Universe,CustomType);
    Element x("x",&A,Variable);
    Element y("y",&B,Variable);
    Element c("c",&B,Constant);
    Element u("u",&A,Constant);
    
    r.intro(A)
     .intro(B)
     .intro(x)
     .intro(y)
     .intro(c)
     .intro(u)
     .abst(x,c)
     .appl(r.pool.back(),u)
     .make_pair(A,B)
     .currying(r(0))
     .emplace(r[0])
     .rec(r(1))
     .ind(r(2))
     .make_copair(x,y,true);
     
    for(auto& is:r.pool)
        std::cout << is.var << " : " << is.type->var <<"\n";
    for(auto& is:r.ref)
        std::cout << is.literal() <<"\n";
    return 0;
}
