//
// Created by Psy.C on 2026/9/6.
//
/**
N = 505：定义最大长度为 500+ 的缓冲区，足够容纳大多数测试数据。
a[N]：存放读取的字符串（C 风格字符数组）。
vis[N]：辅助数组，用于标记哪些字母已出现（0 表示未出现，1 表示已出现
使用 while (cin >> a) 持续读取直到文件结束（EOF）。
memset(vis, 0, sizeof(vis));：清空标记数组，确保每个测试用例独立。
l = strlen(a)：获取字符串长度。
flag = 1：初始化状态标记，默认认为是合法的（YES
m = a[i] - 'a'：将字符映射为对应的下标（'a' -> 0, 'b' -> 1, ...）。
内部循环：遍历当前字符之前的所有字母 (j < m)。
若发现有任何一个前置字母未出现 (!vis[j])，则将 flag 设为 0（标记为非法）。
vis[m] = 1;：标记当前字母已出现，为后续字符提供依据
flag == 1 → 所有字符均符合规则 → 输出 YES。
flag == 0 → 存在违规字符 → 输出 NO
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 505;
char a[N];
int vis[N];
int main() {
    fast;
    while (cin >> a) {
        memset(vis, 0, sizeof(vis));
        int l = strlen(a), flag = 1;
        for (int i = 0; i < l; ++i) {
            int m = a[i] - 'a';
            for (int j = 0; j < m; ++j)
                if (!vis[j]) flag = 0;
            vis[m] = 1;
        }
        cout << (flag ? "YES\n" : "NO\n");
    }
    return 0;
}