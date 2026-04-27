//
// Created by Psy.C on 2026/4/27.
//
/**
n：表示字符串长度
k：表示跳跃步长
a[N]：字符数组存储输入字符串
遍历字符串找到'G'的位置并记录在idx中
初始化标志位flag=0，设置当前位置l=idx
循环条件：l >= 1（确保在有效范围内）
如果当前位置是'T'：设置flag=1并退出循环
如果当前位置是'#'：遇到障碍物，退出循环
否则：向左移动k个单位(l -= k)
如果左方向找到'T'，直接输出"YES"并结束程序
设置当前位置r = idx（从'G'的位置开始）
循环条件：r <= n（确保在有效范围内）
如果当前位置是'T'：设置flag=1并退出循环
如果当前位置是'#'：遇到障碍物，退出循环
否则：向右移动k个单位(r += k)
如果找到了'T'（flag为1）：输出"YES"
否则：输出"NO"
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 107;
int n, k;
char a[N];
int main() {
    cin >> n >> k; scanf("%s", a + 1);
    int idx = 0;
    for (int i = 1; a[i]; ++i)
        if (a[i] == 'G') idx = i;
    int flag = 0, l = idx;
    while (l >= 1) {
        if (a[l] == 'T') { flag = 1; break; }
        if (a[l] == '#') break;
        l -= k;
    }
    if (flag) {
        cout << "YES\n";
        return 0;
    }
    int r = idx;
    while (r <= n) {
        if (a[r] == 'T') { flag = 1; break; }
        if (a[r] == '#') break;
        r += k;
    }
    if (flag) cout << "YES\n"; else cout << "NO\n";
    return 0;
}