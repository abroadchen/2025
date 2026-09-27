//
// Created by Psy.C on 2026/9/27.
//
/**
随机采样至多 M=1000 个节点（用两次 rand() 相乘再取模提高随机性）。
关键记录：d 初始为 st（起点）。在采样中，若查到某节点 t 的值比当前 d 大、且不超过 x，则更新 d = t。
于是经过采样，d 是已见到过的最大的、同时 ≤ x 的节点（贪心逼近 x 的下界）
从采样到的最优 d 出发，顺着 nxt 指针一路向前逐节点询问。
因为链表节点值不降（单调递增），所以一旦遇到 val[i] >= x，它就是第一个满足条件的值，输出答案。
若整个链走完（到 -1）都没找到，输出 ! -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e4+5, M = 1e3;
int n, st, x, d, val[N], nxt[N];
int main() {
    fast;
    srand(time(0));
    cin >> n >> st >> x; d = st;
    for (int i = 1; i <= M; ++i) {
        int t = 1ll*rand()*rand()%n+1;//随机查一个点
        cout << "? " << t << endl;
        cin >> val[t] >> nxt[t];
        if (val[d] < val[t] && val[t] <= x) d = t;// 记录"值最大但≤x"的采样点
    }
    for (int i = d; i != -1; i = nxt[i]) {
        cout << "? " << i << endl;
        cin >> val[i] >> nxt[i];
        if (val[i] >= x) {//遇到 ≥ x 的第一个节点
            cout << "! " << val[i] << endl;
            return 0;
        }
    }
    cout << "! -1" << endl;//链走完都没遇到 ≥ x，输出 -1
    return 0;
}