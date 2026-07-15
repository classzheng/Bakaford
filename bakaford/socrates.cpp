#include "hottreasoner.hpp"
int main(void) {
	using namespace Bakaford;
    Reasoner r;
    Element Human, Death, Socrates, human0, instance, abstraction;
    r.declare("Human",&Universe,CustomType,&Human)
     .declare("Death",&Universe,CustomType,&Death)
     .declare("Socrates",&Human,Constant,&Socrates)
     .declare("human0",&Human,Variable,&human0)
     .declare("@instance",&Death,Variable,&instance)
     .abst(human0,instance) .eq(abstraction)
     .appl(abstraction,Socrates)
     .qed();
    return 0;
}
