//
// Created by Psy.C on 2026/11/10.
//

/**
真正学会的起点..
s：累积保存"前几个集合的交集结果"。
t：临时保存当前读入的集合
读入总集合数 n 和第一个集合的个数 m。
把第一个集合的所有元素 x 对应的 bitset 位 s[x] 置 1（当作初始交集）
对每个后续集合：读入元素填进 t，然后 s &= t 做按位与，只保留同时在"先前交集"和"这个新集合"里的元素。
走完所有集合后，s 即为所有集合的交集
遍历 1..100，把 s 中为 1 的位（即所有集合共有元素）依次输出。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 105;

int n, m, x;
bitset<N> s, t;
int main() {
    fast;
    cin >> n >> m;
    rep(i,m) cin >> x, s[x] = 1;
    rep(i,n-1) {
        cin >> m; t.reset();
        rep(j,m) cin >> x, t[x] = 1;
        s &= t;
    }
    rep(i,N-5) if (s[i]) cout << i << ' ';
    return 0;
}