//
// Created by Psy.C on 2026/2/21.
//
/**
实际上x = '9' - a[i] + 1意味着：
x = (10 - (a[i] - '0')) % 10
这样a[i] + x ≡ 0 (mod 10)

i: 选定基准字符a[i]，计算变换值x
j: 比较变换后字符串的第j位
i+j: 原字符串中参与比较的实际位置

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1001;
int n, b[N];//整数数组存储
char a[N];
int main() {
    fast;
    cin >> n; b[0] = 0;
    for (int i = 1; i < N-1; ++i) b[i] = 9;//初始化为最大值，用于比较更新
    cin >> a;
    for (int i = 0; i < n; ++i) {//遍历每个可能的起始位置
        const int x = '9' - a[i] + 1;//使a[i]变为'0'需要加的值
        for (int j = 1; j < n; ++j) {
            const int y = (a[(i+j)%n] - '0' + x) % 10;//在变换x下，位置(i+j)%n的字符变换结果
            if (y < b[j]) {
                for (int k = 1; k < n; ++k)
                    b[k] = (a[(i+k)%n] - '0' + x) % 10;//更新整个结果
                break;//跳出j循环，不再比较后续位置 继续尝试下一个起始位置i
            }
            if (y > b[j]) break;//放弃这个变换方案 跳出j循环，尝试下一个起始位置i
        }
    }
    for (int i = 0; i < n; ++i) cout << b[i];
    cout << '\n';
    return 0;
}