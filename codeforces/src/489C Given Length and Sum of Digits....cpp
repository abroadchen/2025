//
// Created by Psy.C on 2026/2/18.
//
/**
m: 数字的位数
s: 数字各位之和
len: 当前处理的位置
tot: 剩余的和
num[N]: 存储数字的数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 101;
int m, s, len, tot, num[N];

int main() {
    fast;
    cin >> m >> s;
    //和为0但位数不是1
    if ((s == 0 && m != 1) || s > 9*m) {
        cout << "-1 -1\n";
        return 0;
    }
    //从最后一位开始
    len = m, tot = s;
    while (tot > 0 && len >= 1) {//还有剩余和且位置有效
        if (tot > 9) num[len--] = 9, tot -= 9;//当前位置放9
        else {
            num[len] = tot - 1; num[1]++;//当前位置放tot-1 第一位加1（确保第一位不为0）
            break;
        }
    }
    for (int i = 1; i <= m; ++i) cout << num[i], num[i] = 0;//输出最小数字
    cout << ' ';
    len = 1, tot = s;
    while (tot > 0 && len <= m) {
        if (tot > 9) num[len++] = 9, tot -= 9;
        else num[len++] = tot, tot = 0;
    }
    for (int i = 1; i <= m; ++i) cout << num[i], num[i] = 0;//输出最大数字
    return 0;
}