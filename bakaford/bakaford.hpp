/******************************************************************************
 * Bakaford/Bakaford: A Mechanical Theorem Prover based on Clifford Brackets. *
 * @Author: classzheng@github                                                 *
 * @Date: 2026.8.17 (latest upd)                                              *
 * @Reference: https://doi.org/10.1360/za2007-37-5-523                        *
 * @Modules: { Bakaford::Prover }                                             *
 ******************************************************************************/


#include <vector>
#include <algorithm>
#include <random>
#include <string>
#include <iostream>
#include <sstream>
#include <complex>
#include <functional>

#pragma once
#pragma GCC optimize (2)
namespace Bakaford {
	using quotype = long double;
	using coord = std::complex<quotype>;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<quotype> dist(-1.L, 1.L);
	quotype eps=1e-7;
	class Point {
		public: std::string tag;
		public: coord specialtype;
		public: Point(void) = default;
		public: Point(std::string t, coord s): tag(t), specialtype(s) {}
		public: ~Point(void) = default;
		public: [[nodiscard]] static quotype bracket(const Point &p1, const Point &p2, const Point &p3) {
			coord a=p1.specialtype;
			coord b=p2.specialtype;
			coord c=p3.specialtype;
			return a.real()*(b.imag()-c.imag())+b.real()*(c.imag()-a.imag())+c.real()*(a.imag()-b.imag());
		}
		public: [[nodiscard]] static inline std::string bradump(const Point &a, const Point &b, const Point &c) {
			std::stringstream ss("");
			ss << "[" << a.tag << b.tag << c.tag << "]";
			return ss.str();
		}
		public: [[nodiscard]] inline std::string v(void) {
			return tag;
		}
	};
	[[nodiscard]] inline bool operator< (Point lhs, Point rhs) {
		return std::fabs(lhs.specialtype-rhs.specialtype)<0;  // Very important!!
	}
	[[nodiscard]] inline bool operator==(const Point& lhs, const Point& rhs) {
		return lhs.specialtype==rhs.specialtype;
	}
	class Bracket {  // Triple
		public: Point p1, p2, p3;
		public: Bracket(void) = default;
		public: Bracket(Point a, Point b, Point c): p1(a), p2(b), p3(c) {}
		public: ~Bracket(void) = default;
		public: [[nodiscard]] inline quotype operator() (void) const {
			return Point::bracket(p1,p2,p3);
		}
		public: [[nodiscard]] inline std::string bradump(void) const {
			return Point::bradump(p1,p2,p3);
		}
		public: [[nodiscard]] bool nearmatch(const Bracket rhs) const {
			std::vector<Point> v1={p1,p2,p3};
			return std::find(v1.begin(),v1.end(),rhs.p1)!=v1.end() &&
				   std::find(v1.begin(),v1.end(),rhs.p2)!=v1.end() && 
				   std::find(v1.begin(),v1.end(),rhs.p3)!=v1.end();
		}
		public: [[nodiscard]] inline bool exist(const Point& rhs) const {
			return p1==rhs || p2==rhs || p3==rhs;
		}
		public: [[nodiscard]] inline bool tautology(void) const {
			return p1==p2 || p1==p3 || p2==p3;
		}
		public: [[nodiscard]] Bracket inverse(int rhs) const {  // rhs \in ±1
			if(rhs==1) return Bracket(p1, p2, p3);
			else	   return Bracket(p2, p1, p3);
		}
	};
	[[nodiscard]] inline bool operator== (const Bracket lhs, const Bracket rhs) {
		return lhs.p1.specialtype==rhs.p1.specialtype &&
			   lhs.p2.specialtype==rhs.p2.specialtype &&
			   lhs.p3.specialtype==rhs.p3.specialtype;
	}
	
	struct Monomial {
		std::vector<Bracket> factors; quotype coef;
		[[nodiscard]] inline int operator^ (const Bracket bra) const {
			return int((*this)()/bra());
		}
		[[nodiscard]] quotype operator() (void) const {
			quotype t=coef;
			for(auto& is:factors) t*=is();
			return t;
		}
		[[nodiscard]] inline bool empty(void) const {
			return factors.empty() || std::fabs(coef)<=eps;
		}
	};
	class Polynomial {
		public: Bracket maintain;
		public: std::vector<Monomial> terms;
		public: Polynomial(void) = default;
		public: Polynomial(Bracket m): maintain(m) {}
		public: ~Polynomial(void) = default;
		public: [[nodiscard]] Polynomial& set(const Bracket m) {
			maintain = m;
			return *this;
		}
		public: Polynomial& operator<< (const Monomial m) {
			terms.push_back(m);
			return *this;
		}
		public: [[nodiscard]] inline quotype operator() (void) const {
			return maintain();
		}
		public: [[nodiscard]] inline int operator^ (const Bracket bra) const {
			if(!maintain.nearmatch(bra)) return 0;
			return maintain()/bra();
		}
		
		/**
		 * @function Bakaford::Polynomial::dump
		 * @description "Return the formatted string of a polynomial."
		 * @returns {String}
		 */
		public: [[nodiscard]] std::string dump(void) const {
			std::stringstream ss("=");
			if(terms.empty()) { ss << "0"; return ss.str(); }
			bool first = true, fullempty=true;
			for(auto &t: terms) {
				if(t.empty() || std::fabs(t())<=eps) continue;
				if(!first) {
					if(std::fabs(t.coef-1.L)<=eps) ss << "+";
					if(std::fabs(t.coef+1.L)<=eps) ss << "-";
				}
				for(auto &f: t.factors) {
					if(!f.tautology()) ss << f.bradump(), fullempty=false;
				}
				if(std::fabs(t.coef)-1.L>eps) ss << "(" << t.coef << ")";
				first = false;
			}
			if(fullempty) ss << "0";
			return ss.str();
		}		

		/**
		 * @function Bakaford::Polynomial::eliminate
		 * @description "Eliminate the terms with respect to the eliminators."
		 * @param {Vector} eliminators
		 * @param {Vector} ord  // not available
		 * @returns {Integer}
		 */
		public: [[nodiscard]] int eliminate(const std::vector<Polynomial>& eliminators, [[maybe_unused]] std::vector<Point> ord) {
			std::vector<Monomial> output;
			std::vector<Monomial> work = terms;
			int episode=0;
			work.push_back(Monomial{{maintain},1});
			for(auto m: work) {
				if(m.empty()) continue;
				std::vector<Monomial> cur{m};
				for(auto &e: eliminators) {
					std::vector<Monomial> next;
					for(auto &cm: cur) {
						std::vector<int> index;
						for(int i=0, size=cm.factors.size(); i<size; i++) {
							if(cm.factors[i].nearmatch(e.maintain)) {
								index.push_back(i);
							}
						}
						if(index.empty()) {next.push_back(cm); continue;}
						int i = index[(dist(rng)+1.L)/2.L*index.size()], size=cm.factors.size();
	                    std::cout << e.maintain.bradump() << "=" << e.dump() << "\n";
	                    episode++;
						for(auto &et: e.terms) {
							// if(et.empty()) continue;
							Monomial nm;
							nm.coef = cm.coef * et.coef;
							nm.factors.reserve(size-1 + et.factors.size());
							for(int j=0; j<size; j++) if(j!=i) nm.factors.push_back(cm.factors[j]);
							for(auto &ff: et.factors) nm.factors.push_back(ff);
							next.push_back(nm);
						}
					}
					cur.swap(next);
				}
				for(auto &fm: cur) {
					bool bad=false;
					for(auto &f: fm.factors) if(f.tautology()) { bad=true; break; }
					if(!bad && !fm.empty()) output.push_back(fm);
				}
			}
			terms.swap(output);
			std::cout << "\n" << maintain.bradump() << "=" << dump();
			return episode;
		}
	};

	
	class Prover {
		public: std::vector<Point> conlist;
		public: std::vector<Polynomial> eliminators;
		public: std::vector<std::function<void(Prover&)>> callbacks;
		public: Prover(void) = default;
		public: ~Prover(void) = default;
		
		/**
		 * @function Bakaford::Prover::basepoint, Bakaford::Prover::freepoint,
		 * 			 Bakaford::Prover::collinear, Bakaford::Prover::intersection
		 * @description "A group of chain methods to generate random coordinates."
		 * @param {Point&} p
		 * @param {String} tag
		 * @param {const Point&} p1
		 * @param {const Point&} p2
		 * @param {const Point&} p3
		 * @param {const Point&} p4
		 * @returns {Prover&}
		 */
		public: [[nodiscard]] Prover& basepoint(Point &p, std::string tag) {
			p.tag=tag;
			do p.specialtype = coord(dist(rng), dist(rng));
			while(std::find(conlist.begin(),conlist.end(),p)!=conlist.end());
			conlist.push_back(p);
			callbacks.push_back([p]([[maybe_unused]] Prover& prov)->void{ return ; });  // Empty eliminator
			return (*this);
		}
		
		public: [[nodiscard]] Prover& freepoint(Point &p, std::string tag, const Point &p1, const Point &p2, const Point &p3) {
			p.tag=tag;
			do p.specialtype = p1.specialtype * dist(rng) + p2.specialtype * dist(rng) + p3.specialtype * dist(rng);
			while(std::find(conlist.begin(),conlist.end(),p)!=conlist.end());
			conlist.push_back(p);
			callbacks.push_back([p,p1,p2,p3]([[maybe_unused]] Prover& prov)->void{ return ; });  // Empty eliminator
			return (*this);
		}
		
		public: [[nodiscard]] Prover& collinear(Point &p, std::string tag, const Point &p1, const Point &p2) {
			p.tag=tag;
			do p.specialtype = p1.specialtype+(p2.specialtype-p1.specialtype)*dist(rng); 
			while(std::find(conlist.begin(),conlist.end(),p)!=conlist.end());
			
			Polynomial poly;
			poly.set(Bracket(p,p1,p2))<<Monomial{{},0.L};
			eliminators.push_back(poly);
			
			conlist.push_back(p);
			callbacks.push_back([p,p1,p2](Prover& prov)->void{
				for(auto& is: prov.conlist) {
					if(is==p||is==p1||is==p2) continue;
					prov.eliminate(p,p1,p2,p,is); 
				}
			});
			return (*this);
		}
		
		public: [[nodiscard]] Prover& intersection(Point &p, std::string tag, const Point &p1, const Point &p2, const Point &p3, const Point &p4) {
			p.tag=tag;
			quotype x1 = p1.specialtype.real(), y1 = p1.specialtype.imag();
			quotype x2 = p2.specialtype.real(), y2 = p2.specialtype.imag();
			quotype x3 = p3.specialtype.real(), y3 = p3.specialtype.imag();
			quotype x4 = p4.specialtype.real(), y4 = p4.specialtype.imag();
			quotype d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
			if (d == 0.L) {
				p.specialtype = (p1.specialtype + p2.specialtype + p3.specialtype + p4.specialtype) / 4.L;
			} else {
				quotype det1 = x1*y2 - y1*x2;
				quotype det2 = x3*y4 - y3*x4;
				quotype ux = (det1*(x3 - x4) - (x1 - x2)*det2) / d;
				quotype uy = (det1*(y3 - y4) - (y1 - y2)*det2) / d;
				p.specialtype = coord(ux, uy);
			}
			
			Polynomial poly1, poly2;
			poly1.set(Bracket(p,p1,p2))<<Monomial{{},0.L};
			poly2.set(Bracket(p,p3,p4))<<Monomial{{},0.L};
			eliminators.push_back(poly1);
			eliminators.push_back(poly2);
			
			conlist.push_back(p);
			callbacks.push_back([p,p1,p2,p3,p4](Prover& prov)->void{
				prov.eliminate(p,p1,p2,p3,p4);
			});
			return (*this);
		}
		
		/**
		 * @function Bakaford::Prover::eliminate
		 * @description "Eliminate with respect to the rules."
		 * @param {Point&} p
		 * @param {const Point&} p1
		 * @param {const Point&} p2
		 * @param {const Point&} p3
		 * @param {const Point&} p4
		 * @returns None
		 */
		public: void eliminate(const Point &p, const Point &p1, const Point &p2, const Point &p3, const Point &p4) {
			for(auto& is:conlist) {
				for(auto& si:conlist) {
					if(is==si||is==p1||is==p2||is==p3||is==p4||si==p1||si==p2||si==p3||si==p4||is==p||si==p) continue;
					bool flag=false;
					quotype bra1 = Prover::bracket(p1,is,si)*Prover::bracket(p2,is,si);
					quotype bra2 = Prover::bracket(p3,is,si)*Prover::bracket(p4,is,si);
					quotype bra3 = Prover::bracket(p1,p2,is)*Prover::bracket(p1,p2,si)*Prover::bracket(p3,p4,is)*Prover::bracket(p3,p4,si);
					if(std::fabs(bra1)<=eps) {
						std::cout << Point::bradump(p1,is,si) << Point::bradump(p2,is,si) << "collinear?\n";
						Polynomial poly;
						poly.set(Bracket(p,is,si))
						  << Monomial{{Bracket(p1,p3,p4),Bracket(p2,is,si)}, 1}
						  << Monomial{{Bracket(p2,p3,p4),Bracket(p1,is,si)},-1}, flag=true;
						eliminators.push_back(poly);
					}
					if(std::fabs(bra2)<=eps) {
						std::cout << Point::bradump(p3,is,si) << Point::bradump(p4,is,si) << "collinear?\n";
						Polynomial poly;
						poly.set(Bracket(p,is,si))
						  << Monomial{{Bracket(p4,p1,p2),Bracket(p1,is,si)}, 1}
						  << Monomial{{Bracket(p3,p1,p2),Bracket(p2,is,si)},-1}, flag=true;
						eliminators.push_back(poly);
					}
					if(std::fabs(bra3)<=eps) {
						std::cout << Point::bradump(p1,p2,is) << Point::bradump(p1,p2,si) << Point::bradump(p3,p4,is) << Point::bradump(p3,p4,si) << "collinear?\n";
						Polynomial poly;
						poly.set(Bracket(p,is,si))
						  << Monomial{{Bracket(p1,p2,is),Bracket(p3,p4,si)}, 1}
						  << Monomial{{Bracket(p1,p2,si),Bracket(p3,p4,is)},-1}, flag=true;
						eliminators.push_back(poly);
					}
					if(flag) continue; else {
						std::vector<int> psig={1,2,3};
						do {
							Point ai1, ai2, aj1, aj2, ak1, ak2;
							if(psig[0]==1) ai1=p1, ai2=p2;
							if(psig[0]==2) ai1=p3, ai2=p4;
							if(psig[0]==3) ai1=is, ai2=si;
							
							if(psig[1]==1) aj1=p1, aj2=p2;
							if(psig[1]==2) aj1=p3, aj2=p4;
							if(psig[1]==3) aj1=is, aj2=si;
							
							if(psig[2]==1) ak1=p1, ak2=p2;
							if(psig[2]==2) ak1=p3, ak2=p4;
							if(psig[2]==3) ak1=is, ak2=si;
							if(std::fabs(Point::bracket(p,is,si)-
										(Point::bracket(ai1,aj1,aj2)*Point::bracket(ai2,ak1,ak2)-Point::bracket(ai2,aj1,aj2)*Point::bracket(ai1,ak1,ak2)))
											<=eps) {
								Polynomial poly;
								poly.set(Bracket(p,is,si))
								  << Monomial{{Bracket(ai1,aj1,aj2),Bracket(ai2,ak1,ak2)},1}
								  << Monomial{{Bracket(ai2,aj1,aj2),Bracket(ai1,ak1,ak2)},-1};
								eliminators.push_back(poly);
							}
						} while(std::next_permutation(psig.begin(),psig.end()));
					}
				}
			}
			conlist.erase(std::find(conlist.begin(),conlist.end(),p));
			return ;
		}

		/**
		 * @function Bakaford::Prover::qed
		 * @description "Quiet Easy Done."
		 * @param {Polynomial} conc
		 * @param {Boolean} detail=true
		 * @returns {Integer}
		 */
		public: int qed(Polynomial conc, bool detail=false) {
			std::vector<Point> ord=conlist;
			while(!callbacks.empty()) callbacks.back()(*this), callbacks.pop_back();
			if(detail) {
				std::cout << "\n";
				for(auto &is: eliminators) std::cout << is.maintain.bradump() << "=" << is.dump() << "\\\\\n";
			}
			std::cout << "\neps: " << eps << "; real eps: " << conc.maintain() << "\n";
			return conc.eliminate(eliminators,ord);
		}

		public: [[nodiscard]] static inline quotype bracket(Point p1, Point p2, Point p3) {
			return Point::bracket(p1,p2,p3);
		}
		public: [[nodiscard]] static std::string minidump(Point p1, Point p2, Point p3) {
			if(std::fabs(Point::bracket(p1,p2,p3))<=eps) return "0";
			else										 return Point::bradump(p1,p2,p3);
		}
	};
};
