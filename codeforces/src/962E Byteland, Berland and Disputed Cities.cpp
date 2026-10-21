//
// Created by Psy.C on 2026/10/21.
//
/**
a[i]: 坐标；c[i]: 颜色字符 'B'/'R'/'P'。
mxb/mxr: 相邻两个 B（或 R）之间的最大间距。
lb/lr/lp: 最近一次看到的 B/R/P 坐标。
fb/fr: 第一个遇到的 B/R 坐标。
isb/isr/isp: 是否已见过 B/R/P
读入 n 条 (坐标, 颜色)
对 B：若之前已见过 B，则更新 mxb = max(mxb, a[i]-lb)（相邻两个 B 的最大间距）；否则标记 isb=1 并记下首坐标 fb。最后更新 lb=a[i]。
对 R 同理，维护 mxr、fr、lr
P 同时充当 B 和 R（P 能连接两种网络），因此遇到 P 时：
把它当作一个 B：更新 mxb（用它到上一个 B 的间距），若首个则记 fb；并更新 lb。
也当作一个 R：更新 mxr、fr、lr。
核心决策：若之前已经出现过 P（isp 为真），说明在上一个 P 到当前 P 之间的这段 [lp, a[i]] 需要决定怎么连：
区间长度 a[i]-lp。
mxb+mxr 是可"节省"的部分（这段里最大 B 间距与最大 R 间距可以共用一条边从而省下）。
若 a[i]-lp-mxb-mxr < 0，说明把两个 P 直接用一条共用通道连起来更省（省下的量大于区间长），此时 ans += a[i]-lp-mxb-mxr（一个负数，即净节省）。
换句话说：若省下的共用边超过区间长度，就走"双 P 直连共用"方案并记下净节省；否则这段不额外记账（净节省为非正时不做动作，等价于用独立方案）。
处理完这段后，把 mxb=mxr=0 重置，lp=a[i]; isp=1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 2e5+10;

int n, a[N], mxb, mxr, lb, lr, lp, fb, fr, ans;
char c[N];
bool isb, isr, isp;
signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i] >> c[i];
        if (c[i] == 'B') {
            if (isb) mxb = max(mxb, a[i]-lb);
            else isb = 1, fb = a[i];
            lb = a[i];
        }
        if (c[i] == 'R') {
            if (isr) mxr = max(mxr, a[i]-lr);
            else isr = 1, fr = a[i];
            lr = a[i];
        }
        if (c[i] == 'P') {
            if (isb) mxb = max(mxb, a[i]-lb);
            else isb = 1, fb = a[i];
            lb = a[i];
            if (isr) mxr = max(mxr, a[i]-lr);
            else isr = 1, fr = a[i];
            lr = a[i];
            if (isp && a[i]-lp-mxb-mxr < 0) ans += a[i]-lp-mxb-mxr;
            mxb = mxr = 0;
            lp = a[i]; isp = 1;
        }
    }
    ans += lb-fb+lr-fr; cout << ans;
    return 0;
}