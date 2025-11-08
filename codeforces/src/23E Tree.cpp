//
// Created by Psy.C on 2025/9/19.
//
/*
 *逐位读取数字字符并转换为整数
 *将数字按位分解并输出
 *
 *用数组存储每一位数字
*重载赋值运算符，将整数赋值给大整数
clear函数清除前导零
 *
*深度优先搜索函数
初始化当前节点大小为1，选择当前节点的方案数为1
遍历所有子节点
 *
*状态转移：合并子树结果
计算选择p个节点和在当前子树中选择q个节点的乘积
更新最优解
 *
*计算当前子树选择i个节点时的权值(i * 方案数)
更新全局最优解
 *
 *从根节点1开始DFS
 *
 *
 */
#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int MAXN = 705;
const int MAXLEN = 120;

inline ll read() {
    char ch; ll num, f = 0;
    while (!isdigit(ch = getchar())) f |= (ch == '-');
    num = ch - '0';
    while (isdigit(ch = getchar())) num = num * 10 + ch - '0';
    return f ? -num : num;
}

int n, sz[MAXN];
vector<int> G[MAXN];

template<class T> inline void putnum(T x) {
    if (x < 0) putchar('-'), x = -x;
    register short a[20] = {}, sz = 0;
    while (x) a[sz++] = x % 10, x /= 10;
    if (sz == 0) putchar('0');
    for (int i = sz - 1; i >= 0; --i) putchar('0' + a[i]);
}

struct Node {
    int d[MAXLEN], len;
    Node() { memset(d, 0, sizeof d), len = 1; }
    Node(int num) { *this = num; }

    Node& operator=(const int& num) {
        memset(d, 0, sizeof d);
        int t = num; len = 0;
        while (t) d[++len] = t%10, t /= 10;
        return *this;
    }
    void clear() { while (len > 1 && !d[len]) len--; }

    Node operator+(const Node& num) {
        Node ret = *this;
        ret.len = max(num.len, len);
        for (int i = 1; i <= ret.len; ++i) {
            ret.d[i] += num.d[i];
            if (ret.d[i] >= 10) ret.d[i] -= 10, ret.d[i + 1]++;
        }
        if (ret.d[ret.len + 1]) ret.len++;
        return ret;
    }

    Node operator*(const Node& num) const {
        Node ret;
        for (int i = 1; i <= len; ++i)
            for (int j = 1; j <= num.len; ++j)
                ret.d[i + j - 1] += d[i] * num.d[j];
        for (int i = 1; i <= len + num.len; ++i)
            ret.d[i + 1] += ret.d[i] / 10, ret.d[i] %= 10;
        ret.len = len + num.len + 1;
        ret.clear();
        return ret;
    }

    bool operator>(const Node& num) {
        if (num.len != len) return len > num.len;
        for (int i = len; i >= 1; --i)
            if (d[i] != num.d[i]) return d[i] > num.d[i];
        return false;
    }

    void print() { for (int i = len; i >= 1; --i) putnum(d[i]); }
} dp[MAXN][MAXN];

void dfs(int u, int anc) {
    sz[u] = 1; dp[u][1] = 1;
    for (int i = 0; i < G[u].size(); ++i) {
        int v = G[u][i];
        if (v == anc) continue;
        dfs(v, u);

        for (int p = sz[u]; p >= 1; --p)
            for (int q = sz[v]; q >= 0; --q) {
                Node t = dp[u][p] * dp[v][q];
                if (t > dp[u][p+q]) dp[u][p+q] = t;
            }
        sz[u] += sz[v];
    }

    for (int i = 1; i <= sz[u]; ++i) {
        Node t = dp[u][i] * Node(i);
        if (t > dp[u][0]) dp[u][0] = t;
    }
}

int main() {

    n = read();
    for (int i = 1; i < n; ++i) {
        int x = read(), y = read();
        G[x].push_back(y); G[y].push_back(x);
    }

    dfs(1, 0);
    dp[1][0].print();
    
    return 0;
}