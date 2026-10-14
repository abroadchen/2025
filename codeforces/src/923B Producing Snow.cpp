//
// Created by Psy.C on 2026/10/14.
//
/**
tag 是"全局延迟偏移"（lazy offset）：堆里存的实际值是 真实值 + tag 的形式，比较时统一减去 tag。
每天：把 v[i] + tag 加入堆。
循环：只要堆顶元素（真实值 q.top() - tag）能被今天的 t[i] 消耗掉（≤ t[i]），就把这个真实的量累加到 res 并弹出。
一天结束后 tag += t[i]，即所有剩余堆元素的实际时间点后移 t[i]，这样后续比较自动反映"每个元素都应被每日消耗 t[i]"。
当天输出：res + q.size()*t[i] —— 即今天消耗掉的部分 + 堆里每个剩余元素今天各消耗 t[i]
 */
#include <bits/stdc++.h>
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
#define int long long
using namespace std;

constexpr int N = 1e5+10;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, v[N], t[N], tag, res;
priority_queue<int, vector<int>, greater<>> q;
signed main() {
    cin >> n;
    rep(i,1,n) v[i] = rd();
    rep(i,1,n) t[i] = rd();
    rep(i,1,n) {
        res = 0; q.push(v[i]+tag);
        while (!q.empty() && q.top() - tag <= t[i]) {
            res += q.top() - tag;
            q.pop();
        }
        tag += t[i];
        cout << res + q.size()*t[i] << ' ';
    }
    cout << '\n';
    return 0;
}