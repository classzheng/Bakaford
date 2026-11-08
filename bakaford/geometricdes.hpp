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
	template<typename Type=realtype> class Point {
		public: coord data;
		public: Point(void): data(coord(Transcendentalize::pi_basis(dist(rng)),Transcendentalize::pi_basis(dist(rng))))
				 {} // Freepoint
		public: Point(coord dt): data(dt) {}
		public: Point(Type c1, Type c2): data(coord(c1,c2)) {}
		public: ~Point(void) = default;
		public: Point operator+(const Point& r) {
			return Point(data+r.data);
		}
		public: Point operator-(const Point& r) {
			return Point(data-r.data);
		}
		public: Point operator*(const Type& s) {
			return Point(data*s);
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
	};
};
