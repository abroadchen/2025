//
// Created by Psy.C on 2026/10/16.
//
/**
枚举 x（长度为 a 的组的数量），从 0 到 n/a。
检查剩余 n - x*a 能否被 b 整除，若能则得到 y，标记 flg 并跳出。
若找不到任何符合条件的 (x,y)，输出 -1。
这解决的是整数线性组合 x·a + y·b = n 的一组非负整数解。因 a ≤ b（未强制但典型），枚举 x 一定能在有限步内找到解（若存在）
对每组（长度 L）：

前 L-1 个位置：p[id] = id+1，即当前元素指向下一个（连成一条链 id → id+1 → …）。
最后一个位置：p[id] = id - L + 1，即最后一个元素指回该组第一个元素，形成循环。
整体效果：每个长度为 L 的组构成一个循环轮换（cycle）‍，p 是一个完整的、分成若干循环的排列。

例如长度 a=3 的组 [5,6,7]：p[5]=6, p[6]=7, p[7]=5，是 (5 6 7) 这个 3-轮换
输出排列 p

枚举 x：O(n/a)。
构造：O(n)。
总 O(n + n/a)，对 n ≤ 1e6 可行
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for(int i=(j), i##_end_=(k); i<=i##_end_; ++i)
using namespace std;

constexpr int N = 1e6+10;

int n, a, b, p[N], x, y;
bool flg;
int main() {
    fast;
    cin >> n >> a >> b;
    for (x = 0; x <= n/a; ++x) {
        if ((n-x*a)%b == 0) {
            flg = true;
            y = (n-x*a)/b;
            break;
        }
    }
    if (!flg) cout << "-1\n";
    else {
        int id = 1;
        rep(i,1,x) {
            rep(j,1,a-1) p[id] = id+1, id++;
            p[id] = id - a + 1, id++;
        }
        rep(i,1,y) {
            rep(j,1,b-1) p[id] = id+1, id++;
            p[id] = id - b + 1, id++;
        }
        rep(i,1,n) cout << p[i] << ' ';
    }

    return 0;
}