//
// Created by Psy.C on 2026/9/5.
//
/**
N 定义了数组大小（
10
7
10
7
  左右），足够存储
n
n
​
  个约数（因为
10
14
≈
10
7
10
14

​
 ≈10
7
 ）。
a[N] 用于存储所有找到的小约数。
m 记录当前数组中约数的个数
读取目标整数 n 和查询的第 k 小约数编号 k

循环遍历
1
∼
n
1∼
n
​
 。
若 i 能整除 n，则说明 i 是一个约数：
a[++m] = i：记录下来。
k--：寻找的目标向前推进了一步。
if (!k)：如果此时 k 为 0，说明当前 i 就是第 k 小的约数，直接输出并结束程序
如果 n 是完全平方数（例如
36
36），那么 sqrt(n) 那个约数会被记录两次（一次作为小约数，一次作为大约数）。这里将多余的那一份删除，以免后续计算错误
此时 k 表示剩余未匹配的第几大的约数（因为我们已经遍历完了所有小约数）。
m 是小约数的总数量。
如果 k > m，说明连所有的大约数也不够，说明 n 的约数总数不足 k 个，输出 -1。
否则，第 k 小的约数就是对应的大约数：n / a[m-k+1]

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

constexpr int N = 1e7+5;
int n, k, a[N], m;
inline void work() {
    n = rd(), k = rd();
    for (int i = 1; i <= sqrt(n); ++i)
        if (n%i == 0) {
            a[++m] = i; k--;
            if (!k) {
                cout << i << '\n';
                exit(0);
            }
        }
    if (a[m]*a[m] == n) m--;
    if (k > m) cout << "-1";
    else cout << n/a[m-k+1] << '\n';
}


signed main() {
    fast;
    work();
    return 0;
}