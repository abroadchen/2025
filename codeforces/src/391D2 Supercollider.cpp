//
// Created by Psy.C on 2026/1/29.
//

#include <iostream>
#include <vector>
#include <algorithm>
#define rep(i, l, r) for (int i = l; i <= r; ++i)
#define eb emplace_back
#define pii pair <int, int>
using namespace std;
constexpr int N = 2e5 + 5;
inline int rd ()//快速读入整数
{
	int x = 0, f = 1;
	char ch = getchar ();
	while (! isdigit (ch)) { if (ch == '-') f = -1; ch = getchar (); }
	while (isdigit (ch)) { x = (x << 1) + (x << 3) + ch - 48; ch = getchar (); }
	return x * f;
}
int n, m;//第一类线段的数量 第二类线段的数量
class node
{
	public:
		int x, y, l;//x坐标、y坐标、长度
	friend bool operator < (const node &a, const node &b)
	{
		return a.x < b.x;
	}
} c1[N], c2[N];//存储第一类线段 存储第二类线段
int li[N], len;//离散化数组 离散化后数组长度
vector <int> v1[N], v2[N];//扫描线过程中进入事件的 Y 坐标集合 扫描线过程中离开事件的 Y 坐标集合
vector <pii> q[N];//查询区间集合
int ls[N << 4], rs[N << 4], val[N << 4];//线段树左儿子数组 线段树右儿子数组 线段树节点值数组
int rt, tot;//线段树根节点 线段树节点计数器
void upd (int &p, int l, int r, int x, int k)
{
	if (! p) p = ++ tot;//节点 p 不存在 创建新节点
	if (l == r) return val[p] += k, void ();//更新值并返回
	int mid = l + r >> 1;
	if (x <= mid) upd (ls[p], l, mid, x, k);//根据 x 的位置递归更新
	else upd (rs[p], mid + 1, r, x, k);
	val[p] = val[ls[p]] + val[rs[p]];//更新父节点的值
}
int qry (int p, int l, int r, int L, int R)
{
	if (L > R) return 0;
	if (L <= l && r <= R) return val[p];//返回节点值
	int mid = l + r >> 1, ret = 0;
	if (L <= mid) ret += qry (ls[p], l, mid, L, R);
	if (R > mid) ret += qry (rs[p], mid + 1, r, L, R);
	return ret;
}
int check (int X)
{
	len = 0;//清空离散化数组长度
	rep (i, 1, n) li[++len] = c1[i].x;//将第一类线段的 x 坐标加入离散化数组
	//将第二类线段的 x+X 和 x+l-X 坐标加入离散化数组
	rep (i, 1, m) li[++len] = c2[i].x + X, li[++len] = c2[i].x + c2[i].l - X;
	sort (li + 1, li + len + 1);
	len = unique (li + 1, li + len + 1) - li - 1;//去重并更新长度
	rep (i, 1, n)
	{
		//找到 c1[i].x 在离散化数组中的位置
		int x = lower_bound (li + 1, li + len + 1, c1[i].x) - li;
		q[x].eb (pii (c1[i].y + X, c1[i].y + c1[i].l - X));//在对应位置添加 Y 方向的查询区间
	}
	rep (i, 1, m)
	{
		//找到 x+X 和 x+l-X 在离散化数组中的位置
		int x = lower_bound (li + 1, li + len + 1, c2[i].x + X) - li;
		int y = lower_bound (li + 1, li + len + 1, c2[i].x + c2[i].l - X) - li;
		if (x > y) continue;
		v1[x].eb (c2[i].y);//在 x 位置添加进入事件，在 y 位置添加离开事件
		v2[y].eb (c2[i].y);
	}
	int chk = 0;
	rep (i, 1, len + 1)//遍历每个离散化位置
	{
		//处理进入事件：将 Y 坐标加入线段树
		for (auto v : v1[i]) upd (rt, -1e8, 2e8, v, 1);
		//处理查询：检查是否有区间覆盖
		for (auto p : q[i]) chk |= qry (1, -1e8, 2e8, p.first, p.second);
		//处理离开事件：将 Y 坐标从线段树删除
		for (auto v : v2[i]) upd (rt, -1e8, 2e8, v, -1);
	}
	//清空所有辅助数组
	rep (i, 1, len + 1) v1[i].clear (), v2[i].clear (), q[i].clear ();
	return chk;
}
int main ()
{
	n = rd (), m = rd ();
	rep (i, 1, n) c1[i].x = rd (), c1[i].y = rd (), c1[i].l = rd ();
	rep (i, 1, m) c2[i].x = rd (), c2[i].y = rd (), c2[i].l = rd ();
	sort (c1 + 1, c1 + n + 1);
	int l = 0, r = 2e8, ans = 0;
	while (l <= r)
	{
		int mid = l + r >> 1;
		if (check (mid))
		{
			l = mid + 1; ans = mid;
		} else r = mid - 1;
	}
	printf ("%d\n", ans);
}