//
// Created by Psy.C on 2026/3/12.
//
/**
n: 节点总数
vis[N]: 标记节点是否已被处理
use[N]: 标记节点是否被使用
a[N]: 存储每个节点的邻接信息（动态）
b[N]: 存储每个节点的原始邻接信息
t: 临时变量，用于位运算
e[N]: 存储边的关系
ans: 存储最终答案（边的配对）

flag: 标记是否所有节点都与其他所有节点相连
读入每个节点的邻接信息
k: 节点i的邻居数量
flag &= k == n: 如果所有节点都与n-1个节点相连（完全图），flag为1
将邻居信息存储到位图中

备份原始邻接信息到b数组
特判: 如果是完全图，将节点1与所有其他节点连接
寻找两个集合中的边
t = a[i] & a[j]: 计算节点i和j的共同邻居
t.count() == 2: 如果恰好有2个共同邻居
遍历找到这两个共同邻居x和y
将x-y作为一条边加入结果
标记x和y为已访问
找到与当前节点i相连且未使用的节点p
选择邻居数最少的节点p
标记p为已使用，更新a[i]为b[p]

特殊情况1: 如果只有一条边
p: 未访问节点
u, v: 已访问的两个节点
根据邻接关系将未访问节点连接到对应集合
一般情况: 处理多个未访问节点
清空未访问节点的相关邻接信息
将未访问节点与已访问节点中邻接信息匹配的节点配对

O(n²) + 位运算优化
总体时间复杂度约为 O(n²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 1005, inf = 1e9;

int n, vis[N], use[N];
bitset<N> a[N], b[N], t, e[N];
vector<ii> ans;
int main() {
    fast;
    cin >> n;
    if (n == 2) return cout << "1 2\n", 0;
    int flag = 1;
    for (int i = 1, k; i <= n; ++i) {
        cin >> k;
        flag &= k == n;
        for (int j = 1, x; j <= k; ++j) {
            cin >> x; a[i][x] = 1;
        }
    }
    for (int i = 1; i <= n; ++i) b[i] = a[i];
    if (flag) {
        for (int i = 2; i <= n; ++i) cout << 1 << ' ' << i << '\n';
        return cout << '\n', 0;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j) {
            t = a[i] & a[j];
            if (t.count() == 2) {
                int x = -1, y = -1;
                for (int pos = 0; pos <= n; ++pos) {
                    if (t[pos]) {
                        if (x == -1) x = pos;
                        else if (y == -1) { y = pos; break; }
                    }
                }
                if (x != -1 && y != -1 && !e[x][y]) {
                    ans.emplace_back(x, y);
                    e[x][y] = e[y][x] = 1;
                    vis[x] = vis[y] = 1;
                }
            }
        }
    for (int i = 1; i <= n; ++i) if (!vis[i]) {
        int mn = inf, p = 0;
        for (int j = 1; j <= n; ++j) if (!use[j] && b[j][i]) {
            int now = b[j].count();
            if (now < mn) mn = now, p = j;
        }
        use[p] = 1, a[i] = b[p];
    }
    if (ans.size() == 1) {
        int p = 0, u = 0, v;
        for (int i = 1; i <= n; ++i) {
            if (!vis[i]) p = i;
            else u ? v = i : u = i;
        }
        for (int i = 1; i <= n; ++i) if (!vis[i]) {
            if (a[p] == a[i]) ans.emplace_back(u, i);
            else ans.emplace_back(v, i);
        }
    } else {
        for (int i = 1; i <= n; ++i) {
            if (!vis[i])
                for (int j = 1; j <= n; ++j) a[j][i] = 0;
            else e[i][i] = 1;
        }
        for (int i = 1; i <= n; ++i) if (!vis[i]) {
            for (int j = 1; j <= n; ++j)
                if (vis[j] && e[j] == a[i])
                    ans.emplace_back(i, j);
        }
    }
    for (auto [fst, snd] : ans)
        cout << fst << ' ' << snd << '\n';
    return 0;
}