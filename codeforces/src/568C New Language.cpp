//
// Created by Psy.C on 2026/3/12.
//
/**
指针S指向当前读取位置，T指向缓冲区末尾

快速读取字符串
跳过空白字符
逐字符读取直到遇到空白字符或EOF
返回字符串长度

2-SAT问题中的DFS函数
如果对应节点已被访问，返回false
标记当前节点u已访问
递归访问邻接节点，如果发现冲突返回false

检查给定位置pos的解是否可行
初始化vis数组
对前pos个位置进行DFS检查
对后面的位置根据访问状态分配字符
如果分配失败返回false

读取初始字符串s，长度为l
初始化各种数组
从后往前处理字符串，将'V'映射为0，其他字符映射为1
更新pre和mn数组
读取n和m
处理m个约束条件
根据字符类型（'V'或其他）确定节点索引
构建图的邻接表
重新读取输入字符串
检查当前解是否可行，如果可行则输出
如果某个字符不存在，输出-1
从后往前尝试修改字符串
尝试不同的字符替换方案
如果找到可行解则输出
如果无法找到解则输出"-1"


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int SIZE = 1<<20|1;
char buf[SIZE], *S = buf, *T = buf;
#define gc \
(S == T ? T = ((S = buf) + fread(buf, 1, SIZE, stdin)), \
(S == T ? EOF : *S++) : *S++)

int rd_str(char *s) {
    int top = 0; char ch = gc;
    while (isspace(ch)) ch = gc;
    while (!isspace(ch) && ch != EOF) s[++top] = ch, ch = gc;
    return top;
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = gc) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = gc) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

constexpr int N = 405, M = 30;

int vis[N], n;
vector<int> e[N];
bool dfs(int u) {
    if (vis[u > n ? u - n : u + n]) return false;
    vis[u] = 1;
    for (int& v : e[u]) if (!vis[v])
        if (!dfs(v)) return false;
    return true;
}

int b[N], pre[2];
char s[N];
bool check(int pos) {
    memset(vis, 0, sizeof(vis));
    for (int i = 1; i <= pos; i++)
        if (!dfs(i + b[s[i] - 'a' + 1] * n)) return false;
    for (int i = pos + 1; i <= n; i++) {
        if (vis[i]) s[i] = pre[0] + 'a' - 1;
        else if (vis[i+n]) s[i] = pre[1] + 'a' - 1;
        else {
            int v = min(pre[0], pre[1]);
            if (dfs(i + b[v]*n)) s[i] = v + 'a' - 1;
            else return false;
        }
    }
    return true;
}

int m, l, mn[M][2];
int main() {
    fast;
    l = rd_str(s); mn[l+1][0] = mn[l+1][1] = pre[0] = pre[1] = l + 1;
    for (int i = l; i; i--) {
        b[i] = s[i] == 'V' ? 0 : 1;
        pre[b[i]] = i;
        mn[i][0] = pre[0], mn[i][1] = pre[1];
    }
    n = rd(), m = rd();
    for (int i = 1; i <= m; ++i) {
        int x = rd(), u1, u2, v1, v2; rd_str(s);
        u1 = x + (s[1] == 'V' ? 0 : n), u2 = u1 > n ? u1 - n : u1 + n;
        x = rd(); rd_str(s);
        v1 = x + (s[1] == 'V' ? 0 : n), v2 = v1 > n ? v1 - n : v1 + n;
        e[u1].push_back(v1), e[v2].push_back(u2);
    }
    memset(s, 0, sizeof(s)); rd_str(s);
    if (check(n)) { printf("%s\n", s + 1); return 0; }
    if (pre[0] == l+1 || pre[1] == l+1) return printf("-1\n"), 0;
    for (int i = n; i; i--) {
        int v = s[i] - 'a' + 2, v1 = min(mn[v][0], mn[v][1]), v2 = max(mn[v][0], mn[v][1]);
        if (v1 != l+1) {
            s[i] = v1 + 'a' - 1;
            if (check(i)) {
                printf("%s\n", s + 1);
                return 0;
            }
        }
        if (v2 != l+1) {
            s[i] = v2 + 'a' - 1;
            if (check(i)) {
                printf("%s\n", s + 1);
                return 0;
            }
        }
    }
    return printf("-1\n"), 0;
}