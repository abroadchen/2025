//
// Created by Psy.C on 2026/1/29.
//
/**
* tmp[maxn]：临时数组，存储绝对值和索引
Imid：中间值
n,m：输入参数，数组长度和操作数
An：处理后数组的实际长度
tmpn：临时计数器
pre[maxn],nxt[maxn]：双向链表的前后指针
A[maxn]：处理后的差分数组
a[maxn]：原始输入数组
flag[maxn]：标记数组，表示节点是否有效
inq[maxn]：标记数组，表示节点是否在队列中
 */
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define maxn 4000005
#define LL long long
#define ii pair<LL,int>
using namespace std;

ii tmp[maxn],Imid;
int n,m,An,tmpn;
int pre[maxn],nxt[maxn];
LL A[maxn],a[maxn];
bool flag[maxn];
bool inq[maxn];
queue<int>  Q;
inline bool isdigit(char ch){return ((ch<='9')and(ch>='0'));}
inline void read(int &x){
	char ch;
	bool flag=false;
	for (ch=getchar();!isdigit(ch);ch=getchar()) if (ch=='-') flag=true;
	for (x=0;isdigit(ch);x=x*10+ch-'0',ch=getchar());
	x=flag?-x:x;
}
inline void read(LL &x){
	char ch;
	bool flag=false;
	for (ch=getchar();!isdigit(ch);ch=getchar()) if (ch=='-') flag=true;
	for (x=0;isdigit(ch);x=x*10+ch-'0',ch=getchar());
	x=flag?-x:x;
}
inline void write(int x){//输出整数
    static const int maxlen=100;
    static char s[maxlen];
    if(!x){ putchar('0'); return; }
    if (x<0) {putchar('-');x=-x;}
    int len=0; for(;x;x/=10) s[len++]=x%10+'0';
    for(int i=len-1;i>=0;--i) putchar(s[i]);
}

int min(int a,int b){if (a<b) return a; return b;}
int max(int a,int b){if (a>b) return a; return b;}

LL Labs(LL a){if (a<0) return -a;return a;}//绝对值函数

void prepare(){
	read(n); read(m);
	for (int i=1;i<=n;i++) read(a[i]);
	An=0;
	for (int i=2;i<=n;i++) if (a[i]!=a[i-1])
	{
		An++;
		A[An]=a[i]-a[i-1];//将原数组转换为差分数组
		if((An<2)&&(A[An]<=0)) An--;//跳过非正数的初始段
		if((An>1) &&((A[An]>0)==(A[An-1]>0)))//合并符号相同的连续段
		{
			An--;
			A[An]+=A[An+1];
		}
	}
	while (An>0 && A[An]<0) An--;//移除末尾的负数段
	//构建双向链表结构
	for (int i=0;i<An;i++) nxt[i]=i+1; nxt[An]=0;
	for (int i=1;i<=An;i++) pre[i]=i-1; pre[0]=An; A[0]=0;
}

void addqueue(int u) {
    if (ii(Labs(A[u]),u)<=Imid && !inq[u]) {
        Q.push(u);
        inq[u]=true;
    }
}

void merge(int x){
	int l=pre[x],r=nxt[x];
	//如果左右邻居绝对值更小，返回（不合并）
	if ((l>0) and (Labs(A[l])<Labs(A[x]))) return;
	if ((r>0) and (Labs(A[r])<Labs(A[x]))) return;
	if (!flag[x])return;//当前节点无效
	//更新链表结构，跳过左右邻居
	if (l>0) pre[x]=pre[l];
	if (r>0) nxt[x]=nxt[r];
	nxt[pre[x]]=x;
	pre[nxt[x]]=x;
	flag[l]=0; flag[r]=0;//标记邻居为无效
	A[x]+=A[l]+A[r];//将邻居的值合并到当前节点
	if (l==0)//邻居是边界节点
	{
		nxt[0]=nxt[x];
		pre[nxt[x]]=0;
		flag[x]=0;
	}
	if (r==0)
	{
		pre[0]=pre[x];
		nxt[pre[x]]=0;
		flag[x]=0;
	}
    if (pre[x]>0) addqueue(pre[x]);
    if (nxt[x]>0) addqueue(nxt[x]);
    addqueue(x);
}


void doit(){
	memset(flag,1,sizeof(flag));//初始化所有节点为有效
	for (;;)
	{
		tmpn=0;
		for (int i=nxt[0];i;i=nxt[i])
			if(flag[i])
				{
					tmpn++;
					tmp[tmpn]=ii(Labs(A[i]),i);//按绝对值和索引存储
				}
		if (tmpn-m*2<0) break;//剩余节点数少于 2m
		int mid=(tmpn-m*2+1)/2;
		nth_element(tmp+1,tmp+mid,tmp+tmpn+1);
		Imid=tmp[mid];
		while (!Q.empty()) Q.pop();
		for (int i=nxt[0];i;i=nxt[i])  addqueue(i);
        while (!Q.empty()) {
            int u=Q.front();Q.pop();
            inq[u]=false;
            merge(u);
    	}
	}
	LL ans=0LL;
	for (int i=nxt[0];i;i=nxt[i]) if (A[i]>0) ans+=A[i];
	printf("%lld\n",ans);
}


int main() {
    fast;
    prepare();
    doit();
    return 0;
}