//
// Created by Psy.C on 2026/5/3.
//
/**
fc[20]: 存储2的幂次，fc[i] = 2^i
Log[N]: 存储每个数的以2为底的对数
n, m: 全局变量，分别表示两个字符串的长度
sa[i]: 排名为i的后缀的起始位置
rk[i]: 位置i开始的后缀的排名
hi[i]: sa[i]和sa[i-1]的最长公共前缀长度
h[18][N]: 用于RMQ的ST表，h[i][j]表示区间[j, j+2^i-1]的最小值
wx[], wy[]: 计数排序的辅助数组
wa[], wb[]: 倍增算法的临时数组

比较从位置a和b开始的长度为l的子串是否相等
r[a]==r[b]: 检查前半部分是否相等
r[a+l]==r[b+l]: 检查后半部分是否相等
如果两部分都相等则返回true

初始化计数数组wx，清零字符频次统计
统计每个字符出现次数，同时初始化x数组
x[i]=r[i]: 第一轮排序，x[i]就是字符本身
wx[r[i]]++: 对字符r[i]计数
计算前缀和，得到每个字符的结束位置
从后向前遍历，根据计数排序确定第一轮的后缀顺序
~i等价于i>=0
--wx[x[i]]: 获取字符x[i]在排序中的位置
sa[--wx[x[i]]]=i: 将位置i的后缀放在正确排名
倍增算法主循环
j<<=1等价于j*=2: j翻倍
m=p: 更新字符集大小为当前不同的等级数
将第二关键字为0的后缀（即后缀不够长的）加入y数组
将第一关键字存在且有效的后缀加入y数组
sa[i]>=j: 当前后缀位置足够靠后，能构成长度为j的子串
sa[i]-j: 对应的原始位置
清空计数数组
统计第一关键字的出现次数
wy[i]=x[y[i]]: 记录y[i]的第一关键字
wx[wy[i]]++: 对第一关键字计数
计算前缀和，得到第一关键字的结束位置
根据第一关键字对后缀进行排序
交换x和y的指针，并重新分配等级
t=x,x=y,y=t: 交换x和y的指向
p=1: 新等级从1开始
x[sa[0]]=0: 最小后缀等级为0
根据比较结果分配等级
如果两个后缀相等(cmp返回true)，则等级相同(p-1)
否则等级递增(p++)

计算height数组，k记录当前公共前缀长度
根据sa数组计算rk数组：排名为i的后缀的原始位置是sa[i]
计算height数组，hi[i] = LCP(sa[i], sa[i-1])
每次循环结束后更新k和i
如果k>0则减1，否则保持0
j=sa[rk[i]-1]: 找到排名比当前后缀小1的后缀位置
r[i+k]==r[j+k]: 逐位比较直到不相等
++k: 增加公共前缀长度

调整数组，将索引向右偏移
sa[i]++: sa数组索引加1
rk[i]=rk[i-1]: rk数组向前偏移
设置边界条件
初始化RMQ的ST表
h[0][i]=hi[i]: 第0层就是height数组本身
ST表预处理
fc[j] = 2^j: 预先计算的2的幂
h[j][i]=min(h[j-1][i],h[j-1][i+fc[j-1]]): 区间最小值合并
完整构建后缀数组流程
注意这里传入n+1是因为需要特殊处理结尾
查询区间[x,y]的RMQ值
t=Log[y-x+1]: 计算覆盖整个区间的最大2的幂
返回两个重叠区间的最小值
计算两个后缀的最长公共前缀
转换为排名，然后查询RMQ
比较两个长度为l的子串
如果公共前缀长度≥l，则相等(0)
否则根据排名判断大小关系
特殊的字符串比较函数
fg=x>y: 记录原始大小关系
如果x>y则交换，统一处理x<y的情况
第一种情况：第二个字符串完全包含第一个字符串的某个范围
分段比较不同部分的字典序
第二种情况：字符串有重叠部分
同样分段比较，最后返回基于原始顺序的比较结果

计算数字的位数
y存储最高位的权值
从高位到低位输出数字
x / y获取当前最高位
x % y去掉最高位
y /= 10降一位

Q: 查询数量
len: 总长度
a: 合并后的字符串数组
b: 用于排序的索引数组
c: 排序后的位置映射
ans: 答案数组
mi: RMQ数组
s1, s2: 两个输入字符串
l,r: 查询区间
k: 步长
x,y: 范围限制
id: 查询编号

初始化函数
读入两个字符串和查询数量
计算长度
预计算Log数组，利用递推log2(i) = log2(i/2) + 1
预计算2的幂次方
将字符串转换为数字数组，'a'对应1，'z'对应26
RMQ查询函数，类似calc函数
处理小k值的查询
按k值排序查询
遍历每个k值，找到对应的所有查询
对每种余数k进行RMQ预处理
在满足条件的范围内查询答案
处理大k值的查询，暴力枚举步长
主求解函数
构建后缀数组
对后缀排序
建立位置映射
读入查询并初始化答案
分别处理大小k值
输出结果

 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5 + 7, lim = 90, inf = 0x3f3f3f3f;

int fc[20], Log[N], n, m;
namespace SA {
    int sa[N],rk[N],hi[N],h[18][N];
	int wx[N],wy[N],wa[N],wb[N];
	///比较两个子串是否相等：从位置a开始和从位置b开始的长度为l的子串是否相同
	bool cmp(int *r,int a,int b,int l){return r[a]==r[b] && r[a+l]==r[b+l];}

	/**
	 *
	 * @param r 输入的字符串数组
	 * @param n 字符串长度
	 * @param m 字符集大小
	 */
	void getsa(int *r,int n,int m) {
		int *x=wa,*y=wb,*t,i,j,p;
		for(i=0;i<m;++i) wx[i]=0;
		for(i=0;i<n;++i) wx[x[i]=r[i]]++;
		for(i=1;i<m;++i) wx[i]+=wx[i-1];
		for(i=n-1;~i;--i) sa[--wx[x[i]]]=i;
		for(p=0,j=1;p<n;j<<=1,m=p) {
			for(p=0,i=n-j;i<n;++i) y[p++]=i;
			for(i=0;i<n;++i) if(sa[i]>=j) y[p++]=sa[i]-j;
			for(i=0;i<m;++i) wx[i]=0;
			for(i=0;i<n;++i) wx[wy[i]=x[y[i]]]++;
			for(i=1;i<m;++i) wx[i]+=wx[i-1];
			for(i=n-1;~i;--i) sa[--wx[wy[i]]]=y[i];
			for(t=x,x=y,y=t,i=1,p=1,x[sa[0]]=0;i<n;++i)
				x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
		}
	}
	///相邻排名后缀的最长公共前缀
	void getheight(int *r,int n) {
		int i,j,k=0;
		for(i=1;i<=n;++i) rk[sa[i]]=i;
		for(i=0;i<n;hi[rk[i++]]=k)
			for(k?--k:0,j=sa[rk[i]-1];r[i+k]==r[j+k];++k);
	}
	///将索引整体向右移动一位
	void adjust(int n) {
		for(int i=n;i;--i) sa[i]++,rk[i]=rk[i-1];
		sa[0]=rk[0]=0;
	}
	void output(int n) {
		for(int i=0;i<=n;++i) printf("%d ",sa[i]); puts("");
		for(int i=0;i<=n;++i) printf("%d ",rk[i]); puts("");
		for(int i=0;i<=n;++i) printf("%d ",hi[i]); puts("");
	}
	///用于快速查询区间最小值
	void initrmq(int n) {
		for(int i=1;i<=n;++i) h[0][i]=hi[i];
		for(int j=1;j<18;++j) for(int i=1;i+fc[j]-1<=n;++i)
			h[j][i]=min(h[j-1][i],h[j-1][i+fc[j-1]]);
	}
	void buildsa(int *r,int n,int m) {
		getsa(r,n+1,m);getheight(r,n);adjust(n);initrmq(n);
	}
	///排名在x到y之间的后缀的最小height值
	int calc(int x,int y) {
		int t=Log[y-x+1];
		return min(h[t][x],h[t][y-fc[t]+1]);
	}
	///从位置x和y开始的两个后缀的最长公共前缀长度
	int lcp(int x,int y) {
		x=rk[x];y=rk[y];
		if(x>y) swap(x,y);
		return calc(x+1,y);
	}
	///比较从位置x和y开始的长度为l的两个子串的字典序关系
	int comp(int x,int y,int l) {
		if(lcp(x,y)>=l) return 0;
		return (rk[x]<rk[y])?-1:1;
	}
	///比较两个子串的字典序关系
	bool cmpst(int x,int y) {
		int fg=x>y,t; if(fg) swap(x,y);
		if(m+x<=y)
		{
			t=comp(n+1,x+1,m);
			if(t) return (t<0)^fg;
			t=comp(x+1,x+m+1,y-(x+m));
			if(t) return (t<0)^fg;
			t=comp(y-m+1,n+1,m);
			if(t) return (t<0)^fg;
		}
		else
		{
			t=comp(n+1,x+1,y-x);
			if(t) return (t<0)^fg;
			t=comp(n+y-x+1,n+1,x+m-y);
			if(t) return (t<0)^fg;
			t=comp(x+1,m+n+x-y+1,y-x);
			if(t) return (t<0)^fg;
		}
		return fg^1;
	}
}

namespace IO {
    inline int rd() {
        int f = 0, ch = 0;
        int x = 0;
        for (; !isdigit(ch); ch = getchar())
            if (ch == '-')
                f = 1;
        for (; isdigit(ch); ch = getchar())
            x = (x << 1) + (x << 3) + (ch & 15);
        if (f)
            x = -x;
        return x;
    }
    template <class T>
    void write(T x) {
        if (x < 0) {
            putchar('-');
            x = -x;
        }
        T y = 1;
        int len = 1;
        for (; y <= x / 10; y *= 10)
            ++len;
        for (; len; --len, x %= y, y /= 10)
            putchar(x / y + 48);
    }
    void write_sp(int x) {
        write(x);
        putchar(' ');
    }
}
using namespace IO;

int Q, len;
namespace JJ {
    int a[N],b[N],c[N],ans[N],mi[18][N];
	char s1[N],s2[N];

	struct data {
		int l,r,k,x,y,id;
		void in(int t){ l=rd();r=rd();k=rd();x=rd();y=rd();id=t; }
		bool operator<(const data&rhs) const{ return k<rhs.k; }
	} q[N];
	void init() {
		scanf("%s%s",s1,s2);Q=rd();
		n=strlen(s1);m=strlen(s2);len=n+m;
		for(int i=2;i<=len;++i) Log[i]=Log[i>>1]+1;
		fc[0]=1;for(int i=1;i<18;++i)fc[i]=fc[i-1]<<1;
		for(int i=0;i<n;++i)a[i]=s1[i]-'a'+1;
		for(int i=0;i<m;++i) a[n+i]=s2[i]-'a'+1;
	}
	///计算区间[x,y]内的最小值，使用RMQ
	int calp(int x,int y) {
		if(x>y) return inf;
		int t=Log[y-x+1];
		return min(mi[t][x],mi[t][y-fc[t]+1]);
	}
	///处理小k值的查询（k ≤ lim），使用分块方法
	void solvesmall() {
		sort(q+1,q+Q+1);
		for(int i=1,j=1;i<=lim && j<=Q;++i) if(i==q[j].k) {
			int t=j;
			while(t<Q && q[t+1].k==i) ++t;
			for(int k=0;k<i;++k) {
				int tmp=(n+1)/i+(k<=n%i);
				for(int i1=1;i1<=tmp;++i1) mi[0][i1]=c[(i1-1)*i+k];
				for(int j1=1;j1<18;++j1) for(int i1=1;i1+fc[j1]-1<=tmp;++i1)
					mi[j1][i1]=min(mi[j1-1][i1],mi[j1-1][i1+fc[j1-1]]);
				for(int i1=j;i1<=t;++i1) {
					if(q[i1].x<=k && k<=q[i1].y)
						ans[q[i1].id]=min(ans[q[i1].id],calp((q[i1].l-k+i-1)/i+1,(q[i1].r-k+i)/i));
				}
			}
			j=t+1;
		}
	}
	///处理大k值的查询（k > lim），暴力枚举
	void solvebig() {
		for(int i=1;i<=n+1;++i) mi[0][i]=c[i-1];
		for(int j=1;j<18;++j) for(int i=1;i+fc[j]-1<=n+1;++i)
			mi[j][i]=min(mi[j-1][i],mi[j-1][i+fc[j-1]]);
		for(int i=1;i<=Q;++i) if(q[i].k>lim) {
			for(int j=0;j*q[i].k<=n;++j)
				ans[q[i].id]=min(ans[q[i].id],calp(max(j*q[i].k+q[i].x,q[i].l)+1,min(j*q[i].k+q[i].y,q[i].r)+1));
		}
	}
	void solve() {
		SA::buildsa(a,len,30);
		for(int i=0;i<=n;++i) b[i]=i;
		sort(b,b+n+1,SA::cmpst);
		for(int i=0;i<=n;++i) c[b[i]]=i;
		for(int i=1;i<=Q;++i) q[i].in(i),ans[i]=inf;
		solvesmall();solvebig();
		for(int i=1;i<=Q;++i) write_sp(ans[i]<inf?b[ans[i]]:-1);
	}
}

int main() {
    JJ::init(); JJ::solve();
    return 0;
}
