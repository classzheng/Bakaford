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
     .appl(r.pool[3],u);
     
    Element cart = Handle::constructproduct(A,B);
    r.currying(cart)
     .emplace(r.ref.back())
     .make_pair(x,y);
     
    Element pair = r.pool.back();
    r.rec(pair)
     .ind(pair)
     .make_copair(x,y,true);
     
    for(auto& is:r.pool)
        std::cout << is.var << " : " << is.type->var <<"\n";
    return 0;
}
