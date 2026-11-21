/******************************************************************************
 * Bakaford/Geometric Drofakab Equation Solver: Inverse ⑨                     *
 * @Author: classzheng@github                                                 *
 * @Date: 2026.10.17 (latest upd)                                             *
 * @Reference: https://classzheng.github.io/                                  *
 * @Modules: { Bakaford::Drofakab }                                           *
 ******************************************************************************/

#include "des.hpp"

// #pragma once
#pragma GCC optimize (2)
namespace Bakaford {
	std::uniform_real_distribution<realtype> distuni(-1.L, 1.L);
	std::uniform_real_distribution<realtype> distpos(0.L, 1.L);
	std::uniform_real_distribution<realtype> distneg(-1.L, 0.L);
	
	template<typename> class Point;
	template<typename> class Line;
	template<typename> class Circle;
	
	template<typename Type=realtype> class Point {
		public: std::complex<Type> data;
		public: Point(void): data(coord(Transcendentalize::pi_basis(dist(rng)),Transcendentalize::pi_basis(dist(rng))))
				 {} // Freepoint
		public: Point(std::complex<Type> dt): data(dt) {}
		public: Point(Type c1, Type c2): data(coord(c1,c2)) {}
		public: ~Point(void) = default;
		public: Point<Type> operator+(const Point<Type>& r) {
			return Point(data+r.data);
		}
		public: Point<Type> operator-(const Point<Type>& r) {
			return Point(data-r.data);
		}
		public: Point<Type> operator*(const Type& s) const {
		    return Point<Type>(data*s);
		}
		public: friend Point<Type> operator*(const Type& s, const Point<Type>& p) {
		    return p*s;
		}
		public: Point<Type> foot(const Line<Type>& cf) {
			std::complex<realtype> d=cf.qnt.data-cf.pnt.data, v=data-cf.pnt.data;
		    realtype t=(v.real()*d.real()+v.imag()*d.imag())/std::norm(d);
		    return Point<realtype>(cf.pnt.data+t*d);
		}
	};
	template<typename Type=realtype> class Line {
		public: Point<Type> pnt, qnt;
		public: Line(void)=default;
		public: Line(Point<Type> p1, Point<Type> p2): pnt(p1), qnt(p2) {}
		public: ~Line(void) = default;
		public: Point<Type> semifreepoint(void) {
			Type cf=dist(rng);
			return cf*pnt+(1.L-cf)*qnt;
		}
		public: Point<Type> pointonline(const Type& cf) {
			return cf*pnt+(1.L-cf)*qnt;
		}
		public: Point<Type> intersection(const Line<Type>& l);
		public: Point<Type> intersection(const Circle<Type>& l);
	};
	template<typename Type=realtype> class Circle {
		public: Point<Type> pnt, qnt;
		public: Circle(void)=default;
		public: Circle(Point<Type> p1, Point<Type> p2): pnt(p1), qnt(p2) {}
		public: ~Circle(void) = default;
		public: Point<Type> semifreepoint(void) {
			return pointonarc(Type{dist(rng)});
		}
		public: Point<Type> pointonarc(const Type& cf) {
		    Type radius=std::abs(qnt.data-pnt.data);
		    Type angle=2.L*std::acos(-1.L)*cf;
		    return Point<Type>(pnt.data+std::polar<Type>(radius,angle));
		}
		public: Point<Type> intersection(const Line<Type>& l) const {
			return l.intersection(*this);
		}
		public: Point<Type> intersection(const Circle<Type>& l, const bool inj=false);
	};
	
	template<typename Type> Type crossprod(const std::complex<Type>& a, const std::complex<Type>& b) {
	    return a.real()*b.imag()-a.imag()*b.real();
	}
	
	template<typename Type> Type dotprod(const std::complex<Type>& a, const std::complex<Type>& b) {
	    return a.real()*b.real()+a.imag()*b.imag();
	}
	
	template<typename Type> Point<Type> Line<Type>::intersection(const Line<Type>& l) {
	    std::complex<Type> r=qnt.data-pnt.data, s=l.qnt.data-l.pnt.data;
	    Type t=crossprod(l.pnt.data-pnt.data,s)/crossprod(r,s);
	    return Point<Type>(pnt.data+t*r);
	}
	
	template<typename Type> Point<Type> Line<Type>::intersection(const Circle<Type>& l) {
	    std::complex<Type> d=qnt.data-pnt.data, f=pnt.data-l.pnt.data;
	    Type a=dotprod(d,d), b=2.L*dotprod(f,d);
	    Type c=dotprod(f,f)-std::pow(std::abs(l.qnt.data-l.pnt.data),2);
	    Type t=(-b+std::sqrt(b*b-4.L*a*c))/(2.L*a);
	    return Point<Type>(pnt.data+t*d);
	}
	
	template<typename Type> Point<Type> Circle<Type>::intersection(const Circle<Type>& l, const bool inj) {
	    std::complex<Type> d=l.pnt.data-pnt.data;
	    Type r0=std::abs(qnt.data-pnt.data), r1=std::abs(l.qnt.data-l.pnt.data);
	    Type len=std::abs(d);
	    Type a=(r0*r0-r1*r1+len*len)/(2.L*len);
	    Type h=std::sqrt(r0*r0-a*a);
	    std::complex<Type> base=pnt.data+d*(a/len);
	    std::complex<Type> off(-d.imag()*h/len,d.real()*h/len);
	    Point<Type> p1(base+off), p2(base-off);
	    if(inj) return p1;
	    else    return p2;
	}  // Written by Github Copilot.

	template<typename Type=realtype> class GeoDrofakab {
		public: Container<Container<std::function<Quantity<Type>(Quantity<Type>,Quantity<Type>)>>> patterns;
		public: Container<Container<Quantity<Type>>> constants;
		public: GeoDrofakab(void): patterns(Container<Container<std::function<Quantity<Type>(Quantity<Type>,Quantity<Type>)>>>(2)),
								   constants(Container<Container<Quantity<Type>>>(2)) {}
		public: ~GeoDrofakab(void) = default;
		public: inline GeoDrofakab<Type>& loadpattern(void) {
		    this->patterns[0].push_back(
		        [](Quantity<realtype> value, Quantity<realtype> constant) {
		            return value + constant;
		        }
		    );

		    this->patterns[0].push_back(
		        [](Quantity<realtype> value, Quantity<realtype> constant) {
		            return value - constant;
		        }
		    );

		    this->patterns[1].push_back(
		        [](Quantity<realtype> value, Quantity<realtype> constant) {
		            return value * constant;
		        }
		    );

		    this->patterns[1].push_back(
		        [](Quantity<realtype> value, Quantity<realtype> constant) {
		            return value / constant;
		        }
		    );

		    this->patterns[2].push_back(
		        [](Quantity<realtype> value, [[maybe_unused]] Quantity<realtype> constant) {
		            return value.sqr();
		        }
		    );

		    this->patterns[2].push_back(
		        [](Quantity<realtype> value, [[maybe_unused]] Quantity<realtype> constant) {
		            return value.sqrt();
		        }
		    );
		    return *this;
		}
		public: Quantity<Type> run(Quantity<Type> q, Quantity<Type> q0,
								   const realtype t0, const realtype cdcoef, const realtype expecteps,
								   const unsigned maxepoch=0) {
			Quantity<Type> qnew=q0, qbest=q0;
			static std::function<realtype(Quantity<Type>,Quantity<Type>)> energy=[](Quantity<Type> qcur, Quantity<Type> qtarg)->realtype {
				return std::fabs((qcur-qtarg).data)+qcur.desc.length();
				  // The length of the expression must not be too long.
			};
			realtype temperature=t0;
			realtype bestenergy=energy(qbest,q);
			do {
				Container<Quantity<Type>> qnexts;
				Container<realtype> nextprob;
				for(int i = 0; i < patterns.size(); i++) {
					for(auto& pat:patterns[i]) {
						for(auto& is:constants[i]) {
							qnexts.push_back(pat(qnew,is));
						}
					}
				}
				realtype curenergy=energy(qnew,q);
				for(auto& is:qnexts) {
					for(auto& ct:constants) {
						ct.push_back(is);
					}
					realtype nextenergy=energy(is,q);
					if(nextenergy-bestenergy<expecteps) {
						qbest=is;
						bestenergy=nextenergy;
					}
					realtype delta=nextenergy-curenergy;
					if(delta<=expecteps) nextprob.push_back(1.L);
					else 		   		 nextprob.push_back(std::exp(-delta/temperature));
				}
				realtype probsum=0;
				for(auto& prob:nextprob) probsum+=prob;
				if(probsum>eps) {
					realtype prob=dist(rng)*probsum;
					for(int i=0;i<nextprob.size();++i) {
						prob-=nextprob[i];
						if(prob<=expecteps) {
							qnew=qnexts[i];
							break;
						}
					}
				}
				if(energy(qnew,q)<bestenergy) {
					qbest=qnew;
					bestenergy=energy(qnew,q);
				}
				temperature*=cdcoef;
			} while(temperature>=expecteps);  // Simulated Annealing
			if(bestenergy<=expecteps||maxepoch==0) return qbest;
			else					  			   return (*this).run(q,q0,t0,cdcoef,expecteps,maxepoch-1);  // Search the better solution
		}
	};
};
