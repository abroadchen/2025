//
// Created by Psy.C on 2026/11/2.
//

/**
真正学会的起点..
对每个数做质因数分解，只保留出现次数为奇数的质因子（出现偶数次的可被平方约掉）。p[i] 即该数"需保留的质因数集合"。
x 分解后若还剩 >1，则本身是质因子，一并存入。
每个查询给出 [L, r]，按右端点 r 分组存到 g[r]，便于从左到右扫描时统一处理
对每个位置，枚举其质因子集合的所有子集（状态压缩），设选中质因子的乘积为 x、未选中的个数为 y（即该子集对应的"异或次数"）。
第一遍：用 dp[x][j]（此前某位置出现了质因子积为 x、含 j 个无关因子的位置）更新 ss[j+y] 为这些位置的最大索引——用于判断左端点约束。
处理该右端点下的查询：二分/线性找到使 ss[now] ≥ L 的最小 now，作为答案。
第二遍：把当前子集的 dp[x][y] 记录为当前位置 i，供后续更新
依序输出每个查询的答案
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; ++i)
#define ii pair<int, int>
using namespace std;

constexpr int inf = 0x3f3f3f3f, N = 1e7+10;

int n, q, L[N], ss[20], dp[N][10], ans[N];
vector<int> p[N], g[N];
int main() {
    fast;
    cin >> n >> q;
    rep(i,1,n) {
        int x; cin >> x;
        int mx = sqrt(x+0.5);
        rep(j,2,mx) if (x%j == 0) {
            int t = 0;
            while (x%j == 0) t ^= 1, x /= j;//t 翻转：记录奇偶次
            if (t) p[i].push_back(j);
        }
        if (x) p[i].push_back(x);
    }
    rep(i,1,q) {
        int r; cin >> L[i] >> r;
        g[r].push_back(i);
    }
    rep(i,1,n) {
        int sz = p[i].size(), mx = (1<<sz)-1;
        rep(s,0,mx) {//第一遍：用当前数的所有子集更新 ss
            int x = 1, y = 0;
            rep(j,0,sz-1) {
                if (s>>j&1) x *= p[i][j];//选中的质因子 → 作积 x
                else ++y;// 未选 → 增加异或次数 y
            }
            rep(j,0,15) ss[j+y] = max(ss[j+y], dp[x][j]);
        }
        for (auto j : g[i]) {//该右端点下的查询：求最小需要的分层值
            int now = 0;
            while (ss[now] < L[j]) ++now;//找到 ss ≥ L 的最小层
            ans[j] = now;
        }
        rep(s,0,mx) {//第二遍：把当前数的各子集状态写入 dp
            int x = 1, y = 0;
            rep(j,0,sz-1) {
                if (s>>j&1) x *= p[i][j];
                else ++y;
            }
            dp[x][y] = i;//记录位置 i
        }
    }
    rep(i,1,q) cout << ans[i] << '\n';
    return 0;
}