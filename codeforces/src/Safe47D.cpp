//
// Created by Psy.C on 2025/10/11.
//
/*
*创建字符串数组s用于存储二进制字符串
定义变量n(字符串长度)和m(字符串数量)
创建整数数组a用于存储限制条件
 *
*定义递归函数p，参数i表示当前处理到第几位
递归基础情况：当处理完所有n位时
检查每个字符串的限制条件a[j]是否都为0
如果都为0则返回1(找到一个有效解)，否则返回0

 *
*初始化返回值ret为0，标志f为true
尝试在当前位置i放置'0'：
对于每个字符串，如果第i位是'0'，则将对应的限制值a[j]减1
如果任何a[j]变为负数，说明违反了限制条件，设置f为false
如果没有违反限制，则递归处理下一位，并将结果加到ret中
恢复a[j]的值(回溯)

*同样地，尝试在当前位置i放置'1'：
重置标志f为true
对于每个字符串，如果第i位是'1'，则将对应的限制值a[j]减1
如果没有违反限制，则递归处理下一位，并将结果加到ret中
恢复a[j]的值(回溯)
返回两种选择的总方案数
 *
*读入字符串长度n和字符串数量m
读入m个二进制字符串和对应的限制值a[i]
在每个字符串前添加空格，使索引从1开始便于处理
调用递归函数p(1)计算方案数并输出
 *
 *
 */
#include <ios>
#include <iostream>
using namespace std;

const int N = 40;
string s[N];
int n, m, a[N];


int p(int i) {
    if (i == n + 1) {
        for (int j = 1; j <= m; ++j) if (a[j]) return 0;
        return 1;
    }
    int ret(0); bool f(1);
    for (int j = 1; j <= m; ++j) {
        if (s[j][i] == '0') a[j]--;
        if (a[j] < 0) f = 0;
    }
    if (f) ret += p(i + 1);
    for (int j = 1; j <= m; ++j) if (s[j][i] == '0') a[j]++;
    f = 1;
    for (int j = 1; j <= m; ++j) {
        if (s[j][i] == '1') a[j]--;
        if (a[j] < 0) f = 0;
    }
    if (f) ret += p(i + 1);
    for (int j = 1; j <= m; ++j) if (s[j][i] == '1') a[j]++;
    return ret;
}

void solve() {
    cin >> n >> m;
    for (int i = 1; i <= m; ++i) {
        cin >> s[i] >> a[i];
        s[i] = ' ' + s[i];
    }
    cout << p(1);
}




int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    solve();

    return 0;
}