//
// Created by Psy.C on 2026/11/1.
//

/**
真正学会的起点..
a[]、b[] 存 n 对数。
p[]：候选质因子集合（最多 2e5 规模）。
idx：候选质因子个数
答案质因子一定包含在 a[1] 和 b[1] 的质因数集合中。

为什么？因为如果存在满足条件的质数 x，那么根据题意，x 至少整除第一对中的一个数（a[1] 或 b[1]），所以 x 必然是第一对某个数的质因子。于是只需从第一对的质因数里去找答案即可，无需枚举所有数的因子。

这段代码就是把 a[1] 和 b[1] 做试除分解质因数，把所有质因子（含重复）塞进候选数组 p[]：

标准试除法：从 2 到 √x 枚举因子，while (x%j==0) 把因子 j 全部剥离（记录并计数）。
最后若 x > 1，说明剩下一个大于 √ 的质因子，也加入。
对 a[1] 和 b[1] 各做一遍。
注意：这里 p[] 会记录重复的相同质因子（因为 while 循环每剥离一个就 push 一次）。这不影响正确性，只是集合偏大、稍冗余。
对第 2 到第 n 对，检查每个候选质因子 p[j]：

条件 a[i]%p[j]!=0 && b[i]%p[j]!=0：p[j] 既不能整除 a[i]、也不能整除 b[i]，即这一对中没有一个数是 p[j] 的倍数 → 违反"至少一个被整除"的约束。
满足条件就把 p[j] 标记为 -1（剔除）。
这正好实现了预期约束：某质因子必须让每一对都"至少命中一个数"，一旦某对两个都不命中，就淘汰掉
遍历所有候选，只要找到一个没被淘汰的（!= -1），输出它。
若全部被淘汰，输出 -1（无解）

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define int long long
using namespace std;

constexpr int N = 2e5+5;

int n, a[N], b[N], p[N], idx;
signed main() {
    fast;
    cin >> n;
    rep(i,n) {
        cin >> a[i] >> b[i];
        if (i == 1) {
            int x = a[1], y = b[1];
            for (int j = 2; j*j <= x; j++)
                while (x%j == 0) { p[++idx] = j; x/=j; }
            if (x > 1) p[++idx] = x;
            for (int j = 2; j*j <= y; j++)
                while (y%j == 0) { p[++idx] = j; y/=j; }
            if (y > 1) p[++idx] = y;
        } else {
            rep(j,idx) if (a[i]%p[j] != 0 && b[i]%p[j] != 0)
                p[j] = -1;
        }
    }
    rep(i,idx) if (p[i] != -1) { cout << p[i] << '\n'; return 0; }
    cout << -1 << '\n';
    return 0;
}