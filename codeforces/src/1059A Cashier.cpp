//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
node 存一个已占用区间的左端点 l 和长度 c。
cmp 按左端点 l 升序排序（用于把区间排好序再处理空隙）
n：占用区间个数
L：总轴线长度（0..L）
a：每个可插入片段/内容的长度
ans：答案（最多能插入的个数）
读入 n、总长 L、单段长度 a，再读入 n 个占用区间 [l, l+c)
从开头 0 到第一个占用区间起点 p[0].l 之间的空隙长度 = p[0].l，能塞 p[0].l / a 个
对相邻两个占用区间 i 和 i+1：
区间 i 结束于 p[i].l + p[i].c
区间 i+1 开始于 p[i+1].l
若 结束 < 开始（存在空隙），空隙长度 = p[i+1].l - (p[i].l+p[i].c)
能塞 空隙长度 / a 个（整数除法，只算完整的 a 段）
末尾空隙：从最后一个占用区间结束 p[n-1].l+p[n-1].c 到末端 L，能塞 (L - p[n-1].l - p[n-1].c) / a 个。
若 n == 0，整条 0..L 都是空隙，直接塞 L/a 个。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=0; i<n; i++)
using namespace std;

constexpr int N = 1e6+5;

struct node { int l, c; } p[N];
bool cmp(node a, node b) { return a.l < b.l; }

int n, L, a, ans;
int main() {
    fast;
    cin >> n >> L >> a;
    rep(i,n) cin >> p[i].l >> p[i].c;
    ans += p[0].l/a;
    rep(i,n-1)
        if (p[i].l+p[i].c < p[i+1].l)
            ans += (p[i+1].l-p[i].c-p[i].l)/a;
    if (n != 0) ans += (L-p[n-1].l-p[n-1].c)/a; else ans += L/a;
    cout << ans;
    return 0;
}