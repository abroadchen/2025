//
// Created by Psy.C on 2026/2/12.
//
/**
ch[][]：可持久化线段树节点的左右子节点
cnt[]：节点计数
hx[]：哈希值存储
p1[], p2[]：预计算的幂次（用于哈希）
fst[]：头指针
nxt[]：下一个边
vv[]：终点
cost[]：边权

nxt[e] = fst[u]：新边的next指向原来u的第一个边
fst[u] = e：u的第一个边更新为新边e
 */
#include <bits/stdc++.h>
#define LL long long
#define N 102000
#define mod 1000000007
#define M 3000020
#define md ((ll+rr)>>1)
using namespace std;

const int m1 = 1000000007;
const int m2 = 1000000002;
const int b = 2;//哈希基数

int ch[N * 200][2], cnt[N * 200];//节点计数
LL hx[N * 200];//高32位存一种哈希，低32位存另一种
int tot;//节点编号
int p1[N], p2[N];


int fst[N], nxt[M], vv[M], cost[M], e;


int n, m;//图的顶点数和边数
int s, t;//起点和终点
int pre[N], rt[N];//路径前驱数组（用于重构路径）每个点对应的线段树根节点
bool inq[N];//是否在队列中
int ans;

void init() {
	memset(fst, -1, sizeof fst);
	e = 0;//边计数器清零
	p1[0] = p2[0] = 1;//幂次数组初始化
	for(int i = 1; i < N; ++i) {
		p1[i] = 1LL * p1[i - 1] * b % m1;//b^i
		p2[i] = 1LL * p2[i - 1] * b % m2;
	}
}

void add(const int u, const int v, const int c) {
	cost[e] = c, vv[e] = v, nxt[e] = fst[u], fst[u] = e++;
}

void push_up(const int k, const int ll, const int rr) {
	cnt[k] = cnt[ch[k][0]] + cnt[ch[k][1]];//更新节点k的计数值：等于左右儿子计数之和
	//右移32位，获得高32位 与0xFFFFFFFF做与运算，获得低32位
	LL x = hx[ch[k][0]] >> 32, y = hx[ch[k][0]] & ((1LL << 32) - 1);
	//从右儿子的哈希值中分离高位和低位
	const LL xx = hx[ch[k][1]] >> 32, yy = hx[ch[k][1]] & ((1LL << 32) - 1);
	//左侧哈希乘以相应的幂次再加上右侧哈希 合并左右儿子的哈希值
	x = (x * p1[rr - md] + xx) % m1;//p1[rr-md]：区间长度的幂次，用于哈希合并
	y = (y * p2[rr - md] + yy) % m2;
	hx[k] = (x << 32) + y;//重新组合成一个64位值
}


int update(const int i, const int x, const int v, const int ll, const int rr) {
	const int k = ++tot;//创建新节点k
	ch[k][0] = ch[i][0];//新节点复制旧节点的左右儿子（可持久化特性）
	ch[k][1] = ch[i][1];
	cnt[k] = cnt[i] + v;//旧节点计数+v
	if(ll == rr) {
		hx[k] = ((1LL * v) << 32) + v;//高32位和低32位都设为v
		return k;
	}
	if(x <= md) ch[k][0] = update(ch[i][0], x, v, ll, md);
	else ch[k][1] = update(ch[i][1], x, v, md + 1, rr);
	push_up(k, ll, rr);
	return k;
}


int query(const int i, const int x, const int ll, const int rr) {
	if(cnt[i] == rr - ll + 1) return -1;//整个区间都被标记满了
	if(ll == rr) {
		if(cnt[i] == 1) return -1;//被标记
		return ll;//返回位置
	}
	if(x > md) return query(ch[i][1], x, md + 1, rr);
	if(x == ll) {//从区间开头开始
		//左半区间全满 查右半区间
		if(cnt[ch[i][0]] == md - ll + 1) return query(ch[i][1], md + 1, md + 1, rr);
		return query(ch[i][0], x, ll, md);
	}
	int t = query(ch[i][0], x, ll, md);//先查左子树，查不到再查右子树
	if(t != -1) return t;
	return query(ch[i][1], md + 1, md + 1, rr);
}

int clear0(const int i, const int l, const int r, const int ll, const int rr) {
	if(ll == l && rr == r) {//完全匹配待清除区间
		return 0;//空节点0
	}
	const int k = ++tot;
	ch[k][0] = ch[i][0];
	ch[k][1] = ch[i][1];
	if(r <= md) ch[k][0] = clear0(ch[i][0], l, r, ll, md);
	else if(l > md) ch[k][1] = clear0(ch[i][1], l, r, md + 1, rr);
	else {//跨越中间
		ch[k][0] = clear0(ch[i][0], l, md, ll, md);
		ch[k][1] = clear0(ch[i][1], md + 1, r, md + 1, rr);
	}
	push_up(k, ll, rr);
	return k;
}


bool cmp(const int u, const int v, const int ll, const int rr) {
	if(hx[u] == hx[v]) return 0;
	if(ll == rr) {
		return cnt[u] < cnt[v];
	}
	//优先比较右子树，不同时返回右子树比较结果
	if(hx[ch[u][1]] != hx[ch[v][1]]) return cmp(ch[u][1], ch[v][1], md + 1, rr);
	return cmp(ch[u][0], ch[v][0], ll, md);//相同时返回左子树比较结果
}
void dfs(const int u, const int ll, const int rr) {
	if(ll == rr) {
		if(cnt[u]) ans = ans * 2 + 1;
		else ans *= 2;
		ans %= m1;
		return;
	}
	dfs(ch[u][1], md + 1, rr);
	dfs(ch[u][0], ll, md);
}

struct node {
	int x{}, d{};//x是点编号，d是线段树根
	node() = default;
	node(const int x, const int d):x(x), d(d) {}
	bool operator < (const node &b) const {
		return cmp(b.d, d, 0, N - 1);
	}
};
void spfa() {
	priority_queue<node> q;
	q.emplace(s, rt[s]);
	//初始化除起点外所有点的线段树，标记整个区间
	for(int i = 1; i <= n; ++i) if(i != s) rt[i] = update(0, N - 1, 1, 0, N - 1);
	while(!q.empty()) {
		//取出最小距离点
		const int u = q.top().x, d = q.top().d; q.pop();
		if(rt[u] != d) continue;

		for(int i = fst[u]; ~i; i = nxt[i]) {
			int v = vv[i];
			const int c = cost[i];
			const int p = query(rt[u], c, 0, N - 1);//查询可更新的位置
			if(p == -1) {
				vector<int> g1;
				g1[1] = -1;
			}
			int t = rt[u];
			//清除c到p-1区间，然后在p位置标记
			if(p > c) t = clear0(t, c, p - 1, 0, N - 1);
			t = update(t, p, 1, 0, N - 1);
			if(cmp(t, rt[v], 0, N - 1)) {
				rt[v] = t;
				pre[v] = u;
				q.emplace(v, rt[v]);
			}
		}
	}
}



int main() {
	scanf("%d%d", &n, &m);
	init();
	for(int i = 1; i <= m; ++i) {
		int u, v, c;
		scanf("%d%d%d", &u, &v, &c);
		add(u, v, c);
		add(v, u, c);
	}
	scanf("%d%d", &s, &t);
	if(s == t) {
		printf("0\n1\n1\n");
		return 0;
	}

	spfa();
	if(pre[t] == 0) {//终点无前驱说明不可达
		puts("-1");
		return 0;
	}
	dfs(rt[t], 0, N - 1);
	printf("%d\n", ans);
	vector<int> vt; vt.push_back(t);
	while(t != s) {
		t = pre[t];//通过pre数组重构路径，反转得到正向路径
		vt.push_back(t);
	}
	ranges::reverse(vt);
	printf("%d\n", (int)vt.size());
	for(int i = 0; i < vt.size(); ++i) {
		printf("%d%c", vt[i], i == vt.size() - 1? '\n': ' ');
	}
	return 0;
}