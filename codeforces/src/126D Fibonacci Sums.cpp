//
// Created by Psy.C on 2025/11/18.
//
/*
*将数字n转换为Zeckendorf表示 非连续斐波那契数的和
贪心方法：从最大的斐波那契数开始，如果合适就从n中减去它
在布尔数组r中标记对应位置
 *
*初始化数组a，值为{0,1}
变量z统计表示中连续零的个数
对于表示中的每个1位：
根据前面零的数量应用变换公式
重置零计数器
 *
*z/2*a[1] 计算了与前一个状态a[1]相关的贡献
(z+1)/2*a[0] 计算了与前一个状态a[0]相关的贡献
两者相加得到新的a[0]值
 *
 */
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;
const int N = 91;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    vector<ll> f(N);
    f[0] = 1; f[1] = 2;
    for (int i = 2; i < N; ++i) f[i] = f[i - 1] + f[i - 2];

    int t; cin >> t;
    while (t--) {
        ll n; cin >> n;
        vector<bool> r(N);
        for (int i = N - 1; i >= 0; --i) {
            if (f[i] <= n) {
                r[i] = true;
                n -= f[i];
            }
        }
        array<ll, 2> a; a = {0,1};
        ll z = 0;
        for (int i = 0; i < N; ++i) {
            if (r[i] == 0) { z++; continue; }
            a = {z/2*a[1] + (z+1)/2*a[0], a[0]+a[1]};
            z = 0;
        }
        cout << a[0] + a[1] << '\n';
    }
    return 0;
}