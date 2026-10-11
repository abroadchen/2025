//
// Created by Psy.C on 2026/10/11.
//
/**
a[i]：每个点（坐标 p 和颜色 c）。
d[++tot] = i：记录所有颜色为 G 的点的下标
如果没有绿点，则设 d[1] = n+1（哨兵），相当于把整个区间当作"第一个也是最后一个绿色区间"来处理
在第一个绿点之前的部分：
找到最靠右的红点（第一个出现的 R），从该点走到绿点，代价 = a[d[1]].p - a[i].p（只加一次，因为只用走一个 R 点，其余都不用管——路径从 0 直接到最远的那个点即可覆盖所有左侧红点）。
同理对蓝点：找到最靠右的蓝点，加一次 a[d[1]].p - a[i].p。
因为从 0 出发只需走到该侧"最远的一个同色点"即可顺路覆盖左侧所有同色点，代价就是它到绿点的距离。R 和 B 各走一段，独立累加
在最后一个绿点之后的部分，逻辑对称：
找到最靠左的红点，从绿点走到它，代价 = a[i].p - a[d[tot]].p（一次即可覆盖右侧所有红点）。
同理蓝点各加一次
处理两个相邻绿点之间的区间：

pr / pb：上一个红点 / 蓝点的位置（初始为左端绿点，坐标 a[d[i]].p）。
遍历区间内所有红点，计算相邻红点之间的最大空隙 mxr；蓝点同理得 mxb。
最后再比较一次到右端绿点的那段距离，得到两侧端点的最大空隙
方案 A：2*len —— 在区间内走一个"折返完整往返"：从绿点走到底再走回来，覆盖所有点，代价为两倍区间长。
方案 B：(1 + (mxb!=0) + (mxr!=0))*len - mxr - mxb —— 更优的"利用绿点中继"策略：
若区间内没有某颜色的点（mxr==0 或 mxb==0），则该颜色可以"借用"绿点的另一段路径免费覆盖；
公式用 1（整个区间的某方向直穿）、加每存在一种颜色的 len，再减去红蓝的最大空隙 mxr + mxb。
这个公式本质是：红色点用一段 len（不跨过最大空隙 mxr），蓝色点用一段 len（不跨过 mxb），加上贯穿的一段 len，每个颜色都"省掉"自己最大的一段空隙。
核心思想：绿点可以同时作为红、蓝两条独立折返路径的端点。每个区间的代价取"全走（2·len）"和"分色省空隙"两者中的较小者
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=j; i<=k; ++i)
#define per(i,j,k) for(int i=j; i>=k; --i)
#define ll long long
using namespace std;

constexpr int N = 3e5+5;

struct node { int p; char c; } a[N];
int n, d[N], tot, ans;
char s[10];
int main() {
    fast;
    cin >> n;
    rep(i,1,n) {
        cin >> a[i].p >> s; a[i].c = s[0];
        if (s[0] == 'G') d[++tot] = i;
    }
    if (!tot) d[1] = n+1;
    rep(i,1,d[1]-1) {
        if (a[i].c == 'R') {
            ans += a[d[1]].p - a[i].p;
            break;
        }
    }
    rep(i,1,d[1]-1) {
        if (a[i].c == 'B') {
            ans += a[d[1]].p - a[i].p;
            break;
        }
    }
    per(i,n,d[tot]+1) {
        if (a[i].c == 'R') {
            ans += a[i].p - a[d[tot]].p;
            break;
        }
    }
    per(i,n,d[tot]+1) {
        if (a[i].c == 'B') {
            ans += a[i].p - a[d[tot]].p;
            break;
        }
    }
    rep(i,1,tot-1) {
        int pr = a[d[i]].p, pb = a[d[i]].p, mxr = 0, mxb = 0, len = a[d[i+1]].p-a[d[i]].p;
        rep(j,d[i]+1,d[i+1]-1) {
            if (a[j].c == 'R') {
                mxr = max(mxr, a[j].p - pr);
                pr = a[j].p;
            }
        }
        rep(j,d[i]+1,d[i+1]-1) {
            if (a[j].c == 'B') {
                mxb = max(mxb, a[j].p - pb);
                pb = a[j].p;
            }
        }
        if (pr != a[d[i]].p) mxr = max(mxr, a[d[i+1]].p - pr);
        if (pb != a[d[i]].p) mxb = max(mxb, a[d[i+1]].p - pb);
        ans += min(2*len, (1+(mxb!=0)+(mxr!=0))*len-mxr-mxb);
    }
    cout << ans << '\n';
    return 0;
}