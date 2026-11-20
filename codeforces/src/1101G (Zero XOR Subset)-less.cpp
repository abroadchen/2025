//
// Created by Psy.C on 2026/11/20.
//

/**
真正学会的起点..
p[i] 是线性基数组：第 i 位（bit）存储"最高位是第 i 位的基向量"。
N=60 说明数值范围在 60 位以内；cnt 记录当前线性基中非零基的个数（即线性空间的维数）
标准的线性基插入函数：
从高位到低位扫描 x 中每一位；
若 x 的第 i 位为 1：
如果这一位还没有基（!p[i]），就把 x 作为该位的基存下，cnt++（维数 +1）并返回；
否则用已有的基 p[i] 做异或消去这一位（x ^= p[i]），继续往下扫。
x 最终被消成 0，说明 x 可被线性基表示，不增加维数
读入序列的 n 个数；
维护 f 为前缀异或和（每读入 x 就 f ^= x）；
把每个前缀异或和 f 插入线性基；
最后：
若 f（整个数组的总异或和）非零 → 输出 cnt（线性基维数，即可达到的"线性无关"异或个数，代表能组合出的独立异或方向数）；
若 f == 0（整体异或和为 0）→ 输出 -1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 60;

int p[N+5], cnt;
void ins(int x) {
    for (int i = N; i >= 0; i--) if ((1ll<<i)&x) {
        if (!p[i]) { p[i] = x, cnt++; return; }
        x ^= p[i];
    }
}


int main() {
    fast;
    int n; cin >> n;
    int f = 0;
    for (int i = 1, x; i <= n; i++) { cin >> x; f ^= x; ins(f); }
    if (f) cout << cnt; else cout << -1;
    return 0;
}