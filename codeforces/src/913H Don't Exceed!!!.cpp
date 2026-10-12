//
// Created by Psy.C on 2026/10/12.
//
/**
eval(const vi& f, int x) —— 多项式求值
用 Horner 法则求 f(x)。注意系数数组是升幂存储：f = [c0, c1, ..., cm-1] 表示 f(x)=c0 + c1·x + ...
从最高次逐次 ans = x·ans + ci 折叠，得到多项式值（我验证 eval([1,2],3)=7，即 1+2·3 ✓）
eval(iv f, int x) —— 分段函数求值
用 ranges::upper_bound 找到 x 所在分段（断点 ≤ x 的最后一段），对该段多项式求值。这是分段函数的求值入口
flatten(iv f, int x) —— 在断点 x 处"压平"
若最后一段的起点已 ≤ x 则不动；否则把 x 之后的分段删掉，在 x 处补入一个值等于当前函数值 eval(f,x) 的常值分段，用于后续在 x 处以该值继续构建
integral(const vi& f) —— 单多项式不定积分
对升幂系数做积分：F[0]=0，F[i]=f[i-1]·inv[i]（模 998244353 下的逆元）。即 F(x)=∫f dx + C，常数项取 0（我验证公式 ✓）
这是关键：对每段多项式逐段积分，并调整各段的积分常数，使积分结果在整个定义区间上连续。第 i 段积分后，令其常数项 p[0] = t - eval(p, x_i)，其中 t 是前一积分段在断点处的累积值。这样把若干"分片不定积分"拼成一个连续的整体函数
minus（两个重载）—— 多项式 / 分段函数相减
单多项式版：对应位系数相减。
分段版：把两个分段函数的所有断点合并排序，在每个子区间上对应段多项式相减，保证逐点 f - g
trans(const vi& f, int k) —— 平移 Taylor 展开
trans(f,k) 计算 g(x) = f(x + k) 的系数。推导（我验证过）：f(x+k) = Σⱼ [Σᵢ≥ⱼ C(i,j)·k^(i-j)·f[i]]·xʲ，代码用二维耗散 res[j] += C[i][j]·k^(i-j)·f[i] 精确实现了这一点 ✓。这里 k += mod 处理负数
trans(const iv& f, int k) —— 分段平移
把每个分段的多项式做 trans(p,k)（即把该段整体沿 x 平移 k），并把所有断点 x -= k，最前面补 (0, 0) 段。

mod = 998244353（常用 NTT 模数），INV = 616898040 是某个常数的模逆（我验证它不是 1/2，其确切含义需题干确认）。
M=40、N=1e3 为规模上限；inf=1e6 用作 trans 里的平移量 -inf。
init() 预计算 inv[1..N]（费马逆元）和组合数 C[i][j]（杨辉三角）。这些是 integral（÷i）和 trans（C(i,j)）所需
trans(ans, -inf)：把函数沿 x 平移 -1e6；
minus(ans, ·)：两个分段函数相减；
integral：积分（得到一个连续的分段函数）；
mul(·, INV)：整体乘以常数 INV；
flatten(·, a[i])：在数值 a[i] 处压平截断。
然后再进入下一轮。最终输出最末一段多项式的常数项 (--ans.end())->second[0]。

从形态上看，这正是"连续随机变量分布函数 / 生存函数的逐次卷积与截断"的经典写法：minus(ans, trans(ans,-inf)) 对应某种"平移后相减"（如求某随机过程在一段时间的增量、或两个相邻时刻的分布差），integral 对应把密度转成分布函数，mul INV 对应归一化因子，flatten(a[i]) 对应按给定的 n 个阈值逐级截断

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define vi vector<int>
#define iv vector<pair<int, vi>>
using namespace std;

constexpr int N = 1e3, mod = 998244353, INV = 616898040, M = 40, inf = 1e6;

int eval(const vi& f, int x) {
    int ans = 0;
    for (int i = f.size()-1; ~i; --i) ans=(1ll*x*ans+f[i])%mod;
    return ans;
}

int eval(iv f, int x) {
    return eval((--ranges::upper_bound(f, make_pair(x, vi())))->second, x);
}

iv flatten(iv f, int x) {
    if ((--f.end())->first <= x) return f;
    int val = eval(f, x);
    f.erase(ranges::lower_bound(f, make_pair(x, vi())), f.end());
    f.emplace_back(x, vi(1, val));
    return f;
}

vi mul(vi f, int v) {
    for (int& i : f) i = 1ll*i*v%mod;
    return f;
}
iv mul(iv f, int v) {
    for (auto &p: f | views::values)
        p = mul(p, v);
    return f;
}

int inv[N+10];
vi integral(vi f) {
    if (*--f.end()) f.push_back(0);
    for (int i = f.size()-1; i; --i) f[i] = 1ll*inv[i]*f[i-1]%mod;
    f[0] = 0;
    return f;
}

iv integral(iv f) {
    int t = 0, n = f.size();
    for (int i = 0; i < n; ++i) {
        auto& p = f[i].second;
        p = ::integral(p);
        p[0] = (1ll*p[0]+t-eval(p, f[i].first)+mod)%mod;
        if (i < n-1) t = eval(p, f[i+1].first);
    }
    return f;
}

vi minus(const vi& f, const vi& g) {
    vi h;
    for (int i = 0; i < max(f.size(), g.size()); ++i)
        h.push_back(((i<f.size()?f[i]:0)-(i<g.size()?g[i]:0)+mod)%mod);
    return h;
}
iv minus(const iv& f, const iv& g) {
    assert(f[0].first == 0 && g[0].first == 0);
    vector<int> pt;
    int n = f.size(), m = g.size();
    for (int i = 0; i < n; ++i) pt.push_back(f[i].first);
    for (int i = 0; i < m; ++i) pt.push_back(g[i].first);
    ranges::sort(pt); pt.erase(ranges::unique(pt).begin(), pt.end());
    iv ans;
    int i = 0, j = 0;
    for (int x : pt) {
        if (i < n-1 && f[i+1].first <= x) i++;
        if (j < m-1 && g[j+1].first <= x) j++;
        ans.emplace_back(x, ::minus(f[i].second, g[j].second));
    }
    return ans;
}

int C[N+10][N+10];
vi trans(const vi& f, int k) {
    k += mod;
    vi res(f.size(), 0);
    for (int i = 0; i < f.size(); ++i) {
        int t = 1;
        for (int j = i; ~j; --j)
            res[j]=(res[j]+1ll*t*C[i][j]%mod*f[i])%mod, t=1ll*t*k%mod;
    }
    return res;
}
iv trans(iv f, int k) {
    for (auto& [x, p] : f) x -= k, p = trans(p, k);
    f.emplace(f.begin(), 0, vi(1, 0));
    return f;
}


void init() {
    inv[1] = 1;
    for (int i = 2; i <= N; ++i)
        inv[i] = 1ll*(mod-mod/i)*inv[mod%i]%mod;
    for (int i = 0; i <= N; ++i) {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = (C[i-1][j] + C[i-1][j-1])%mod;
    }
}


int n, a[M];
string s[M];
void solve() {
    cin >> n; init();
    for (int i = 1; i <= n; ++i) {
        cin >> s[i];
        if (s[i].find('.') == -1) s[i] += ".000000";
        else {
            while (s[i].size()-s[i].find('.') <= 6)
                s[i] += '0';
        }
        for (char c : s[i])
            if (c != '.') a[i] = a[i]*10 + c - '0';
    }
    iv ans; ans.emplace_back(0, vi(1, 1));
    for (int i = 1; i <= n; ++i)
        ans = ::flatten(::mul(::integral(::minus(ans, trans(ans, -inf))),
            INV), a[i]);
    cout << (--ans.end())->second[0] << '\n';
}

int main() {
    fast;
    solve();
    return 0;
}