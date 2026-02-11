//
// Created by Psy.C on 2026/2/11.
//
/**
n：输入的节点数
mid：二分查找的中间值
siz[i]：节点i的子树大小
val[i]：节点i的值（-1表示内部节点）
l[i], r[i]：节点i的左右子节点
dp[i][j][k]：记忆化搜索的DP数组
vis[i][j][k]：DP数组的访问标记

第一层merge：合并左右子树结果，对手玩家视角
第二层merge：将当前ans与上述结果合并，当前玩家视角
 */
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 255;

template <typename T> void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
template <typename T> void write(T x) {
	if (x < 0) x = -x, putchar('-');//取绝对值并输出负号
	if (x > 9) write(x / 10);//递归输出高位数字
	putchar(x % 10 + '0');//输出个位数字
}
template <typename T> void writeln(T x) {
	write(x);
	puts("");
}
int n, mid, siz[MAXN], val[MAXN], l[MAXN], r[MAXN];
bool dp[MAXN][2][3], vis[MAXN][2][3];
bool merge(bool x, bool y, bool who) {
	if (x == who || y == who) return who;//有一个等于who，则返回who
	return !who;//否则返回!who（对手获胜）
}

/**
 *
 * @param pos 当前节点位置
 * @param who 当前轮到的玩家
 * @param skip 跳过的状态
 * @return
 */
bool getdp(int pos, bool who, int skip) {
	if (val[pos] != -1) {//叶节点，返回值是否大于mid
		return val[pos] > mid;
	}
	if (siz[pos] == 1) {
		return merge(getdp(l[pos], 0, 0), getdp(r[pos], 0, 0), who ^ (skip == 2));
	}
	if (vis[pos][who][skip]) {
		return dp[pos][who][skip];
	}
	bool &ans = dp[pos][who][skip];
	vis[pos][who][skip] = true;
	if (skip) {
		ans = getdp(pos, !who, 0);//交换玩家角色
		if (siz[pos] & 1) {
			if (siz[l[pos]] & 1) {
				ans = merge(ans, merge(getdp(l[pos], who, 0),
					getdp(r[pos], !who, 1 + (siz[l[pos]] == 1 && skip == 1)), !who), who);
				ans = merge(ans, merge(getdp(r[pos], who, 0),
					getdp(l[pos], !who, 1 + (siz[r[pos]] == 1 && skip == 1)), !who), who);
			} else {
				if (siz[l[pos]]) {
					ans = merge(ans, merge(getdp(l[pos], who, 1 + (skip == 1 && siz[r[pos]] == 0)),
						getdp(r[pos], !who, 0), !who), who);
				}
				if (siz[r[pos]]) {
					ans = merge(ans, merge(getdp(r[pos], who, 1 + (skip == 1 && siz[l[pos]] == 0)),
						getdp(l[pos], !who, 0), !who), who);
				}
			}
		} else {
			ans = merge(ans, merge(getdp(l[pos], who, 1 + (skip == 1 && siz[r[pos]] == 0)),
				getdp(r[pos], who, 0), who), who);
		}
	} else {
		if (siz[pos] & 1) {
			if (siz[l[pos]] & 1) {
				ans = merge(getdp(l[pos], who, 1), getdp(r[pos], who, 1), who);
			} else {
				ans = merge(getdp(l[pos], who, 0), getdp(r[pos], who, 0), who);
			}
		} else {
			ans = merge(merge(getdp(l[pos], who, 0), getdp(r[pos], !who, 0), !who),
			            merge(getdp(r[pos], who, 1), getdp(l[pos], !who, 1), !who), who);
		}
	}
	return ans;
}
void dfs(int pos) {
	siz[pos] = 0;
	if (val[pos] != -1) return;
	dfs(l[pos]), dfs(r[pos]);
	siz[pos] = 1 + siz[l[pos]] + siz[r[pos]];
	if (siz[r[pos]] & 1) swap(l[pos], r[pos]);
}
void init(int n) {
	for (int i = 0; i <= n - 1; i++) {
		read(val[i]);
		if (val[i] == -1) {//内部节点，读取左右子节点
			read(l[i]);
			read(r[i]);
		} else l[i] = r[i] = -1;//叶节点，设置子节点为空
	}
	dfs(0);//从根节点开始DFS计算子树大小
}
int main() {
	int T; read(T);
	while (T--) {
		read(n), init(n);
		int l = 0, r = 1e3;
		while (l < r) {
			mid = (l + r) / 2;
			memset(vis, false, sizeof(vis));
			if (getdp(0, 1, 0)) l = mid + 1;
			else r = mid;
		}
		writeln(l);
	}
	return 0;
}