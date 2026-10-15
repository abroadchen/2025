//
// Created by Psy.C on 2026/10/15.
//
/**
N 既作为数组开的上界，也作为“权值阈值基准”。因为读入的权值 t[i] 都是 [1, 1e5] 级别的，加/减一个很大的偏移 100001 > N，就能让一个点权值从“≤N”翻到“>N”或反之，从而改变它是否被计入 all
struct edge{ int to,nxt; }e[N];         // 链式前向星存树边
bool col[N];                            // col[i] = 1 表示节点 i 已被“删除/不点亮”
int n,m,
	fa[N],   // 父亲
	head[N], // 前向星头
	cnt,     // 边计数
	dfn[N],  // dfs 序（点到 dfs 编号）
	idx,     // dfs 序计数器
	top[N],  // 所在重链顶端
	sz[N],   // 子树大小
	son[N],  // 重儿子
	dep[N],  // 深度
	bel[N],  // dfs 编号属于哪个块
	idfn[N], // dfs 编号 -> 点
	tail[N]; // 重链底端点
int t[N];               // 每个点权值
int all;                // 全局答案（统一点亮节点中权值> N 的个数）
int blocks;             // 分块个数
vector<int>tmp;         // sort 辅助数组
int tot[600005];        // 值域桶（值偏移后计数），供块内部分重排用

每一“块”管理一段 dfs 序连续的区间 [L, R]，维护这些位置上的点权
struct Block{
	int L{}, R{}, tag{};        // 区间左右端点；整块懒标记 tag
	vector<int> a;              // a[i] 该块第 i 个位置的“加点”偏移记录
								// 实际点权 = 原始 t + tag + a 中额外值
	vector<pair<int,int>> b;    // 压缩后的权值->个数(前缀和)表，按权值升序
	int it{};                   // 二分指针：第一个满足 b[i].first + tag > 0 的位置
	int ans{};                  // 当前块内满足条件的点数
b 是一张“权值 → 个数”的有序表，并且 second 存的是前缀和（前 i 个权值的总个数）。tag 是整块统一加的“懒标记”。

实际判定“某权值 > N”等价于判定 权值 > N = 100001−1，代码用了一个技巧：
读入时 t[i]++，删除时 add(id, 100001)、添加时 add(id, -100001)，所以一个点的“有效权值” = t[原] + ±100001 + tag。
判断 权值 + tag > N 即 权值 + tag > 100001，等价于 权值 + tag ≥ 100002，也就是 权值 + tag > 0（因为 t[i]≥1，偏移后约等于判断是否 > 100001）。
it 指向 b 中第一个使 first + tag > 0 的位置，因此 ans = it ? b[it-1].second : 0（即小于该位置的个数之和，也就是 ≤0 的那些；因为整块按 cnt[b[x]][a[x]]>N 升序判断，实际统计的是 first+tag > 0 的个数的互补——这块细节结合主逻辑看，ans 表示“满足条件（权值> N）的点数”）


分成一条条块，且块的边界与重链对齐——块都是长度约 0.7*sqrt(链长) 的“链上连续段”。这样“某个 x 到它的重链顶端”的路径区间，在 dfs 序上就是若干个完整块，可被整块懒标记快速处理。
all 在此处被初始化为所有块 ans 之和
删除一个点亮节点 erase(x)
先给被删节点本身权值 +100001，使它确定性超过阈值 N（col 标记它计入统计）。
然后从它的父亲一直沿着重链往上：对每条重链的 [dfn[top], dfn[x]] 区间做 dec（整块减 1 / 散块重构），相当于“x 到根路径”整体减 1，同时更新全局答案 all。

步骤 A：全局答案先扣掉本块旧贡献
老规矩：改块前先把 all 中的这段 ans 扣掉，改完再加回
步骤 B：求出实际受到 −1 影响的散点
代码开头 dec(int l,int r) 的参数是主函数传来的“所在重链的 [L,R]”，可能覆盖不完全。这里把它裁剪到本块范围内，只处理本块真正被覆盖的部分。所以下面处理的 [l, r] 是本块内真正减 1 的那段
a[i - L] 是块内第 i-L 个位置的a值。
++tot[200001 + x]：在真正 −1 之前，用桶记录“原值 x 有几个点被减”。200001 是偏移量偏置，因为 x 可能为负（权值可能被 tag 或其他操作减到负），加上 200001 保证下标非负（tot 开了 600005，足够容纳 [-200001, 200001] 范围）。
--x 真正把该点权值减 1。
注意：这里只改了 a，没改 tag——因为散块里只有这一部分被减，不能整体动 tag。
为什么用桶 tot？因为多个点可能有相同权值，比如 5 个点权值都是 7，它们被 −1 后都变成 6。桶把相同原值合并计数，避免一个点一个点去处理，O(块长)
步骤 C：把 b 表从“前缀和”还原成“原始频率
之前 b[i].second 存的是前缀和（前 i 个频率之和）。这里从后往前差分，把每个 b[i].second 还原成该权值自己的频率（注意 i 从大到小，因为 b[i-1] 还是旧前缀和，从后往前才不会破坏）。

现在 b 变成：(权值, 该权值的个数)，是未加 −1 影响的原始频率表（仍按权值升序）
步骤 D：从 b 中“减去”被 −1 的部分，生成变化表 t1
遍历 b 的每个权值 fst。如果这个权值在步骤 B 中有被减的点（tot[桶] != 0）：
把这 x 个点“从原权值 fst”移到“新权值 fst-1”，记录到 t1：(fst-1, x)。
从 b 中这个权值的频率里扣掉 x（因为这些点不再留在原权值处）。
清空桶。
所以此时：
b = 处理掉被减点后的剩余原始频率表（仍升序，但有些权值少了/空了）；
t1 = 所有因为 −1 而新产生的权值 (fst-1, x)，也是升序（因为 b 升序，fst-1 也升序）
步骤 E：归并（merge）b 与 t1，生成新表 t2
标准的双指针归并，b 和 t1 都升序：

first 相等 → 合并频率；
否则取 first 较小者。
x == 0 的表项跳过（不存空频率）。
结果 t2 是一个新的、按权值升序的频率表，包含了散点 −1 之后的完整权值分布。此时它还是“频率”形式（不是前缀和）
步骤 F：重建前缀和 + 重算 it 与 ans
把新表 t2 重新变成前缀和，写入 b。

重新用 tag 计算指针 it：第一个满足 b[i].first + tag > 0 的位置。
这里 upper_bound(make_pair(-tag, ...))：找第一个 first > -tag 的项，即 first + tag > 0。

ans = it ? b[it-1].second : 0：b[it-1] 是最后一个 first+tag ≤ 0 的项，其前缀和就是“权值有效值≤ N 的点数”。
最后 all += ans 把新贡献加回
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+10;

struct edge{ int to,nxt; }e[N];
bool col[N];
int n,m,fa[N],head[N],cnt,dfn[N],idx,top[N],sz[N],son[N],dep[N],bel[N],idfn[N],tail[N];
int t[N];
int all,blocks;
vector<int>tmp;
int tot[600005];
struct Block{
	int L{},R{}, tag{};
	vector<int>a;
	vector<pair<int,int>>b;
	int it{},ans{};
	void re(){//把 a 排序，压缩成 (权值, 个数前缀和)，然后根据 tag 计算 it 和 ans
		tmp=a;
		ranges::sort(tmp);
		b.clear();
		int v=tmp[0],x=1;
		for(int i=1;i<tmp.size();++i)
		if(tmp[i]!=v)b.emplace_back(v,x),x=1,v=tmp[i];else ++x;
		b.emplace_back(v,x);
		for(int i=1;i<b.size();++i)b[i].second+=b[i-1].second;
		it=upper_bound(b.begin(),b.end(),make_pair(-tag,0x3fffffff))-b.begin();
		ans=it?b[it-1].second:0;
	}
	void init(int l,int r){//用 dfs 序区间初始化块
		L=l,R=r;
		for(int i=l;i<=r;++i)a.push_back(t[idfn[i]]);
		re();
	}
	//单点权值改动的压缩表维护 在 b 有序表里删除/插入一个权值值为 val 的单点，并维护前缀和
	//（找到含 val 的位置，把它之后所有前缀和 −1，再把该位置计数 −1，若计数为 0 或有重复前缀值则擦除该表项。）
	void _erase(int val){
		auto pos=ranges::lower_bound(b,make_pair(val,0));
		for(auto i=pos+1;i<b.end();++i)--i->second;
		--pos->second;
		if((pos==b.begin()&&!pos->second)||pos->second==(pos-1)->second)b.erase(pos);
	}
	//（把 val 及其之后所有前缀和 +1；若 val 不存在则插入新表项。）
	void _insert(int val){
		auto pos=ranges::lower_bound(b,make_pair(val,0));
		for(auto i=pos;i<b.end();++i)++i->second;
		if(pos==b.end()||pos->first!=val){
			int ct=(pos==b.begin()?1:(pos-1)->second+1);
			b.insert(pos,make_pair(val,ct));
		}
	}
	//块内单点权值加 x 改答案前扣掉、改完再加回，保证 all 始终等于各块 ans 之和
	void add(int id,int x){
		all-=ans;//先从全局答案中“扣除”旧的块贡献
		id=id-L;//转为块内下标
		_erase(a[id]);
		_insert(a[id]+=x);//修改该点权值并更新压缩表
		it=upper_bound(b.begin(),b.end(),make_pair(-tag,0x3fffffff))-b.begin();
		ans=it?b[it-1].second:0;
		all+=ans;//再把新块贡献加回全局答案
	}
	//区间“整块/散块”加权-1 / +1（删除/添加的路径区间加）
	void dec(int l,int r){
		all-=ans;
		l=max(l,L),r=min(r,R);
		if(L==l&&r==R){//若区间覆盖整个块 [L,R]：只需修改懒标记 tag，并移动指针 it（O(1)）
			--tag;
			if(it<b.size()&&b[it].first+tag<=0)++it;
			ans=it?b[it-1].second:0;
			all+=ans;
			return;
		}
		/*否则是“散块”，需要重构 b 表：对区间内每个散点先“解除前缀和”for(...,i) b[i].second -= b[i-1].second，
		 *用 tot 桶收集权值变化，再合并 t1（变化点）与 b 做归并（类似 merge-sort），重建前缀和，最后重算 it、ans、all。
		 *dec 与 inc 结构几乎一致，只是符号相反、字典序相反的判断（< vs >）*/
		static pair<int,int>t1[N],t2[N];int top1=0,top2=0;
		for(int i=l;i<=r;++i){
			int&x=a[i-L];
			++tot[200001+x];//用值域桶记录：这个值有一个点要被 -1
			--x;//实际把该点权值 -1
		}
		for(int i=b.size()-1;i;--i)b[i].second-=b[i-1].second;
		for(auto &[fst, snd] : b)
			if(tot[200001+fst]){
				int&x=tot[200001+fst];
				t1[++top1]=make_pair(fst-1,x);//原值 fst 有 x 个点被减到 fst-1
				snd-=x,x=0;//从 b 的原始频率里减去这些点 清桶
			}
		int it1=0,it2=1;
		while(it1<b.size()&&it2<=top1)
			if(b[it1].first==t1[it2].first){
				int x=b[it1].second+t1[it2].second;
				if(x)t2[++top2]=make_pair(b[it1].first,x);
				++it1,++it2;
			}else
				if(b[it1].first<t1[it2].first){
					int x=b[it1].second;
					if(x)t2[++top2]=make_pair(b[it1].first,x);
					++it1;
				}else{
					int x=t1[it2].second;
					if(x)t2[++top2]=make_pair(t1[it2].first,x);
					++it2;
				}
		while(it1<b.size()){
			int x=b[it1].second;
			if(x)t2[++top2]=make_pair(b[it1].first,x);
			++it1;
		}
		while(it2<=top1){
			int x=t1[it2].second;
			if(x)t2[++top2]=make_pair(t1[it2].first,x);
			++it2;
		}
		b.clear();
		for(int i=1;i<=top2;++i)t2[i].second+=t2[i-1].second,b.push_back(t2[i]);
		it=upper_bound(b.begin(),b.end(),make_pair(-tag,0x3fffffff))-b.begin();
		ans=it?b[it-1].second:0;
		all+=ans;
	}
	void inc(int l,int r){
		all-=ans;
		l=max(l,L),r=min(r,R);
		if(L==l&&r==R){
			++tag;
			if(it&&b[it-1].first+tag>0)--it;
			ans=it?b[it-1].second:0;
			all+=ans;
			return;
		}
		static pair<int,int>t1[N],t2[N];int top1=0,top2=0;
		for(int i=l;i<=r;++i){
			int&x=a[i-L];
			++tot[200001+x];
			++x;
		}
		for(int i=b.size()-1;i;--i)b[i].second-=b[i-1].second;
		for(auto &[fst, snd] : b)
			if(tot[200001+fst]){
				int&x=tot[200001+fst];
				t1[++top1]=make_pair(fst+1,x);
				snd-=x,x=0;
			}
		int it1=0,it2=1;
		while(it1<b.size()&&it2<=top1)
			if(b[it1].first==t1[it2].first){//两表同一权值 → 频率相加
				int x=b[it1].second+t1[it2].second;
				if(x)t2[++top2]=make_pair(b[it1].first,x);
				++it1,++it2;
			}else
				if(b[it1].first<t1[it2].first){//b 较小 → 取 b
					int x=b[it1].second;
					if(x)t2[++top2]=make_pair(b[it1].first,x);
					++it1;
				}else{//t1 较小 → 取 t1
					int x=t1[it2].second;
					if(x)t2[++top2]=make_pair(t1[it2].first,x);
					++it2;
				}
		while(it1<b.size()){
			int x=b[it1].second;
			if(x)t2[++top2]=make_pair(b[it1].first,x);
			++it1;
		}
		while(it2<=top1){
			int x=t1[it2].second;
			if(x)t2[++top2]=make_pair(t1[it2].first,x);
			++it2;
		}
		b.clear();
		for(int i=1;i<=top2;++i)t2[i].second+=t2[i-1].second,b.push_back(t2[i]);
		it=upper_bound(b.begin(),b.end(),make_pair(-tag,0x3fffffff))-b.begin();
		ans=it?b[it-1].second:0;
		all+=ans;
	}
}G[N];

//求重儿子、子树大小、深度（轻重链剖分第一步）
void dfs(int now){
	sz[now]=1,son[now]=0;
	for(int i=head[now];i;i=e[i].nxt){
		dep[e[i].to]=dep[now]+1;
		dfs(e[i].to);
		sz[now]+=sz[e[i].to];
		if(!son[now]||sz[son[now]]<sz[e[i].to])son[now]=e[i].to;
	}
}

//分配 dfs 序，并按重链分块
void dfs2(int now){
	idfn[dfn[now]=++idx]=now;
	if(son[now])top[son[now]]=top[now],dfs2(son[now]);else tail[top[now]]=now;//重链末端记下
	for(int i=head[now];i;i=e[i].nxt) if(e[i].to!=son[now])dfs2(top[e[i].to]=e[i].to);
	if(top[now]==now){//当前点是某条重链的顶端 → 对该链分块
		int l=dfn[now],r=dfn[tail[now]],siz=0.7*sqrt(r-l+1);
		if(siz<1)siz=1;
		for(int i=l;i<=r;i+=siz){
			const int L=i,R=min(i+siz-1,r);
			G[++blocks].init(L,R);
			for(int j=L;j<=R;++j)bel[j]=blocks;
			all+=G[blocks].ans;
		}
	}
}
void erase(int x){
	int id=dfn[x];
	if(col[x])return;//已删除则跳过
	col[x]=1;//标记
	G[bel[id]].add(id,100001);//该点权值 +100001（超过阈值N）
	for(x=fa[x];x;x=fa[top[x]]){//沿 x 到根的每条重链
		int L=dfn[top[x]],R=dfn[x];
		const int bL=bel[L],bR=bel[R];
		for(int i=bL;i<=bR;++i)G[i].dec(L,R);//路径上所有点权值 -1
	}
}
void add(int x){
	int id=dfn[x];
	if(!col[x])return;//已点亮则跳过
	col[x]=0;//取消标记
	G[bel[id]].add(id,-100001);//该点权值 -100001（恢复 ≤N）
	for(x=fa[x];x;x=fa[top[x]]){//x 到根路径每条重链
		int L=dfn[top[x]],R=dfn[x];
		const int bL=bel[L],bR=bel[R];
		for(int i=bL;i<=bR;++i)G[i].inc(L,R);//路径上所有点权值 +1
	}
}
int main(){
	fast;
	cin>>n>>m;
	for(int i=2;i<=n;++i){
		cin>>fa[i];
		e[++cnt]=(edge){.to = i,.nxt = head[fa[i]]},head[fa[i]]=cnt;
	}
	for(int i=1;i<=n;++i)cin>>t[i],++t[i];//权值整体 +1
	dfs(dep[1]=1);
	dfs2(top[1]=1);//建树剖 + 分块，初始化 all
	while(m--){
		int k;
		cin>>k;
		//删除 添加
		if(k>0)erase(k);else add(-k);
		cout<<all<<' ';
	}
	return 0;
}