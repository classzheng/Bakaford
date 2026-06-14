/******************************************************************************
 * Bakaford/Bakaford: A Mechanical Theorem Prover based on Clifford Brackets. *
 * @Author: classzheng@github                                                 *
 * @Date: 2026.5.16 (latest upd)                                              *
 * @Reference: https://doi.org/10.1360/za2007-37-5-523                        *
 * @Modules: {}                                                               *
 ******************************************************************************/


#include <vector>
#include <random>
#include <string>
#include <sstream>

// #pragma once
#pragma GCC optimize (2)

namespace Bakaford {
	std::random_device rd;
	std::mt19937 rng(rd());
	
	template<class _Type=void> class CliffordBracket {
		public: unsigned arg[3];
		public: signed invflag;  // [ABC]^(invflag)
		public: CliffordBracket(void) = default;
		public: CliffordBracket(unsigned a, unsigned b, unsigned c): arg({a,b,c}) {}
		public: ~CliffordBracket(void) = default;
		public: CliffordBracket Invert(void) {  // [A,B,C]=-[B,A,C], etc.
			return CliffordBracket(arg[1],arg[0],arg[2]);
		}
		public: std::vector<std::vector<CliffordBracket<>>> expand(const CliffordBracket<> &resp) {
		  // [X,Y,Z] = [X,B,C][Y,Z,A]/[A,B,C] + [X,C,A][Y,Z,B]/[A,B,C] + [X,A,B][Y,Z,C]/[A,B,C].
		    std::vector<std::vector<CliffordBracket<>>> res;
		    unsigned X = arg[0], Y = arg[1], Z = arg[2];
		    unsigned A = resp.arg[0], B = resp.arg[1], C = resp.arg[2];
		    CliffordBracket<> t0(A, B, C); t0.invflag = 1;

		    // Term 1: [X,B,C] [Y,Z,A] [A,B,C]^(-1)
			{
			    CliffordBracket<> t1(X, B, C); t1.invflag = 0;
			    CliffordBracket<> t2(Y, Z, A); t2.invflag = 0;
			    res.push_back({ t1, t2, t0 });
			}
			
		    // Term 2: [X,C,A] [Y,Z,B] [A,B,C]^(-1)
		    {
			    CliffordBracket<> t3(X, C, A); t3.invflag = 0;
			    CliffordBracket<> t4(Y, Z, B); t4.invflag = 0;
			    res.push_back({ t3, t4, t0 });
			}
			
		    // Term 3: [X,A,B] [Y,Z,C] [A,B,C]^(-1)
		    {
			    CliffordBracket<> t5(X, A, B); t5.invflag = 0;
			    CliffordBracket<> t6(Y, Z, C); t6.invflag = 0;
			    res.push_back({ t5, t6, t0 });
			}
		    return res;
		}
		public: std::string dump(void) {
			std::stringstream ss((invflag)?"^(-1)":"");
			ss << "[" << arg[0] << "," << arg[1] << "," << arg[2] << "]";
			return ss.str();
		}
		public: inline bool occurs(unsigned v) const {
			return arg[0]==v || arg[1]==v || arg[2]==v;
		}
	};
	
	template<class _Type=void> class CliffordProduct {
		public: std::vector<CliffordBracket<>> factors;  // p := Π[v1,v2,v3].
		public: CliffordProduct(void) = default;
		public: CliffordProduct(const std::vector<CliffordBracket<>> init): factors(std::move(init)) {}
		public: ~CliffordProduct(void) = default;
		public: std::string dump(void) {
			std::stringstream ss("");
			for(auto& is:factors) {
				ss << is.dump();
			}
			return ss.str();
		}
		public: std::vector<CliffordProduct<>> passexpansion(unsigned v, const CliffordBracket<>& resp) {
			for(auto& is:factors) {
				if(is.occurs(v)) {
					std::vector<std::vector<CliffordBracket<>>> fac=is.expand(resp);
					std::vector<CliffordProduct<>> list;
					for(auto& si:fac) {
						list.push_back(si);
					}
					return list;
				}
			}
			return std::vector<CliffordProduct<>>();
		}
	};
	
	template<class _Type=void> class CliffordPolynomial {
		public: std::vector<CliffordBracket<>> factors;  // p := Σ Π[v1,v2,v3].
		public: CliffordPolynomial(void) = default;
		public: CliffordPolynomial(const std::vector<CliffordBracket<>> init): factors(std::move(init)) {}
		public: ~CliffordPolynomial(void) = default;
		public: std::string dump(void) {
			std::stringstream ss("");
			for(auto& is:factors) {
				ss << is.dump() << "+";
			}
			return ss.str()+";;";
		}
		public: void expand(unsigned v, const CliffordBracket<>& basepoints) {
		    std::vector<std::vector<CliffordBracket<>>> terms(1);
		    for (auto &br : factors) {
		        if (br.occurs(v)) {
		            auto fac = br.expand(basepoints);
		            std::vector<std::vector<CliffordBracket<>>> nt;
		            for (auto &t : terms) {
		                for (auto &f : fac) {
		                    std::vector<CliffordBracket<>> tmp = t;
		                    tmp.insert(tmp.end(), f.begin(), f.end());
		                    nt.push_back(std::move(tmp));
		                }
		            }
		            terms.swap(nt);
		        } else {
		            for (auto &t : terms) t.push_back(br);
		        }
		    }
		    std::vector<CliffordBracket<>> res;
		    for (auto &t : terms) {
		        for (auto &b : t) res.push_back(b);
		    }
		    factors.swap(res);
		    return ;
		}
	};
	
	template<class _Type=void> class Conclusion {
		public: CliffordProduct<> conc;  // conc=0 means it has proved.
		public: Conclusion(void) = default;
		public: ~Conclusion(void) = default;
		public: void eliminate1(unsigned v) {
			;
			return ;
		}
	};
}
