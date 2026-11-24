//
// Created by Psy.C on 2026/11/24.
//

/**
真正学会的起点..
x=数字, sum=它还剩余可用的个数
堆排序：sum 越大越优先出堆（大根堆按剩余量）
b[x]=数字 x 出现的次数
输出的回文矩阵
读入 n^2个数，统计每种数字数量；把数量>0的数字压入堆
对前n/2*n/2个"四角单元"各取一个数字填满 4 个对称位置。
若某次取出的最大剩余量 <4，说明数字数量配不成 4 元组 → NO
中间列上 n/2 对（上下）各需 2 个 → 每次取堆顶填 2 个，不足 2 → NO。
中间行上 n/2 对（左右）各需 2 个，同理。
最后正中心 1 个，直接取堆顶（题目保证总和 n^2为奇数时必有剩余）。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1e3;

struct node {
    int x, sum;
    bool operator<(const node& o) const { return sum < o.sum; }
} t;

int n, x, b[N+10], a[N+100][N+100];
priority_queue<node> q;
int main() {
    fast;
    cin >> n;
    rep(i,n*n) { cin >> x; b[x]++; }
    rep(i,N) if (b[i]) { t.sum = b[i]; t.x = i; q.push(t); }
    rep(i,n/2) rep(j,n/2) {
        t = q.top(); q.pop();
        if (t.sum < 4) { cout << "NO\n"; return 0; }
        a[i][j] = a[i][n-j+1] = a[n-i+1][j] = a[n-i+1][n-j+1] = t.x;
        t.sum -= 4;
        if (t.sum > 0) q.push(t);//还能再用则放回
    }
    if (n&1) {
        int j = n/2+1;
        rep(i,n/2) {
            auto now = q.top(); q.pop();
            if (now.sum < 2) { cout << "NO\n"; return 0; }
            a[i][j] = a[n-i+1][j] = now.x; now.sum -= 2;//上下对称两点
            if (now.sum) q.push(now);
        }
        rep(i,n/2) {
            auto now = q.top(); q.pop();
            if (now.sum < 2) { cout << "NO\n"; return 0; }
            a[j][i] = a[j][n-i+1] = now.x; now.sum -= 2;//左右对称两点
            if (t.sum) q.push(now);
        }
        auto now = q.top(); q.pop();//正中心 1 个
        a[n/2+1][n/2+1] = now.x;
    }
    cout << "YES\n";
    rep(i,n) rep(j,n) cout << a[i][j] << " \n"[j==n];
    return 0;
}