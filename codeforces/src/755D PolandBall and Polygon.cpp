//
// Created by Psy.C on 2026/9/2.
//
/**
now 是起点（已标记，后面会 add），to 是终点
  中间 [now+1, to-1] 区域内已标记的位置数就是跳过的次数

to -= n 让 to 变成绕回到左边的位置
  query(n) + query(to-1) - query(now)
  = (a[1~n] 已标记数) + (a[1~to-1] 已标记数) - (a[1~now] 已标记数)
  = 跨越边界时，now 到 n 之间已标记的 + 1 到 to-1 之间已标记的
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e6+1e3;
inline int lowbit(int x) { return x & -x; }

ll c[N];//树状数组，每个位置存前缀和区间的信息
int n;//位置总数
//在位置 x 处增加 val 值（这里是标记位置，val=1 表示已标记）
inline void add(int x, int val) {
    for (; x <= n; x += lowbit(x)) c[x] += val;
}
//查询 a[1] ~ a[x] 的前缀和
inline ll query(int x) {
    ll ret = 0;
    for (; x; x -= lowbit(x)) ret += c[x];
    return ret;
}

int k;
int main() {
    fast;
    //在一个 n 个位置的圆圈 上，向前走 k 步 = 向后走 n-k 步 （到达同一个位置）
    cin >> n >> k; k = min(k, n-k);
    ll ans = 1;//计数器：第几个被标记的
    int now = 1, to = 0;//当前位置 目标位置
    for (int i = 1; i <= n; ++i) {
        //从当前位置向前走 k 步，到达临时目标位置
        //先假设要走的 k 步都是 未标记 的，所以 ans 先加 1
        to = now + k; ++ans;
        if (to > n) {
            to -= n;
            ans += query(n) + query(to-1) - query(now);
        } else ans += query(to-1) - query(now);
        //每次标记 两个位置 ——当前位置 now 和目标位置 to ！
        add(now, 1); add(to, 1);
        now = to;//下一轮的起点就是这一轮的终点
        cout << ans << ' ';
    }
    return 0;
}