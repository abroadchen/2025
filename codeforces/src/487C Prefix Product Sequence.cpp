//
// Created by Psy.C on 2026/2/18.
//
/**
b[N+1]: 标记数组，用于埃拉托斯特尼筛法
p[N+1]: 存储素数的数组
cnt: 素数计数器
inv[N+1]: 逆元数组

埃拉托斯特尼筛法的改进版（欧拉筛/线性筛）
b[i] == 0 表示i是素数
p[++cnt] = i 将素数i存入数组
内层循环标记合数，i*p[j] > N跳出，i%p[j] == 0时break避免重复标记
inv[i] = (n - n/i) * inv[n%i] % n
这是利用递推关系 i * inv[i] ≡ 1 (mod n) 推导出的

筛法：O(N)
逆元计算：O(n)
总体：O(N)，其中N是预设的最大值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 100000;
ll n, b[N+1], p[N+1], cnt, inv[N+1];

int main() {
    fast;
    cin >> n;
    if (n == 1) {
        cout << "YES\n" << 1;
        return 0;
    }
    if (n == 4) {
        cout << "YES\n" << 1 << '\n' << 3 << '\n' << 2 << '\n' << 4;
        return 0;
    }
    for (int i = 2; i <= N; ++i) {
        if (b[i] == 0) p[++cnt] = i;
        for (int j = 1; j <= cnt; ++j) {
            if (i*p[j] > N) break;
            b[i*p[j]] = 1;
            if (i%p[j] == 0) break;
        }
    }
    if (b[n] == 1) { cout << "NO"; return 0; }//n是合数
    inv[1] = 1;
    for (int i = 2; i < n; ++i) inv[i] = (n-n/i)*inv[n%i]%n;
    for (int i = 1; i < n; ++i) inv[i] = inv[i]*(i+1)%n;
    cout << "YES\n" << 1 << '\n';
    for (int i = 1; i < n; ++i)
        cout << (inv[i] + n - 1)%n + 1 << '\n';
    return 0;
}