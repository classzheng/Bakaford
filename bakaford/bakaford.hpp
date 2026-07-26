/******************************************************************************
 * Bakaford/Bakaford: A Mechanical Theorem Prover based on Clifford Brackets. *
 * @Author: classzheng@github                                                 *
 * @Date: 2026.6.28 (latest upd)                                              *
 * @Reference: https://doi.org/10.1360/za2007-37-5-523                        *
 * @Modules: {}                                                               *
 ******************************************************************************/


#include <vector>
#include <valarray>
#include <random>
#include <string>
#include <iostream>
#include <sstream>
#include <complex>

// #pragma once
#pragma GCC optimize (2)

namespace Bakaford {

	using contype = enum {
		_basepoint, _conlinear, _centroid, _concyclic, _midpoint, _intersection, _projection
	};
	using realtype = long double;
	using coord = std::complex<realtype>;
	
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<realtype> dist(-1.L,1.L);
	realtype eps=1e-5;

	template<typename _t1, typename _t2> class TrivialMap {
		public: std::vector<_t1> key;
		public: std::vector<_t2> val;
		public: TrivialMap(void) = default;
		public: ~TrivialMap(void) = default;
		public: _t2& operator[] (const _t1 &t) {
			for(int i = 0; i < key.size(); i++) {
				if(key[i]==t) return val[i];
			}
			key.push_back(t);
			val.push_back(_t2());
			return val.back();
		}
	};
	
	class Construction {
	
		public: contype handle=_basepoint;
		public: coord targetpoint;
		public: std::vector<coord> basepoints;
		
		public: Construction(void) = default;
		// public: Construction(const contype &c, coord &p0, coord pz[]): handle(c), targetpoint(p0), basepoints(pz) {}
		public: Construction(const contype &c, coord &p0, std::vector<coord> pz): handle(c), basepoints(pz) {
			switch((int) handle) {
				case (_basepoint): {
					targetpoint = pz[0] + pz[1] + pz[2];  // Identity vector.
					break;
				}
				
				case (_conlinear): {  // with 2 basepoints
					targetpoint = basepoints[0] + (basepoints[1] - basepoints[0]) * dist(rng);
					break;
				}
				
				case (_centroid): {  // with 3 basepoints
					targetpoint = (basepoints[0] + basepoints[1] + basepoints[2]) / 3.L;
					break;
				}
				
				case (_concyclic): {  // with 3 basepoints
					realtype x1 = basepoints[0].real(), y1 = basepoints[0].imag();
					realtype x2 = basepoints[1].real(), y2 = basepoints[1].imag();
					realtype x3 = basepoints[2].real(), y3 = basepoints[2].imag();
					coord circularcen;
					realtype d = 2.L * ( x1*(y2 - y3) + x2*(y3 - y1) + x3*(y1 - y2) );
					if (d == 0.L) {
						circularcen = (basepoints[0] + basepoints[1] + basepoints[2]) / 3.L;
					} else {
						realtype s1 = x1*x1 + y1*y1;
						realtype s2 = x2*x2 + y2*y2;
						realtype s3 = x3*x3 + y3*y3;
						realtype ux = ( s1*(y2 - y3) + s2*(y3 - y1) + s3*(y1 - y2) ) / d;
						realtype uy = ( s1*(x3 - x2) + s2*(x1 - x3) + s3*(x2 - x1) ) / d;
						circularcen = coord(ux, uy);
					}
					realtype r = std::abs(basepoints[0] - circularcen);
					if (r == 0.L) {
						targetpoint = (basepoints[0] + basepoints[1] + basepoints[2]) / 3.L;
					} else {
						realtype theta = dist(rng) * 2.L * acosl(-1.L);
						targetpoint = circularcen + coord(r * cosl(theta), r * sinl(theta));
					}
					break;
				}
				
				case (_midpoint): {  // with 2 basepoints
					targetpoint = (basepoints[0]+basepoints[1]) / 2.L;
					break;
				}
				
				case (_intersection): {  // with 4 basepoints
					realtype x1 = basepoints[0].real(), y1 = basepoints[0].imag();
					realtype x2 = basepoints[1].real(), y2 = basepoints[1].imag();
					realtype x3 = basepoints[2].real(), y3 = basepoints[2].imag();
					realtype x4 = basepoints[3].real(), y4 = basepoints[3].imag();
					realtype d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
					if (d == 0.L) {
						targetpoint = (basepoints[0] + basepoints[1] + basepoints[2] + basepoints[3]) / 4.L;
					} else {
						realtype det1 = x1*y2 - y1*x2;
						realtype det2 = x3*y4 - y3*x4;
						realtype ux = (det1*(x3 - x4) - (x1 - x2)*det2) / d;
						realtype uy = (det1*(y3 - y4) - (y1 - y2)*det2) / d;
						targetpoint = coord(ux, uy);
					}
					break;
				}

				case (_projection): {  // with 3 basepoints
					realtype x0 = basepoints[0].real(), y0 = basepoints[0].imag();
					realtype xa = basepoints[1].real(), ya = basepoints[1].imag();
					realtype xb = basepoints[2].real(), yb = basepoints[2].imag();
					realtype abx = xb - xa, aby = yb - ya;
					realtype den = abx*abx + aby*aby;
					if (den == 0.L) {
						targetpoint = (basepoints[0] + basepoints[1]) / 2.L;
					} else {
						realtype t = ((x0 - xa)*abx + (y0 - ya)*aby) / den;
						targetpoint = coord(xa + t*abx, ya + t*aby);
					}
					break;
				}

				default: {}
			};
			p0=targetpoint;
			return ;
		}
		public: ~Construction(void) = default;
		
		public: const contype& operator* (void) {
			return handle;
		}
		public: const coord& operator~ (void) {
			return targetpoint;
		}
		public: std::string literal(void) {
			std::stringstream ss("");
			switch((int) handle) {
				case (_basepoint): {
					ss << "Basepoints(" << basepoints[0] << "," << basepoints[1] << "," << basepoints[2] << ");";
					break;
				}
				
				case (_conlinear): {
					ss << "Conlinear(" << targetpoint << ";"
					   << basepoints[0] << "," << basepoints[1] << ");";
					break;
				}
				
				case (_centroid): {
					ss << "Centroid(" << targetpoint << ";"
					   << basepoints[0] << "," << basepoints[1] << "," << basepoints[2] << ");";
					break;
				}
				
				case (_concyclic): {
					ss << "Concyclic(" << targetpoint << ";"
					   << basepoints[0] << "," << basepoints[1] << "," << basepoints[2] << ");";
					break;
				}
				
				case (_midpoint): {
					ss << "Midpoint(" << targetpoint << ";"
					   << basepoints[0] << "," << basepoints[1] << ");";
					break;
				}
				
				case (_intersection): {
					ss << "Intersection(" << targetpoint << ";"
					   << basepoints[0] << "*" << basepoints[1] << "," << basepoints[2] << "*" << basepoints[3] << ");";
					break;
				}
				
				case (_projection): {
					ss << "Projection(" << targetpoint << ";"
					   << basepoints[0] << "," << basepoints[1] << "," << basepoints[2] << ");";
					break;
				}

				default: {}
			};
			return ss.str();
		}
	};
	class Prover {
	
		private: std::vector<coord> varlist;  // also the order of elimination.
		private: std::vector<Construction> conlist;
		private: TrivialMap<coord,std::string> varmap;
		
		public: Prover(void) = default;
		public: ~Prover(void) = default;
		
		public: inline Prover& basepoints(coord a, coord b, coord c) {
			std::vector<coord> initlist={a,b,c};
			coord base(0,0);
			conlist.push_back(Construction(_basepoint,base,initlist));
			varlist.push_back(~conlist[conlist.size()-1]);
			varlist.push_back(a);
			varlist.push_back(b);
			varlist.push_back(c);
			return (*this);
		}
		public: inline Prover& conlinear(coord &p, coord a, coord b) {
			std::vector<coord> initlist={a,b};
			conlist.push_back(Construction(_conlinear,p,initlist));
			// varlist.push_back(~conlist[conlist.size()-1]);
			varlist.push_back(p);
			return (*this);
		}
		public: inline Prover& centroid(coord &p, coord a, coord b, coord c) {
			std::vector<coord> initlist={a,b,c};
			conlist.push_back(Construction(_centroid,p,initlist));
			// varlist.push_back(~conlist[conlist.size()-1]);
			varlist.push_back(p);
			return (*this);
		}
		public: inline Prover& concyclic(coord &p, coord a, coord b, coord c) {
			std::vector<coord> initlist={a,b,c};
			conlist.push_back(Construction(_concyclic,p,initlist));
			// varlist.push_back(~conlist[conlist.size()-1]);
			varlist.push_back(p);
			return (*this);
		}
		public: inline Prover& midpoint(coord &p, coord a, coord b) {
			std::vector<coord> initlist={a,b};
			conlist.push_back(Construction(_midpoint,p,initlist));
			// varlist.push_back(~conlist[conlist.size()-1]);
			varlist.push_back(p);
			return (*this);
		}
		public: inline Prover& intersection(coord &p, coord a, coord b, coord c, coord d) {
			std::vector<coord> initlist={a,b,c,d};
			conlist.push_back(Construction(_intersection,p,initlist));
			// varlist.push_back(~conlist[conlist.size()-1]);
			varlist.push_back(p);
			return (*this);
		}
		public: inline Prover& projection(coord &p, coord a, coord b, coord c) {
			std::vector<coord> initlist={a,b,c};
			conlist.push_back(Construction(_projection,p,initlist));
			// varlist.push_back(~conlist[conlist.size()-1]);
			varlist.push_back(p);
			return (*this);
		}
		public: inline Prover& declare(const coord &a, std::string t) {
			varmap[a]=t;
			return (*this);
		}
		
		public: inline static realtype bracket(const coord &a, const coord &b, const coord &c) {
			return a.real()*(b.imag()-c.imag())+b.real()*(c.imag()-a.imag())+c.real()*(a.imag()-b.imag());
		}
		public: inline std::string bradump(const coord &a, const coord &b, const coord &c) {
			std::stringstream ss("");
			ss << "\\left[" << varmap[a] << varmap[b] << varmap[c] << "\\right]";
			return ss.str();
		}
		public: void eliminate(const Construction& con) {
			switch((int) con.handle) {  // Not incidence geometric constructions: Not available
				case (_basepoint): {
					std::cout << "  \\left[" << varmap[con.basepoints[0]] << varmap[con.basepoints[1]] << varmap[con.basepoints[2]] << "\\right]\\neq 0.\\\\\n";
					break;
				}
				
				case (_conlinear): {
					std::cout << "  \\left[" << varmap[con.basepoints[0]] << varmap[con.basepoints[1]] << varmap[con.targetpoint] << "\\right]=0.\\\\\n";
					break;
				}
				
				case (_centroid): {  // Not incidence geometric constructions: Not available
					break;
				}
				
				case (_concyclic): {  // Not incidence geometric constructions: Not available
					break;
				}
				
				case (_midpoint): {  // Not incidence geometric constructions: Not available
					break;
				}
				
				case (_intersection): {
					const coord &pt0=con.basepoints[0], &pt1=con.basepoints[1], &pt2=con.basepoints[2], &pt3=con.basepoints[3]; 
					for(auto& is:varlist) {
						for(auto& si:varlist) {
							if(is==si||is==pt0||is==pt1||is==pt2||is==pt3||si==pt0||si==pt1||si==pt2||si==pt3||is==con.targetpoint||si==con.targetpoint) continue;
							realtype bra1=Prover::bracket(pt0,is,si)*Prover::bracket(pt1,is,si);
							realtype bra2=Prover::bracket(pt2,is,si)*Prover::bracket(pt3,is,si);
							realtype bra3=Prover::bracket(pt0,pt1,is)*Prover::bracket(pt0,pt1,si)*Prover::bracket(pt2,pt3,is)*Prover::bracket(pt2,pt3,si);
							if(std::fabs(bra1)<=eps)
								std::cout << "  \\left[" << varmap[con.targetpoint] << varmap[is] << varmap[si] << "\\right] = \\left["
										  << varmap[pt0] << varmap[pt2] << varmap[pt3] << "\\right]\\left[" << varmap[pt1] << varmap[is] << varmap[si] << "\\right] - \\left["
										  << varmap[pt1] << varmap[pt2] << varmap[pt3] << "\\right]\\left[" << varmap[pt0] << varmap[is] << varmap[si] << "\\right].\\\\\n";
							if(std::fabs(bra2)<=eps)
								std::cout << "  \\left[" << varmap[con.targetpoint] << varmap[is] << varmap[si] << "\\right] = -\\left["
										  << varmap[pt2] << varmap[pt0] << varmap[pt1] << "\\right]\\left[" << varmap[pt1] << varmap[is] << varmap[si] << "\\right] + \\left["
										  << varmap[pt3] << varmap[pt0] << varmap[pt1] << "\\right]\\left[" << varmap[pt0] << varmap[is] << varmap[si] << "\\right].\\\\\n";
							if(std::fabs(bra3)<=eps)
								std::cout << "  \\left[" << varmap[con.targetpoint] << varmap[is] << varmap[si] << "\\right] = \\left["
										  << varmap[pt0] << varmap[pt1] << varmap[is] << "\\right]\\left[" << varmap[pt2] << varmap[pt3] << varmap[si] << "\\right] - \\left["
										  << varmap[pt0] << varmap[pt1] << varmap[si] << "\\right]\\left[" << varmap[pt2] << varmap[pt3] << varmap[is] << "\\right].\\\\\n";
							// Damn, i forgot that i've implemented Prover::bradump.
						}
					}
					break;
				}
				
				case (_projection): {  // Not incidence geometric constructions: Not available
					break;
				}

				default: {}
			};
			return ;
		}
		public: void prove(coord arg, coord brg, coord crg) {
			std::cout << "\\huge{\\boldsymbol{\\text{Eliminate Rules:}}} \\\\ \n\\begin{cases}\n";
			for(auto& is:conlist) eliminate(is);
			std::cout << "\r\\end{cases}\\\\\n\n";
			std::cout << bradump(arg,brg,crg) << "=\n";
			return ;
		}
	};
}
