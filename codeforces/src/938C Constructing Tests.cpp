//
// Created by Psy.C on 2026/10/17.
//
/**
多组测试，每组读入目标值 x
x == 0：直接答案 (1,1)（此时 n²−(n/m)²=0，如 n=1,m=1）。
x == 1：直接无解 → -1（因为 x=1 无法表示成两个平方差为 1 且满足关系的正整数对，代码直接判 -1）
枚举 n（n 从 1 到 N=1e5+10）：
若 n*n <= x 则跳过（因为 n²−(…)² ≤ n²，若 n²≤x 则差不可能等于更大的 x，剪枝）。
k = sqrt(n*n - x)：令 k² = n² − x 的整数开方（k² 要恰好等于被减的那个平方项，即 floor(n/m) 的平方）。
m = n / k：反推 m = floor(n / k)（整数除法）。
检验条件 k>0 且 n*n − (n/m)*(n/m) == x：实际验证 floor(n/m) == k 是否成立，从而满足原方程。
满足则输出 n 和 m，结束。
枚举完没找到 → 输出 -1
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+10;

int main() {
    fast;
    int T; cin >> T;
    while (T--) {
        ll x; cin >> x;
        if (x == 0) cout << "1 1\n";
        else if (x == 1) cout << "-1\n";
        else {
            int f = 0;
            for (ll n = 1; n < N; ++n) {
                if (n*n <= x) continue;
                ll k = sqrt(n*n - x), m = n/k;
                if (k > 0 && n*n-(n/m)*(n/m) == x) {
                    f = 1;
                    cout << n << ' ' << m << '\n';
                    break;
                }
            }
            if (!f) cout << "-1\n";
        }
    }
    return 0;
}