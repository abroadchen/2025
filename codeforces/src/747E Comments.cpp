//
// Created by Psy.C on 2026/8/25.
//
/**
- len ：存储输入字符串的长度。
- mx ：辅助变量，记录DFS过程中的最大位置，用于回溯

- j ：移动指针，从位置 i 开始遍历。
- num ：计数器，记录已处理的子节点数量
无限循环，持续解析当前节点的子节点
- 清空临时字符串 t 。
- 从位置 j 开始读取字符，直到遇到逗号','或字符串结束。
- 将读取的字符拼接成节点名称 t 。
- 将节点名称添加到当前层 v[dep] 的末尾。
- 定义 t1 存储子节点数量。
- j++ 跳过节点名称后面的逗号。
- 读取数字字符，转换为整数： t1 = t1 * 10 + (字符 - '0')
更新 mx 为当前最大位置，用于后续回溯
- 若 t1 == 0 ：当前节点无子女， j++ 跳过下一个逗号。
- 否则：
- 保存当前位置到 mx 。
- 递归调用 dfs 处理子节点：位置为 j + 1 （跳过当前逗号），子节点数量为 t1 ，层级加1。
- 递归返回后，将 j 设置为 mx （回溯到正确位置）
- 已处理的子节点数量 num 加1。
- 若已处理完 x 个子节点，返回

- 读取输入字符串到 s[1] （从下标1开始存储，方便处理）。
- 计算字符串长度 len
- 初始化层级 dep 为1。
- 调用DFS从位置1开始解析，根节点的"子节点数量"设为 len （实际是遍历整个字符串），层级为1
计算实际的最大深度 dep ，只要下一层 v[dep+1] 非空，就继续增加深度
输出树的最大深度
- 遍历每一层 i （从1到最大深度）。
- 获取该层的节点数量 len 。
- 遍历该层的每个节点：
- 输出节点名称 v[i][j] 。
- 若是该层最后一个节点，输出换行；否则输出空格分隔
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e6+100;
int len, mx;
string t;//临时字符串，用于解析节点名称
char s[N];//存储输入的树结构字符串
vector<string> v[N];//存储第 dep 层的所有节点名称
/**
 *
 * @param i 当前解析的起始位置（在字符串中的下标）
 * @param x 当前节点的 子节点数量
 * @param dep 当前层级深度
 */
void dfs(int i, ll x, int dep) {
    int j = i, num = 0;
    while (true) {
        if (j > len) return;//超出字符串长度则返回
        t = "";
        while (j <= len && s[j] != ',') { t += s[j]; j++; }
        v[dep].push_back(t);
        ll t1 = 0;
        j++;
        while (j <= len && s[j] != ',') {
            t1 = t1 * 10 + s[j] - '0';
            j++;
        }
        mx = max(mx, j + 1);
        if (t1 == 0) j++;
        else {
            mx = j + 1;
            dfs(j + 1, t1, dep + 1);
            j = mx;
        }
        num++;
        if (num == x) return;
    }
}

int main() {
    fast;
    scanf("%s", s + 1);
    len = strlen(s + 1);
    int dep = 1;
    dfs(1, len, 1);
    while (!v[dep+1].empty()) dep++;
    cout << dep << endl;
    for (int i = 1; i <= dep; ++i) {
        int len = v[i].size();
        for (int j = 0; j <= len - 1; ++j) {
            cout << v[i][j];
            if (j == len - 1) cout << endl; else cout << ' ';
        }
    }
    return 0;
}