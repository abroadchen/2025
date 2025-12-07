//
// Created by Psy.C on 2025/12/6.
//
/*
*n: 数组大小
a[]: 存储原始数据及其变换后的结果
st[][]: Sparse Table 实现区间最小值查询的数据结构
fa[][]: 倍增跳转表，记录每个位置经过若干步后到达的位置
ans: 最终答案计数器
 *
 *读入前 n 个元素，并复制一份形成环状数组（扩展到 2n 长度）
 *对数组进行一次预处理转换，使得 a[i] 成为当前点能跳转到的第一个合法位置（防止负数或越界）
 *初始化 sparse table 第一层（每个节点初始指向自己）
 *构建 sparse table 结构，利用动态规划思想填充每层的最小值索引
 *初始化倍增跳转表第一层：fa[i][0] 记录从位置 i 开始，跳一步能到达的位置
 *构建完整的倍增跳转表，第 j 层表示跳 $2^j$ 步的结果
 *
*对于每一个起点 i，模拟跳跃过程并统计步数：
初始化 cnt=2, cur=i+n-1
如果可以直接到达目标，则增加一步计数
否则尝试大跨度跳跃（基于倍增表）逐步逼近终点
将累计步数加入总答案 ans
 */
#include <iostream>
#include <algorithm>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 501010
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

constexpr int M = 30;
ll n, a[N], st[N][M], fa[N][M], ans;

ll query(const ll l, const ll r) {//返回指定范围内最小元素索引
    const ll k = static_cast<ll>(log2(r - l + 1));
    if (a[st[l][k]] < a[st[r-(1<<k)+1][k]]) return st[l][k];
    return st[r-(1<<k)+1][k];
}

int main() {
    fast;
    cin>>n;
    rep(i,n) cin>>a[i], a[i+n] = a[i];
    rep(i,2*n) a[i] = max(i - a[i], 1ll);
    for (ll i = 1; i <= 2 * n; ++i) st[i][0] = i;
    for (ll j = 1; j <= M - 1; ++j) {
        for (ll i = 1; i <= 2 * n - (1<<j) + 1; ++i) {
            if (a[st[i][j-1]] < a[st[i+(1<<(j-1))][j-1]])
                st[i][j] = st[i][j-1];
            else st[i][j] = st[i+(1<<(j-1))][j-1];
        }
    }
    rep(i,2*n) fa[i][0] = query(a[i], i);
    rep(j,M-1) rep(i,2*n) fa[i][j] = fa[fa[i][j-1]][j-1];
    rep(i,n) {
        ll cnt = 2, cur = i + n - 1;
        if (a[cur] <= i) { ans++; continue; }
        for (ll j = M-1; j >= 0; --j) if (a[fa[cur][j]] > i) {
            cnt += 1<<j, cur = fa[cur][j];
        }
        ans += cnt;
    }
    cout << ans;
    return 0;
}