//
// Created by Psy.C on 2026/8/30.
//
/**
- ii ： pair<int,int> 的别名，存 (x, fa[x]) 形式的并查集撤销记录。
- ull ： unsigned long long 的别名，用于哈希键（64 位无符号整数）。
- N = 1010 ：网格边长上限（实际 h 和 w 都 ≤ 1000）
- fa[N*N+10] ： 带撤销的并查集 的父节点数组，总大小 1010² ≈ 100 万 （每个格子一个编号）。
- p ： 撤销栈 ，每次修改 fa[x] 前，把旧值 (x, fa[x]) 存入 p ，查询结束后回滚

- 普通并查集：路径压缩 fa[x] = findfa(fa[x]) ，但不记录修改。
- 带撤销版本 ：在修改 fa[x] 前，先把 (x, fa[x]) 推入撤销栈 p ，确保后续可以恢复原状。
- p.emplace_back(x, fa[x]) ：在路径压缩过程中，每一层节点的 fa 都会被改写，所以每一层都要记录
- 先找两个根。
- 根不同才合并： 记录旧值 (x, fa[x]) ，然后 fa[x] = y 。
- 这样撤销时可以把 fa[x] 恢复成原来的值
- 预处理阶段用不带撤销的版本 ，因为预处理不会被撤销。
- 后续查询阶段用带撤销的版本

- mod = 999979 ：质数哈希表大小（选择质数减少冲突）。
- st[mod+10] ：链表头数组，每个哈希桶一个链表头。
- edge 结构体 ：
- key ：完整的 64 位哈希键。
- last ：下一个同哈希值节点的下标（链地址法）。
- e[N*N*4] ：哈希表的节点池，每个节点存一个 key
- 计算哈希桶 h = key % mod 。
- 遍历链表，如果 key 已存在则 不重复插入 。
- 不存在则在链表头插入新节点（ ++tot 分配新位置）
同样算哈希桶，遍历链表找 key，找到返回 true ，没找到返回 false

- read(int&) ：标准快速整数读入，跳过非数字字符，逐字符转整数（ (x<<1)+(x<<3) = x*10 ， ch^48 = ch-'0' ）。
- readc(char&) ：快速读入字符，跳过非 # 和 . 的字符（只关心这两种）
h, w, q 网格高度、宽度、查询次数
g[...] 临时数组 ，用于存储附近所有连通块的根节点（去重后不重复）
dx[8], dy[8] 八方向偏移 （上、右上、右、右下、下、左下、左、左上）
x[N+10], y[N+10] 当前查询要修复的格子的坐标列表
16 个偏移，覆盖以当前格子为中心的 5×5 正方形边界 （距离 ≤ 2 的格子）。用于检查修复后的连通性是否与预计算的哈希表匹配
vis[i][j] ：标记网格 (i,j) 是否可通行（true = . 可通行，false = # 障碍）。
把 (x, y) 映射为并查集中的唯一编号。 w+2 是因为加了一圈边界（0 和 h+1 行、0 和 w+1 列），总宽度 w+2 。
y+1 让编号从 1 开始（并查集需要自环 fa[id] = id ）。

- 读入网格高 h 、宽 w 、查询数 q 。
- 遍历每个格子，读字符： ch == '.' 则可通行 vis[i][j]=true 。
手动设置四角和相邻位置为可通行 。这是经典技巧：
- 左上外部节点可以通过这几个位置连通到网格内部。
- 右下外部节点同理。
- 这样就把 边界的连通性问题 转化为 网格内部的连通性问题 。
遍历所有格子（包括虚拟边界），每个节点的父节点初始化为自己（自环）
合并所有 障碍格 （ vis=false ），规则是 八方向 （上下左右 + 四个对角），两两相邻的障碍合并到同一个连通块
上 i>0 && !vis[i-1][j] (i,j) 和 (i-1,j)
左 j>0 && !vis[i][j-1] (i,j) 和 (i,j-1)
左上 i>0 && j>0 && !vis[i-1][j-1] (i,j) 和 (i-1,j-1)
右上 i>0 && j<w+1 && !vis[i-1][j+1] (i,j) 和 (i-1,j+1)
预处理阶段用 merge1 合并，但没有做路径压缩。这里统一对所有节点做一次 findfa1 ，让每个节点直接指向根（彻底路径压缩），后续查询更快。
遍历所有 可通行格 （ vis=true ），跳过左上 (1,1) 和右下 (h,w)
- g[0] 是计数器（栈顶指针风格），初始 0。
- 遍历八方向，如果某个方向相邻的是障碍格（ !vis ），把那个障碍格的 连通块根 存入 g[++g[0]] 。
- 这样 g[1..g[0]] 就是当前可通行格周围所有障碍连通块的根节点列表
两两配对 + 插入哈希表 ：
- 对当前可通行格周围的所有障碍连通块根做两两配对 (g[k], g[w]) 。
- 如果两个根不同，插入哈希表 t ：
  - 键 = N*N*g[k] + g[w] （用 ull 避免溢出）。
  - 同时插入 (g[w], g[k]) （反过来也插入，因为查询时方向不确定）
- id(h+1, 0) ： 右下外部节点 的编号。
- id(0, w+1) ： 左上外部节点 的编号。
- 如果这两个节点在同一个连通块 → 原始网格已经不满足要求了， 所有查询都输出 NO ，直接 return
读当前查询要修复的 k 个格子的坐标 (x[i], y[i])
- 先把两个外部节点的根加进 g 。
- 再把每个修复格周围的障碍连通块根也加进 g 。
- 这些是查询中 可能受影响的连通块根 ，用于后续的哈希表查询
- 把要修复的格子标记为障碍（ vis=false ），然后 与周围八方向的障碍合并 。
- 使用 带撤销的 merge ，所有修改会被记录到 p 栈中
修复后如果左上和右下外部连通了 → 直接 ans=false
遍历每个修复格的 16 个近邻（5×5 边界）：
- 对于每个可通行的近邻格（实际是障碍格 !vis ，因为修复后 vis 是 false），检查：
  - 修复格和近邻格中，一个连通左上外部、另一个连通右下外部 → ans=false （对角路径被打通了）。
- 这个检查基于"修复可能改变附近 5×5 范围的连通性"的局部影响假设
用预计算的哈希表做最终检查：
- 遍历 g 中所有连通块根的两两配对。
- 如果预计算的哈希表中 曾经存在 配对 (g[i], g[j]) （说明原始网格中这两个连通块被某个可通行格隔开）。
- 而修复后这两个连通块的状态变成： 一个连通左上外部、另一个连通右下外部 → ans=false （对角路径被打通了）。
- 输出答案 ：NO 或 YES， fflush(stdout) 确保立即输出。
- 恢复 vis 数组 ：把修复过的格子重新标记为可通行（ vis=true ）。
- 撤销并查集 ：
- ranges::reverse(p) ：把撤销栈反转（栈是 push 顺序，撤销要倒序）。
- for(auto v:p) fa[v.first]=v.second ：逐个恢复 fa 的旧值。
- p.clear() ：清空撤销栈，准备下一次查询
 */
#include <bits/stdc++.h>
using namespace std;
#define ii pair<int, int>
#define ull unsigned long long
constexpr int N = 1010;

int fa[N*N+10];
vector<ii> p;
int findfa(int x) {
	if(fa[x]==x) return x;
	p.emplace_back(x,fa[x]);
	return fa[x]=findfa(fa[x]);
}
void merge(int x,int y) {
	x=findfa(x),y=findfa(y);
	if(x!=y) {
		p.emplace_back(x,fa[x]);
		fa[x]=y;
	}
}
int findfa1(int x) {
	if(fa[x]==x) return x;
	return fa[x]=findfa1(fa[x]);
}
void merge1(int x,int y) {
	x=findfa1(x),y=findfa1(y);
	if(x!=y) fa[x]=y;
}
const ull mod=999979;
struct hash_table {
	int st[mod+10],tot;
	struct edge { ull key;int last; } e[N*N*4];
	void insert(ull key) {
		ull h=key%mod;
		for(int i=st[h];i!=0;i=e[i].last)
			if(e[i].key==key) return;
		e[++tot].key=key;
		e[tot].last=st[h];
		st[h]=tot;
	}
	bool query(ull key) {
		ull h=key%mod;
		for(int i=st[h];i!=0;i=e[i].last)
			if(e[i].key==key)
				return true;
		return false;
	}
}t;

void read(int &res) {
	res=0;char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while('0'<=ch&&ch<='9') res=(res<<1)+(res<<3)+(ch^48),ch=getchar();
}
void readc(char &ch) {
	ch=getchar();
	while(ch!='#'&&ch!='.') ch=getchar();
}

int h, w, q, g[N*N+10], dx[] = {-1, -1, -1, 0, 0, 1, 1, 1},
dy[] = {-1, 0, 1, -1, 1, -1, 0, 1}, x[N+10], y[N+10], dex[] = {
	-2, -2, -2, -2, -2, -1, -1, 0, 0, 1, 1, 2, 2, 2, 2, 2
}, dey[] = {
	-2, -1, 0, 1, 2, -2, 2, -2, 2, -2, 2, -2, -1, 0, 1, 2
};
bool vis[N+10][N+10];

int id(int x, int y) { return x*(w+2)+y+1; }

int main() {
	read(h),read(w),read(q);
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++) {
			char ch;readc(ch);
			vis[i][j]=(ch=='.');
		}
	vis[0][0]=vis[0][1]=vis[1][0]=vis[h+1][w+1]=vis[h][w+1]=vis[h+1][w]=true;
	for(int i=0;i<=h+1;i++)
		for(int j=0;j<=w+1;j++)
			fa[id(i,j)]=id(i,j);
	for(int i=0;i<=h+1;i++)
		for(int j=0;j<=w+1;j++) {
			if(vis[i][j]) continue;
			if(i>0&&!vis[i-1][j]) merge1(id(i,j),id(i-1,j));
			if(j>0&&!vis[i][j-1]) merge1(id(i,j),id(i,j-1));
			if(i>0&&j>0&&!vis[i-1][j-1]) merge1(id(i,j),id(i-1,j-1));
			if(i>0&&j<w+1&&!vis[i-1][j+1]) merge1(id(i,j),id(i-1,j+1));
		}
	for(int i=0;i<=h+1;i++)
		for(int j=0;j<=w+1;j++)
			fa[id(i,j)]=findfa1(id(i,j));
	for(int i=1;i<=h;i++)
		for(int j=1;j<=w;j++) {
			if(!vis[i][j]) continue;
			if(i==1&&j==1||i==h&&j==w) continue;
			g[0]=0;
			for(int d=0;d<8;d++)
				if(!vis[i+dx[d]][j+dy[d]])
					g[++g[0]]=fa[id(i+dx[d],j+dy[d])];
			for(int k=1;k<=g[0];k++)
				for(int w=k+1;w<=g[0];w++)
					if(g[k]!=g[w])
						t.insert((ull)N*N*g[k]+g[w]),t.insert((ull)N*N*g[w]+g[k]);
		}
	if(fa[id(h+1,0)]==fa[id(0,w+1)]) {
		while(q--) { puts("NO\n"); fflush(stdout); }
		return 0;
	}
	for(int k;q--;) {
		read(k);
		for(int i=1;i<=k;i++) read(x[i]),read(y[i]);
		g[0]=0,g[++g[0]]=fa[id(h+1,0)],g[++g[0]]=fa[id(0,w+1)];
		for(int i=1;i<=k;i++)
			for(int d=0;d<8;d++)
				if(!vis[x[i]+dx[d]][y[i]+dy[d]])
					g[++g[0]]=fa[id(x[i]+dx[d],y[i]+dy[d])];
		for(int i=1;i<=k;i++) {
			vis[x[i]][y[i]]=false;
			for(int d=0;d<8;d++)
				if(!vis[x[i]+dx[d]][y[i]+dy[d]])
					merge(id(x[i],y[i]),id(x[i]+dx[d],y[i]+dy[d]));
		}
		bool ans=true;
		if(findfa(id(h+1,0))==findfa(id(0,w+1))) ans=false;
		else {
			for(int i=1;i<=k;i++) {
				for(int d=0;d<16;d++) {
					int Dx=x[i]+dex[d],Dy=y[i]+dey[d];
					if(0<=Dx&&Dx<=h+1&&0<=Dy&&Dy<=w+1&&!vis[Dx][Dy]) {
						if(findfa(id(h+1,0))==findfa(id(Dx,Dy))&&findfa(id(0,w+1))==findfa(id(x[i],y[i]))
						||findfa(id(h+1,0))==findfa(id(x[i],y[i]))&&findfa(id(0,w+1))==findfa(id(Dx,Dy))) {
							ans=false;
							break;
						}
					}
				}
				if(!ans) break;
			}
			if(ans) {
				for(int i=1;i<=g[0];i++) {
					for(int j=1;j<=g[0];j++)
						if(g[i]!=g[j]) {
							if(t.query((ull)N*N*g[i]+g[j]))
								if(findfa(id(h+1,0))==findfa(g[i])&&findfa(id(0,w+1))==findfa(g[j])) {
									ans=false;
									break;
								}
						}
					if(!ans) break;
				}
			}
		}
		if(!ans) puts("NO"); else puts("YES"); fflush(stdout);
		for(int i=1;i<=k;i++) vis[x[i]][y[i]]=true;
		ranges::reverse(p);
		for(auto v:p) fa[v.first]=v.second;
		p.clear();
	}
	return 0;
}