//
// Created by Psy.C on 2026/3/11.
//
/**
构建第id个字母的线段树
叶子节点：判断该位置是否为字母id
非叶子节点：左右子树计数之和

区间更新操作
d: 设置值（0或1）
如果完全包含在目标区间内，直接打标记
否则递归处理左右子树
查询区间[l,r]内字母id的出现次数
如果完全包含，直接返回计数值
否则递归查询左右子树
将线段树中的信息还原到原字符串
递归到叶子节点，如果计数为1，则该位置应为字母id

构建26棵线段树（每个字母一棵）
opt == 1: 升序排列（按字母顺序从小到大放置）
opt == 2: 降序排列（按字母顺序从大到小放置）
对每个字母统计在区间内的出现次数
清空区间内该字母的标记
按照排序要求重新放置该字母
清空原字符串数组
从线段树重建最终字符串
输出结果

单次操作：O(26 × log n)
总体：O(q × 26 × log n)
 */
#include<bits/stdc++.h>
using namespace std;
const int nn = 1e5 + 5;
struct SegTree {
	int l, r, cnt, lazy;
	#define l(p, i) tree[i][p].l
	#define r(p, i) tree[i][p].r
	#define lazy(p, i) tree[i][p].lazy
	#define cnt(p, i) tree[i][p].cnt
}tree[26][nn * 8];
char a[nn];
int n, q;
#define ls (p << 1)
#define rs (p << 1 | 1)
void build(int p, int l, int r, int id) {
	l(p, id) = l;
	r(p, id) = r;
	lazy(p, id) = -1;
	if (l == r) {
		cnt(p, id) = (a[l] == id + 'a');
		return;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid, id);
	build(rs, mid + 1, r, id);
	cnt(p, id) = cnt(ls, id) + cnt(rs, id);
}
inline void spread(int p, int id) {
	if (~lazy(p, id)) {
		lazy(ls, id) = lazy(rs, id) = lazy(p, id);
		cnt(ls, id) = lazy(ls, id) * (r(ls, id) - l(ls, id) + 1);
		cnt(rs, id) = lazy(rs, id) * (r(rs, id) - l(rs, id) + 1);
		lazy(p, id) = -1;
	}
}
void change(int p, int l, int r, int d, int id) {
	if (l <= l(p, id) && r(p, id) <= r) {
		lazy(p, id) = d;
		cnt(p, id) = d * (r(p, id) - l(p, id) + 1);
		return;
	}
	spread(p, id);
	if (l <= r(ls, id))
		change(ls, l, r, d, id);
	if (l(rs, id) <= r)
		change(rs, l, r, d, id);
	cnt(p, id) = cnt(ls, id) + cnt(rs, id);
}
int ask(int p, int l, int r, int id) {
	if (l <= l(p, id) && r(p, id) <= r)
		return cnt(p, id);
	spread(p, id);
	int ans = 0;
	if (l <= r(ls, id))
		ans += ask(ls, l, r, id);
	if (l(rs, id) <= r)
		ans += ask(rs, l, r, id);
	return ans;
}
void final(int p, int id) {
	if (l(p, id) == r(p, id)) {
		if (cnt(p, id) == 1)
			a[l(p, id)] = id + 'a';
		return;
	}
	spread(p, id);
	final(ls, id);
	final(rs, id);
}
int main() {
	scanf("%d %d", &n, &q);
	scanf("%s", a + 1);
	for (int i = 0; i < 26; i++) build(1, 1, n, i);
	int l, r, opt;
	while (q--) {
		scanf("%d %d %d", &l, &r, &opt);
		if (opt == 1) {
			int f = l, len;
			for (int i = 0; i < 26; i++) {
				len = ask(1, l, r, i);
				if (len == 0) continue;
				change(1, l, r, 0, i);
				change(1, f, f + len - 1, 1, i);
				f += len;
			}
		} else {
			int f = r, len;
			for (int i = 0; i < 26; i++) {
				len = ask(1, l, r, i);
				if (len == 0) continue;
				change(1, l, r, 0, i);
				change(1, f - len + 1, f, 1, i);
				f -= len;
			}
		}
	}
	memset(a, 0, sizeof(a));
	for (int i = 0; i < 26; i++) final(1, i);
	for (int i = 1; i <= n; i++) putchar(a[i]);
	return 0;
}