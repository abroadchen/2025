//
// Created by Psy.C on 2026/10/8.
//
/**
26 个字母 0..25 作为图的结点。
每个长度 ≥ 2 的字符串，其相邻字符之间连一条有向边：e[c[j]-'a'][c[j+1]-'a'] = true，表示"字符 c[j] 后面必须接 c[j+1]"。
这个模型把"拼出一条合法单词链"转化为：是否存在一条路径，能把这些有向边全部走完且每个结点的入度/出度 ≤ 1（即每个字母做"前驱/后继"最多各一次），从而整条链是一条没有分叉的线
读入 n 个字符串。长度 1 的只标记 d（表示这个小写字母可以单独存在）；长度 ≥2 的把每对相邻字符建成有向边
计算每个字母作为"前驱"(out)和"后继"(in)的次数
若某字母出度或入度 > 1，说明它要同时接多个不同字母，链会分叉 → 无解
对所有"链头"（入度 0、出度 ≥1 的字母）分别从它开始 DFS，尝试把一条链完整走出来。
独立单字母（既无入边也无出边）直接接到结果里
DFS 从链头出发，沿有向边走，把沿途字母依次追加进字符串 s。若走到已访问结点（成环），返回 false → 无解
检查所有"参与建边"的字母都被访问过（即所有链都被走出来且不遗漏），否则无解。全部通过则输出拼接好的字符串
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 35, M = 26;

bool vis[N], e[N][N];
string s;
bool dfs(int x) {
    vis[x] = true;
    s = s + static_cast<char>(x + 'a');
    for (int i = 0; i < M; ++i) {
        if (e[x][i]) {
            if (vis[i]) return false;
            return dfs(i);
        }
    }
    return true;
}

char c[N];
bool d[N];
int n, len, in[N], out[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> c; len = strlen(c);
        if (len == 1) d[c[0]-'a'] = true;
        else {
            for (int j = 0; j < len-1; ++j)
                e[c[j]-'a'][c[j+1]-'a'] = true;
        }
    }
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < M; ++j)
            if (e[i][j]) in[j]++, out[i]++;
    for (int i = 0; i < M; ++i)
        if (in[i] > 1 || out[i] > 1) {
            cout << "NO\n"; return 0;
        }
    s = "";
    for (int i = 0; i < M; ++i) {
        if (in[i] == 0 && out[i]) {
            if (!dfs(i)) { cout << "NO\n"; return 0; }
        }
        if (d[i] && in[i] == 0 && out[i] == 0)
            s = s + static_cast<char>(i + 'a');
    }
    for (int i = 0; i < M; ++i) {
        if (in[i] || out[i]) {
            if (!vis[i]) { cout << "NO\n"; return 0; }
        }
    }
    cout << s << '\n';
    return 0;
}