#include <bits/stdc++.h>
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
	std::uniform_real_distribution<realtype> dist(-1.L, 1.L);
	const realtype eps=1e-7;
	
	template<typename Type> class IcyVector {  // Implementation of trivial vectors
		public: std::vector<Type> vec;
		public: IcyVector(void) = default;
		public: ~IcyVector(void) = default;
		public: IcyVector(const int n, const Type init=Type{}): vec(std::vector<Type>(n,init)) {}
		public: IcyVector(const std::vector<Type> v): vec(v) {}
		public: IcyVector& operator=(const std::vector<Type> v) {
			vec=v;
			return (*this);
		}
		public: IcyVector& operator=(const IcyVector v) {
			vec=v.vec;
			return (*this);
		}
	
		public: Type l1norm(void) const {
			Type norm=Type(0);
			for(const auto& is: vec) norm=norm+std::abs(is);
			return norm;
		}
	
		public: Type l2norm(void) const {
			Type norm=Type(0);
			for(const auto& is: vec) norm=norm+is*is;
			return norm;
		}
	
		public: Type dot(const IcyVector<Type> &rhs) const {
			Type norm=Type(0);
			const int size=std::min(vec.size(),rhs.vec.size());
	
			for(int i = 0; i < size; i++) {
				norm=norm+vec[i]*rhs.vec[i];
			}
	
			return norm;
		}
	
		public: const std::function<Type(void)> abs =
				[this](void)->Type {
			return l2norm();
		};
		
		// Vector operations
		public: IcyVector<Type> operator+ (const IcyVector<Type> &rhs) {
			IcyVector<Type> sum(std::max((*this).vec.size(),rhs.vec.size()),Type(0));  // Left align
			if((*this).vec.size()>=rhs.vec.size()) {
				sum.vec=(*this).vec;
				for(int i = 0; i < rhs.vec.size(); i++) {
					sum.vec[i]=sum.vec[i]+rhs.vec[i];
				}
			} else {
				sum.vec=rhs.vec;
				for(int i = 0; i < (*this).vec.size(); i++) {
					sum.vec[i]=sum.vec[i]+(*this).vec[i];
				}
			}
			return sum;
		}
		public: IcyVector<Type> operator- (const IcyVector<Type> &rhs) {
			IcyVector<Type> diff(std::max((*this).vec.size(),rhs.vec.size()),Type(0));  // Left align
			if((*this).vec.size()>=rhs.vec.size()) {
				diff.vec=(*this).vec;
				for(int i = 0; i < rhs.vec.size(); i++) {
					diff.vec[i]=diff.vec[i]-rhs.vec[i];
				}
			} else {
				diff.vec=rhs.vec;
				for(int i = 0; i < (*this).vec.size(); i++) {
					diff.vec[i]=diff.vec[i]-(*this).vec[i];
				}
			}
			return diff;
		}
		public: IcyVector<Type> operator* (const IcyVector<Type> &rhs) {
			IcyVector<Type> prod(std::max((*this).vec.size(),rhs.vec.size()),Type(0));  // Left align
			if((*this).vec.size()>=rhs.vec.size()) {
				prod.vec=(*this).vec;
				for(int i = 0; i < rhs.vec.size(); i++) {
					prod.vec[i]=prod.vec[i]*rhs.vec[i];
				}
			} else {
				prod.vec=rhs.vec;
				for(int i = 0; i < (*this).vec.size(); i++) {
					prod.vec[i]=prod.vec[i]*(*this).vec[i];
				}
			}
			return prod;
		}
		public: IcyVector<Type> operator* (const Type &rhs) {
			IcyVector<Type> prod((*this).vec);
			for(auto& is: prod.vec) is*=rhs;
			return prod;
		}

		// Comparison methods
		public: inline bool operator< (const IcyVector<Type> &rhs) const {
			return (*this).l2norm() < rhs.l2norm();
		}
		public: inline bool operator> (const IcyVector<Type> &rhs) const {
			return (*this).l2norm() > rhs.l2norm();
		}
		public: inline bool operator<= (const IcyVector<Type> &rhs) const {
			return (*this).l2norm() <= rhs.l2norm();
		}
		public: inline bool operator>= (const IcyVector<Type> &rhs) const {
			return (*this).l2norm() >= rhs.l2norm();
		}
		
		public: inline bool operator<< (const IcyVector<Type> &rhs) const {
			return (*this).l1norm() < rhs.l1norm();
		}
		public: inline bool operator>> (const IcyVector<Type> &rhs) const {
			return (*this).l1norm() > rhs.l1norm();
		}
		public: inline bool operator<<= (const IcyVector<Type> &rhs) const {
			return (*this).l1norm() <= rhs.l1norm();
		}
		public: inline bool operator>>= (const IcyVector<Type> &rhs) const {
			return (*this).l1norm() >= rhs.l1norm();
		}
		
		public: inline bool operator== (const IcyVector<Type> &rhs) const {
			return (*this).vec == rhs.vec;
		}
	};

	template<typename Type> class LatticeBasis {
		public: std::vector<IcyVector<Type>> basis;
		public: std::vector<IcyVector<Type>> gsedvec;
		public: std::function<Type(unsigned,unsigned)> mu =
		  [&](unsigned i, unsigned j)->Type {
			if(i >= basis.size() || j >= gsedvec.size()) return Type(0);
			IcyVector<Type> &u=gsedvec[j];
			IcyVector<Type> &v=basis[i];
			return (v.dot(u))/u.l2norm();
		};
		public: LatticeBasis(void) = default;
		public: ~LatticeBasis(void) = default;
		public: void gram_schmidt(void) {
			const int size=basis.size();
			if(size == 0) return;
			gsedvec.assign(size, IcyVector<Type>(basis[0].vec.size(), Type(0)));
			for(int k = 0; k < size; k++) {
				gsedvec[k]=basis[k];
				for(int i = 1; i <= k; i++) {
					gsedvec[k]=gsedvec[k]-gsedvec[k-i]*mu(k,k-i);
				}
			}
			return ;
		}
		public: void reduce(const Type& delta=Type{.75L}) {
			const int size=basis.size();
			if(size <= 1) return;
			gram_schmidt();
			for(int k = 1; k < size; ) {
				for(int j = k-1; j >= 0; j--) {
					if(std::fabs(mu(k,j)) > .5L) {
						int q=std::round(mu(k,j));
						basis[k]=basis[k]-basis[j]*q;
						gram_schmidt();
					}
				}
				if(basis[k].l2norm()>=(delta-mu(k,k-1)*mu(k,k-1))*basis[k-1].l2norm()) {  // Lovasz condition
					k++;
				} else {
					std::swap(basis[k], basis[k-1]);
					gram_schmidt();
					k=std::max(k-1,1);
				}
			}
			return ;
		}
	};

	template<typename Type=realtype> class Ramanubin {
		public: std::vector<Type> sequence;
		public: LatticeBasis<Type> latbasis;
		public: Type precision=1e6L;
		public: Type delta=.75L;
		public: Ramanubin(void) = default;
		public: ~Ramanubin(void) = default;
		public: void allocate(const std::vector<realtype>& seq) {
			sequence=std::move(seq);
		    latbasis.basis.clear();
		    for(int i = 0; i < sequence.size(); i++){
		        Bakaford::IcyVector<long double> v(sequence.size()+1,0.L);
		        v.vec[i]=1.L;
		        v.vec[sequence.size()]=std::floor(precision * sequence[i]);
		        latbasis.basis.push_back(v);
		    }
			return ;
		}
		public: Ramanubin& push(IcyVector<Type> v) {
			latbasis.basis.push(v);
			return (*this);
		}
		public: void clear(void) {
			latbasis.basis.clear();
			return ;
		}
		public: [[nodiscard]] std::vector<Type> run(void) {
	    	latbasis.reduce(delta);
			return latbasis.basis[0].vec;
		}
		public: [[nodiscard]] inline Type residual(void) const {
			return latbasis.basis[0].vec[sequence.size()]/precision;
		}
	};
};
