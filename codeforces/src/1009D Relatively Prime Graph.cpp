//
// Created by Psy.C on 2026/10/29.
//

/**
真正学会的起点..
递归+迭代的辗转相除法（欧几里得算法）‍求最大公约数。

首先若 a < b，交换确保 a ≥ b（使被除数不小于除数）。
然后 while (b) 迭代：a % b 不断取余，直到 b 变为 0，此时 a 就是 gcd。
（其实交换那步冗余——欧几里得算法不管 a<b 也能正确工作，但保证 a≥b 能减少迭代次数一点的书写，逻辑上无害。）
用途：判断两点 i、j 是否互质（gcd(i,j) == 1）来决定能否连边
n：顶点数。
m：需要的边数。
cur：当前已经构造出的边数（同时也是 ans 数组的下标）。
ans[]：存储所有已生成的边 (u, v)（ii 即 pair<int,int>）
至少要构成连通图才有意义（题目通常要求图连通，或至少有 n-1 条边才能连起 n 个点）。
若 m < n-1，边数不足以保证连通（n 个点的连通图至少需要 n-1 条边），直接输出 Impossible
两层循环，用字典序枚举所有点对 (i,j)（i < j，避免重复边）：

外层 i 从 1 到 n，只要 cur < m（还没凑够边数）就继续。
内层 j 从 i+1 到 n。
仅当 gcd(i,j) == 1（两点互质）时，把这条边 (i,j) 记入 ans[++cur]。
贪心策略：按编号从小到大（i 优先小、j 从小到大）的顺序尝试取互素对，边取边数，直到：

取满 m 条（cur == m，内层 break）；
或枚举完仍不足 m（cur < m 且外循环结束）。
为什么按字典序取就够？ 因为本问题只关心"能否凑出恰好 m 条互素边"，而不在乎具体取哪些。只要互素对总数（最大可取得边数）≥ m，就必然能按这个顺序取到 m 条。顺序只影响输出的边长什么样，不影响可行性
枚举结束后核对 cur 是否恰好等于 m：
若 cur != m（说明所有互素对都取完了仍不足 m），输出 Impossible。
若 cur == m（正好取满），输出 Possible 并打印全部边

两两点对共 C(n,2) = n(n-1)/2 对，每对做一次 gcd。
时间复杂度 O(n² · log n)（gcd 约 O(log) 级别）。
空间 O(m) 存边。
对 n ≤ 1e5，n² 明显偏大，但常数小、且这类 CF 题 n 通常不会到 1e5（若 n 真到 1e5 则会 TLE，需另用「欧拉 / 数论计数」优化——即最大互素边数用 1 与一切互素，加上素数与所有更小非倍数求和算，那样可 O(n log n) 求总数，再决定能否构造）


欧拉函数公式（把 n 按质因子分解）：

φ(n) = n · (1-1/p1) · (1-1/p2) · …
用筛法批量求 1..n 的 φ：

const int N = 1e5+5;
int phi[N];

void euler(int n) {                 // 埃氏筛求 1..n 的欧拉函数
    iota(phi, phi+n+1, 0);          // 初始 phi[i]=i
    for (int i = 2; i <= n; i++)
        if (phi[i] == i) {          // i 是素数（还没被处理过）
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j]/i; // 施乘 (1-1/i)
        }
}
初始 phi[i]=i，遇到素数 i 时对所有 i 的倍数 j 乘上 (1-1/i)。
复杂度 O(n log log n)。
求总和：

ll sum = 0;
for (int i = 1; i <= n; i++) sum += phi[i];
其中 φ(1)=1 需保留（题解约定计入，对应 1 这个特殊顶点），实际构造时从顶点 1 出发连所有点可提供 n-1 条边。



int phi[N];
vector<pair<int,int>> ans;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, m;
    cin >> n >> m;

    // 1) 预处理欧拉函数（埃氏筛）
    for (int i = 1; i <= n; i++) phi[i] = i;
    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {                    // phi[i]==i → i 是素数
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }

    // 2) 数论可行性判断：最大互素边数 = Σφ(i)
    ll sum = 0;
    for (int i = 1; i <= n; i++) sum += phi[i];
    if (m < n-1 || m > sum) {                  // 边数不足/互素对不足
        cout << "Impossible\n";
        return 0;
    }

    // 3) 构造：按字典序枚举互素对，凑满 m 条
    for (int i = 1; i <= n && (int)ans.size() < m; i++) {
        if (ans.size() >= m) break;
        for (int j = i+1; j <= n; j++) {
            if (__gcd(i, j) == 1) {
                ans.push_back({i, j});
                if ((int)ans.size() == m) break;
            }
        }
    }

    cout << "Possible\n";
    for (auto &e : ans) cout << e.first << ' ' << e.second << '\n';
    return 0;
}





*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; i++)
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e5+5;

int gcd(int a, int b) {
    if (a < b) return gcd(b, a);
    while (b) { int t = b; b = a % b; a = t; }
    return a;
}

int n, m, cur;
ii ans[N];
int main() {
    fast;
    cin >> n >> m;
    if (m < n-1) { cout << "Impossible\n"; return 0; }
    for (int i = 1; i <= n && cur < m; i++) rep(j,i+1,n) if (gcd(i,j) == 1) {
        ans[++cur] = {i,j};
        if (cur == m) break;
    }
    if (cur != m) { cout << "Impossible\n"; return 0; }
    cout << "Possible\n";
    rep(i,1,m) cout << ans[i].first << ' ' << ans[i].second << '\n';
    return 0;
}