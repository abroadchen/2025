//
// Created by Psy.C on 2026/8/28.
//

/**
N = 100005 ：节点编号上限（满二叉树 2^h - 1 ≤ 10万 ，所以 h ≤ 17 ）
t int 测试用例数量
h int 树的高度（输入）
n int 节点总数 = 2^h - 1
dep[N] int[N] 节点深度估计值 ， dep[x] 存储"节点 x 到根还有多少层"（逐步逼近）
bro[N] vector<int>[N] 查询结果缓存 ， bro[x] 是节点 x 的邻居列表（避免重复查询）
- 缓存命中 ：如果节点 u 已经查过（ vis[u]=true ）， 直接返回缓存 bro[u] ，不发交互请求。
- 标记已查询 ： vis[u] = 1 ，告诉系统"我们准备查这个节点了"
- printf("? %d\n", u) ：格式化输出查询请求，格式 ? 节点编号 。
- fflush(stdout) ：强制刷新输出缓冲区。 交互题必须 flush ，否则请求卡在缓冲区里系统收不到，程序会死锁等待回复
- scanf("%d", &k) ：读回邻居数量 k 。
- 循环读 k 个邻居编号，存入临时向量 v 。
- bro[u] = v ： 缓存到全局数组 （下次再查直接返回）。
- 返回邻居列表 v
static ：内部链接，只在当前文件可见。
- getans = 1 ：标记"已经找到根了"，后续所有代码块都通过 if (!getans) 跳过。
- printf("! %d\n", x) ：按题目要求格式输出答案。
- fflush(stdout) ： 必须刷新 ，确保答案提交出去

返回一个 pair<int, int> ，是节点 u 的 两个未查询过的邻居 。
- 兜底查询 ：如果 bro[u] 还没缓存过，先调 query(u) 查一下。
- 遍历邻居 ：跳过已经查过的邻居，取前两个未查过的分别放入 p 和 q 。
- 返回结果 ： make_pair(p, q) ，两个都是 -1 说明所有邻居都查过了。
作用 ：每次往上一层走时，需要知道"还有哪两个方向没探索过"，挑一个继续爬

- scanf("%d", &t) ：读测试用例数。
- 循环 while(t--) ：处理每组。
- nnx = -1 ：重置辅助变量。
- scanf("%d", &h) ：读树高。
- n = (1 << h) - 1 ：计算节点总数 2^h - 1 （满二叉树公式）。 1 << h 等价于 pow(2, h) ，但整数运算更快更精确。
每组测试 必须重置 所有全局状态：
- vis[i] = 0 ：所有节点重新标记为"未查询"。
- bro[i].clear() ：清空缓存。
- bro[i].shrink_to_fit() ：释放内存（ vector::clear() 只清空元素，不缩容， shrink_to_fit 真正把内存还给系统）。
- dep[i] = 0 ：深度估计归零。
- getans = 0 ：答案标记归零。
为什么要 shrink_to_fit？ 多组测试用例跑下来，如果不清内存，程序可能被内存限制卡掉

- query(1) ：先查节点 1（任意起点都行，选 1 最方便）。
- g.size() == 2 ：邻居数恰好是 2 → 节点 1 就是根 ！直接 report(1) 结束。
- 如果 size ≠ 2，说明节点 1 不是根，需要继续找
节点 1 只有 1 个邻居 → 节点 1 是 叶子节点 （在满二叉树中，叶子只有父节点一个邻居）。
- dep[1] = h ：节点 1 的深度估计设为 h （最多可能离根有 h-1 层）。
- LCA = 1 ：后面会从这里开始往上找
节点 1 有多个邻居（中间节点，既不是根也不是叶子）。取前两个邻居 x 和 y ， 分别沿两条不同方向走一条链到叶子
- 一直查当前节点，加入路径。
- 遇到根（size==2） ：直接 report 结束！
- 遇到叶子（size==1） ：到达链条末端，break。
- 否则有 3+ 邻居：选一个还没查过的邻居继续走
- reverse(path) ：把第一条路径反转（从叶子到 1 的顺序）。
- path.emplace_back(1) ：节点 1 也加进来。
- 第二条链同理：遇根 report，遇叶子停，否则沿未查邻居继续
两条路径 x→...→1→...→y 拼起来就是一条从叶子到叶子的完整路径。 路径中点一定是 LCA （最近公共祖先）！
- path.size()/2 ：取中点下标。
- dep[LCA] = h - path.size()/2 ：LCA 到根的距离估计
- get(LCA) ：找 LCA 的未访问邻居。
- fa = res.first ：选其中一个作为往上爬的方向（假设这个方向通向根）
如果估计 LCA 到根只剩 1 层，直接 report 它。
- dep[fa] = dep[LCA] - 1 ：父节点离根更近一层。
- 如果父节点深度估计是 1，直接 report。
父节点到根只差 2 层，展开查它的两个邻居，哪个是根就 report。
- g.back() 和 g.pop_back() ：取其中一个邻居放在一边当兜底。
- 查另一个邻居，如果邻居数 = 2 就是根。
- 两边都不是 → 兜底那个一定是根。
- nx = LCA ：记录上一层的位置（防止爬回头）。
- ggg = dep[fa] - 2 ：还要爬多少层才到"快到根"的地方（剩下 2 层内改用暴力）。
- 循环逐层向上爬：
- 查当前 fa 的邻居。
- 过滤掉 nx （上一层的节点，防止回头），剩下两个候选。
- cs = pd[0] ：选第一个候选方向试试
试探性地沿 cs 方向往下走 nd 步 ：
- nd = h - dep[fa] ：cs 这条链理论上最长不超过这么多步。
- 遇叶子（size==1）：标记 flag=1 ，说明这个方向是往下走的分支。
- 遇根（size==2）：找到了！report 结束。
- 有多个邻居：沿未访问的方向继续。
判断正确方向 ：
- flag=1 ：cs 方向是往下（遇到叶子），说明 另一个方向才通向根 ，选 pd[1] 。
- flag=0 ：cs 方向没遇到叶子（还在中间层）， cs 方向就是通向根的 ，选 pd[0] 。
- 更新 fa 为新的往上爬的节点，深度减 1。
逐层爬完还没找到？做最后一次暴力。
- 查 fa 的邻居，跳过已经知道的那个方向 nnx 。
- 把邻居的邻居收集起来，逐个查，谁的邻居数是 2 谁就是根。
- 兜底：都不是就 report 最后一个。
 */
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;

int t, h, n, dep[N];
vector<int> bro[N];
bool vis[N];
bool getans = 0;
int nnx;

inline vector<int> query(int u) {
	if (vis[u]) return bro[u];
	vis[u] = 1;
	vector<int> v;
	printf("? %d\n", u);
	fflush(stdout);
	int k;
	scanf("%d", &k);
	for (int i = 1; i <= k; i++) {
		int x;
		scanf("%d", &x);
		v.emplace_back(x);
	}
	bro[u] = v;
	return v;
}

static void report(int x) {
	getans = 1;
	printf("! %d\n", x);
	fflush(stdout);
}

pair<int, int> get(int u) {
	if (bro[u].empty()) query(u);
	int p = -1, q = -1;
	for (auto& j : bro[u]) {
		if (!vis[j]) {
			if (p == -1) p = j;
			else q = j;
		}
	}
	return make_pair(p, q);
}

int main() {
	scanf("%d", &t);
	while (t--) {
		nnx = -1;
		scanf("%d", &h);
		n = (1 << h) - 1;
		for (int i = 1; i <= n; i++) {
			vis[i] = 0;
			bro[i].clear(), bro[i].shrink_to_fit();
			dep[i] = 0;
		}
		getans = 0;
		vector<int> g = query(1);
		if (g.size() == 2) report(1);
		else {
			int LCA;
			if (g.size() == 1) {
				dep[1] = h;
				LCA = 1;
			}
			else {
				vector<int> path;
				int x = g[0], y = g[1];
				while (true) {
					auto p = query(x);
					path.emplace_back(x);
					if (p.size() == 2) {
						report(x);
						break;
					}
					if (p.size() == 1) break;
					for (auto& j : p) {
						if (!vis[j]) {
							x = j;
							break;
						}
					}
				}
				reverse(path.begin(), path.end());
				path.emplace_back(1);
				while (!getans) {
					auto p = query(y);
					path.emplace_back(y);
					if (p.size() == 2) {
						report(y);
						break;
					}
					if (p.size() == 1) break;
					for (auto& j : p) {
						if (!vis[j]) {
							y = j;
							break;
						}
					}
				}
				if (!getans) {
					LCA = path[path.size() / 2];
					dep[LCA] = h - path.size() / 2;
				}
			}
			if (!getans) {
				auto res = get(LCA);
				int fa = res.first;
				if (dep[LCA] == 1) {
					report(LCA);
					getans = 1;
				}
				else {
					dep[fa] = dep[LCA] - 1;
					if (dep[fa] == 1) report(fa);
					else if (dep[fa] == 2) {
						auto g = query(fa);
						int res = g.back();
						g.pop_back();
						for (auto& j : g) {
							auto k = query(j);
							if (k.size() == 2) {
								report(j);
								break;
							}
						}
						if (!getans) report(res);
					}
					else {
						int nx = LCA;
						int ggg = dep[fa] - 2;
						for (int i = 1; i < ggg; i++) {
							auto g = query(fa);
							vector<int> pd;
							for (auto& gg : g)
								if (gg != nx) pd.emplace_back(gg);
							int cs = pd[0];
							int nd = h - dep[fa];
							int pre = fa;
							bool flag = 0;
							for (int j = 1; j <= nd; j++) {
								auto g = query(cs);
								if (g.size() == 1) {
									flag = 1;
									break;
								}
								if (g.size() == 2) {
									report(cs);
									break;
								}
								for (auto& k : g) {
									if (k != pre) {
										pre = cs;
										cs = k;
										break;
									}
								}
							}
							if (getans) break;
							int nfa;
							if (flag) nfa = pd[1];
							else nfa = pd[0];
							nx = fa;
							fa = nfa;
							dep[fa] = dep[nx] - 1;
							nnx = nx;
						}
					}
				}
				if (!getans) {
					auto g = query(fa);
					vector<int> pp;
					for (auto& k : g) {
						if (k == nnx) continue;
						auto gg = query(k);
						for (auto& x : gg)
							if (x != fa) pp.emplace_back(x);
					}
					g = pp;
					for (int i = 0; i + 1 < g.size(); i++) {
						auto kk = query(g[i]);
						if (kk.size() == 2) {
							report(g[i]);
							break;
						}
					}
					if (!getans) report(g.back());
				}
			}
		}
	}
	return 0;
}