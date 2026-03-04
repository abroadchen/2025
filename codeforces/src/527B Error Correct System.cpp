//
// Created by Psy.C on 2026/3/3.
//
/**
n: 字符串长度
v[N]: 记录每个字符首次出现在s中的位置
a[N][N]: 二维数组，记录从字符s[i]到字符t[i]的变换位置
flag: 标记操作类型（0表示无操作，1表示单次交换，2表示两次变换）
s[M], t[M]: 存储两个输入字符串

初始化不同字符对的数量为ans=0
遍历字符串的每个位置i
如果s[i] ≠ t[i]，说明该位置字符不同：
增加ans计数
v[s[i]] = i记录字符s[i]在s中的位置
a[s[i]][t[i]] = i记录从s[i]转换到t[i]的位置

初始化交换位置l=-1, r=-1
遍历字符串，寻找可以互相交换的字符对
如果位置i上的字符不同，且t[i]在s中出现过（v[t[i]]非零）：
找到了一对可以交换的字符：将s[v[t[i]]]与s[i]交换
设置flag=1表示找到第一种优化
记录交换位置l和r
跳出循环

双重循环遍历所有字母对(i,j)
检查是否存在两个位置，使得字符i→j和j→i的变换同时存在
如果存在这样的变换对，说明可以通过一次变换解决两个不匹配：
a[i][j]是将字符i变为j的位置
a[j][i]是将字符j变为i的位置
设置flag=2表示找到第二种优化
记录变换位置l和r

ans -= flag：根据找到的优化方案减少操作次数
输出剩余的不同字符对数量
输出建议的操作位置（如果是-1表示没有找到有效操作）

 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 256, M = 2e5+1;
int n, v[N], a[N][N], flag;
char s[M], t[M];
int main() {
    scanf("%d", &n);
    scanf("%s", s + 1); scanf("%s", t + 1);
    int ans = 0;
    for (int i = 1; i <= n; ++i)
        if (s[i] != t[i]) {
            ans++;
            v[s[i]] = i;
            a[s[i]][t[i]] = i;
        }
    int l = -1, r = -1;
    for (int i = 1; i <= n; ++i)
        if (t[i] != s[i]) {
            if (v[t[i]]) {
                l = v[t[i]], r = i;
                flag = 1;
                break;
            }
        }
    for (char i = 'a'; i <= 'z'; ++i)
        for (char j = 'a'; j <= 'z'; ++j)
            if (a[i][j] && a[j][i]) {
                l = a[i][j], r = a[j][i];
                flag = 2;
                break;
            }
    ans -= flag;
    printf("%d\n", ans);
    printf("%d %d\n", l, r);
    return 0;
}