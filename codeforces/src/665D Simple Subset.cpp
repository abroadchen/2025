//
// Created by Psy.C on 2026/4/12.
//
/**
最初将所有数字标记为可能的质数
设置isp[1] = 0（1不是质数）
对于每个质数i，将其所有倍数标记为合数
p[K]: 存储输入数字的数组
cnt: 输入中数字1的计数
c2: 标志，指示数字2是否存在

如果输入中有2个或更多1
寻找偶数p[i]，使得p[i]+1是质数
如果找到，答案包括所有1加上这个偶数（因为1 + 偶数 = 奇数，我们希望和成为质数）
输出计数和选定的数字
按升序对数组排序
寻找任何和为质数的数字对
如果不存在这样的对，选择排序数组中的第一个质数
如果不存在质数，选择第一个元素（根据问题约束必须是1）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e6+5, M = N<<1, K = 1005;
int isp[M+1];
void get() {
    for (int i = 1; i <= M; ++i) isp[i] = 1;
    isp[1] = 0;
    for (int i = 2; i*i <= M; ++i) if (isp[i]) {
        int x = i;
        while (x*i <= M) {
            isp[x*i] = 0;
            x++;
        }
    }
}

int n, p[K];
int main() {
    fast;
    cin >> n; get();
    int cnt = 0, c2 = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
        if (p[i] == 1) cnt++;
        if (p[i] == 2) c2 = 1;
    }
    if (cnt >= 2) {
        int t = 0;
        for (int i = 1; i <= n; ++i) if (p[i]%2 == 0)
            if (isp[p[i]+1]) t = p[i];
        if (t == 0) cout << cnt; else cout << cnt + 1;
        cout << '\n';
        while (cnt--) cout << 1 << ' ';
        if (t) cout << t;
        cout << '\n';
    } else {
        sort(p + 1, p + n + 1);
        for (int i = 1; i < n; ++i)
            for (int j = i + 1; j <= n; ++j)
                if (isp[p[i]+p[j]]) {
                    cout << 2 << '\n' << p[i] << ' ' << p[j];
                    return 0;
                }
        int ok = 0;
        for (int i = 1; i <= n; ++i)
            if (isp[p[i]]) {
                ok = p[i];
                break;
            }
        if (ok) cout << 1 << '\n' << ok;
        else cout << 1 << '\n' << p[1];
    }
    return 0;
}