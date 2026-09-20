//
// Created by Psy.C on 2026/9/20.
//
/**
n 选手数；a[i]、b[i] 分别存第 i 名选手的算分前、算分后的 rating
读选手数 n，再按名次顺序（i 从 1 到 n，第 1 名到第 n 名）读入每个选手的 a、b
遍历所有人，只要发现任意
a
i
≠
b
i
a
i
​


=b
i
​
 ，说明有人分数变了，那么这一定是一场 rated（真正计分）的比赛。
输出 "rated" 后立即 return 0 结束程序
分数全没变 → 不可能是 rated。
若顺序也不对（有逆序）→ 不够格叫 maybe（maybe 需要顺序合理成为可能的不记分比赛），而这种情况官方答案给 unrated。
若顺序对 → 落到下面的 maybe

外层 i：选第一个选手（名次较靠前）。
内层 j = i+1...n：只选排在 i 后面的选手（名次较靠后）。
这样
j
j 一定在
i
i 后面，正好对应"后面的人分数不能更高"这个检查，if (a[j] > a[i]) 就是发现逆序。
内层从 i+1 开始，是为了不重复比较：只比较"i 在前、j 在后"这一种有序组合，避免把 (i,j) 和 (j,i) 各比一次
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e3+5;
int n, a[N], b[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i] >> b[i];
    for (int i = 1; i <= n; ++i)
        if (a[i] != b[i])
            return cout << "rated\n", 0;
    for (int i = 1; i <= n; ++i)
        for (int j = i+1; j <= n; ++j)
            if (a[j] > a[i])
                return cout << "unrated\n", 0;
    cout << "maybe\n";
    return 0;
}