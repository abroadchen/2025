//
// Created by Psy.C on 2026/3/7.
//
/**
num[i]：存储数字i的素因子个数
外层循环：遍历从2到N的所有数字
if (!num[i])：如果i还没有被标记过，说明i是素数
内层循环：对于素数i，遍历其所有倍数j
while (t % i == 0)：计算j中有多少个因子i
num[j]++：每发现一个素因子就增加计数
num[i]现在表示从1到i的所有数字的素因子总数
区间(l, r]内的素因子总数
时间复杂度：预处理O(N log N)，查询O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 5e6;

int num[N+5];
void get() {
    for (int i = 2; i <= N; ++i) if (!num[i]) {
        for (int j = i; j <= N; j += i) {
            int t = j;
            while (t % i == 0) { num[j]++; t /= i; }
        }
    }
}

int q, l, r;
int main() {
    fast;
    get();
    for (int i = 2; i <= N; ++i) num[i] += num[i-1];
    cin >> q;
    while (q--) {
        cin >> r >> l;
        cout << num[r] - num[l] << '\n';
    }
    return 0;
}