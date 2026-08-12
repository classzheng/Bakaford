// bakaford.cpp
#include "bakaford.hpp"
using namespace Bakaford;
int main(){
    Prover P;
    Point A,B,C,S,Ap,Bp,Cp,X,Y,Z;
    P.basepoint(A,"A").basepoint(B,"B").basepoint(C,"C").basepoint(S,"S")
     .collinear(Ap,"A^*",S,A).collinear(Bp,"B^*",S,B).collinear(Cp,"C^*",S,C)
     .intersection(X,"X",A,B,Ap,Bp)
     .intersection(Y,"Y",B,C,Bp,Cp)
     .intersection(Z,"Z",C,A,Cp,Ap)
     .qed();
    std::cout<<Point::bradump(X,Y,Z)<<"&="<<Point::bracket(X,Y,Z)<<".\\\\\n";
    return 0;
}
