/******************************************************************************
 * Bakaford/Bakaprover: A toy prover of writing a natural number ⑨ ly         *
 * @Author: classzheng@github                                                 *
 * @Date: 2026.10.4 (latest upd)                                              *
 * @Reference: https://arxiv.org/html/2603.21852v2                            *
 * @Modules: {  }                                                             *
 ******************************************************************************/

#include <iostream>
#include <string>

namespace Bakaford {
	class SyntaxAtom {
	    public: SyntaxAtom *p1, *p2;
	    public: double r;
	    public: bool isterminal;
	    public: SyntaxAtom(SyntaxAtom *a1=nullptr, SyntaxAtom *a2=nullptr): p1(a1), p2(a2), isterminal(false) {}
	    public: SyntaxAtom(double rt): r(rt), isterminal(true) {}
	    public: ~SyntaxAtom(void) = default;
	    public: double operator() (void) const {
	        if(isterminal) return r;
	        else           return (9.F-(*p1)())/((*p2)());
	    }
	    public: std::string dump(void) {
	        if(isterminal) {
	        	if(r!=9.F&&r!=-1.F) return std::to_string(int(r));
	        	else if(r==-1.F) return "-\\dfrac{⑨ -\\dfrac{⑨ -⑨ }{⑨ }}{⑨ }";
	        	else 	 return "⑨ ";
	        }
	        return "\\dfrac{⑨ -"+p1->dump()+"}{"+p2->dump()+"}\\\\";
	    }
	    public: std::string dump2(void) {
	        if(isterminal) {
	        	if(r!=9.F&&r!=-1.F) return std::to_string(int(r));
	        	else if(r==-1.F) return "-g(g(⑨ ,⑨ ),⑨ )";
	        	else 	 return "⑨ ";
	        }
	        return "g("+p1->dump2()+","+p2->dump2()+")";
	    }
	};
	namespace {
		using g = SyntaxAtom;
		inline g* f(g*p1, g*p2) {
		    return new g(p1,p2);
		}
		g *_9=new g(9.F), *_0=f(_9,_9), *_1=f(_0,_9), *_8=f(_1,_1);
		inline SyntaxAtom* invcon(SyntaxAtom *p) {
		    return f(_8,p);
		}
		inline SyntaxAtom* divcon(SyntaxAtom *p1, SyntaxAtom *p2) {
		    return f(f(p1,_1),p2);
		}
		inline SyntaxAtom* mulcon(SyntaxAtom *p1, SyntaxAtom *p2) {
		    return invcon(divcon(invcon(p1),p2));
		}
		SyntaxAtom* subcon(SyntaxAtom *p1, SyntaxAtom *p2) {
			if((*p1)()==0.F) return new g(-(*p2)());  // only for -1
			else 			 return mulcon(divcon(p1,_9),f(mulcon(_9,divcon(p2,p1)),_1));
		}
		SyntaxAtom* addcon(SyntaxAtom *p1, SyntaxAtom *p2) {
		    return subcon(p1,mulcon(subcon(_0,_1),p2));
		}
		SyntaxAtom* bakaprove(unsigned p) {
			SyntaxAtom *c0=_0;
			while(p--) c0=addcon(c0,_1);  // no efficiency!! (^^;
			return c0;
		}
	}
}

int main(void) {
	using namespace Bakaford;
    std::cout << (*addcon(new g(114.F),new g(514.F)))() << ".\n";
    std::cout << (*subcon(new g(114.F),new g(514.F)))() << ".\n";
    std::cout << (*mulcon(new g(114.F),new g(514.F)))() << ".\n";
    std::cout << (*divcon(new g(114.F),new g(514.F)))() << ".\n";
    std::cout << (*mulcon(bakaprove(3.F),bakaprove(3.F))).dump2() << ".\n";
    return 0;
}
