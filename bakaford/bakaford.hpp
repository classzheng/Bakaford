// bakaford.hpp
#include "bits/stdc++.h"
namespace Bakaford {
	using quotype = long double;
	using coord = std::complex<quotype>;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<quotype> dist(-1.L, 1.L);
	quotype eps=1e-16;
	class Point {
		public: std::string tag;
		public: coord specialtype;
		public: Point(void) = default;
		public: Point(std::string t, coord s): tag(t), specialtype(s) {}
		public: ~Point(void) = default;
		public: static quotype bracket(const Point &p1, const Point &p2, const Point &p3) {
			coord a=p1.specialtype;
			coord b=p2.specialtype;
			coord c=p3.specialtype;
			return a.real()*(b.imag()-c.imag())+b.real()*(c.imag()-a.imag())+c.real()*(a.imag()-b.imag());
		}
		public: static inline std::string bradump(const Point &a, const Point &b, const Point &c) {
			std::stringstream ss("");
			// ss << "\\left[" << a.tag << b.tag << c.tag << "\\right]";
			ss << "[" << a.tag << b.tag << c.tag << "]";
			return ss.str();
		}
		public: inline std::string v(void) {
			return tag;
		}
	};
	inline bool operator< (Point lhs, Point rhs) {
		return std::fabs(lhs.specialtype-rhs.specialtype)<0;  // Very important!!
	}
	inline bool operator==(const Point& lhs, const Point& rhs) {
		return lhs.specialtype==rhs.specialtype;
	}
	class Bracket {  // Triple
		public: Point p1, p2, p3;
		public: Bracket(void) = default;
		public: Bracket(Point a, Point b, Point c): p1(a), p2(b), p3(c) {}
		public: ~Bracket(void) = default;
		public: inline quotype operator() (void) const {
			return Point::bracket(p1,p2,p3);
		}
		public: inline std::string bradump(void) const {
			return Point::bradump(p1,p2,p3);
		}
		public: bool nearmatch(const Bracket rhs) const {  // near match
			std::vector<Point> v1={p1,p2,p3};
			return std::find(v1.begin(),v1.end(),rhs.p1)!=v1.end() &&
				   std::find(v1.begin(),v1.end(),rhs.p2)!=v1.end() && 
				   std::find(v1.begin(),v1.end(),rhs.p3)!=v1.end();
		}
		public: Bracket inverse(int rhs) const {  // rhs \in ±1
			if(rhs==1) return Bracket(p1, p2, p3);
			else	   return Bracket(p2, p1, p3);
		}
	};
	inline bool operator== (const Bracket lhs, const Bracket rhs) {
		return lhs.p1.specialtype==rhs.p1.specialtype &&
			   lhs.p2.specialtype==rhs.p2.specialtype &&
			   lhs.p3.specialtype==rhs.p3.specialtype;
	}
	class Polynomial {
		public: Bracket maintain;
		public: struct Monomial { std::vector<Bracket> factors; quotype coef; };
		public: std::vector<Monomial> terms;
		public: Polynomial(void) = default;
		public: Polynomial(Bracket m): maintain(m) {}
		public: ~Polynomial(void) = default;
		public: Polynomial& setmain(const Bracket m) {
			maintain = m;
			return *this;
		}
		public: Polynomial& setterm1(const Bracket a, const Bracket b) {
			terms.push_back(Monomial{{a,b}, 1.L});
			return *this;
		}
		public: Polynomial& setterm2(const Bracket a, const Bracket b) {
			terms.push_back(Monomial{{a,b}, 1.L});
			return *this;
		}
		public: inline quotype operator() (void) const {
			return maintain();
		}
		public: inline int operator^ (const Bracket bra) const {
			if(!maintain.nearmatch(bra)) return 0;
			quotype v = maintain()/bra();
			if(std::fabs(v) <= eps) return 0;
			return v > 0 ? 1 : -1;
		}
		public: std::string dump(void) const {
			std::stringstream ss("");
			ss << maintain.bradump() << "&=";
			if(terms.empty()) { ss << "0"; return ss.str(); }
			bool first = true;
			for(const auto &t: terms) {
				if(std::fabs(t.coef) <= eps) continue;
				if(!first) ss << "+";
				for(const auto &f: t.factors) ss << f.bradump();
				if(std::fabs(t.coef - 1.L) > eps) ss << "(" << t.coef << ")";
				first = false;
			}
			return ss.str();
		}
		public: std::string localdump(void) const {
			std::stringstream ss("");
			ss << "  &=";
			if(terms.empty()) { ss << "0"; return ss.str(); }
			bool first = true;
			for(const auto &t: terms) {
				if(std::fabs(t.coef) <= eps) continue;
				if(!first) ss << "+";
				for(const auto &f: t.factors) ss << f.bradump();
				if(std::fabs(t.coef - 1.L) > eps) ss << "(" << t.coef << ")";
				first = false;
			}
			return ss.str();
		}
		public: void eliminate([[maybe_unused]] const std::vector<Polynomial>& eliminators) {
			std::cout << maintain.bradump() << "&=";
			terms.push_back(Monomial{{maintain},1.L});
			
			std::cout << localdump();
			return ;
		}
	};
	class Prover {
		public: std::vector<Point> conlist;
		public: std::map<Point, unsigned> linepassed;
		public: std::vector<Polynomial> eliminators;
		public: std::vector<std::function<void(Prover&)>> callbacks;
		public: Prover(void) = default;
		public: ~Prover(void) = default;
		
		public: Prover& basepoint(Point &p, std::string tag) {
			p.tag=tag;
			do p.specialtype = coord(dist(rng), dist(rng));
			while(std::find(conlist.begin(),conlist.end(),p)!=conlist.end());
			conlist.push_back(p);
			callbacks.push_back([p]([[maybe_unused]] Prover& prov)->void{ return ; });  // Empty eliminator
			return (*this);
		}
		
		public: Prover& freepoint(Point &p, std::string tag, const Point &p1, const Point &p2, const Point &p3) {
			p.tag=tag;
			do p.specialtype = p1.specialtype * dist(rng) + p2.specialtype * dist(rng) + p3.specialtype * dist(rng);
			while(std::find(conlist.begin(),conlist.end(),p)!=conlist.end());
			conlist.push_back(p);
			callbacks.push_back([p,p1,p2,p3]([[maybe_unused]] Prover& prov)->void{ return ; });  // Empty eliminator
			return (*this);
		}
		
		public: Prover& collinear(Point &p, std::string tag, const Point &p1, const Point &p2) {
			p.tag=tag;
			do p.specialtype = p1.specialtype+(p2.specialtype-p1.specialtype)*dist(rng); 
			while(std::find(conlist.begin(),conlist.end(),p)!=conlist.end());
			conlist.push_back(p);
			linepassed[p]++;
			callbacks.push_back([p,p1,p2](Prover& prov)->void{
				// std::cout << Point::bradump(p,p1,p2) << "&=0.\\\\\n";
				for(auto& is: prov.conlist) {
					if(is==p||is==p1||is==p2) continue;
					prov.eliminate(p,p1,p2,p,is); 
				}
			});
			return (*this);
		}
		
		public: Prover& intersection(Point &p, std::string tag, const Point &p1, const Point &p2, const Point &p3, const Point &p4) {
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
			conlist.push_back(p);
			linepassed[p]++;
			callbacks.push_back([p,p1,p2,p3,p4](Prover& prov)->void{
				// std::cout << Point::bradump(p,p1,p2) << "&=0.\\\\\n";
				// std::cout << Point::bradump(p,p3,p4) << "&=0.\\\\\n";
				prov.eliminate(p,p1,p2,p3,p4);
			});
			return (*this);
		}
		
		public: Prover& eliminate(const Point &p, const Point &p1, const Point &p2, const Point &p3, const Point &p4) {
			for(auto& is:conlist) {
				for(auto& si:conlist) {
					// std::cout << is.tag << si.tag << "\n";
					if(is==si||is==p1||is==p2||is==p3||is==p4||si==p1||si==p2||si==p3||si==p4||is==p||si==p) continue;
					bool flag=false;
					quotype bra1 = Prover::bracket(p1,is,si)*Prover::bracket(p2,is,si);
					quotype bra2 = Prover::bracket(p3,is,si)*Prover::bracket(p4,is,si);
					quotype bra3 = Prover::bracket(p1,p2,is)*Prover::bracket(p1,p2,si)*Prover::bracket(p3,p4,is)*Prover::bracket(p3,p4,si);
					if(std::fabs(bra1)<=eps) {
						Polynomial poly;
						poly.setmain(Bracket(p,is,si))
						  .setterm1(Bracket(p1,p3,p4), Bracket(p2,is,si))
						  .setterm2(Bracket(p2,p3,p4), Bracket(p1,is,si)), flag=true;
						eliminators.push_back(poly);
					}
					if(std::fabs(bra2)<=eps) {
						Polynomial poly;
						poly.setmain(Bracket(p,is,si))
						  .setterm2(Bracket(p3,p1,p2), Bracket(p2,is,si))
						  .setterm1(Bracket(p4,p1,p2), Bracket(p1,is,si)), flag=true;
						eliminators.push_back(poly);
					}
					if(std::fabs(bra3)<=eps) {
						Polynomial poly;
						poly.setmain(Bracket(p,is,si))
						  .setterm1(Bracket(p1,p2,is), Bracket(p3,p4,si))
						  .setterm2(Bracket(p1,p2,si), Bracket(p3,p4,is)), flag=true;
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
								poly.setmain(Bracket(p,is,si))
								  .setterm1(Bracket(ai1,aj1,aj2), Bracket(ai2,ak1,ak2))
								  .setterm2(Bracket(ai2,aj1,aj2), Bracket(ai1,ak1,ak2));
								eliminators.push_back(poly);
							}
						} while(std::next_permutation(psig.begin(),psig.end()));
					}
				}
			}
			conlist.erase(std::find(conlist.begin(),conlist.end(),p));
			return (*this);
		}

		public: void qed(Polynomial conc) {
			while(!callbacks.empty()) callbacks.back()(*this), callbacks.pop_back();
			for(auto& is: eliminators) std::cout << is.dump() << "\\\\\n";
			conc.eliminate(eliminators);
			return ;
		}

		public: static inline quotype bracket(Point p1, Point p2, Point p3) {
			return Point::bracket(p1,p2,p3);
		}
		public: static std::string minidump(Point p1, Point p2, Point p3) {
			if(std::fabs(Point::bracket(p1,p2,p3))<=eps) return "0";
			else										 return Point::bradump(p1,p2,p3);
		}
	};
};
