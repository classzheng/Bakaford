#include <iostream>
#include <iomanip>
#include "bakaford.hpp"
using namespace Bakaford;

int main() {
    std::cout<<std::fixed<<std::setprecision(9);
    coord A(dist(rng), dist(rng));
    coord B(dist(rng), dist(rng));
    coord C(dist(rng), dist(rng));
    coord S(dist(rng), dist(rng));
    coord A1 = S + (A - S) * 1.37L;
    coord B1 = S + (B - S) * 0.78L;
    coord C1 = S + (C - S) * 1.21L;
    coord P,Q,R;
    Prover prover;
    prover
	    .basepoints(A,B,C)
	    .intersection(P, A, B, A1, B1)
	    .intersection(Q, B, C, B1, C1)
	    .intersection(R, C, A, C1, A1)
	    .declare(A,"A")
	    .declare(B,"B")
	    .declare(C,"C")
	    .declare(S,"S")
	    .declare(A1,"A_1")
	    .declare(B1,"B_1")
	    .declare(C1,"C_1")
	    .declare(P,"P")
	    .declare(Q,"Q")
	    .declare(R,"R");
    std::cout<<"A = "<<A<<"\nB = "<<B<<"\nC = "<<C<<"\nS = "<<S<<"\n\n";
    std::cout<<"A' = "<<A1<<"\nB' = "<<B1<<"\nC' = "<<C1<<"\n\n";
    std::cout<<"P = "<<P<<"\nQ = "<<Q<<"\nR = "<<R<<"\n\n";
    long double val = Prover::bracket(P,Q,R);
    std::cout<<"Bracket [P Q R] = "<<val<<"\n\n";
    prover.prove(P,Q,R);
    return 0;
}
