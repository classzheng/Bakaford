/******************************************************************************
 * Bakaford/TemplateUniverse: The implementation of HoTT based on TMP.		  *
 * @Author: classzheng@github                                                 *
 * @Date: 2026.9.30 (latest upd)                                              *
 * @Modules: { Bakaford::TemplateUniverse }                                   *
 ******************************************************************************/

#include <iostream>
#include <functional>
#include <string>
#include <memory>
#include <variant>

#if __cplusplus<=202000L
#	pragma message("Request C++ 20.")
#endif

#pragma once
#pragma GCC optimize (2)

namespace Bakaford {
	namespace TemplateUniverse {
	  // Unit Types
		class G0 {
			public: G0(void) = default;
			public: static G0 con(void) {
				return G0();
			}
			public: ~G0(void) = default;
			public: inline std::string what(void) {
				return "G0";
			}
		};
		class G1 {
			public: G1(void) = default;
			public: static G1 con(void) {
				return G1();
			}
			public: ~G1(void) = default;
			public: inline std::string what(void) {
				return "G1";
			}
		} star;  // \star:\mathbf1
		
	  // Universe
	  	template<typename inst>
	  	class UniverseOf {
	  		public: UniverseOf(void) = default;
			public: static UniverseOf<inst> con(void) {
				return UniverseOf<inst>();
			}
	  		public: ~UniverseOf(void) = default;
			public: inline std::string what(void) {
				return "UniverseOf<"+inst().what()+">";
			}
			public: template<typename nt> inline bool iselement(nt s) const {
				return std::is_same<inst,nt>::value;
			}
			public: static constexpr auto subclass=inst::con;
	  	};
	  	
	  	template<typename i1, typename i2>
	  	class Projection {
	  		public: std::function<i2(i1)> func;
	  		public: Projection(void) = default;
			public: static Projection<i1,i2> con(void) {
				return Projection<i1,i2>();
			}
	  		public: Projection(std::function<i2(i1)> f): func(f) {}
			public: static Projection<i1,i2> con(std::function<i2(i1)> f) {
				return Projection<i1,i2>(f);
			}
	  		public: ~Projection(void) = default;
			public: inline std::string what(void) {
				return "Projection<"+i1().what()+i2().what()+">";
			}
			public: inline i2 operator() (i1& r) {
				return func(r);
			}
	  	};
	  	
	  	template<typename i1, typename i2, typename ut=G0>
	  	class Product {
	  		public: i1 fst;
	  		public: i2 snd;
	  		
	  		public: Product(void) = default;
			public: static Product<i1,i2> con(void) {
				return Product<i1,i2>();
			}
	  		public: Product(i1 f, i2 s): fst(f), snd(s) {}
			public: static Product<i1,i2> con(i1 f, i2 s) {
				return Product<i1,i2>(f,s);
			}
	  		public: ~Product(void) = default;
			public: inline std::string what(void) {
				return "Product<"+i1().what()+","+i2().what()+">";
			}
			public: template <typename rs> inline rs reductor(Projection<i1,Projection<i2,rs>> f) {
			    return f(fst)(snd);
			}
			public:
			inline UniverseOf<ut> inductor(Projection<Product<i1, i2>, UniverseOf<ut>> f) {
			    return f(Product<i1, i2>(fst, snd));
			}
	  	};
	  	
	  	template<typename i1, typename i2, typename ut=G0>
	  	class Coproduct {
	  		public: bool proj;
	  		public: std::variant<i1,i2> inst;
	  		public: static Coproduct<i1,i2,ut> inl(i1 i) {
	  			return Coproduct<i1,i2,ut>(i,false);
	  		}
	  		public: static Coproduct<i1,i2,ut> inr(i2 i) {
	  			return Coproduct<i1,i2,ut>(i,true);
	  		}
	  		public: Coproduct(void) = default;
			public: static Coproduct<i1,i2> con(void) {
				return Coproduct<i1,i2>();
			}
	  		public: Coproduct(std::variant<i1,i2> i, bool p): inst(i), proj(p) {}
			public: static Coproduct<i1,i2> con(std::variant<i1,i2> i, bool p) {
				return Product<i1,i2>(i,p);
			}
	  		public: ~Coproduct(void) = default;
			public: inline std::string what(void) {
				return "Coproduct<"+i1().what()+","+i2().what()+">";
			}
			public: template <typename rs> 
			inline rs recursor(Projection<i1,rs> g0, Projection<i2,rs> g1) const {
				if(!proj) return g0(std::get<i1>(inst));
				if(proj)  return g1(std::get<i2>(inst));
			}
	  	};
		
	  	class Nat {
	  		public: std::shared_ptr<Nat> pred;
			public: static Projection<Nat,Nat> successor;
	  		public: Nat(std::shared_ptr<Nat> p=nullptr): pred(p) {}  // Zero
			public: static Nat con(std::shared_ptr<Nat> p=nullptr) {
				return Nat(p);
			}
	  		public: ~Nat(void) = default;
	  		public: inline Nat succ(void) {
	  			return Nat(std::make_shared<Nat>(*this));
	  		}
	  		public: int integer(void) {
	  			int itg=0;
	  			std::shared_ptr<Nat> current=pred;
	  			while(current!=nullptr) current=current->pred, itg++;
	  			return itg;
	  		}
	  		public: Nat church(Projection<Nat,Nat> cf, Nat cs) {
	  			std::shared_ptr<Nat> current=pred;
	  			Nat ret=cs;
	  			while(current!=nullptr) current=current->pred, ret=cf(ret);
	  			return ret;
	  		}
	  		public: Projection<Nat,Nat> churchnum(void) {
	  			Projection<Nat,Nat> cn([&](Nat n)->Nat{return (*this).church(Nat::successor,n);});
	  			return cn;
	  		}
			public: inline std::string what(void) {
				return "Nat";
			}
			public: Nat operator+ (Nat &rhs) {
				return (*this).church(Nat::successor,rhs);
			}
			public: Nat operator* (Nat &rhs) {
				return (*this).church(rhs.churchnum(),Nat{});
			}
	  	};
	  	Projection<Nat,Nat> Nat::successor([](Nat n)->Nat{return n.succ();});

	  	template<template<typename> class r, typename ut = G0>
	  	class Mu {  // Recursion type
	  		public: using self=Mu<r,ut>;
	  		public: std::shared_ptr<r<self>> inst;
	  		public: Mu(void) = default;
	  		public: static Mu con(void) {
	  			return Mu();
	  		}
	  		public: Mu(std::shared_ptr<r<self>> p): inst(std::move(p)) {}
  		    public: static Mu con(std::shared_ptr<r<self>> p) {
  		    	return Mu(p);
  		    }
	  		public: ~Mu(void) = default;
  		    public: static Mu fold(const r<self> &v) {
  		    	return Mu(std::make_shared<r<self>>(v));
  		    }
  		    public: r<self> &unfold(void) const {
  		    	return *inst;
  		    }
  		    public: inline std::string what() const {
  		    	return "Mu<"+r<self>().what()+","+ut().what()+">";
  		    }
	  	};
  	};

  	namespace Shortcuts {
  		using namespace TemplateUniverse;
  		using g0=G0;
  		using g1=G1;
  		template<typename p> using uni=UniverseOf<p>;
  		template<typename p, typename q> using proj=Projection<p,q>;
  		template<typename p, typename q> using prod=Product<p,q>;
  		template<typename p, typename q> using coprod=Coproduct<p,q>;
  		using nat=Nat;
  	};
};
