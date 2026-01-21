//
// Created by Psy.C on 2026/1/20.
//
/**
* 读入n（总长度）、m（类型数）、d（窗口大小）
ori[N]：记录每个位置属于哪个类型
vis[25]：窗口内各类型的出现次数
mp[M]：记录哪些状态可达
ans = m：初始答案为m
I = (1<<m)-1：全1掩码，表示所有类型都包含
 *
*读入m种类型的数据
k：第i种类型包含的元素个数
将元素a标记为属于类型i
 *统计初始窗口[1,d]内各类型的出现次数
*滑动窗口从[1,d]到[n-d+1,n]
st：当前窗口内存在的类型集合（位掩码）
if (vis[i]) st |= 1<<(i-1)：如果类型i存在，设置对应位
mp[I - st] = 1：记录缺失类型的掩码（补集）
 *
*从大到小遍历所有可能的状态
if (mp[st])：如果状态st可达
rep(j,m) if (st & 1<<(j-1))：遍历st中包含的每个类型j
mp[st^(1<<(j-1))] = 1：移除类型j后的新状态也可达
else ans = min(__builtin_popcount(st), ans)：
如果状态st不可达，计算其包含的类型数
更新最小值
 *
*滑动窗口：O(n)
状态处理：O(2^m × m)
总体：O(n + 2^m × m)（当m较小时可行）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define M 1050000
#define rep(i,n) for (int i=1; i<=n; ++i)
using namespace std;


int main() {
    fast;
    int n, m, d; cin >> n >> m >> d;
    int ori[N]={}, vis[25]={}, mp[M]={}, ans = m;
    const int I = (1<<m)-1;
    for (int i = 1, a, k; i <= m; ++i) {
        cin >> k;
        while (k--) { cin >> a; ori[a] = i; }
    }
    rep(i,d) vis[ori[i]]++;
    for (int l = 1, r = d; r <= n; vis[ori[l]]--, l++, r++, vis[ori[r]]++) {
        int st = 0;
        rep(i,m) if (vis[i]) st |= 1<<(i-1);
        mp[I - st] = 1;
    }
    for (int st = I; st >= 0; st--) {
        if (mp[st]) {
            rep(j,m) if (st & 1<<(j-1)) mp[st^(1<<(j-1))] = 1;
        } else ans = min(__builtin_popcount(st), ans);
    }
    cout << ans << '\n';
    return 0;
}