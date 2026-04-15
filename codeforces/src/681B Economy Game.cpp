//
// Created by Psy.C on 2026/4/15.
//
/**
k = n - f[0]*i - f[1]*j: 计算剩余值
if (k < 0) break: 如果剩余值为负，跳出内层循环
if (k%f[2] == 0) flag = true: 如果剩余值能被f[2]整除，标记为true

寻找方程 f[0]*i + f[1]*j + f[2]*? = n 的非负整数解
即：1234567*i + 123456*j + 1234*? = n
通过枚举i和j，检查剩余部分是否能被1234整除
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int f[] = {
    1234567,123456,1234
};
int n, k;
int main() {
    fast;
    cin >> n;
    bool flag = false;
    for (int i = 0; i < 820; ++i)
        for (int j = 0; j < 8200; ++j) {
            k = n - f[0]*i - f[1]*j;
            if (k < 0) break;
            if (k%f[2] == 0) flag = true;
        }
    flag ? cout << "YES\n" : cout << "NO\n";
    return 0;
}