//
// Created by Psy.C on 2026/9/26.
//
/**
先求 a、b 的最大公约数，把 a、b 同时除以 g，使两者互质（约到最简）。
注意：并不是把 a、b 化简成最简分数，而是约掉共同因子，便于后续处理
对化简后的 a 做试除法质因数分解：把所有质因子压入 v（可含重复——即因子含幂次）。
if (a != 1) v.push_back(a)：最后若剩余 >1，则它本身是一个大于 √(原a) 的质因子。
分解完把 a 还原成 A，因为后面的循环还要用 a
循环条件：b>1 且 a>1（只要还有质因子要消且 b 还能变化）。
步骤：
在所有尚未使用的质因子 v[i] 中，选择 b % v[i] 最小的那个（贪心优先级：余数最小）。
a /= v[idx]：让 a 丢掉一个质因子。
代价 ans += b % v[idx]：累加这一次的"余数"。
b /= v[idx]：b 也同步除以该因子。
mp[idx]=1：该质因子用过了，后面不再用。
贪心含义：每次挑"b 对某个质因子取余最小"的因子来除，以最小化累积成本。这是这类"每次除一个质因子，代价 = 当前 b 对它的余数"问题的常见贪心策略。
循环结束后输出 ans + b。
+b：当循环因为 b 或 a 无法继续（比如 a 已到 1，或剩下的质因子都用完）而退出时，把剩余的 b 一并加入答案
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int a, b, ans;
vector<int> v;
map<int, bool> mp;
signed main() {
    fast;
    cin >> a >> b;
    int g = __gcd(a, b); a/=g, b/=g;
    int A = a;
    for (int i = 2; i*i <= a; ++i)
        while (a%i == 0) v.push_back(i), a/=i;
    if (a != 1) v.push_back(a);
    a = A;
    while (b > 1 && a > 1) {
        int mn = 1e18, idx = -1;
        for (int i = 0; i < v.size(); ++i) {
            if (mp[i]) continue;
            if (mn > b%v[i]) mn = b%v[i], idx = i;
        }
        a/=v[idx]; ans+=b%v[idx]; b/=v[idx]; mp[idx]=1;
    }
    cout << ans+b;
    return 0;
}