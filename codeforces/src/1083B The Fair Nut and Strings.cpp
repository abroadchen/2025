//
// Created by Psy.C on 2026/11/15.
//

/**
真正学会的起点..
x 表示：当前前缀 i（前 i 个字符）下，介于 a、b 之间且以 a 为下界、b 为上界的"可行前缀数量"。

逐步解释：

初值 x=1：前 0 个字符时，介于二者之间的空前缀有 1 个。
x <<= 1：每个字符位置有 2 种选择（'a' 或 'b'），前缀数量翻倍。
x -= (a[i]=='b') + (b[i]=='a')：剔除违反边界的两类前缀：
若 a[i]=='b'：说明以 a 的前缀为下界，此时取 'a'（<边界）不合法，扣除 1。
若 b[i]=='a'：说明以 b 的前缀为上界，此时取 'b'（>边界）不合法，扣除 1。
ans += x：每层累加"前 i 位为止、介于二者之间且前缀数量 = x"的长度为 i（每层）的合法串个数
一旦某层可行前缀数 x ≥ k，后续每一层至少还有 k 个可行串，总共再算 (n-i) 层，每层至少 k 个 —— 所以答案封顶 ans + (n-i)*k，直接输出避免继续爆炸增长（因为数量可能呈指数级、超出 long long / 题目只问是否 ≥k 截断计数）

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 5e5+5;

int n, k;
char a[N], b[N];
ll ans;
int main() {
    fast;
    cin >> n >> k >> a >> b;
    ll x = 1;
    for (int i = 0; i < n; ++i) {
        x <<= 1;
        x -= (a[i] == 'b') + (b[i] == 'a');
        if (x >= k) {
            cout << ans + (ll)(n-i)*k << '\n';
            return 0;
        }
        ans += x;
    }
    cout << ans << '\n';
    return 0;
}