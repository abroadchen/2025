//
// Created by Psy.C on 2026/9/13.
//
/**
jump[u][0] = u 的父节点（倍增 LCA 用的第 0 层）。
对每个子节点 v，记录它与父节点之间边的字符 va。
hush1 / hush2 是沿边方向的哈希（用于后面树上字符串比较的"向上/向下"段）。
hush_rt[v] = root→v 路径字符串的 前缀哈希（每步乘 base + 字符）——用来比较两条"根到后代"路径的字典序。
hush_po[v] 是一个幂位置加权哈希
jump[j][i] = j 的 2^i 级祖先。hush1/hush2 倍增合并，得到任意向上/向下路径的 O(log n) 哈希查询

find 统计子树大小和最大子树；add 计算"颠倒后的最大部分"并选出重心 pointy（pointy 最终存的是重心，sz 之外用 son）。这是标准点分治的"不断向下递归找重心"
点分治建"重构树/重心树"：
每一层 depth 维护一组"这块里的重心" rtt[depth]。
bel[u][depth]：点 u 在 depth 层属于重心 rt 的哪个子树方向（0 表示 u 就是 rt，其它为子块编号 ppt）。
noe[rt]：以 rt 为根，按字符子树划分，用来后续二分排名。
递归 split(v, depth+1) 对每个子连通块继续点分治。
这是整题最核心的"点分治分层结构"，用于后续对任意路径字符串按字典序做"分段比较 + 计数排名"
以每个重心 RT 为根，把它能延伸出去的子树路径按字符建一棵 Trie（trie[RT][ch][pos]），va[RT][pos] 记录落在该 Trie 节点 pos 下的所有真实树上的点（用于最终计数）。这是把"树上点到根方向的路径"转成"字典序 trie"以便排序比较
dfs_cal：对每个 Trie 节点（前缀长度为 len），用字符串哈希 hushi 表示，把"落在此节点覆盖范围内的真实点"记录，并按长度丢进 discont[RT][len]（之后排序便于二分）。
str[RT][pos] 记录覆盖到当前位置的累计点数（用于后面的排名差值计算）。
sorty 对所有深度的节点按哈希排序 → 形成按字典序排序后的"节点桶"，这就是 SA（后缀数组）式的有序结构
hushit(x,y) 给出树上 x 到 y 路径的整条字符串的哈希（正向拼接），用于后面二分比较两条路径字符串是否相等/大小。
辅助：
que(x,y,l)：取路径上第 l 个节点。
jump_it(x,y,lca,l,len,cal)：返回从 x 走向 y 的路径上第 l 个节点（若 l 超过 cal 部分则从 y 那边倒数）

两条树的路径各看成字符串，fc 用 LCP + 比较下一个字符判断谁字典序大。返回值：
1 表示第一条路径更大，-1 表示更小，2 表示第一条是第二条前缀（更短），3 表示两条相等
取树上路径第 l 个字符（从 x 端起），供 fc 在 LCP 之后比较字符。query1 用跳表跳到对应节点，取出 hush1[x][0] 即该字符

对每次询问 (QX,QY)，题目要求返回"询问路径字符串在整棵树所有路径中的排名/个数"。dfs_ans 借助点分治层级 + Trie + 哈希二分，把"所有其他路径"按字典序和询问路径比大小，逐层累加比它小的路径数量 delta，最终 ANS 就是排名。主循环里 printf("%d\n", ANS-1) 输出。

flag 分支逻辑：
flag==-1：询问串比到该层重心的整条路径都小，这层计数为 0；
flag==1：询问串更大，重心 C 下的整片子树的所有路径都比它小，直接加 SIZE[C]（并减去下一层重复计数的部分差值）；
否则（flag==2 或询问串是该层前缀）：进入二分查找——用 discont[C][mid] 那些已按哈希排序好的桶，二分出"比询问串更小的最长前缀长度 ans"，再用 ddd（Trie 子树覆盖点数）计算这层贡献 delta，并处理小的 zdelta 去重修正。
else 里的大段二分：先二分 LCP 长度 mid（在 discont[C][mid] 中二分找第一个哈希 ≥ 询问串哈希的位置），得到 ans=最大可匹配长度、hhh=对应 Trie 节点。然后：

若 ans==QLEN-len（询问串这层完全匹配到底）：ddd = str[C][hhh-1] - va[C][hhh-1].size()（该前缀下的点数减去重复）。
否则：跳到 len+ans 位置比较下一字符，并在 Trie 的 0..s-1 字符子树中累加更小的覆盖数 maxn_sub，得到 ddd。
noe[C][col]（以重心 C 为根按子树划分的点的最终序号桶）配合 zdelta 二分，处理"同一重心不同子树方向"的去重——保证不重复计数


 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 2e4+1e3+5;
//字符串哈希基数 哈希模数
constexpr ll base = 70134ll, mod = 998244353ll;
//边计数 邻接表头 邻接表终点 邻接表下一指针
int cnt(0), hed[N], tal[N<<1], nxt[N<<1];
char val[N<<1];//边上字符
inline void addege(int x,int y,char z){
    cnt++;
    tal[cnt]=y;
    val[cnt]=z;
    nxt[cnt]=hed[x];
    hed[x]=cnt;
}

int jump[N][20], dep[N];
ll hush1[N][20], hush2[N][20], hush_rt[N], hush_po[N], hus[N];
inline void dfs(int u,int fa){
    jump[u][0]=fa;//2^0=1 级祖先
    for(int i=hed[u];i;i=nxt[i]){
        int v=tal[i];
        if(v==fa)  continue;
        dep[v]=dep[u]+1;//深度
        ll va=(val[i]-'a'+1);//字符转数字 1..26
        hush1[v][0]=va;//向上链哈希（正向）
        hush2[v][0]=va;//向下链哈希（反向）
        hush_rt[v]=(hush_rt[u]*base+va)%mod;//根到v的字符串哈希
        hush_po[v]=(hush_po[u]+(va*hus[dep[v]-2]%mod))%mod;//另一种哈希
        dfs(v,u);
    }
}

int sz[N], maxn, son[N], pointy;
bool used[N];
inline void find(int u,int fa){
    sz[u]=1;
    maxn++;
    for(int i=hed[u];i;i=nxt[i]){
        int v=tal[i];
        if(v==fa||used[v]) continue;
        find(v,u);
        sz[u]+=sz[v];
        son[u]=max(son[u],sz[v]);
    }
}

inline void add(int u,int fa){
    son[u]=max(son[u],maxn-sz[u]);//子树外部分
    if(son[u]<son[pointy]) pointy=u;//更新重心候选
    for(int i=hed[u];i;i=nxt[i]){
        int v=tal[i];
        if(v==fa||used[v]) continue;
        add(v,u);
    }
}

inline void clear(int u,int fa){//清空
    sz[u]=0;
    son[u]=0;
    for(int i=hed[u];i;i=nxt[i]){
        int v=tal[i];
        if(v==fa||used[v]) continue;
        clear(v,u);
    }
}

//求连通块v的重心
inline void findp(int v){
    pointy=0;
    clear(v,v);
    maxn=0;
    pointy=0;
    find(v,v);
    add(v,v);
}

int bel[N][20], b[N][20];
inline void dfs_modify1(int step,int u,int fa,int val,int noddd){
    bel[u][step]=val;
    b[u][step]=noddd;
    for(int i=hed[u];i;i=nxt[i]){
        int v=tal[i];
        if(v==fa||used[v]) continue;
        dfs_modify1(step,v,u,val,noddd);
    }
}
inline void dfs_modify2(int step,int u,int fa,int val){
    bel[u][step]=val;
    for(int i=hed[u];i;i=nxt[i]){
        int v=tal[i];
        if(v==fa||used[v]) continue;
        dfs_modify2(step,v,u,val);
    }
}

int isrt[N], SIZE[N], id[N], dis[N], indexy[N];
vector<int> rtt[20], init, nexty[N];
vector<vector<int>> noe[N];
inline void split(int exroot,int depth){
    clear(exroot,exroot);
    findp(exroot);
    int rt=pointy;//当前块重心
    isrt[rt]=depth;//记录这是 depth 层重心
    rtt[depth].push_back(rt);//该层所有重心
    int dd=pointy;
    SIZE[rt]=maxn;//当前块大小
    b[rt][depth]=rt;
    int ppt=0;
    //给块内每个点标 bel[u][depth]=0，并记录所属子树
    dfs_modify1(depth,exroot,exroot,0,dd);
    used[rt]=1;
    bel[rt][depth]=0;
    noe[rt].push_back(init);//init 是空 vector
    for(int i=hed[rt];i;i=nxt[i]){
        int v=tal[i];
        if(used[v]) continue;
        findp(v);
        nexty[dd].push_back(pointy);
        ++ppt;
        id[pointy]=ppt;
        dis[pointy]=val[i]-'a'+1;
        indexy[pointy]=v;
        dfs_modify2(depth,v,v,ppt);//该子树内所有点 bel[u][depth]=ppt
        noe[rt].push_back(init);
        split(v,depth+1);//递归下一层
    }
}

vector<int> trie[N][30], str[N], maxn_sub[N];
int nod[N]{};
vector<vector<int>> va[N];
inline void dfs_str(int u,int fa,int RT,int pos){
    for(int i=hed[u];i;i=nxt[i]){
        int v=tal[i];
        if(v==fa||used[v]) continue;
        if(!trie[RT][val[i]-'a'][pos-1]){//该字符子节点不存在就新建
            nod[RT]++;
            va[RT].push_back(init);
            va[RT][nod[RT]-1].push_back(v);
            trie[RT][val[i]-'a'][pos-1]=nod[RT];
            for(int k=0;k<=25;k++) trie[RT][k].push_back(0);
            str[RT].push_back(0);
            maxn_sub[RT].push_back(0);
            dfs_str(v,u,RT,nod[RT]);
        }
        else{
            va[RT][trie[RT][val[i]-'a'][pos-1]-1].push_back(v);
            dfs_str(v,u,RT,trie[RT][val[i]-'a'][pos-1]);
        }
    }
}

inline void make_Trie(){
    for(int i=1;i<=16;i++){
        for(int RT : rtt[i]){
            nod[RT]=1;
            va[RT].push_back(init);
            str[RT].push_back(0);
            maxn_sub[RT].push_back(0);
            va[RT][0].push_back(RT);
            for(int k=0;k<=25;k++) trie[RT][k].push_back(0);
            dfs_str(RT,RT,RT,1);//对 RT 建字符 Trie
            used[RT]=1;
        }
    }
}

int maxnnnn;
inline void dfs_first(int RT,int u,int depth){
    maxnnnn=max(maxnnnn,depth);
    for(int i=0;i<=25;i++){
        if(!trie[RT][i][u-1]) continue;
        dfs_first(RT,trie[RT][i][u-1],depth+1);
    }
}

struct node { ll hush; int nody; };
bool operator<(node x, node y) { return x.hush < y.hush; }
vector<vector<node>> discont[N];
int zzzzz(0), Count(0);
vector<int> final[N];
inline void dfs_cal(int RT,int u,int depth,ll hushi,int len){
    zzzzz=max(zzzzz,len);
    for(int i=0;i<va[RT][u-1].size();i++){
        final[RT].push_back(va[RT][u-1][i]);
        noe[RT][bel[va[RT][u-1][i]][depth]].push_back(final[RT].size());
        Count++;
        discont[RT][len].push_back((node){hushi,u});
    }
    str[RT][u-1]=Count;
    maxn_sub[RT][u-1]=Count;
    for(int i=0;i<=25;i++){
        if(!trie[RT][i][u-1]) continue;
        dfs_cal(RT,trie[RT][i][u-1],depth,(hushi*base%mod)+(i+1)%mod,len+1);
        maxn_sub[RT][u-1]=max(maxn_sub[RT][u-1],maxn_sub[RT][trie[RT][i][u-1]-1]);
    }
}

inline void dfs_second(int RT,int u,int value){
    int sum=0;
    for(int i=0;i<=25;i++){
        if(!trie[RT][i][u-1]) continue;
        dfs_second(RT,trie[RT][i][u-1],sum);
    }
}

vector<node> inint;
inline void sorty(){
    for(int i=1;i<=16;i++){
        for(int j=0;j<rtt[i].size();j++){
            int RT=rtt[i][j];
            maxnnnn=0;
            dfs_first(RT,1,0);//求最大深度 maxnnnn
            for(int k=0;k<=maxnnnn;k++) discont[RT].push_back(inint);
            Count=0;
            zzzzz=0;
            dfs_cal(RT,1,i,0ll,0);//计算每个 Trie 节点的哈希和覆盖
            for(int k=0;k<=zzzzz;k++){//同深度按哈希排序
                sort(discont[RT][k].begin(),discont[RT][k].end());
            }
            dfs_second(RT,1,0);
        }
    }
}

inline int LCA(int x,int y){
    if(dep[x]>dep[y]) swap(x,y);
    for(int i=16;i>=0;i--) if(dep[jump[y][i]]>=dep[x]) y=jump[y][i];
    if(x==y) return x;
    for(int i=16;i>=0;i--) if(jump[x][i]!=jump[y][i]) x=jump[x][i],y=jump[y][i];
    x=jump[x][0];
    return x;
}

//y 是 x 的祖先，返回 x 到 y 经过的边数
inline int calcnum(int x,int y){
    if(x==y) return 0;
    int sum=0;
    for(int i=16;i>=0;i--){
        if(dep[jump[x][i]]>dep[y]){
            sum+=(1<<i);
            x=jump[x][i];
        }
    }
    sum++;
    return sum;
}

//从 x 向上到 y 的路径字符哈希（顺序）
inline ll hushjump1(int x,int y){
    if(x==y) return 0;
    ll sum=0ll;
    for(int i=16;i>=0;i--) if(dep[jump[x][i]]>dep[y]) sum=((sum*hus[1<<i]%mod)+hush1[x][i])%mod,x=jump[x][i];
    sum=((sum*hus[1<<0]%mod)+hush1[x][0])%mod;
    return sum;
}
//从 y 向上到 x 的路径字符哈希（逆序拼接）
inline ll hushjump2(int x,int y){
    if(x==y) return 0;
    ll sum=0ll,cont=0;
    for(int i=16;i>=0;i--) if(dep[jump[y][i]]>dep[x]) sum=((hush2[y][i]*hus[cont]%mod)+sum)%mod,cont+=1ll<<i,y=jump[y][i];
    sum=((hush2[y][0]*hus[cont]%mod)+sum)%mod,cont+=1ll<<0,y=jump[y][0];
    return sum;
}
//完整 x→y 路径的字符串哈希
inline ll hushit(int x,int y){
    if(x==y) return 0;
    ll sum=0;
    int lca=LCA(x,y);
    sum=hushjump1(x,lca);
    sum=((sum*hus[calcnum(y,lca)]%mod)+hushjump2(lca,y))%mod;
    return sum;
}

inline int que(int x,int y,int l){
    if(l==0) return x;
    l--;
    for(int i=16;i>=0;i--) if(l&(1<<i)) x=jump[x][i];
    return jump[x][0];
}
inline int jump_it(int x,int y,int lca,int l,int len,int cal){
    if(l>len) return y;
    if(cal>=l) return que(x,lca,l);
    return que(y,lca,len-l);
}

//二分最长公共前缀长度
inline int lcp(int x_1,int y_1,int x_2,int y_2,int LCA1,int LCA2,int len1,int len2,int cal1,int cal2){
    int l=1,r=min(len1,len2),ans=0;
    while(l<=r){
        int mid=(l+r)>>1;
        int d_1=jump_it(x_1,y_1,LCA1,mid,len1,cal1);
        int d_2=jump_it(x_2,y_2,LCA2,mid,len2,cal2);
        if(hushit(x_1,d_1)==hushit(x_2,d_2)) ans=mid,l=mid+1;
        else r=mid-1;
    }
    return ans;
}

//返回路径 x→y 第 l 个边的字符数字
inline int query1(int x,int y,int l){
    l--;
    for(int i=16;i>=0;i--) if(l&(1<<i)) x=jump[x][i];
    return hush1[x][0];
}

inline int ask(int x,int y,int l,int lca,int len){
    if(calcnum(x,lca)>=l) return query1(x,lca,l);
    return query1(y,lca,len-l+1);
}

// 比较两条路径字符串
inline int fc(int x_1,int y_1,int x_2,int y_2){
    int LCA1=LCA(x_1,y_1),LCA2=LCA(x_2,y_2);
    int len1=calcnum(x_1,LCA1)+calcnum(y_1,LCA1);
    int len2=calcnum(x_2,LCA2)+calcnum(y_2,LCA2);
    int l=lcp(x_1,y_1,x_2,y_2,LCA1,LCA2,len1,len2,calcnum(x_1,LCA1),calcnum(x_2,LCA2));
    int aa,bb;
    if(len1==l) aa=-1;
    else aa=ask(x_1,y_1,l+1,LCA1,len1);//第 l+1 个字符是谁
    if(len2==l) bb=-1;
    else bb=ask(x_2,y_2,l+1,LCA2,len2);
    if(l==len2&&len1==len2) return 3;//完全相同
    if(l==len2) return 2;//第一条是第二条前缀
    if(aa>bb) return 1;//第一条更大
    return -1;//第一条更小
}

int QX,QY,QLCA,QCAL,QLEN, ANS(0);
inline void dfs_ans(int step) {
    if(!b[QX][step]) return;//QX 不在这一层重心块 → 返回
	int C=b[QX][step];//第 step 层的重心 C
	int flag=fc(QX,QY,QX,C);//比较询问路径 QX→QY 与 QX→C(重心) 的字典序
	int delta=0;
	if(flag==-1){//询问路径 < QX→C，此层重心所有都更大，无贡献
		delta=0;
	}
	else if(flag==1&&QX!=C){//询问路径更大，整个 C 子树路径都更小 → 全计入
		delta=SIZE[C];
		if(b[QX][step+1]) delta-=SIZE[b[QX][step+1]];
	}
	else{
		int T=LCA(QX,C);
		int len=calcnum(QX,T)+calcnum(C,T);
		int W=jump_it(QX,QY,QLCA,len,QLEN,QCAL);
		int EXW=jump_it(QX,QY,QLCA,len+1,QLEN,QCAL);
		int EEXW=jump_it(QX,QY,QLCA,len+2,QLEN,QCAL);
		int l=0,r=discont[C].size()-1,ans=0,hhh=0;
		while(l<=r){
			int mid=(l+r)>>1;
			int RL=jump_it(QX,QY,QLCA,len+mid,QLEN,QCAL);
			ll HUSH=hushit(W,RL);
			int exhus=0;
			int L=0,R=discont[C][mid].size()-1,AS=-1;
			while(L<=R){
				int MID=(L+R)>>1;
				if(discont[C][mid][MID].hush>HUSH) R=MID-1;
				else if(discont[C][mid][MID].hush<HUSH) L=MID+1;
				else{
					AS=discont[C][mid][MID].nody,exhus=discont[C][mid][MID].nody,L=MID+1;
				}
			}
			if(AS==-1) r=mid-1;
			else{
				ans=mid,hhh=exhus,l=mid+1;
			}
		}
		int ddd=0;
		if(ans==QLEN-len){
			if(hhh<=str[C].size()) ddd=str[C][hhh-1];
			ddd-=va[C][hhh-1].size();
		}
		else{
			int DDA=jump_it(QX,QY,QLCA,len+ans,QLEN,QCAL);
			int DDB=jump_it(QX,QY,QLCA,len+ans+1,QLEN,QCAL);
			int s=hushit(DDA,DDB);
			if(hhh<=str[C].size()) ddd=str[C][hhh-1];
			for(int i=0;i<26;i++){
				if(hhh>trie[C][i].size()) continue;
				if(trie[C][i][hhh-1]<=0) continue;
				if(i+1>=s) break;
				int p=trie[C][i][hhh-1];
				if(trie[C][i][hhh-1]<=maxn_sub[C].size()){
					if(maxn_sub[C][trie[C][i][hhh-1]-1]>ddd){
						ddd=maxn_sub[C][trie[C][i][hhh-1]-1];
					}
				}
			}
		}
		delta+=ddd;
		if(b[QX][step+1]!=0){
			int zdelta=0;
			int da=hushit(W,EXW);
			int db=dis[b[QX][step+1]];
			if(da<db) zdelta+=0;
			else if(da>db){
				zdelta+=SIZE[b[QX][step+1]];
			}
			else{
				int ctt=ddd;
				int col=bel[QX][step];
				l=1,r=noe[C][col].size(),ans=r+1;
				while(l<=r){
					int mid=(l+r)>>1;
					if(noe[C][col][mid-1]>ctt) ans=mid,r=mid-1;
					else l=mid+1;
				}
				zdelta+=ans-1;
			}
			delta-=zdelta;
		}
	}
	ANS+=delta;
	dfs_ans(step+1);
}

int n, q;
char c[2];
int main() {
    memset(b,0,sizeof(b));
    inint.clear();
    init.clear();
    son[0]=2147483647;
    memset(used,0,sizeof(used));
    scanf("%d%d",&n,&q);//n 个点，q 个询问
    hus[0]=1ll;
    for(int i=1;i<=n;i++) hus[i]=(hus[i-1]*base)%mod;//幂表
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        scanf("%s",c);
        addege(x,y,c[0]);
        addege(y,x,c[0]);
    }
    hush_po[1]=0ll;
    hush_rt[1]=0ll;
    dep[1]=1;
    dfs(1,1);//树上预处理（跳表+哈希）
    for(int i=1;i<=16;i++){
        for(int j=1;j<=n;j++){
            jump[j][i]=jump[jump[j][i-1]][i-1];
            hush1[j][i]=((hush1[j][i-1]*hus[1<<(i-1)]%mod)+(hush1[jump[j][i-1]][i-1]))%mod;
            hush2[j][i]=((hush2[jump[j][i-1]][i-1]*hus[1<<(i-1)]%mod)+(hush2[j][i-1]))%mod;
        }
    }
    memset(used,0,sizeof(used));
    split(1,1);//点分治分层
    memset(used,0,sizeof(used));
    make_Trie();//建重心 Trie
    sorty();//按哈希排序所有 Trie 节点 → SA 式有序结构
    int lx,ly,lans;
    for(int PPP=1;PPP<=q;PPP++){//
        scanf("%d%d",&QX,&QY);
        QLCA=LCA(QX,QY);
        QCAL=calcnum(QX,QLCA);
        QLEN=calcnum(QX,QLCA)+calcnum(QY,QLCA);//QX→QY 路径长度(边数)
        ANS=0;
        dfs_ans(1);//逐层统计排名
        lx=QX,ly=QY,lans=ANS-1;
        ANS--;
        printf("%d\n",ANS);//实际输出 ANS-1 或 ANS，取决于题目问"排名"还是"个数"
    }
    return 0;
}