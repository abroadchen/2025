//
// Created by Psy.C on 2026/10/25.
//

/**
真正学会的起点..
fa：并查集父指针（带路径压缩 find）。
a[N]：各点权值。
s[N]：并查集每个根的集合大小。
x[N], y[N]：边 (x[i], y[i])。
ans[N]：答案，ans[d] = 恰为 d 的计数。
op[N]：op[d] 存与 d 相关的边的编号列表
读入 n。对每个点 i：
cin >> a[i]：读权值。
fa[i] = i, s[i] = 1：并查集初始化（每点自成集合，size=1）。
枚举 a[i] 的所有因子 j：对每个因子 j（含 a[i]/j），ans[j]++。
ans[j] 初始含义："含因子 j 的点的数量"（统计每个点是哪些 d 的倍数点）。
注意：这里的 ans[j] 是点数统计（不是对数），后面会通过并查集合并把它换算成若干"恰好 gcd = 该值"的对数
对每条边 i：
读入 x[i], y[i]。
g = __gcd(a[x[i]], a[y[i]])：这条边两端点权的 gcd。
枚举 g 的所有因子 j，把这条边 i 加入 op[j]。
op[d] = 所有"gcd 能被 d 整除"的边（即两端点权都含因子 d 的边）
对每个 d（从 1 到 N-5）处理 op[d] 中的所有边：

第一部分——并查集合并：

对每条属于 op[d] 的边 (x,y)：
找到两端点所在集合根 f1, f2。
若在不同集合：
ans[i] -= s[f1]*(s[f1]-1)/2 + s[f2]*(s[f2]-1)/2：先减去两个集合各自内部的"投影对数"（因为合并后这些对不再是跨集合贡献）。
合并：fa[f1]=f2; s[f2]+=s[f1]。
ans[i] += s[f2]*(s[f2]-1)/2：把合并后新集合的内部对数加回去
第二部分——复原并查集：

处理完 d 后，把 op[d] 中所有边涉及的点重置为独立集合（fa=p 指向自己，size=1）
从大到小遍历 i（per），对每个 i 的所有倍数 j（j=2i,3i,...），执行 ans[i] -= ans[j]
输出所有 ans[i] != 0 的 (i, 数量)
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(i=1;i<=n;i++)
#define per(i,n) for(i=n;i>=1;i--)
#define ll long long
using namespace std;

constexpr int N = 2e5+5;

int fa[N];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }

int n, i, j, a[N], s[N], x[N], y[N], g, f1, f2;
ll ans[N];
vector<int> op[N];
int main() {
    fast;
    cin >> n;
    rep(i,n) {
        cin >> a[i], fa[i] = i, s[i] = 1;
        for (j = 1; j*j <= a[i]; j++) if (a[i]%j == 0) {
            ans[j]++;
            if (a[i]/j != j) ans[a[i]/j]++;
        }
    }
    rep(i,n-1) {
        cin >> x[i] >> y[i];
        g = __gcd(a[x[i]], a[y[i]]);
        for (j = 1; j*j <= g; j++) if (g%j == 0) {
            op[j].push_back(i);
            if (g/j != j) op[g/j].push_back(i);
        }
    }
    rep(i,N-5) {
        for (j = 0; j < op[i].size(); j++) {
            f1 = find(x[op[i][j]]), f2 = find(y[op[i][j]]);
            if (f1 != f2) {
                ans[i] -= 1ll*s[f1]*(s[f1]-1)/2+1ll*s[f2]*(s[f2]-1)/2;
                fa[f1] = f2; s[f2] += s[f1];
                ans[i] += 1ll*s[f2]*(s[f2]-1)/2;
            }
        }
        for (j = 0; j < op[i].size(); j++)
            fa[x[op[i][j]]] = x[op[i][j]], fa[y[op[i][j]]] = y[op[i][j]], s[x[op[i][j]]] = s[y[op[i][j]]] = 1;
    }
    per(i,N-5) for (j = i+i; j <= N-5; j += i) ans[i] -= ans[j];
    rep(i,N-5) if (ans[i]) cout << i << ' ' << ans[i] << '\n';
    return 0;
}