//
// Created by Psy.C on 2026/9/20.
//
/**
向判题发出查询 1 x y，刷新输出缓冲区，读取回答，若为 "TAK" 返回 1，否则 0。
在区间 [l, r] 上二分，找出满足 check(mid, mid+1) 为真的最小位置（返回 ans）。
逐次查询相邻位置对 (mid, mid+1) 来判断单调边界在哪。
若全程不满足，返回 0 表示没找到
x = ef(1, n-1)：在 [1, n-1] 二分，找到第一个满足条件的位置 x。
y = ef(1, x-1)：在 x 左侧再二分，尝试找 x 前面的第二个特殊位置 y。
若没找到（y == 0）‍：
换到 x 右侧二分 ef(x+1, n-1) 找 y。
若右边也没有能找到的 y，或 check(n, y) 判定边界情况，就直接设 y = n。
out(x, y)：提交 2 x y 作为最终答案
 */
#include <bits/stdc++.h>
using namespace std;

int check(int x, int y) {
    cout << "1 " << x << " " << y << '\n';
    fflush(stdout);
    string s; cin >> s;
    return s == "TAK";
}
void out(int x, int y) {
    cout << "2 " << x << " " << y << '\n';
    fflush(stdout);
}

int ef(int l, int r) {
    int ans = 0;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (check(mid, mid+1))
            ans = mid, r = mid-1;
        else l = mid+1;
    }
    return ans;
}


int main() {
    int n, k; cin >> n >> k;
    int x = ef(1, n-1), y = ef(1, x-1);
    if (!y) {
        y = ef(x+1, n-1);
        if (!y || check(n, y)) y = n;
    }
    out(x, y);
    return 0;
}