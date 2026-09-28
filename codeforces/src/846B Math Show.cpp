//
// Created by Psy.C on 2026/9/28.
//
/**
a[] 存 k 种任务各自的单次代价
s = 一轮（把每种任务各做 1 次）需要的总代价 sum(a[])。
把 a[] 升序排序——贪心时优先选代价小的任务，以便在有限预算内做更多
外层枚举 i：假设完成了 i 轮"全套"（每轮做 k 种各一次，代价 s）。
l = m - i*s：花掉 i 轮后剩下的预算。若 l < 0 说明钱不够做 i 轮，直接 break（i 越大 s 越费，后面也别看了）
已确定完成的题目数：i 轮 × 每轮 k 种 = i*k 道；再加 i（代码里多算 i 道，通常代表那一轮还有一次额外的"额外题"机会）
内层贪心：用剩余预算 l，按代价从小到大依次尝试每种任务：
每种任务最多还能做 n-i 个（剩余天数/容量 n-i）。
若能完整买下当前任务的所有 n-i 个（l >= (n-i)*a[j]），就全买，ans += n-i，扣掉预算；
否则只能买 l/a[j] 个（取与 n-i 的较小值），加到 ans 后 break（钱不够了，后面更贵的也不用看）。
因为排序过，这个贪心保证用剩余钱买到最多的题数
对每个枚举的 i 更新全局最大值
每组数据输出最大完成数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, k, m, a[105];
int main() {
    fast;
    while (cin >> n >> k >> m) {
        ll s = 0, mx = 0;
        for (int i = 1; i <= k; ++i) cin >> a[i], s += a[i];
        sort(a+1, a+k+1);
        for (int i = 0; i <= n; ++i) {
            int l = m - i*s;
            if (l < 0) break;
            ll ans = i*k + i;
            for (int j = 1; j <= k; ++j) {
                if (l >= (n-i)*a[j]) {
                    l -= (n-i)*a[j];
                    ans += n-i;
                } else {
                    ans += min(l/a[j], n-i);
                    break;
                }
            }
            mx = max(mx, ans);
        }
        cout << mx << '\n';
    }
    return 0;
}