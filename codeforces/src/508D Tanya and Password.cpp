//
// Created by Psy.C on 2026/2/26.
//
/**
to：到达的节点
nxt：下一条边的索引
tot：边的计数器
head[N]：每个节点的第一条边索引
cnt：答案字符计数器
ans[N]：存储结果字符串

欧拉路径DFS函数：
从节点s开始深度优先搜索
删除已访问的边
将边的字符加入答案数组

n：字符串数量
od[N]：出度数组
id[N]：入度数组
s[10]：临时字符数组
str[10000]：存储所有出现的2字符子串
mp：字符串到节点编号的映射

每个3字符字符串拆分为两个2字符子串
将子串映射为节点编号
添加从第一个子串到第二个子串的边
统计出入度

c1：出度比入度多1的节点数
c2：入度比出度多1的节点数
st：起始节点（出度比入度多1的节点）
要么所有节点出入度相等（欧拉回路）
要么恰好有一个节点出度比入度多1，一个节点入度比出度多1（欧拉路径）

如果访问的边数不等于n，说明不连通
先输出起始节点的前两个字符
再逆序输出DFS得到的字符序列
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+1;
struct node { int to, nxt; } e[N];

int tot, head[N];
char val[N];//存储每条边对应的字符
void add(const int a, const int b, const char v) {
    e[tot].to = b; val[tot] = v; e[tot].nxt = head[a]; head[a] = tot++;
}

int cnt;
char ans[N];
void dfs(const int s) {
    while (~head[s]) {
        const int i = head[s];
        head[s] = e[i].nxt;
        dfs(e[i].to);
        ans[cnt++] = val[i];
    }
}

int n, od[N], id[N];
char s[10];
string str[10000];
map<string, int> mp;

void init() {
    memset(head, -1, sizeof(head));
    memset(id, 0, sizeof(id));
    memset(od, 0, sizeof(od));
    tot = 0; cnt = 0;
}

int main() {
    fast;
    cin >> n; init();
    for (int i = 1; i <= n; ++i) {
        cin >> s;
        string t1, t2;
        t1 += s[0]; t1 += s[1]; t2 += s[1]; t2 += s[2];
        if (!mp[t1]) {
            mp[t1] = ++cnt;
            str[cnt] = t1;
        }
        if (!mp[t2]) {
            mp[t2] = ++cnt;
            str[cnt] = t2;
        }
        add(mp[t1], mp[t2], s[2]);
        od[mp[t1]]++, id[mp[t2]]++;
    }
    int st = 1, c1 = 0, c2 = 0;
    for (int i = 1; i <= cnt; ++i) {
        if (od[i] - id[i] == 1) c1++, st = i;
        else if (od[i] - id[i] == -1) c2++;
        else if (od[i] - id[i]) c1 = 3;
    }
    if (!((c1 == 0 && c2 == 0) || (c1 == 1 && c2 == 1)))
        cout << "NO\n";
    else {
        cnt = 0; dfs(st);
        if (cnt != n) cout << "NO\n";
        else {
            cout << "YES\n";
            cout << str[st][0] << str[st][1];
            for (int i = cnt-1; i >= 0; --i)
                cout << ans[i];
            cout << '\n';
        }
    }
    return 0;
}