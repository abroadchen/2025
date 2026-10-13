//
// Created by Psy.C on 2026/10/13.
//
/**
把 n 按二进制位分解：第 i 位为 1 就压入一个 2^i（堆里存的是指数 i）。此时堆里的个数就是 n 的二进制中 1 的个数，即最少的拆分个数。b 是 a 的拷贝，后面输出阶段用（因为输出时需要同时保留原始集合做参考）
sz = k - a.size()：表示还需要把元素数增加到 k 需要拆几次。

如果 sz < 0，说明初始个数已经比 k 多（>k 个 2 的幂），此时无法靠"拆分"（只会增多）来减到 k 个，输出 No。（注意：越小越能拆，n<k 时连 1 都不够分，这里因每个数是 2 的幂、最小为 1，若 n 的 1 的个数都超 k 则无解
输出 Yes，然后循环 sz 次：每次取堆顶（当前最大的 2 的幂，指数 t），把它拆成两个 2^(t-1)（指数 t-1）。拆一次元素数 +1，sz 次之后堆里恰好有 k 个 2 的幂，且它们是 n 的一种合法拆分。（取堆顶优先拆最大的，保证不会拆出负数指数。）
输出阶段独立于 a，用备份的 b 来打印答案：

先取 t = a.top()（a 最终堆里最大的指数）。为了让 b 与 a 达到相同的"元素集合规模"，把 b 中比 t 大的元素也逐个对半拆分。
然后 b.size()>1 循环：依次输出 b.top()（指数）并弹出，k--；最后一个特殊处理成 b.top()-i / b.top()-k+1 的形式逐项输出，保证所有数之和仍为 n、且恰好 k 个数。
这最后一段是比较"trick"的输出构造：由于堆内可能还有些数没被显式拆到和 a 完全一致，作者用"拷贝堆逐项拆分 + 末尾按等差递减输出 b.top()-1, b.top()-2, ..., b.top()-k+1"的方式，保证最终的 k 个数互不相同地排开、且总和恰为原来的 n

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

priority_queue<int> a, b;
int n, k;
signed main() {
    fast;
    cin >> n >> k;
    for (int i = 62; i >= 0; --i)
        if (n&(1ll<<i)) a.push(i);//n 的二进制第 i 位是1 → 存入指数 i
    b = a;
    int sz = k - a.size();
    if (sz < 0) { cout << "No"; return 0; }
    cout << "Yes\n";
    for (int i = 1; i <= sz; ++i) { int t = a.top(); a.pop(); t--; a.push(t); a.push(t); }
    int t = a.top();
    while (b.top() > t) { int x = b.top(); b.pop(); x--; b.push(x); b.push(x); }
    while (b.size() > 1) { cout << b.top() << ' '; b.pop(); k--; }
    for (int i = 1; i < k; ++i) cout << b.top()-i << ' ';
    cout << b.top()-k+1;
    return 0;
}