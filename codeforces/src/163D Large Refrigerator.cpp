//
// Created by Psy.C on 2025/11/27.
//
/*
*t: 测试用例数
n: 因子种类数
w[N]: 因子值数组
c[N]: 每个因子的指数数组
A, B, C: 最优解的三个维度
v: 目标体积（初始化为1）
s: 当前最优解（初始化为很大值3×10^18）
 *
*计算函数alpha(a) = 2√(a)√(v) + v/a
这是用于优化的连续函数近似解
返回向下取整的整数值
 *
*三维DFS的第二层：固定第一维a，搜索第二维b和第三维c
剪枝条件：如果a×b² > v，则不可能是有效解
*递归终止条件：处理完所有因子
计算目标函数值：a×b + v/a + v/b
如果更优则更新最优解
*枚举当前因子在第二维b中的分配
从c[p]个因子中选择i个分配给b维
递归处理下一个因子
 *
*三维DFS的第一层：搜索第一维a
剪枝条件：如果a³ > v，则不可能是有效解
*递归终止条件：处理完所有因子
使用连续近似解alpha(a)进行初步筛选
如果可能更优则进入第二层搜索
*枚举当前因子在第一维a中的分配
从c[p]个因子中选择i个分配给a维
递归处理下一个因子
 */
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;
typedef long double ld;
constexpr int N = 127;
constexpr ld eps = 1e-6;
ll t, n, w[N], c[N], A, B, C,
v(1), s(3e18);

ll alpha(const ll a) {
    const auto ad= static_cast<double>(a),
    vd = static_cast<double>(v),
    res = 2. * sqrt(ad) * sqrt(vd) + vd / ad;
    return static_cast<ll>(floor(res));
}

void dfs1(const int p, const ll a, const ll b) {
    if (static_cast<ld>(b) * static_cast<ld>(b) *
        static_cast<ld>(a) - eps > static_cast<ld>(v)) return;
    if (p == n) {
        if (a * b + v / a + v / b < s) {
            s = a * b + v / a + v / b;
            A = a; B = b; C = v / a / b;
        }
        return;
    }
    ll cm = 1;
    for (int i = 0; i < c[p]; ++i) cm *= w[p];
    for (ll i = c[p]; i >= 1; --i) {
        c[p] -= i;
        dfs1(p + 1, a, b * cm);
        c[p] += i;
        cm /= w[p];
    }
    dfs1(p + 1, a, b);
}

void dfs(const int p, const ll a) {
    if (static_cast<ld>(a) * static_cast<ld>(a) *
        static_cast<ld>(a) - eps > static_cast<ld>(v)) return;
    if (p == n) { if (alpha(a) < s) dfs1(0, a, 1); return; }
    ll cm = 1;
    for (int i = 0; i < c[p]; ++i) cm *= w[p];
    for (ll i = c[p]; i >= 1; --i) {
        c[p] -= i;
        dfs(p + 1, a * cm);
        c[p] += i;
        cm /= w[p];
    }
    dfs(p + 1, a);
}

int main() {
    fast;
    cin >> t;
    while (t--) {
        v = 1; s = 3e18;
        cin >> n;
        for (int i = 0; i < n; ++i) {
            cin >> w[i] >> c[i];
            for (int j = 0; j < c[i]; ++j) v *= w[i];
        }
        dfs(0, 1);
        cout << (s<<1) << ' ' << A << ' ' << B << ' ' << C << '\n';
    }
    return 0;
}