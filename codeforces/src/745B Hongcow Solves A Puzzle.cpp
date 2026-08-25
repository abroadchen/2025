//
// Created by Psy.C on 2026/5/26.
//
/**
mz[N][N] - 二维字符数组，存储迷宫或矩阵数据
s[N] - 字符数组，存储全为'.'的行
p[N] - 字符数组，存储第一个非空行的模式

flag标志变量，用于区分是否已找到第一个非空白行
flag=0表示还未遇到非空白行
flag=1表示已经遇到过非空白行

外层循环遍历每一行
当flag==0时（还未找到第一个有效行）：
!strcmp(s, mz[i])判断当前行是否全为'.'，如果是则跳过
找到第一个非空白行后，设置flag=1
将该行内容复制到p数组作为模板
统计该行中'X'字符的数量
当flag==1时（已经找到模板行）：
如果当前行是空白行（全为'.'），输出"YES"并退出（表示找到了合理的模式）
如果当前行与模板行p相同，则继续检查下一行
如果当前行既不是空白行也不是模板行，则输出"NO"并退出
如果所有行都符合规则（要么是模板行，要么是空白行，且空白行出现过），则输出"YES"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 501;
char mz[N][N], s[N], p[N];
int n, m;
int main() {
    fast;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) s[i] = '.';//代表空白行
    for (int i = 0; i < n; ++i) cin >> mz[i];
    int flag = 0;
    for (int i = 0, num = 0; i < n; ++i) {
        if (flag == 0) {
            if (!strcmp(s, mz[i])) continue;
            flag = 1;
            for (int j = 0; j < m; ++j) {
                p[j] = mz[i][j];
                if (mz[i][j] == 'X') num++;
            }
        } else {
            if (!strcmp(mz[i], s)) {
                cout << "YES\n";
                return 0;
            }
            if (!strcmp(mz[i], p)) continue;
            if (strcmp(mz[i], p) != 0) {
                cout << "NO\n";
                return 0;
            }
        }
    }
    cout << "YES\n";
    return 0;
}