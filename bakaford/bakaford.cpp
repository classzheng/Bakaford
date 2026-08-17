/******************************************************************************
 * Bakaford/Bakaford: A Mechanical Theorem Prover based on Clifford Brackets. *
 * @Author: classzheng@github                                                 *
 * @Date: 2026.8.17 (latest upd)                                              *
 * @Reference: https://doi.org/10.1360/za2007-37-5-523                        *
 * @Modules: {  }                                                             *
 ******************************************************************************/
#include "bakaford.hpp"
int main(void) {
    Bakaford::Prover P;
    Bakaford::Point A,B,C,S,Ap,Bp,Cp,X,Y,Z;
    P.basepoint(A,"A").basepoint(B,"B").basepoint(C,"C").basepoint(S,"S")
     .collinear(Ap,"A^*",S,A).collinear(Bp,"B^*",S,B).collinear(Cp,"C^*",S,C)
     .intersection(X,"X",A,B,Ap,Bp)
     .intersection(Y,"Y",B,C,Bp,Cp)
     .intersection(Z,"Z",C,A,Cp,Ap)
     .qed(Bakaford::Polynomial(Bakaford::Bracket(X,Y,Z)));
    return 0;
}
