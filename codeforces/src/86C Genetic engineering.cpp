//
// Created by Psy.C on 2025/11/7.
//
/*
 *n表示字符串长度，m表示禁止模式的数量
 *将字符'A','T','C','G'映射为数字0,1,2,3
 *nx[4]: 四个子节点指针，对应A,T,C,G四个字符
 *fail: 失配指针
 *val: 节点值，表示以此节点结尾的模式长度
 *t[207]: 节点数组
 *root: 根节点编号
 *tot: 当前节点总数
 *maxl: 最长禁止模式的长度
 *
*void insert(char *s): 将字符串s插入AC自动机：
计算字符串长度len
更新最大长度maxl
从根节点开始，逐字符构建Trie树路径
如果子节点不存在则创建新节点
在终点节点设置val为模式长度
 *
*void getfail(): 构建失配指针：
初始化根节点的子节点指向根节点自身
使用BFS遍历所有节点
对每个节点u和字符i：
如果子节点v不存在，则指向fail节点的对应子节点
如果子节点v存在，则设置v的fail指针
更新v的val值为当前值和通过fail指针到达节点值的最大值
 *
 *
 *设置初始状态：长度为0，在根节点，连续长度为0的状态方案数为1
*三重循环进行状态转移：
i: 当前字符串长度
j: 当前所在的AC自动机节点
k: 当前连续不包含禁止串的长度
l: 下一个字符(0-3对应A,T,C,G)
状态转移：从(i,j,k)转移到(i+1,v,new_k)
如果到达的节点v包含禁止串(t[v].val > k)，则重置连续长度为0
否则连续长度加1
 *
 */
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int mod = 1000000009;
int n, m;
char s[15];//临时存储输入的禁止模式字符串

int get(char c) { return c == 'A' ? 0 : c == 'T' ? 1 : c == 'C' ? 2 : 3; }
void add(int& a, int b) { a += b; if (a >= mod) a -= mod; }

struct AC {
    struct node {
        int nx[4], fail, val;
        void init() { memset(nx, -1, sizeof(nx)); fail = val = 0; }
    } t[207];
    int root, tot, maxl, dp[1007][207][15];
    int newnode() { t[++tot].init(); return tot; }//创建新节点并初始化，返回节点编号
    void init() { tot = 0; maxl = 0; root = newnode(); }// 初始化AC自动机，重置计数器，创建根节点
    void insert(char *s) {
        int len = strlen(s);
        maxl = max(maxl, len);
        int cur = root;
        for (int i = 0; i < len; ++i) {
            int v = get(s[i]);
            if (t[cur].nx[v] == -1) t[cur].nx[v] = newnode();
            cur = t[cur].nx[v];
        }
        t[cur].val = len;
    }

    void getfail() {
        for (int i = 0; i < 4; ++i) t[0].nx[i] = 1;
        queue<int> q; q.push(1); t[1].fail = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int i = 0; i < 4; ++i) {
                int v = t[u].nx[i], f = t[u].fail;
                if (v == -1) { t[u].nx[i] = t[f].nx[i]; continue; }
                t[v].fail = t[f].nx[i];
                t[v].val = max(t[v].val, t[t[v].fail].val);
                q.push(v);
            }
        }
    }

    void dfs() {
        memset(dp, 0, sizeof(dp));
        dp[0][1][0] = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 1; j <= tot; ++j) {
                for (int k = 0; k < maxl; ++k) {
                    for (int l = 0; l < 4; ++l) {
                        int v = t[j].nx[l];
                        if (v == -1) continue;
                        add(dp[i + 1][v][t[v].val > k ? 0 : k + 1],
                            dp[i][j][k]);
                    }
                }
            }
        }
        int ans(0);
        for (int j = 1; j <= tot; ++j) add(ans, dp[n][j][0]);
        printf("%d\n", ans);
    }
} acam;


int main() {
    scanf("%d %d", &n, &m);
    acam.init();
    for (int i = 1; i <= m; ++i) { scanf("%s", s); acam.insert(s); }
    acam.getfail();
    acam.dfs();
    return 0;
}