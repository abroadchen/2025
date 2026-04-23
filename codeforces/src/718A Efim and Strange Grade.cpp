//
// Created by Psy.C on 2026/4/22.
//
/**
m：小数点位置索引
t：最多可以执行的进位操作次数
r：结果有效长度
s：输入的数字字符串
从位置x开始向前递归处理进位
x == m：到达小数点位置停止
t <= 0：进位次数用完停止
如果当前字符是'5'到'9'，需要向上一位进位
如果前一位是小数点，则跳过小数点向更前一位进位
r = x：记录当前处理的有效长度

从小数点后第一位开始查找需要进位的数字
找到第一个≥5的数字就调用dfs处理
从右到左处理可能的进位溢出（数字≥10的情况）
如果最高位发生进位，输出1
跳过小数点字符
如果某位≥10，向高位进位，当前位减10]
按有效长度输出结果
只输出数字字符和小数点
O(n + t)，其中n是字符串长度，t是最大进位次数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int m, t, r;
string s;
void dfs(int x) {
    if (x == m || t <= 0) return;
    if (s[x] >= '5' && s[x] <= '9') {
        if (s[x-1] == '.') s[x-2]++;
        s[x-1]++, r = x;
    }
    t--;
    dfs(x-1);
}

int n;
int main() {
    fast;
    cin >> n >> t; r = n;
    cin >> s;
    for (int i = 0; i < n; ++i) if (s[i] == '.') {
        m = i; break;
    }
    if (m == 0) m = n;//没有小数点则整个都是整数部分
    for (int i = m+1; i < n; ++i) {
        if (s[i] >= '5' && s[i] <= '9') {
            dfs(i); break;
        }
    }
    for (int i = r-1; i >= 0; --i) {
        if (i == 0 && s[i] - '0' >= 10) cout << 1;
        if (s[i] == '.') continue;
        if (s[i] - '0' >= 10) {
            if (s[i-1] == '.') s[i-2]++; else s[i-1]++;
            s[i] -= 10;
        }
    }
    for (int i = 0; i < r; ++i)
        if ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')
            cout << s[i];
    return 0;
}