//
// Created by Psy.C on 2026/10/26.
//

/**
真正学会的起点..
node：每个物品两个属性 a、b。数组 a[N] 存物品（注意结构体名与成员同名 a，这里成员 a.b 引用的是结构体数组里每个元素的字段）。
cmp：排序规则——先按 a 降序（x.a > y.a），a 相同时按 b 降序（x.b > y.b）。
dp[N][N]：DP 表，用于 check。
v[N]：分组——v[i] 存第 i 组内物品的下标（在排序后数组 a[] 中的下标）。
m：组数；n：物品总数。
memset(dp, 0x3f, ...)：初始化为大值，dp[0][0]=0。
外层循环遍历 m 个组，sum 累积到当前组为止的物品总数。
dp[i][j]：表示处理完前 i 组，共选 j 个物品时的最小化对象的取值。
内层对每个 j，枚举当前组选 k 个物品（0 ≤ k ≤ 本组大小，且有约束 k ≤ j 且 j-k >= sum-j）。
x：当 k>0 时累加本组被选中的前 k 个物品的线性表达式：
每个选中物品贡献 1000*a - mid*b。
注意：本组内选的是"排序后下标 v[i][0..k-1]"的前 k 个。由于组内已经按 a/b 降序排序，通常取"最大/最优的 k 个"。
转移：dp[i][j] = min( dp[i][j], dp[i-1][j-k] + x )。
最后：若存在 dp[m][i] <= 0，返回 true（可行）。
语义解读：check(mid) 在问——能不能在每组按序各取若干（总数任意）的前提下，让目标值 1000*Σa - mid*Σb ≤ 0。即是否
Σ
a
Σ
b
≤
m
i
d
1000
Σb
Σa
​
 ≤
1000
mid
​
 ，是典型的 0-1 分数规划 / 最优比率问题（二分比值 + DP 判定）。
读入 n，然后读入 n 个 a、n 个 b（注意 rep 定义 for(i=1;i<=n;++i)，这里使用了全局 i）。
sort(a+1, a+1+n, cmp)：对物品 1..n 排序。
a[0].a = a[1].a - 1：给哨兵位赋一个不同于第一个组的值，保证分组时第一组能正确触发 ++m。
分组：遍历排序后的物品，若 a[i].a != a[i-1].a 则开新组（++m），把下标 i 放入当前组 v[m]。由于已排序，a 相同的会连续分在同一组。
二分：l=0, r=inf(1e11)。check(mid) 可行则把 ans 更新为 mid 并缩小上界（找最小可行 mid），否则放大下界。注意这里 r 是 1e11（10^11），mid 是整数值。
最终输出 ans（最小的可行 mid，即最优比率的二分近似值）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(i=1;i<=n;++i)
#define ll long long
using namespace std;

constexpr ll N = 55, inf = 1e11;

struct node { ll a, b; } a[N];
bool cmp(node x, node y) { return x.a == y.a ? x.b > y.b : x.a > y.a; }

ll dp[N][N];
int m, n;
vector<int> v[N];
bool check(ll mid) {
    memset(dp, 0x3f, sizeof(dp)); dp[0][0] = 0;
    for (int i = 1, sum = 0; i <= m; ++i) {
        sum += v[i].size();
        for (int j = 0; j <= sum; ++j) {
            ll x = 0;
            for (int k = 0; k <= v[i].size() && k <= j && j-k >= sum-j; ++k) {
                if (k) x += 1ll*1000*a[v[i][k-1]].a-mid*a[v[i][k-1]].b;
                dp[i][j] = min(dp[i][j], dp[i-1][j-k]+x);
            }
        }
    }
    for (int i = 0; i <= n; ++i)
        if (dp[m][i] <= 0) return 1;
    return 0;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int main() {
    fast;
    n = rd();
    int i;
    rep(i,n) a[i].a = rd();
    rep(i,n) a[i].b = rd();
    sort(a+1, a+1+n, cmp);
    a[0].a = a[1].a - 1;
    rep(i,n) {
        if (a[i].a != a[i-1].a) ++m;
        v[m].push_back(i);
    }
    ll l = 0, r = inf, ans = 0;
    while (l <= r) {
        ll mid = (l+r)>>1;
        if (check(mid)) ans = mid, r = mid-1;
        else l = mid+1;
    }
    cout << ans << '\n';
    return 0;
}