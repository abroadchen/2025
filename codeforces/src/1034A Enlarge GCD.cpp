//
// Created by Psy.C on 2026/11/4.
//

/**
真正学会的起点..
N：筛选/标记数组的上界（数值被约分后可能达到约 1.5e7）。
M：读入数组 a[] 的最大长度（n 上限）
b[]：布尔标记数组（下标是否合数），b[i]=0 表示 i 是质数。
p[]：从小到大收集到的所有质数。
tot：已筛出的质数个数
n：数的个数；a[]：读入的 n 个数。
x：约分/分解时的当前值。
sum[]：sum[prime] 统计"有多少个数把 prime 作为质因数"
这是欧拉线性筛（每个合数恰好被其最小质因数筛一次，O(N)）：

若 b[i]==0，说明 i 未被标记成合数，即质数，压入 p。
然后用 i 去筛掉 i*p[j]；一旦 i 能被 p[j] 整除就 break，保证每个合数只被最小质因子标记一次，从而保证线性复杂度
先筛好质数表，再读入 n 个数，并边读边累积所有数的最大公约数 d
先除以全体 gcd d。因为 d 是公共因子，约分后得到的 x 之间不再有公共因子，这样后面统计到的"共享质因数"就是题目真正关心的。
对每个 x 做质因数分解（用前面筛出的质数表，只试到 p[j]*p[j] <= x）：
只要 p[j] 能整除 x，就 sum[p[j]]++（记录"这个质因子又被一个数用到了"），再用 while 把所有 p[j] 因子除净。
循环结束后若 x > 1，则剩下的 x 是一个 > sqrt 的大质因子，sum[x]++。
分解完所有数后，sum[p] 就表示"把质数 p 作为质因数的那些数，一共有多少个"
扫描所有质数，找出 sum 最大的一项，记为 ans，即"同一个质因数最多被 ans 个数共享"。
若 ans == 0：说明没有任何质因子被 ≥1 个数共享（每个数约分后都是 1，或质因子互不相同），输出 -1。
否则输出 n - ans，即除掉这 ans 个共享质因子的数之外，其余数都要"改多少"（这是题目要求的答案——要修改的数的个数）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
using namespace std;

constexpr int N = 1.5e7+5, M = 3e5+10;

int b[N], p[N], tot;
void get() {
    for (int i = 2; i < N; i++) {
        if (!b[i]) p[tot++] = i;
        for (int j = 0; j < tot && i*p[j] < N; j++) {
            b[i*p[j]] = 1;
            if (i%p[j] == 0) break;
        }
    }
}

int n, a[M], x, sum[N];
int main() {
    fast;
    cin >> n; get();
    int d = 0;
    rep(i,n) {
        cin >> a[i];
        d = __gcd(d, a[i]);
    }
    rep(i,n) {
        x = a[i]/d;
        for (int j = 0; p[j]*p[j] <= x && j < tot; j++) {
            if (x%p[j] == 0) sum[p[j]]++;
            while (x%p[j] == 0) x/=p[j];
        }
        if (x > 1) sum[x]++;
    }
    int ans = 0;
    for (int i = 0; i < tot; i++) ans = max(ans, sum[p[i]]);
    if (ans == 0) cout << "-1\n"; else cout << n-ans << '\n';
    return 0;
}