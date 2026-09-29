//
// Created by Psy.C on 2026/9/29.
//
/***
dp0/dp1/dp2：三组"普通"（线性）DP，下标 0/1/2 代表末尾状态（比如末尾颜色/是否……具体由题定）。
ep0/ep1/ep2：三组"增强 / 特殊"DP，同样分三状态。
add(a,b)：a += b 并取模。
后面我们会看到 dp 与 ep 两套其实是高度同构的，ep 相当于对 dp 的"扩展/乘以分支数"。
第一部分：循环 i=2..n，得到 ans1 = ep2[n]
初始化：dp0[1]=1; ep0[1]=1;
对每个 i，依次考虑 四种"块长"的转移：块长 2、3、4、5（对应从 i-1, i-2, i-3, i-4 转移过来）。下面逐块解读。
块长 2（i>=2）
从 dp2[i-1] 加进 dp0[i] 和 ep0[i]。
含义：结尾状态 2 后面接一块长 2，转到状态 0
块长 3（i>=3）
从 i-2 的三种状态转移，系数是 2 的幂（×1、×2、×4 等），说明每个状态能展开的分支数成 2 的幂。
ep 与 dp 共用同一套 ddp，区别是 ep 额外累加 ddp * 2 的部分——ep 是 dp 的"带额外倍数"版本
块长 4（i>=4）
从 i-3 转移，三种状态汇成一个 ddp0，然后 dp0/dp1/dp2 都加上它（说明块长 4 后状态被"归一"为同一种）。
ep 加 ddp0*2
块长 5（i>=5）
从 i-4 转移，系数为 2 的更高次幂（×4、×8、×16）。
第一部分结果：ans1 = ep2[n];——即"首尾相接（环形）"那一部分的方案数取 ep2[n]
第二部分：清空数组，换初始化，重跑一遍
换了一组初始化（从 dp[2]=1, ep[2]=2 开始），表示另一类边界条件（比如"首尾不接、开头的固定结构不同"）。
转移体完全复用第一部分那四个 if 块（块长 2/3/4/5）。
第二部分答案取的是 n-1 处的各种状态做带权求和：
dp0、ep0 系数 1
dp1、ep1 系数 2
dp2、ep2 系数 1
最终答案 = ans1 + ans2

总方案数 =  环色部分(ep2[n] = ans1)
		  + 线性部分(dp0[n-1]+2·dp1[n-1]+dp2[n-1]
					+ ep0[n-1]+2·ep1[n-1]+ep2[n-1] = ans2)
两种边界情况分开算再相加：第一部分初始化 dp0[1]=1（从 1 开始，代表"首尾相接/环形"）；第二部分用 dp[2]=1（从 2 开始，代表"不接回/线性"），且取的是 n-1 的状态（不是 n），再乘不同系数。
同一套转移体被复用了两次：四个 if 块（块长 2/3/4/5）对应从 i-1, i-2, i-3, i-4 四种长度回退，检验了"结尾必须留出至少多大的空地"这类约束。
系数全是 2 的幂（×2、×4、×8、×16），强烈暗示每个状态存在"二选一/多选一"的分支展开，典型于"两种颜色 / 方向翻转"计数。
dp 与 ep 是两套视角：ep 基本是 dp 同构递推再额外加一个 ddp × 系数 项，用来区分"这种块是否允许 / 强制带某额外分支"。
ans2 的系数 (1,2,1)：对状态 0/1/2 分别加权 1、2、1，说明状态 1 有 2 种对称等价情况而在计数中被展开。
 */
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int N = 205416, mod = 998244353;
#define add(a,b) (a+=(b),a%=mod)

int n, dp0[N], dp1[N], dp2[N], ep0[N], ep1[N], ep2[N];
signed main() {
    scanf("%lld",&n);
    dp0[1]=1;ep0[1]=1;
	for(int i=2;i<=n;i++){
		if(i>=2) { add(dp0[i],dp2[i-1]); add(ep0[i],dp2[i-1]); }
		if(i>=3) {
			int ddp0=0,ddp1=0,ddp2=0;
			add(ddp0,dp0[i-2]);
			add(ddp1,dp0[i-2]*2); add(ddp1,dp1[i-2]);
			add(ddp2,dp0[i-2]*4); add(ddp2,dp1[i-2]*4); add(ddp2,dp2[i-2]);
			add(dp0[i],ddp0); add(dp1[i],ddp1); add(dp2[i],ddp2);
			add(ep0[i],ep0[i-2]);
			add(ep1[i],ep0[i-2]*2); add(ep1[i],ep1[i-2]);
			add(ep2[i],ep0[i-2]*4); add(ep2[i],ep1[i-2]*4); add(ep2[i],ep2[i-2]);
			add(ep0[i],ddp0*2); add(ep1[i],ddp1*2); add(ep2[i],ddp2*2);
		}
		if(i>=4) {
			int ddp0=0;
			add(ddp0,dp0[i-3]); add(ddp0,dp1[i-3]*2); add(ddp0,dp2[i-3]);
			add(dp0[i],ddp0); add(dp1[i],ddp0); add(dp2[i],ddp0);
			add(ep0[i],ddp0*2); add(ep1[i],ddp0*2); add(ep2[i],ddp0*2);
		}
		if(i>=5) {
			int ddp0=0,ddp1=0,ddp2=0;
			add(ddp0,dp0[i-4]);
			add(ddp1,dp0[i-4]*4); add(ddp1,dp1[i-4]);
			add(ddp2,dp0[i-4]*16); add(ddp2,dp1[i-4]*8); add(ddp2,dp2[i-4]);
			add(dp0[i],ddp0); add(dp1[i],ddp1); add(dp2[i],ddp2);
			add(ep0[i],ep0[i-4]);
			add(ep1[i],ep0[i-4]*4); add(ep1[i],ep1[i-4]);
			add(ep2[i],ep0[i-4]*16); add(ep2[i],ep1[i-4]*8); add(ep2[i],ep2[i-4]);
			add(ep0[i],ddp0*4); add(ep1[i],ddp1*4); add(ep2[i],ddp2*4);
		}
	}
	int ans1=ep2[n];
	memset(dp0,0,sizeof(dp0)); memset(dp1,0,sizeof(dp0)); memset(dp2,0,sizeof(dp0));
	memset(ep0,0,sizeof(dp0)); memset(ep1,0,sizeof(dp0)); memset(ep2,0,sizeof(dp0));
	dp0[2]=1;dp1[2]=1;dp2[2]=1;ep0[2]=2;ep1[2]=2;ep2[2]=2;
	for(int i=3;i<=n;i++){
		if(i>=2) { add(dp0[i],dp2[i-1]); add(ep0[i],dp2[i-1]); }
		if(i>=3) {
			int ddp0=0,ddp1=0,ddp2=0;
			add(ddp0,dp0[i-2]);
			add(ddp1,dp0[i-2]*2); add(ddp1,dp1[i-2]);
			add(ddp2,dp0[i-2]*4); add(ddp2,dp1[i-2]*4); add(ddp2,dp2[i-2]);
			add(dp0[i],ddp0); add(dp1[i],ddp1); add(dp2[i],ddp2);
			add(ep0[i],ep0[i-2]);
			add(ep1[i],ep0[i-2]*2); add(ep1[i],ep1[i-2]);
			add(ep2[i],ep0[i-2]*4); add(ep2[i],ep1[i-2]*4); add(ep2[i],ep2[i-2]);
			add(ep0[i],ddp0*2); add(ep1[i],ddp1*2); add(ep2[i],ddp2*2);
		}
		if(i>=4) {
			int ddp0=0;
			add(ddp0,dp0[i-3]); add(ddp0,dp1[i-3]*2); add(ddp0,dp2[i-3]);
			add(dp0[i],ddp0); add(dp1[i],ddp0); add(dp2[i],ddp0);
			add(ep0[i],ddp0*2); add(ep1[i],ddp0*2); add(ep2[i],ddp0*2);
		}
		if(i>=5) {
			int ddp0=0,ddp1=0,ddp2=0;
			add(ddp0,dp0[i-4]);
			add(ddp1,dp0[i-4]*4); add(ddp1,dp1[i-4]);
			add(ddp2,dp0[i-4]*16); add(ddp2,dp1[i-4]*8); add(ddp2,dp2[i-4]);
			add(dp0[i],ddp0); add(dp1[i],ddp1); add(dp2[i],ddp2);
			add(ep0[i],ep0[i-4]);
			add(ep1[i],ep0[i-4]*4); add(ep1[i],ep1[i-4]);
			add(ep2[i],ep0[i-4]*16); add(ep2[i],ep1[i-4]*8); add(ep2[i],ep2[i-4]);
			add(ep0[i],ddp0*4); add(ep1[i],ddp1*4); add(ep2[i],ddp2*4);
		}
	}
	int ans2=dp0[n-1]+dp1[n-1]*2+dp2[n-1]+ep0[n-1]+ep1[n-1]*2+ep2[n-1];
	printf("%lld\n",(ans1+ans2)%mod);
    return 0;
}