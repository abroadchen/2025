//
// Created by Psy.C on 2026/10/31.
//

/**
真正学会的起点..
向裁判发起一次询问：输出 ? x，询问位置 x 上的值。
读回裁判返回的 res。
endl 刷新是交互题的关键，否则裁判可能收不到询问
读入序列长度 n。

if (n&2) 判无解：

n&2 判断 n 的二进制的第二位是否为 1，即 n 被 4 除余 2 或 3，实际上这里判断的是 n % 4。
常见题意：序列 a[i] 中，奇数位置值是 + 号，偶数位置值是 - 号（如 a[i] = +1, -1, ... 交替，或 (i-1)/2 取反之类），且要求 a[x] == a[x+n/2] 且能构成整数位置。
在这类题目里，当 n 使得 n/2 为奇数（即 n%4==2）时必无解，直接输出 ! -1。
所以 n&2 == true ⇔ n % 4 ∈ {2,3} 时直接判无解返回
询问对称的两个端点：位置 1 和位置 1 + n/2。
得到 l 和 r。
定义方向 f：
f = 0：l == r → 两侧相等，直接找到答案 x=1，输出 ! 1 并结束。
f = 1：l < r（左侧小于右侧，标记方向为「升」）；
f = -1：l > r（方向为「降」）。
初始方向 f 代表序列上这一段的增减方向
询问对称的两个端点：位置 1 和位置 1 + n/2。
得到 l 和 r。
定义方向 f：
f = 0：l == r → 两侧相等，直接找到答案 x=1，输出 ! 1 并结束。
f = 1：l < r（左侧小于右侧，标记方向为「升」）；
f = -1：l > r（方向为「降」）。
初始方向 f 代表序列上这一段的增减方向
若二分结束仍未找到，输出 ! -1（无解兜底）。正常有解时会在二分中早退
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

int query(int x) {
    cout << "? " << x << endl;
    int res; cin >> res;
    return res;
}

void solve() {
    int n; cin >> n;
    if (n&2) { cout << "! -1" << endl; return; }
    int l = query(1), r = query(1+n/2);
    int f = l == r ? 0 : l < r ? 1 : -1;
    if (f == 0) { cout << "! " << 1 << endl; return; }
    int lo = 1, hi = n/2+1;
    while (lo < hi) {
        int x = (lo+hi)>>1;
        l = query(x), r = query(x+n/2);
        int nf = l == r ? 0 : l < r ? 1 : -1;
        if (nf == 0) { cout << "! " << x << endl; return; }
        if (nf == f) lo = x + 1; else hi = x;
    }
    cout << "! " << -1 << endl;
}


int main() {
    fast;
    int T = 1;
    while (T--) solve();
    return 0;
}