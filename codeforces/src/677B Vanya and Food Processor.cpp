//
// Created by Psy.C on 2026/4/13.
//
/**
n: 物品数量
h: 容器最大容量
k: 每次处理的单位容量
a[N]: 每个物品的大小

情况1：sum + a[i] > h（当前累积值加上新物品会溢出）
if (sum % k == 0) ans += sum/k; else ans += sum/k + 1;
将当前累积的sum清空，计算需要多少次处理
如果sum能被k整除，直接除法
否则向上取整（需要多一次处理）
ans += a[i]/k;：处理新物品需要的次数
sum = a[i]%k;：剩余未处理的部分
情况2：sum + a[i] <= h（可以安全添加）
sum += a[i];：累加到当前批次
ans += sum/k;：处理当前批次中能被k整除的部分
sum %= k;：保留不足k的部分
if (sum > 0) ans++;：如果最后还有剩余未处理的部分，需要一次额外操作
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+5;
int n, h, k, a[N];
int main() {
    fast;
    cin >> n >> h >> k;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    ll ans = 0, sum = 0;
    for (int i = 1; i <= n; ++i) {
        if (sum + a[i] > h) {
            if (sum % k == 0) ans += sum/k;
            else ans += sum/k + 1;
            ans += a[i]/k;
            sum = a[i]%k;
        } else {
            sum += a[i];
            ans += sum/k;
            sum %= k;
        }
    }
    if (sum > 0) ans++;
    cout << ans << '\n';
    return 0;
}