//
// Created by Psy.C on 2026/4/19.
//
/**
x, y: 分子和分母
构造函数：自动约分，处理负号
if (y < 0) g = -g: 确保分母为正
实现分数的基本四则运算
交叉相乘比较，避免浮点误差
表示线段：y = k*x + b，定义域为[l, r]
比较函数依赖于全局变量tim
d[N]: 节点深度
f[N]: 父节点
s[N]: 子树大小
son[N]: 重儿子
dfn[N]: DFS序
top[N]: 链顶
heavy[N], light[N]: 重链和轻边上的线段
使用树链剖分求LCA
沿着重链向上跳
第一遍DFS：求子树大小和重儿子
第二遍DFS：分配DFS序和链顶
s: 起始时间
v: 速度
将树上路径转化为线段
求两条线段的交点时间
如果平行，返回无穷大或交点
将线段的左右端点作为事件
按时间排序，使用平衡树维护当前活跃线段

在树上模拟运动轨迹
将树链剖分，处理路径上的几何关系
使用分数类避免精度误差
用扫描线算法找到最早的相遇时间
时间复杂度：O(m log²n)，空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define vi vector<int>
#define pb push_back
#define mp make_pair
#define fi first
#define se second
using namespace std;

template<class T>
void rd(T& x) {
    int f = 0, ch = 0; x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
}

struct frac {
	ll x{}, y{};
	frac() = default;

	frac(ll _x, ll _y = 1ll) : x(_x), y(_y) {
		ll g = __gcd(abs(x), abs(y));
		if (y < 0) g = -g;
		x /= g, y /= g;
	}
	friend frac operator+(frac e, frac b) { return {e.x * b.y + e.y * b.x, e.y * b.y}; }
	friend frac operator-(frac e, frac b) { return {e.x * b.y - e.y * b.x, e.y * b.y}; }
	friend frac operator*(frac e, frac b) { return {e.x * b.x, e.y * b.y}; }
	friend frac operator/(frac e, frac b) { return {e.x * b.y, e.y * b.x}; }
	friend bool operator<(frac e, frac b) { return e.x * b.y < b.x * e.y; }
	friend bool operator>(frac e, frac b) { return e.x * b.y > b.x * e.y; }
	friend bool operator<=(frac e, frac b) { return e.x * b.y <= b.x * e.y; }
	friend bool operator>=(frac e, frac b) { return e.x * b.y >= b.x * e.y; }
	friend bool operator==(frac e, frac b) { return e.x * b.y == b.x * e.y; }
};

const int N = 1e5 + 7, inf = 1e9;
int n, m, d[N], f[N], s[N], son[N], dfn[N], top[N], num;
vi e[N];
double Ans = inf;
frac tim, ans;
struct P {
	frac k, b, l, r;
	P() = default;
	P(frac k, frac b, frac l, frac r) : k(k), b(b), l(l), r(r) {}
	friend bool operator < (P a, P b) {
		if (a.k * tim + a.b == b.k * tim + b.b)
			return a.l == b.l ? a.r == b.r ? a.k < b.k : a.r < b.r : a.l < b.l;
		return a.k * tim + a.b < b.k * tim + b.b;
	}
};
multiset<P> st;
vector<P> heavy[N], light[N];

inline int lca(int x, int y) {
	while (top[x] != top[y]) {
		if (d[top[x]] < d[top[y]]) swap(x, y);
		x = f[top[x]];
	}
	return d[x] < d[y] ? x : y;
}

inline frac dist(int x, int y) {
	return {d[x] + d[y] - 2 * d[lca(x,y)]};
}

void dfs(int x) {
	s[x] = 1;
	for (int y : e[x])
		if (y != f[x]) {
			f[y] = x, d[y] = d[x] + 1, dfs(y), s[x] += s[y];
			if (s[y] > s[son[x]]) son[x] = y;
		}
}

void dfs(int x, int p) {
	dfn[x] = ++num, top[x] = p;
	if (son[x]) dfs(son[x], p);
	for (int y : e[x])
		if (y != son[x] && y != f[x]) dfs(y, y);
}

inline void solve(int x, int y, frac s, frac v) {
	frac t = s + dist(x, y) / v;
	while (top[x] != top[y])
		if (d[top[x]] > d[top[y]]) {
			int p = top[x];
			heavy[p].pb(P(frac(0) - v, frac(d[x]) + v * s, s, s + frac(d[x] - d[p]) / v));
			s = s + frac(d[x] - d[p]) / v, x = top[x], p = f[x];
			light[x].pb(P(frac(0) - v, frac(d[x]) + v * s, s, s + frac(d[x] - d[p]) / v));
			s = s + frac(d[x] - d[p]) / v, x = f[x];
		} else {
			int p = top[y];
			heavy[p].pb(P(v, frac(d[y]) - v * t, t - frac(d[y] - d[p]) / v, t));
			t = t - frac(d[y] - d[p]) / v, y = top[y], p = f[y];
			light[y].pb(P(v, frac(d[y]) - v * t, t - frac(d[y] - d[p]) / v, t));
			t = t - frac(d[y] - d[p]) / v, y = f[y];
		}
	int p = top[x];
	if (d[x] > d[y]) heavy[p].pb(P(frac(0) - v, frac(d[x]) + v * s, s, t));
	else heavy[p].pb(P(v, frac(d[y]) - v * t, s, t));
}

inline frac get(P a, P b) {
	if (a.k == b.k) return a.b == b.b ? max(a.l, b.l) : frac(inf);
	frac o = (b.b - a.b) / (a.k - b.k);
	return o >= max(a.l, b.l) && o <= min(a.r, b.r) ? o : frac(inf);
}

inline void work(vector<P> p) {
	st.clear(), ans = frac(inf);
	vector<pair<P, bool>> q;
	for (P x : p) q.pb(mp(x, 1)), q.pb(mp(x, 0));
	ranges::sort(q, [](pair<P, bool> x, pair<P, bool> y) {
		frac tx = x.se ? x.fi.l : x.fi.r, ty = y.se ? y.fi.l : y.fi.r;
		return tx == ty ? x.se > y.se : tx < ty;
	});
	for (auto x : q) {
		frac now = x.se ? x.fi.l : x.fi.r;
		if (now >= ans) break;
		tim = now;
		if (x.se) {
			auto tmp = st.insert(x.fi), pre = tmp, suf = tmp;
			if (pre != st.begin()) ans = min(ans, get(*--pre, *tmp));
			if (++suf != st.end()) ans = min(ans, get(*tmp, *suf));
		} else {
			auto tmp = st.lower_bound(x.fi), pre = tmp, suf = tmp;
			if (++suf != st.end() && pre != st.begin()) ans = min(ans, get(*--pre, *suf));
			st.erase(tmp);
		}
	}
	Ans = min(Ans, 1.0 * ans.x / ans.y);
}

int main() {
	rd(n), rd(m);
	for (int i = 1, x, y; i < n; i++) rd(x), rd(y), e[x].pb(y), e[y].pb(x);
	d[1] = 1, dfs(1), dfs(1, 1);
	for (int i = 1, t, c, x, y; i <= m; i++)
		rd(t), rd(c), rd(x), rd(y), solve(x, y, frac(t), frac(c));
	for (int i = 1; i <= n; i++) work(heavy[i]), work(light[i]);
	if (Ans == inf) return printf("-1\n"), 0;
	printf("%.10f\n", Ans);
	return 0;
}