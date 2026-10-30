//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
k > s：总步数 k 大于总和 s，做不到（起码每步要 ≥1，总和至少＝步数）。准确说 s≥k 才可能。
n*k < s：若每一步最大加 n，k 步最多 n*k，小于 s 则达不到；同理保证可行性。
这两条合并就是经典构造题里"步数×单步最大 ≥ 总和 ≥ 步数×单步最小"的可满足判断
对前 s % k 个位置：

当 i 为奇数：a[i] = s/k + 2
当 i 为偶数：a[i] = 1
这里在做"大步与小步交替"，用奇偶切换不同幅值，把总和的余数部分 s%k 消耗掉，同时保证相邻变化仍 ≤ 步长限制
对剩余位置：

若前一个 a[i-1] <= s/k → a[i] = a[i-1] + s/k（向上加）
否则若 a[i-1] > s/k → a[i] = a[i-1] - s/k（向下减）
这是摆动 (bounce) 构造：让序列在 s/k 附近上下震荡，保证每个相邻差的绝对值为 s/k，从而满足"单步 ≤ n"（因为 s/k 接近每步平均值 ≤ n）
输出这 k 个数（1-based）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 2e5+5;

ll n, k, s, a[N];
int main() {
    fast;
    cin >> n >> k >> s; n--; a[0] = 1;
    if (n*k < s || k > s) return cout << "NO\n", 0;
    cout << "YES\n";
    for (int i = 1; i <= s%k; i++) a[i] = i&1?s/k+2:1;
    for (int i = s%k+1; i <= k; i++)
        a[i] = a[i-1] + (a[i-1] <= s/k ? s/k : -s/k);
    for (int i = 1; i <= k; i++) cout << a[i] << ' ';
    cout << '\n';
    return 0;
}