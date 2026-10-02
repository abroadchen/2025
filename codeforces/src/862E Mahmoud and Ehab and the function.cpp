//
// Created by Psy.C on 2026/10/2.
//
/**
s1 = A 序列的交替符号和（奇数下标加、偶数下标减）
sum[i] 存 B 中同奇偶间隔项的累计和：sum[i] = b[i] + b[i-2] + b[i-4] + ...
这为后续"取 B 窗口的交替和"做前缀准备
对 B 中每个长度 n 的滑动窗口（起点 i-n+1），通过 s2、s3 的隔项前缀差算出窗口分奇偶的交替和，转换成一个值塞进数组 c（带 -inf/inf 哨兵）。
排序后供二分查找
对 -s 在排序数组 c 上二分，找最接近的两个邻居（c[pos] 与 c[pos-1]），返回 min(|s + c[pos]|, |s + c[pos-1]|)——即让 A 的交替和与 B 某窗口交替和之差最小的那个差值绝对值。
这就是核心答案：A 序列通过 +x 区间更新后，与 B 中某窗口匹配能得到的"最小交替和之差"
每次区间 [l,r] 全体加 x：交替和改变量只取决于区间长度奇偶：
区间长度为偶数 → 加/减对消，s1 不变；
区间长度为奇数 → 首项决定符号（l 奇则该项加，l 偶则减），所以 s1 += x 或 s1 -= x。
更新后重新 get(s1) 输出当前最小差值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+5;
constexpr ll inf = 1e18;
int cnt;
ll c[N];
ll get(ll s) {
    int pos = lower_bound(c, c+1+cnt, -s) - c;
    return min(abs(s+c[pos]), abs(s+c[pos-1]));
}

ll a[N], b[N], s1, sum[N];
int main() {
    fast;
    int n, m, q; cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (i&1) s1 += a[i]; else s1 -= a[i];
    }
    for (int i = 1; i <= m; ++i) {
        cin >> b[i];
        if (i > 1) sum[i] = sum[i-2];//继承上上个位置
        sum[i] += b[i];//加上当前
    }
    c[cnt] = -inf;
    for (int i = n; i <= m; ++i) {
        ll s2 = sum[i], s3 = sum[i-1];
        int pos = i-n+1;
        if (n&1) {
            s2 -= sum[max(pos-2, 0)];
            s3 -= sum[max(pos-1, 0)];
            c[++cnt] = -s2+s3;
        } else {
            s2 -= sum[max(pos-1, 0)];
            s3 -= sum[max(pos-2, 0)];
            c[++cnt] = s2 - s3;
        }
    }
    c[++cnt] = inf;
    sort(c, c+1+cnt);
    cout << get(s1) << '\n';
    ll l, r, x;
    for (int i = 1; i <= q; ++i) {
        cin >> l >> r >> x;
        if ((r-l+1)&1) {
            if (l&1) s1 += x; else s1 -= x;
        }
        cout << get(s1) << '\n';
    }
    return 0;
}