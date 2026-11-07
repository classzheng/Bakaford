/******************************************************************************
 * Bakaford/Drofakab Equation Solver (D.E.S): Inverse ⑨                       *
 * @Author: classzheng@github                                                 *
 * @Date: 2026.11.07 (latest upd)                                             *
 * @Reference: https://classzheng.github.io/                                  *
 * @Modules: { Bakaford::Drofakab }                                           *
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
	std::uniform_real_distribution<realtype> dist(0.L, 1.L);
	const realtype eps=1e-7;
	
	namespace Transcendentalize {
	  // Ensure the Linear Independence of each coordinate, cf. https://classzheng.github.io/ (placeholder currently)
	  	[[nodiscard]] inline realtype precision(const realtype s, const realtype e=eps) {
	  		return std::round(s/e)*e;
	  	}
	  	[[nodiscard]] realtype shorten(realtype s) {
	  		while(std::fabs(s)>=1.L) s/=10.L;
	  		return s;
	  	}
		[[nodiscard]] realtype pi_basis(const realtype &d) {
			static realtype pi_power=0;
			return shorten(std::pow(M_PI,pi_power++)*precision(d));
		}
		[[nodiscard]] realtype e_basis(const realtype &d) {
			static realtype e_power=0;
			return shorten(std::pow(M_E,e_power++)*precision(d));
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
	
	template<typename Type> class Quantity {
		public: int prior;
		public: Type data;
		public: std::string desc;
		public: Quantity(void) = default;
		public: Quantity(const Quantity<Type>& q) : data(q.data), desc(q.desc) {}
		public: Quantity(Type da, std::string de, int pr=2): data(da), desc(de), prior(pr) {}
		public: ~Quantity(void) = default;
		public: Quantity operator+ (const Quantity<Type> q) const {
			return Quantity(data+q.data, desc+"+"+q.desc,0);
		}
		public: Quantity operator- (const Quantity<Type> q) const {
			return Quantity(data-q.data, desc+"-"+q.desc,0);
		}
		public: Quantity operator* (const Quantity<Type> q) {
			std::string d1, d2;
			if(prior<1) d1="("+desc+")";
			else		d1=desc;
			if(q.prior<1) d2="("+q.desc+")";
			else		  d2=q.desc;
			return Quantity(data*q.data, d1+"*"+d2,1);
		}
		public: Quantity operator/ (const Quantity<Type> q) {
			std::string d1, d2;
			if(prior<1) d1="("+desc+")";
			else		d1=desc;
			if(q.prior<1) d2="("+q.desc+")";
			else		  d2=q.desc;
			return Quantity(data/q.data, d1+"/"+d2,1);
		}
		public: Quantity operator^ (const Quantity<Type> q) {
			std::string d1, d2;
			if(prior<2) d1="("+desc+")";
			else		d1=desc;
			if(q.prior<2) d2="("+q.desc+")";
			else		  d2=q.desc;
			return Quantity(std::pow(data,q.data), d1+"^"+d2,2);
		}
		public: Quantity sqr(void) const {
			std::string d;
			if(prior<2) d="("+desc+")";
			else		d=desc;
			return Quantity(data*data, d+"^2",2);
		}
		public: Quantity sqrt(void) const {
			return Quantity(std::sqrt(data), "sqrt("+desc+")",2);
		}
	};

	template<typename Type=realtype> class Drofakab {
		public: Container<std::function<Quantity<Type>(Quantity<Type>,Quantity<Type>)>> patternadd;
		public: Container<std::function<Quantity<Type>(Quantity<Type>,Quantity<Type>)>> patternprod;
		public: Container<Quantity<Type>> addits;
		public: Container<Quantity<Type>> coefs;
		public: Drofakab(void) = default;
		public: ~Drofakab(void) = default;
		public: Quantity<Type> run(Quantity<Type> q, Quantity<Type> q0, const realtype t0, const realtype cdcoef) {
			Quantity<Type> qnew=q0, qbest=q0;
			static std::function<realtype(Quantity<Type>,Quantity<Type>)> energy=[](Quantity<Type> qcur, Quantity<Type> qtarg)->realtype {
				return std::fabs((qcur-qtarg).data);
			};
			realtype temperature=t0;
			realtype bestenergy=energy(qbest,q);
			do {
				Container<Quantity<Type>> qnexts;
				Container<realtype> nextprob;
				for(auto& pat:patternadd) {
					for(auto& is:addits) {
						qnexts.push_back(pat(qnew,is));
					}
				}
				for(auto& pat:patternprod) {
					for(auto& is:coefs) {
						qnexts.push_back(pat(qnew,is));
					}
				}
				realtype curenergy=energy(qnew,q);
				for(auto& is:qnexts) {
					addits.push_back(is);
					coefs.push_back(is);
					realtype nextenergy=energy(is,q);
					if(nextenergy-bestenergy<eps) {
						qbest=is;
						bestenergy=nextenergy;
					}
					realtype delta=nextenergy-curenergy;
					if(delta<=eps) nextprob.push_back(1.L);
					else 		   nextprob.push_back(std::exp(-delta/temperature));
				}
				realtype probsum=0;
				for(auto& prob:nextprob) probsum+=prob;
				if(probsum>eps) {
					realtype prob=dist(rng)*probsum;
					for(int i=0;i<nextprob.size();++i) {
						prob-=nextprob[i];
						if(prob<=eps) {
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
			} while(temperature>=eps);  // Simulated Annealing
			return qbest;
		}
	};
};
