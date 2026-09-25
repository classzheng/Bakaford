/******************************************************************************
 * Bakaford/Bakaford: A Mechanical Theorem Prover based on Clifford Brackets. *
 * @Author: classzheng@github                                                 *
 * @Date: 2026.8.17 (latest upd)                                              *
 * @Reference: https://doi.org/10.1360/za2007-37-5-523                        *
 * @Modules: { Bakaford::Prover }                                             *
 ******************************************************************************/


#include <algorithm>
#include <random>
#include <iostream>
#include <sstream>
#include <complex>
#include <functional>
#include <string>
#include <utility>
#include <initializer_list>
#include <iterator>

// #pragma once
#pragma GCC optimize (2)
namespace Bakaford {
	using realtype = long double;
	using coord = std::complex<realtype>;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<realtype> distuni(-1.L, 1.L);
	std::uniform_real_distribution<realtype> distneg(-1.L, 0.L);
	std::uniform_real_distribution<realtype> distpos(0.L, 1.L);
	const realtype eps=1e-7;
	namespace Transcendentalize {
	  // Ensure the Linear Independence of each coordinate, cf. https://classzheng.github.io/ (placeholder currently)
		[[nodiscard]] realtype pi_basis(const realtype &d) {
			return std::pow(M_PI,d);
		}
		[[nodiscard]] inline static realtype e_basis(const realtype &d) {
			return std::pow(M_E,d);
		}
	};
	
	template<typename type>	class Container {
		private: std::vector<type> storage;
	    using value_type = type;
	    using size_type = typename std::vector<type>::size_type;
	    using iterator = typename std::vector<type>::iterator;
	    using const_iterator = typename std::vector<type>::const_iterator;
	    using reverse_iterator = typename std::vector<type>::reverse_iterator;
	    using const_reverse_iterator = typename std::vector<type>::const_reverse_iterator;
	
	    public: Container() = default;
	    public: Container(size_type n, const type& val = type{}) : storage(n, val) {}
	    public: Container(std::initializer_list<type> init) : storage(init) {}
	    public: template<typename It> Container(It first, It last) : storage(first, last) {}
	
	    public: ~Container() = default;
	
	    public: inline void push_back(const type& val) {
	        storage.push_back(val);
	        return ;
	    }
	
	    public: inline void push_back(type&& val) {
	        storage.push_back(std::move(val));
	        return ;
	    }
	
	    public: inline void pop_back(void) {
	        if (!storage.empty()) storage.pop_back();
	        return ;
	    }
	
	    public: inline void reserve(size_type n) {
	        storage.reserve(n);
	        return ;
	    }
	
	    public: inline void resize(size_type n, const type& val = type{}) {
	        storage.resize(n, val);
	        return ;
	    }
	
	    public: inline bool empty(void) const {
	        return storage.empty();
	    }
	
	    public: inline size_type size(void) const {
	        return storage.size();
	    }
	
	    public: inline type& operator[](size_type idx) {
	        return storage[idx];
	    }
	
	    public: inline const type& operator[](size_type idx) const {
	        return storage[idx];
	    }
	
	    public: inline type& at(size_type idx) {
	        return storage.at(idx);
	    }
	
	    public: inline const type& at(size_type idx) const {
	        return storage.at(idx);
	    }
	
	    public: inline type& front(void) {
	        return storage.front();
	    }
	
	    public: inline const type& front(void) const {
	        return storage.front();
	    }
	
	    public: inline type& back(void) {
	        return storage.back();
	    }
	
	    public: inline const type& back(void) const {
	        return storage.back();
	    }
	
	    public: inline void clear(void) {
	        storage.clear();
	        return ;
	    }
	
	    public: inline void swap(Container& other) {
	        storage.swap(other.storage);
	        return ;
	    }
	
	    public: inline iterator begin(void) {
	        return storage.begin();
	    }
	
	    public: inline const_iterator begin(void) const {
	        return storage.begin();
	    }
	
	
	    public: inline iterator end(void) {
	        return storage.end();
	    }
	
	    public: inline const_iterator end(void) const {
	        return storage.end();
	    }
	
	    public: inline iterator erase(const_iterator pos) {
	        return storage.erase(pos);
	    }
	
	    public: inline iterator erase(const_iterator first, const_iterator last) {
	        return storage.erase(first, last);
	    }
	
	    public: inline iterator find(const type& val) {
	        return std::find(begin(), end(), val);
	    }
	
	    public: inline const_iterator find(const type& val) const {
	        return std::find(begin(), end(), val);
	    }
	};  // Written by Github Copilot QwQ
	
	class Point {
		public: std::string tag;
		public: coord specialtype;
		public: Point(void) = default;
		public: Point(std::string t, coord s): tag(t), specialtype(s) {}
		public: ~Point(void) = default;
		public: [[nodiscard]] static realtype bracket(const Point &p1, const Point &p2, const Point &p3) {
			coord a=p1.specialtype;
			coord b=p2.specialtype;
			coord c=p3.specialtype;
			return .5L*(a.real()*(b.imag()-c.imag())+b.real()*(c.imag()-a.imag())+c.real()*(a.imag()-b.imag()));
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
		public: [[nodiscard]] inline realtype operator() (void) const {
			return Point::bracket(p1,p2,p3);
		}
		public: [[nodiscard]] inline std::string bradump(void) const {
			return Point::bradump(p1,p2,p3);
		}
		public: [[nodiscard]] bool nearmatch(const Bracket rhs) const {
			Container<Point> v1={p1,p2,p3};
			return v1.find(rhs.p1)!=v1.end() &&
				   v1.find(rhs.p2)!=v1.end() && 
				   v1.find(rhs.p3)!=v1.end();
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
		Container<Bracket> factors; realtype coef;
		[[nodiscard]] inline int operator^ (const Bracket bra) const {
			return int((*this)()/bra());
		}
		[[nodiscard]] realtype operator() (void) const {
			realtype t=coef;
			for(auto& is:factors) t*=is();
			return t;
		}
		[[nodiscard]] inline bool empty(void) const {
			return factors.empty() || std::fabs(coef)<=eps;
		}
	};

	
	class Polynomial {
		public: Bracket maintain;
		public: Container<Monomial> terms;
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
		public: [[nodiscard]] inline realtype operator() (void) const {
			return maintain();
		}
		public: [[nodiscard]] inline int operator^ (const Bracket bra) const {
			if(!maintain.nearmatch(bra)) return 0;
			return maintain()/bra();
		}
		
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
		
		public: [[nodiscard]] int eliminate(const Container<Polynomial>& eliminators,
											[[maybe_unused]] Container<Point> ord, 
											std::uniform_real_distribution<realtype>& dist) {
			Container<Monomial> output;
			Container<Monomial> work = terms;
			int episode=0;
			work.push_back(Monomial{{maintain},1});
			for(auto m: work) {
				if(m.empty()) continue;
				Container<Monomial> cur{m};
				for(auto &e: eliminators) {
					Container<Monomial> next;
					for(auto &cm: cur) {
						Container<int> index;
						for(int i=0, size=cm.factors.size(); i<size; i++) {
							if(cm.factors[i].nearmatch(e.maintain)) {
								index.push_back(i);
							}
						}
						if(index.empty()) {next.push_back(cm); continue;}
						int i = index[(Transcendentalize::pi_basis(dist(rng))+1.L)/2.L*index.size()], size=cm.factors.size();
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
			std::cout << "\n" << maintain.bradump() << "=" << dump() << ". □\n";
			return episode;
		}
	};

	
	class Prover {
		public: Container<Point> conlist;
		public: Container<Polynomial> eliminators;
		public: Container<std::function<void(Prover&)>> callbacks;
		public: Prover(void) = default;
		public: ~Prover(void) = default;
		
		public: [[nodiscard]] Prover& basepoint(Point &p, std::string tag,
												std::uniform_real_distribution<realtype> dist=distuni) {
			p.tag=tag;
			p.specialtype = coord(Transcendentalize::pi_basis(dist(rng)), Transcendentalize::pi_basis(dist(rng)));
			conlist.push_back(p);
			callbacks.push_back([p,dist]([[maybe_unused]] Prover& prov)->void{ return ; });  // Empty eliminator
			return (*this);
		}
		
		public: [[nodiscard]] Prover& freepoint(Point &p, std::string tag,
												const Point &p1, const Point &p2, const Point &p3,
												std::uniform_real_distribution<realtype> dist=distuni) {
			p.tag=tag;
			p.specialtype = p1.specialtype * Transcendentalize::pi_basis(dist(rng)) + p2.specialtype * Transcendentalize::pi_basis(dist(rng)) + p3.specialtype * Transcendentalize::pi_basis(dist(rng));
			conlist.push_back(p);
			callbacks.push_back([p,p1,p2,p3,dist]([[maybe_unused]] Prover& prov)->void{ return ; });  // Empty eliminator
			return (*this);
		}
		
		public: [[nodiscard]] Prover& collinear(Point &p, std::string tag,
												const Point &p1, const Point &p2,
												std::uniform_real_distribution<realtype> dist=distuni) {
			p.tag=tag;
			p.specialtype = p1.specialtype+(p2.specialtype-p1.specialtype)*Transcendentalize::pi_basis(dist(rng));
			
			Polynomial poly;
			poly.set(Bracket(p,p1,p2))<<Monomial{{},0.L};
			eliminators.push_back(poly);
			
			conlist.push_back(p);
			callbacks.push_back([p,p1,p2,dist](Prover& prov)->void{
				for(auto& is: prov.conlist) {
					if(is==p||is==p1||is==p2) continue;
					prov.eliminate(p,p1,p2,p,is,dist); 
				}
			});
			return (*this);
		}
		
		public: [[nodiscard]] Prover& intersection(Point &p, std::string tag, 
												   const Point &p1, const Point &p2, const Point &p3, const Point &p4,
												   const std::uniform_real_distribution<realtype> dist=distuni) {
			p.tag=tag;
			realtype x1 = p1.specialtype.real(), y1 = p1.specialtype.imag();
			realtype x2 = p2.specialtype.real(), y2 = p2.specialtype.imag();
			realtype x3 = p3.specialtype.real(), y3 = p3.specialtype.imag();
			realtype x4 = p4.specialtype.real(), y4 = p4.specialtype.imag();
			realtype d = (x1 - x2)*(y3 - y4) - (y1 - y2)*(x3 - x4);
			if (d == 0.L) {
				p.specialtype = (p1.specialtype + p2.specialtype + p3.specialtype + p4.specialtype) / 4.L;
			} else {
				realtype det1 = x1*y2 - y1*x2;
				realtype det2 = x3*y4 - y3*x4;
				realtype ux = (det1*(x3 - x4) - (x1 - x2)*det2) / d;
				realtype uy = (det1*(y3 - y4) - (y1 - y2)*det2) / d;
				p.specialtype = coord(ux, uy);
			}
			
			Polynomial poly1, poly2;
			poly1.set(Bracket(p,p1,p2))<<Monomial{{},0.L};
			poly2.set(Bracket(p,p3,p4))<<Monomial{{},0.L};
			eliminators.push_back(poly1);
			eliminators.push_back(poly2);
			
			conlist.push_back(p);
			callbacks.push_back([p,p1,p2,p3,p4,dist](Prover& prov)->void{
				prov.eliminate(p,p1,p2,p3,p4,dist);
			});
			return (*this);
		}
		
		public: void eliminate(const Point &p, const Point &p1, const Point &p2, const Point &p3, const Point &p4,
							   [[maybe_unused]] const std::uniform_real_distribution<realtype>& dist) {
			for(auto& is:conlist) {
				for(auto& si:conlist) {
					if(is==si||is==p1||is==p2||is==p3||is==p4||si==p1||si==p2||si==p3||si==p4||is==p||si==p) continue;
					bool flag=false;
					realtype bra1 = Prover::bracket(p1,is,si)*Prover::bracket(p2,is,si);
					realtype bra2 = Prover::bracket(p3,is,si)*Prover::bracket(p4,is,si);
					realtype bra3 = Prover::bracket(p1,p2,is)*Prover::bracket(p1,p2,si)*Prover::bracket(p3,p4,is)*Prover::bracket(p3,p4,si);
					if(std::fabs(bra1)<=eps) {
						Polynomial poly;
						poly.set(Bracket(p,is,si))
						  << Monomial{{Bracket(p1,p3,p4),Bracket(p2,is,si)}, 1}
						  << Monomial{{Bracket(p2,p3,p4),Bracket(p1,is,si)},-1}, flag=true;
						eliminators.push_back(poly);
					}
					if(std::fabs(bra2)<=eps) {
						Polynomial poly;
						poly.set(Bracket(p,is,si))
						  << Monomial{{Bracket(p4,p1,p2),Bracket(p1,is,si)}, 1}
						  << Monomial{{Bracket(p3,p1,p2),Bracket(p2,is,si)},-1}, flag=true;
						eliminators.push_back(poly);
					}
					if(std::fabs(bra3)<=eps) {
						Polynomial poly;
						poly.set(Bracket(p,is,si))
						  << Monomial{{Bracket(p1,p2,is),Bracket(p3,p4,si)}, 1}
						  << Monomial{{Bracket(p1,p2,si),Bracket(p3,p4,is)},-1}, flag=true;
						eliminators.push_back(poly);
					}
					if(flag) continue; else {
						Container<int> psig={1,2,3};
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
			conlist.erase(conlist.find(p));
			return ;
		}

		public: int qed(Polynomial conc, bool detail=false, std::uniform_real_distribution<realtype>& dist=distuni) {  // Quite Easy Done!! □
			Container<Point> ord=conlist;
			while(!callbacks.empty()) callbacks.back()(*this), callbacks.pop_back();
			if(detail) {
				std::cout << "\n";
				for(auto &is: eliminators) std::cout << is.maintain.bradump() << "=" << is.dump() << "\\\\\n";
			}
			std::cout << "\neps: " << eps << "; real eps: " << conc.maintain() << "\n";
			return conc.eliminate(eliminators,ord,dist);
		}

		public: [[nodiscard]] static inline realtype bracket(Point p1, Point p2, Point p3) {
			return Point::bracket(p1,p2,p3);
		}
		public: [[nodiscard]] static std::string minidump(Point p1, Point p2, Point p3) {
			if(std::fabs(Point::bracket(p1,p2,p3))<=eps) return "0";
			else										 return Point::bradump(p1,p2,p3);
		}
	};
};
