//
// Created by Psy.C on 2026/9/17.
//
/**
把 n 分解成质因数的多重集合。x 初始为 n，逐步除以质因子。
注意这里 i <= sqrt(x)，且 x 在循环中不断缩小，所以 sqrt(x) 也在变。这是常见的质因数分解写法。
while(x%i==0)：把 i 这个质因子全部除尽，每除掉一次就 push 进 v 一次。所以 v 中可能有重复元素（比如 n=12 分解出 2,2,3）。
循环结束后，若 x > 1，说明还剩下一个大于 1 的质因子（此时它必为质数），也 push 进 v。
结果：v 中包含 n 的全部质因子（含重复），且 v 中所有元素乘积 = n
要把 n 拆成 k 个大于 1 的数相乘，最少需要的"份数"就是质因子的总个数 v.size()（因为质因子不能再拆成两个 >1 的整数，拆得最"细"就是这个数量）。
所以如果 v.size() < k，即质因子总数不足以拆成 k 个数，就无解，输出 -1
既然 v.size() >= k，方案是：取前 k-1 个质因子作为前 k-1 个数（各为 1 个数）‍，把剩下的所有质因子相乘作为第 k 个数 t。
这样总共有 k 个数：v[0], v[1], ..., v[k-2], t。
因为 v 中每个元素都 >1，前 k-1 个数都 >1；t 是至少一个 >1 的质因子之积，也 >1。它们的乘积 = (v[0]·…·v[k-2])·(v[k-1]·…·v[last]) = n
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

vector<int> v;//存放 n 的所有质因子
int main() {
    fast;
    int n, k; cin >> n >> k;
    int x = n;
    for (int i = 2; i <= sqrt(x); ++i) {
        while (x%i == 0) { x /= i; v.push_back(i); }
    }
    if (x > 1) v.push_back(x);
    if (v.size() < k) cout << "-1\n";
    else {
        for (int i = 0; i < k-1; ++i) cout << v[i] << ' ';
        int t = 1;
        for (int i = k-1; i < v.size(); ++i) t *= v[i];
        cout << t << '\n';
    }
    return 0;
}