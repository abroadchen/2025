//
// Created by Psy.C on 2026/2/13.
//
/**
n：第一个数组长度
m：第二个数组长度
a[N]：第一个数组
b[N]：第二个数组（模式串）
nxt[N]：KMP算法的next数组（失效函数）
ans：匹配计数

将原数组转换为相邻元素的差分数组
a[i] = a[i+1] - a[i]：a数组的差分
b[i] = b[i+1] - b[i]：b数组的差分

i = 2, j = 0：从第二个位置开始构造
while (j && b[i] != b[j+1]) j = nxt[j]：
当不匹配时，回退到之前的匹配位置
j = nxt[j]：按照KMP的失配函数回退
if (b[i] == b[j+1]) j++：匹配成功，j向前移动
nxt[i] = j：记录位置i的最长公共前后缀长度

i = 1, j = 0：文本串从1开始，模式串从0开始
while (j && a[i] != b[j+1]) j = nxt[j]：
不匹配时，模式串指针j回退
if (a[i] == b[j+1]) j++：匹配成功，j向前移动
if (j == m - 1) ans++, j = nxt[j]：
当模式串完全匹配（长度为m-1，因为是差分数组）
ans++：计数加1
j = nxt[j]：继续寻找下一个可能的匹配

构建next数组：O(m)
匹配过程：O(n)
总体：O(n + m)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200005
using namespace std;

int n, m, a[N], b[N], nxt[N], ans;

int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= m; ++i) cin >> b[i];
    for (int i = 1; i < n; ++i) a[i] = a[i+1] - a[i];
    for (int i = 1; i < m; ++i) b[i] = b[i+1] - b[i];
    for (int i = 2, j = 0; i <= m; ++i) {
        while (j && b[i] != b[j+1]) j = nxt[j];
        if (b[i] == b[j+1]) j++;
        nxt[i] = j;
    }
    for (int i = 1, j = 0; i <= n; ++i) {
        while (j && a[i] != b[j+1]) j = nxt[j];
        if (a[i] == b[j+1]) j++;
        if (j == m - 1) ans++, j = nxt[j];
    }
    cout << ans;
    return 0;
}