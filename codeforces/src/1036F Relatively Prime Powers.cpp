//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
if (res >= inf/i) return inf+7; 表示若 res*i 会超过上限 inf=2e18，直接返回一个极大值 inf+7 作为"溢出哨兵"。
因为二分里要用 ksm(mid,x) <= n 比较，一旦溢出就返回无穷大，Comparator 会正确判定为"超过 n"。
inf+7 纯粹是一个远小于 2^63、又大过 n 上限的标记值，用它表示"这个数的 x 次方已经爆了，肯定 > n"
用浮点 pow(n, 1.0/x) 估计 x 次根的大致位置，再上下浮动 ±3 作为二分范围（避免浮点误差）。
二分查找满足 mid^x <= n 的 最大 mid（即 ⌊n^(1/x)⌋）。
最后返回 res-1：去掉 mid=1 的情况（因为底数至少为 2），即统计的是满足 2 ≤ base 且 base^x ≤ n 的底数个数。
例：find(2) 表示 ⌊√n⌋ - 1，即区间 [2, ⌊√n⌋] 里有几个数可作为平方的底
莫比乌斯函数 μ(n) 的定义：

μ(n) = 1      若 n 是 1 或偶数个不同质因子的乘积
μ(n) = -1     若 n 是奇数个不同质因子的乘积
μ(n) = 0      若 n 含有平方因子（某个质因子出现≥2次）
在这题里，mu[i] 的作用是容斥系数：用来剔除被"重复计数"的完全幂
find(i) = 满足 base^i ≤ n 的底数个数（即 cnt(i) 减去底为1的情况）；
累加 mu[i] * find(i) 完成容斥；
枚举上限 1ll<<i <= n（即 2^i ≤ n），因为底数最小为2时幂次最大到 log2(n)；
跳过 mu[i]==0（含平方因子的指数无贡献）。
最后：

ans = (n-1)  [总整数数]  −  [完全幂个数]  =  非完全幂个数
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1010;
constexpr ll inf = 2e18;

ll ksm(ll i, ll p) {
    ll res = 1ll;
    while (p) {
        if (p&1) {
            if (res >= inf/i) return inf+7;
            res = res*i;
        }
        if (p > 1) {
            if (i > inf/i) return inf+7;
            i = i*i;
        }
        p >>= 1;
    }
    return res;
}

ll n;
int find(int x) {
    int l = max(1,(int)pow(n,1.0/x)-3), r = (int)pow(n,1.0/x)+3;
    int res = 0;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (ksm(mid, x) <= n) { res = mid; l = mid+1; }
        else r = mid-1;
    }
    return res-1;
}

int mu[N], isp[N], pr[N], cnt;
void init() {
    mu[1] = 1;
    for (int i = 2; i <= 100; ++i) {
        if (!isp[i]) {
            pr[++cnt] = i;
            mu[i] = -1;//质数的 μ = -1
        }
        for (int j = 1; j <= cnt && pr[j]*i <= 100; ++j) {
            isp[i*pr[j]] = 1;
            if (i%pr[j] == 0) { mu[i*pr[j]] = 0; break; }//有平方因子 → μ=0
            mu[i*pr[j]] = -mu[i];//否则 μ 变号
        }
    }
}


int main() {
    fast;
    init();
    int T; cin >> T;
    while (T--) {
        cin >> n;
        ll ans = n-1;//初始：认为 [2,n] 全部"非完全幂"（共 n-1 个）
        for (int i = 2; 1ll<<i <= n; ++i) {//只枚举指数 i，到 2^i <= n 为止
            if (mu[i] == 0) continue;//μ(i)=0 时该项容斥贡献为0，跳过
            ans += 1ll*mu[i]*find(i);//用莫比乌斯系数调整
        }
        cout << ans << '\n';
    }
    return 0;
}