//
// Created by Psy.C on 2026/10/14.
//
/**
欧拉线性筛，筛出 1e6 以内的所有质数存入 pri，vis 标记合数。
每个合数只被其最小质因子筛掉一次，O(N) 复杂度
分解 x 的质因数，返回 x 的最大质因子（最后剩下的大质因子会赋给 ret）。
循环条件 pri[i] <= t/pri[i] 即 pri[i] <= sqrt(t)，只试到根号即可（剩下的 x!=1 必是质数且是最大质因子）
st = get(n)：n 的最大质因子。
枚举 i ∈ [n-st+1, n]：
t = i - get(i) + 1：以 i 为右端点，i 减去其最大质因子再加 1，得到某个左端点候选。
若 t >= 3 则更新最小答案。
输出最小可行的 t
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e6+10;

bool vis[N];
int pri[N], cnt;
void sieve() {
    for (int i = 2; i < N; ++i) {
        if (!vis[i]) pri[cnt++] = i;
        for (int j = 0; j < cnt && i < N/pri[j]; ++j) {
            int k = i*pri[j]; vis[k] = true;
            if (i%pri[j] == 0) break;
        }
    }
}

int get(int x) {
    int ret = 0, t = x;
    for (int i = 0; i < cnt && pri[i] <= t/pri[i]; ++i) {
        while (x%pri[i] == 0) {
            x/=pri[i];
            ret = pri[i];
        }
    }
    if (x != 1) ret = x;
    return ret;
}

int n;
int main() {
    fast;
    sieve();
    while (cin >> n) {
        int st = get(n), ans = INT_MAX;
        for (int i = n-st+1; i <= n; ++i) {
            int t = i - get(i) + 1;
            if (t >= 3) ans = min(ans, t);
        }
        cout << ans << '\n';
    }
    return 0;
}