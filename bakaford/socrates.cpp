#include "hottreasoner.hpp"
using namespace Bakaford;
int main(void) {
    Reasoner r;
    Element 
    	Human("Human",&Universe,CustomType),
    	Death("Death",&Universe,CustomType),
    	Socrates("Socrates",&Human,Constant),
    	human0("human0",&Human,Variable),
    	instance("@instance",&Death,Variable);
    r.intro(Human)
     .intro(Death)
     .intro(Socrates)
     .intro(instance)
     .abst(human0,instance)
     .appl(r(0),Socrates)
     .emplace(r[0]);
    for(auto& is:r.pool)
        std::cout << is.var << " : " << is.type->var <<"\n";
    for(auto& is:r.ref)
        std::cout << is.literal() <<"\n";
    return 0;
}
