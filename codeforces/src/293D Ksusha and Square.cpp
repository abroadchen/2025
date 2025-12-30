/**
* Cntri, Cntle, Cnthi, Cntlo: 计数器，分别记录右侧、左侧、上方、下方的点数
Cnty[]: 统计每个y坐标上的点数
Cntx[]: 统计每个x坐标上的点数
*p[]: 存储输入的点
Highest: 最高点，初始为(0,-INF)
Lowest: 最低点，初始为(0,INF)
Leftest: 最左点，初始为(INF,0)
Rightest: 最右点，初始为(-INF,0)
 *
 *分别存储左侧、右侧、上方、下方的点集合
 */
#include <iostream>
#include <cmath>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
using namespace std;


struct Point {
	int x, y;
	Point () : x(0), y(0) {}
	Point ( const int _x, const int _y ): x ( _x ), y ( _y ) {}
	void Input () { scanf ( "%d %d", &x, &y ); }
	void Print () const { printf ( "( %d, %d )", x, y ); }
	Point Symmetric () { return { y, x }; }
	friend bool operator != ( const Point p, const Point q ) { return p.x ^ q.x || p.y ^ q.y; }
};

constexpr int MAXN = 1e5, INF = 0x3f3f3f3f, MAXX = 1e6, EPS = 1e-7;
int n, Cntri, Cntle, Cnthi, Cntlo, Cnty[2 * MAXX + 5] = {}, Cntx[2 * MAXX + 5] = {};
Point p[MAXN + 5] = {}, Highest ( 0, -INF ), Lowest ( 0, INF ), Leftest ( INF, 0 ), Rightest ( -INF, 0 );
Point LeftP[MAXN + 5] = {}, RightP[MAXN + 5] = {}, HighP[MAXN + 5] = {}, LowP[MAXN + 5] = {};

inline bool Cmp1 ( const Point p, const Point q ) {
	return p.x < q.x;
}

inline bool Cmp2 ( const Point p, const Point q ) {
	return p.y > q.y;
}
//判断三点是否共线
inline bool Collinear ( const Point p, const Point q, const Point r ) {
	if ( p.x == q.x ) return p.x == r.x;
	if ( p.x == r.x ) return p.x == q.x;
	return 1LL * ( p.y - q.y ) * ( p.x - r.x ) == 1LL * ( p.y - r.y ) * ( p.x - q.x );
}

template<typename _T>
_T Abs ( const _T x ) { return x < 0 ? -x : x; }

template<class _T>
void Swap ( _T& a, _T& b ) { _T t = a; a = b, b = t; }

inline int Indx ( const int x ) { return x + MAXX; }//将坐标值映射到非负索引
//判断点p是否在从_dn到_up方向的左侧
inline bool LeftCheck ( const Point p, Point _up, Point _dn ) {
	if ( _up.y < _dn.y ) Swap ( _up, _dn );
	if ( _up.x == _dn.x ) return p.x < _up.x;
	if ( p.x == _dn.x ) return ! ( ( _up.y - _dn.y >= 0 ) ^ ( _up.x - _dn.x >= 0 ) );
	if ( p.x == _up.x ) return ( _up.y - _dn.y >= 0 ) ^ ( _up.x - _dn.x >= 0 );
	if ( ( _up.y - _dn.y >= 0 ) ^ ( _up.x - _dn.x >= 0 ) ) {
		return 1LL * ( p.y - _dn.y ) * ( _up.x - _dn.x ) > 1LL * ( _up.y - _dn.y ) * ( p.x - _dn.x );
	}
	return ( ( p.y - _dn.y >= 0 ) ^ ( p.x - _dn.x >= 0 ) )
	       || 1LL * ( p.y - _dn.y ) * ( _up.x - _dn.x ) > 1LL * ( _up.y - _dn.y ) * ( p.x - _dn.x );
}

///该函数统计每个y坐标值上的点数
///将点分为左右两部分，分别处理
///计算每条水平线上包含的整数点数量
inline void PrepareX () {
	// 将点分为左右两部分
	for (int i = 1; i <= n; ++ i ) {
		if ( p[i] != Highest && p[i] != Lowest ) {
			if ( ! LeftCheck ( p[i], Highest, Lowest ) ) {
				RightP[++ Cntri] = p[i];
			} else {
				LeftP[++ Cntle] = p[i];
			}
		}
	}
	//排序并处理边界点
	int rupper = 1, lupper = 1;
	sort ( RightP + 1, RightP + Cntri + 1, Cmp2 ), sort ( LeftP + 1, LeftP + Cntle + 1, Cmp2 );
	if ( ! Cntri || RightP[1].y ^ Highest.y ) RightP[--rupper] = Highest;
	if ( ! Cntle || LeftP[1].y ^ Highest.y ) LeftP[--lupper] = Highest;
	if ( RightP[Cntri].y ^ Lowest.y ) RightP[++Cntri] = Lowest;
	if ( LeftP[Cntle].y ^ Lowest.y ) LeftP[++Cntle] = Lowest;
	//计算每个y坐标上的点数
	for (int y = Highest.y - 1; y > Lowest.y; -- y ) {
		//更新左右边界
		if ( y < RightP[rupper + 1].y ) ++rupper;
		if ( y < LeftP[lupper + 1].y ) ++lupper;
		//计算左边界x坐标
		Point _up = LeftP[lupper], _dn = LeftP[lupper + 1];
		int lx = 0, rx = 0, Choice[5] = {}; double JuncX;
		if ( _up.x == _dn.x ) {
			lx = ceil ( _up.x );
		} else if ( y == _dn.y ) {
			lx = _dn.x;
		} else {
			JuncX = 1.0 * ( _up.x - _dn.x )
						* ( y - _dn.y + 1.0 * ( _up.y - _dn.y ) * _dn.x / ( _up.x - _dn.x ) ) / ( _up.y - _dn.y );
			Choice[2] = ( Choice[1] = floor ( JuncX ) - 1 ) + 1, Choice[4] = ( Choice[3] = ceil ( JuncX ) ) + 1;
			for (int i = 1; i <= 4; ++ i ) {
				if ( Collinear ( { Choice[i], y }, _up, _dn ) ) {
					lx = Choice[i];
					break;
				}
				if ( ! LeftCheck ( { Choice[i], y }, _up, _dn ) ) {
					lx = Choice[i];
					break;
				}
			}
		}
		//计算右边界x坐标
		_up = RightP[rupper], _dn = RightP[rupper + 1];
		if ( _up.x == _dn.x ) {
			rx = floor ( _up.x );
		} else if ( y == _dn.y ) {
			rx = _dn.x;
		} else {
			JuncX = 1.0 * ( _up.x - _dn.x )
						* ( y - _dn.y + 1.0 * ( _up.y - _dn.y ) * _dn.x / ( _up.x - _dn.x ) ) / ( _up.y - _dn.y );
			Choice[2] = ( Choice[1] = ceil ( JuncX ) + 1 ) - 1, Choice[4] = ( Choice[3] = floor ( JuncX ) ) - 1;
			for (int i = 1; i <= 4; ++i) {
				if ( Collinear ( { Choice[i], y }, _up, _dn ) ) {
					rx = Choice[i];
					break;
				} else if ( LeftCheck ( { Choice[i], y }, _up, _dn ) ) {
					rx = Choice[i];
					break;
				}
			}
		}
		Cnty[Indx ( y )] = rx - lx + 1;
	}
}

inline void PrepareY () {
	for (int i = 1; i <= n; ++ i ) {
		if ( p[i] != Leftest && p[i] != Rightest ) {
			if ( LeftCheck ( p[i].Symmetric (), Rightest.Symmetric (), Leftest.Symmetric () ) ) {
				LowP[++ Cntlo] = p[i];
			} else {
				HighP[++ Cnthi] = p[i];
			}
		}
	}
	int uleft = 1, dleft = 1;
	sort ( HighP + 1, HighP + Cnthi + 1, Cmp1 ), sort ( LowP + 1, LowP + Cntlo + 1, Cmp1 );
	if ( ! Cnthi || HighP[1].x ^ Leftest.x ) HighP[-- uleft] = Leftest;
	if ( ! Cntlo || LowP[1].x ^ Leftest.x ) LowP[-- dleft] = Leftest;
	if ( HighP[Cnthi].x ^ Rightest.x ) HighP[++ Cnthi] = Rightest;
	if ( LowP[Cntlo].x ^ Rightest.x ) LowP[++ Cntlo] = Rightest;
	for (int x = Leftest.x + 1; x < Rightest.x; ++ x ) {
		if ( x > HighP[uleft + 1].x ) ++ uleft;
		if ( x > LowP[dleft + 1].x ) ++ dleft;
		Point _le = HighP[uleft], _ri = HighP[uleft + 1];
		int uy = 0, dy = 0, Choice[5] = {}; double JuncY;
		if ( _le.y == _ri.y ) {
			uy = floor ( _le.y );
		} else if ( x == _ri.x ) {
			uy = _ri.y;
		} else {
			JuncY = _le.y + 1.0 * ( _ri.y - _le.y ) / ( _ri.x - _le.x ) * ( x - _le.x );
			Choice[2] = ( Choice[1] = ceil ( JuncY ) + 1 ) - 1, Choice[4] = ( Choice[3] = floor ( JuncY ) ) - 1;
			for (int i = 1; i <= 4; ++ i ) {
				if ( Collinear ( { x, Choice[i] }, _le, _ri ) ) {
					uy = Choice[i];
					break;
				} else if ( LeftCheck ( Point ( x, Choice[i] ).Symmetric (), _le.Symmetric (), _ri.Symmetric () ) ) {
					uy = Choice[i];
					break;
				}
			}
		}
		_le = LowP[dleft], _ri = LowP[dleft + 1];
		if ( _le.y == _ri.y ) {
			dy = ceil ( _le.y );
		} else if ( x == _ri.x ) {
			dy = _ri.y;
		} else {
			JuncY = _le.y + 1.0 * ( _ri.y - _le.y ) / ( _ri.x - _le.x ) * ( x - _le.x );
			Choice[2] = ( Choice[1] = floor ( JuncY ) - 1 ) + 1, Choice[4] = ( Choice[3] = ceil ( JuncY ) ) + 1;
			for (int i = 1; i <= 4; ++ i ) {
				if ( Collinear ( { x, Choice[i] }, _le, _ri ) ) {
					dy = Choice[i];
					break;
				}
				if ( ! LeftCheck ( Point ( x, Choice[i] ).Symmetric (), _le.Symmetric (), _ri.Symmetric () ) ) {
					dy = Choice[i];
					break;
				}
			}
		}
		Cntx[Indx ( x )] = uy - dy + 1;
	}
}

///读入点数据，更新极值点
///调用PrepareX和PrepareY统计各坐标轴上的点数
///计算距离平方和的统计值
///输出最终结果
inline void Work () {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++ i ) {
		p[i].Input ();
		//更新极值点并统计边界点数
		if ( p[i].y > Highest.y ) {
			Cnty[Indx ( p[i].y )] = 1;
			Highest = p[i];
		} else if ( p[i].y == Highest.y ) {
			Cnty[Indx ( p[i].y )] = Abs ( p[i].x - Highest.x ) + 1;
		}
		if ( p[i].y < Lowest.y ) {
			Cnty[Indx ( p[i].y )] = 1;
			Lowest = p[i];
		} else if ( p[i].y == Lowest.y ) {
			Cnty[Indx ( p[i].y )] = Abs ( p[i].x - Lowest.x ) + 1;
		}
		if ( p[i].x < Leftest.x ) {
			Cntx[Indx ( p[i].x )] = 1;
			Leftest = p[i];
		} else if ( p[i].x == Leftest.x ) {
			Cntx[Indx ( p[i].x )] = Abs ( p[i].y - Leftest.y ) + 1;
		}
		if ( p[i].x > Rightest.x ) {
			Cntx[Indx ( p[i].x )] = 1;
			Rightest = p[i];
		} else if ( p[i].x == Rightest.x ) {
			Cntx[Indx ( p[i].x )] = Abs ( p[i].y - Rightest.y ) + 1;
		}
	}
	PrepareX ();
	PrepareY ();
	double ResX = 0.0, ResY = 0.0, PointCnt = 0.0;
	double Sqrx = 0.0, Sumx = 0.0;
	for (int x = Leftest.x; x <= Rightest.x; ++ x ) {
		PointCnt += Cntx[Indx ( x )];
	}
	for (int x = Leftest.x; x <= Rightest.x; ++ x ) {
		Sqrx += 0.5 * Cntx[Indx ( x )] * x * x;
		Sumx += 0.5 * Cntx[Indx ( x )] * x;
	}
	ResX = Sqrx * PointCnt - Sumx * Sumx * 2.0;
	double Sqry = 0.0, Sumy = 0.0;
	for (int y = Highest.y; y >= Lowest.y; -- y ) {
		Sqry += 0.5 * Cnty[Indx ( y )] * y * y;
		Sumy += 0.5 * Cnty[Indx ( y )] * y;
	}
	ResY = Sqry * PointCnt - Sumy * Sumy * 2.0;
	printf ( "%.10lf\n", ( ResX + ResY ) / PointCnt / ( PointCnt - 1.0 ) * 2.0 );
}

int main () {
	Work ();
	return 0;
}