//
// Created by Psy.C on 2026/4/15.
//
/**
n: 测试用例数量
b: 评级变化前的分数
a: 评级变化后的分数
s[32]: 存储姓名的字符数组（最多31个字符+结束符）

b >= 2400: 评级变化前分数≥2400
b < a: 评级增加了（a > b）
如果条件满足，设置flag = true
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, b, a;
char s[32];
int main() {
    fast;
    cin >> n;
    bool flag = false;
    for (int i = 0; i < n; ++i) {
        cin >> s >> b >> a;
        if (b >= 2400 && b < a)
            flag = true;
    }
    if (flag) cout << "YES\n"; else cout << "NO\n";
    return 0;
}