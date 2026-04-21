//
// Created by Psy.C on 2026/4/20.
//
/**
s[3]：存储三元组的数组
x：目标值
y：初始值
持续读取输入直到结束
将三元组s的三个元素都初始化为y
sort(s, s + 3)：对三元组排序，使s[0] ≤ s[1] ≤ s[2]
s[0] = min(s[1] + s[2] - 1, x)：更新最小值
新的s[0] = s[1] + s[2] - 1（但不超过目标值x）
ans++：操作次数增加
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int s[3], x, y;
int main() {
    fast;
    while (cin >> x >> y) {
        s[0] = s[1] = s[2] = y;
        int ans = 0;
        while (s[0] != x || s[1] != x || s[2] != x) {
            sort(s, s + 3);
            s[0] = min(s[1] + s[2] - 1, x);
            ans++;
        }
        cout << ans << '\n';
    }
    return 0;
}