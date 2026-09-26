//
// Created by Psy.C on 2026/9/25.
//
/**
f2：反复除以 2，统计 num 里 2 的因子数量，存到 c2[pos]。
f5 同理统计 5 的因子数量到 c5[pos]
读入 n 个数，逐个统计各自的 2、5 因子数
dp[j][l]：选 j 个数，且这 j 个数5 因子总数恰好为 l 时，能得到的 2 因子总数的最大值。
为什么用 5 因子数作"容量"维度：末尾 0 = min(2 总数, 5 总数)，5 的因子通常更稀缺（更可能是瓶颈），且 5 的因子总数上限设为 M=5000 够用
全部初始化为极小值（-0x3f3f3f3f 级别），表示不可达；dp[0][0]=0（选 0 个数、0 个 5 因子时 2 因子数为 0
对每个数字 i，做 01 背包：
j 从 k 到 1 逆序（保证每个数最多选一次）。
l 从 c5[i] 到 M，表示"选了这个数的 5 因子"。
转移：不选 = dp[j][l]；选 = 在 dp[j-1][l-c5[i]]（少选一个、少 c5 个因子）基础上加上该数的 2 因子数 c2[i]。
结果：dp[j][l] 是选 j 个数、5 因子总数为 l 时的最大 2 因子总数
对每种"5 因子总数 = i"，末尾 0 的个数 = min(i, 2因子总数) = min(i, dp[k][i])。
取所有 i 中的最大值即为答案。
注意 dp[k][i] 可能是不可达的负值，min(i, 负值) 得负，不影响 ans 取最大
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 220, M = 5e3;

int c2[N];
void f2(ll num, int pos) {
    while (num%2 == 0) {
        c2[pos]++;
        num /= 2;
    }
}
int c5[N];
void f5(ll num, int pos) {
    while (num%5 == 0) {
        c5[pos]++;
        num /= 5;
    }
}

int n, k, dp[N][M+10];
int main() {
    fast;
    cin >> n >> k;
    for (int i = 1; i <= n; ++i) {
        ll num; cin >> num;
        f2(num, i); f5(num, i);
    }
    memset(dp, -0x3f, sizeof dp); dp[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = k; j >= 1; --j)
            for (int l = c5[i]; l <= M; ++l)
                dp[j][l] = max(dp[j][l], dp[j-1][l-c5[i]]+c2[i]);
    }
    int ans = 0;
    for (int i = 1; i <= M; ++i)
        ans = max(ans, min(i, dp[k][i]));
    cout << ans << '\n';
    return 0;
}