//
// Created by Psy.C on 2026/4/22.
//
/**
Turn：转移矩阵
st：单位矩阵
makeI()：构造单位矩阵
empty()：判断是否为单位矩阵
sum：区间和（矩阵形式）
add：懒标记（区间乘法标记）
对于叶子节点，根据a[l]的值初始化矩阵
如果a[l] > 2，应用转移矩阵的幂次
设置斐波那契转移矩阵 [[1,1],[1,0]]
时间复杂度：O(m log n * 4)，其中4是矩阵乘法的常数
 */
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 100010, mod = 1e9 + 7;
int a[N], n, m;
struct Matrix {
	int a[2][2];
	void clear(int x) {memset(a, x, sizeof a);}
	void makeI() { a[0][0] = 1; a[0][1] = 0; a[1][0] = 0; a[1][1] = 1; }
	bool empty() {return ((a[0][0] == 1) and (a[0][1] == 0) and (a[1][0] == 0) and (a[1][1] == 1));}
} Turn, st;

Matrix operator + (const Matrix& A, const Matrix& B) {
	Matrix res{};
	res.clear(0);
	for (int i = 0; i <= 1; i ++ )
		for (int j = 0; j <= 1; j ++ )
			res.a[i][j] = (A.a[i][j] + B.a[i][j]) % mod;
	return res;
}
Matrix operator * (const Matrix& A, const Matrix& B) {
	Matrix res{};
	res.clear(0);
	for (int i = 0; i <= 1; i ++ )
		for (int j = 0; j <= 1; j ++ )
			for (int k = 0; k <= 1; k ++ )
				(res.a[i][j] += (A.a[i][k] * B.a[k][j])) %= mod;
	return res;
}
Matrix operator ^ (Matrix A, int b) {
	Matrix res{};
	res.makeI();
	while (b) {
		if (b & 1) res = res * A;
		A = A * A;
		b >>= 1;
	}
	return res;
}

namespace Segment_Tree {
	struct Tree {
		int l, r;
		Matrix sum, add;
		#define ls u<<1
		#define rs (u<<1|1)
	} tr[N << 2];

	void pushup(int u) {
		tr[u].sum = tr[ls].sum + tr[rs].sum;
	}
	void pushdown(int u) {
		if (!tr[u].add.empty()) {
			tr[ls].add = tr[ls].add * tr[u].add;
			tr[rs].add = tr[rs].add * tr[u].add;
			tr[ls].sum = tr[ls].sum * tr[u].add;
			tr[rs].sum = tr[rs].sum * tr[u].add;
			tr[u].add.makeI();
		}
	}
	void build(int u, int l, int r) {
		tr[u] = {l, r};
		tr[u].add.a[0][0] = tr[u].add.a[1][1] = 1;
		if (l == r) {
			if (a[l] == 1) tr[u].sum.a[0][0] = 1;
			else tr[u].sum.a[0][0] = tr[u].sum.a[0][1] = 1;
			if(a[l] > 2) tr[u].sum = tr[u].sum * (Turn ^ (a[l] - 2));
			return;
		}
		int mid = l + r >> 1;
		build(ls, l, mid), build(rs, mid + 1, r);
		pushup(u);
	}
	void modify(int u, int l, int r, Matrix v) {
		if (tr[u].l >= l && tr[u].r <= r) {
			tr[u].add = tr[u].add * v, tr[u].sum = tr[u].sum * v;
			return;
		}
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1;
		if (l <= mid) modify(ls, l, r, v);
		if (r > mid) modify(rs, l, r, v);
		pushup(u);
	}
	int query(int u, int l, int r) {
		if (tr[u]. l >= l && tr[u].r <= r) return tr[u].sum.a[0][0];
		pushdown(u);
		int mid = tr[u].l + tr[u].r >> 1, res = 0;
		if (l <= mid) res = (res + query(ls, l, r)) % mod;
		if (r > mid) res = (res + query(rs, l, r)) % mod;
		return res;
	}
}
using namespace Segment_Tree;

signed main() {
	{
		Turn.a[0][0] = Turn.a[0][1] = Turn.a[1][0] = 1;
	}
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i ++ )
		scanf("%lld", &a[i]);
	build(1, 1, n);
	while (m -- ) {
		int op, l, r, v;
		scanf("%lld%lld%lld", &op, &l, &r);
		if (op == 1) {
			scanf("%lld", &v);
			modify(1, l, r, Turn ^ v);//区间加v（斐波那契意义上的加法）
		} else {
			printf("%lld\n", query(1, l, r) % mod);//查询区间和
		}
	}
	return 0;
}