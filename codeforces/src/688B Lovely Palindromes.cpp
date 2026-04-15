//
// Created by Psy.C on 2026/4/15.
//
/**
n：输入字符串数组
ans：结果字符串数组
将原字符串复制到ans数组
从后往前遍历：从字符串的最后一个字符开始
反向添加：将原字符串的字符按相反顺序添加到ans数组的后面
计数器：cnt用于跟踪添加了多少个字符
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1105+2e5;
char n[N], ans[N];
int main() {
    fast;
    cin >> n; int len = strlen(n);
    strcpy(ans, n);
    int cnt = 0;
    for (int i = len-1; i >= 0; --i) {
        ans[len+cnt] = n[i];
        cnt++;
    }
    cout << ans << '\n';
    return 0;
}