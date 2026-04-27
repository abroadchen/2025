//
// Created by Psy.C on 2026/4/27.
//
/**
n: 数组长度
b[N], c[N]: 输入数组
s[N]: s[i] = b[i] + c[i]
avg: 所有s[i]的平均值
a[N]: 要求的目标数组
p[N][30]: a数组的二进制表示
u[30]: 每一位上1的个数
sum: 所有s[i]的总和

当第j位为1时：b贡献(1<<j)*u[j]，c贡献(1<<j)*n
当第j位为0时：b贡献0，c贡献(1<<j)*u[j]

b[i] = Σ(a[i] & a[j]) (j ≠ i)
c[i] = Σ(a[i] | a[j]) (j ≠ i)
由于AND和OR运算的性质，我们可以利用：
a[i] & a[j] + a[i] | a[j] = a[i] + a[j]
所以 b[i] + c[i] = Σ(a[j]) + (n-1)*a[i]
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 2e5+7;
int n, b[N], c[N], s[N], avg, a[N], p[N][30], u[N];
ll sum;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> b[i];
    for (int i = 1; i <= n; ++i) cin >> c[i];
    for (int i = 1; i <= n; ++i)
        s[i] = b[i] + c[i], sum += s[i];
    avg = sum / (2*n);
    for (int i = 1; i <= n; ++i)
        a[i] = (s[i] - avg)/n;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < 30; ++j)
            if (a[i]>>j&1)
                p[i][j] = 1, u[j]++;//统计每一位上1的个数（存储在u[j]中）
    int flag = 1;
    for (int i = 1; i <= n; ++i) {
        b[0] = c[0] = 0;
        for (int j = 0; j < 30; ++j) {
            if (p[i][j]) {
                b[0] += (1<<j)*u[j];
                c[0] += (1<<j)*n;
            } else c[0] += (1<<j)*u[j];
        }
        if (b[0] != b[i] || c[0] != c[i]) {
            flag = 0;
            break;
        }
    }
    if (flag)//验证通过
        for (int i = 1; i <= n; ++i)
            cout << a[i] << ' ';
    else cout << "-1\n";
    return 0;
}