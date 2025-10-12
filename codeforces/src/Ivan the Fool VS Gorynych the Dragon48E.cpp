//
// Created by Psy.C on 2025/10/12.
//
/*
*N = 205：最大尺寸约束
h, t, r：初始头数、尾数，以及最大生物总数（h+t ≤ r）
n, m：伊凡和兹梅伊的法术数量
h1[N], t1[N]：伊凡的法术效果（将1个头转换为h1[i]个头和t1[i]个尾）
h2[N], t2[N]：兹梅伊的法术效果（将1个尾转换为h2[i]个头和t2[i]个尾）
ct：唯一状态ID的计数器
sl：特殊"失败"状态ID
id[N][N]：二维数组，将(头数,尾数)状态映射到唯一ID
sw：胜利状态ID（0头，0尾）
vis[N*N]：图遍历中的访问数组
ind[N*N]：拓扑排序的入度数组
g[N*N], sg[N*N]：图的邻接表（正向和反向）
q：BFS遍历的队列
 *
*执行BFS以找到从初始状态到胜利状态(0,0)的最短路径：

初始化访问数组并将起始状态(h,t)以距离0加入队列
当队列不为空时：
取出队首元素并删除
如果到达胜利状态(0,0)，返回距离
如果已访问过，跳过
标记为已访问
将所有邻居以增加的距离加入队列
如果未找到路径返回-1
 *
*执行反向拓扑排序以确定兹梅伊是否能强制获胜：

重置访问数组并清空队列
构建反向图(sg)并计算入度
从失败状态开始反向工作
如果能达到初始状态，说明兹梅伊能强制获胜
使用拓扑排序找到DAG中的最长路径
 *
 *
*读取初始头数(h)、尾数(t)和最大生物数(r)
读取伊凡的法术(n个法术，每个将1个头转换为h1[i]个头和t1[i]个尾)
读取兹梅伊的法术(m个法术，每个将1个尾转换为h2[i]个头和t2[i]个尾)
*sl：为特殊失败状态分配ID（当总生物数>r时）
对于所有有效的(头数,尾数)组合，其中头数+尾数≤r，分配唯一ID
sw：胜利状态(0头,0尾)的ID
 *
*图构建：

对于每个有效状态(i个头，j个尾)：
对于伊凡的每个法术(k=1到min(n,i))：
应用法术k：移除1个头，添加h1[k]个头和t1[k]个尾
如果总生物数超过r，转移到失败状态
否则转移到新状态
对于兹梅伊的每个法术(k=1到min(m,j))：
应用法术k：移除1个尾，添加h2[k]个头和t2[k]个尾
如果总生物数超过r，转移到失败状态
否则转移到新状态
 *
 *
 */
#include <algorithm>
#include <ios>
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
typedef pair<int, int> pii;

const int N = 205;
int h, t, r, n, m, h1[N], t1[N], h2[N], t2[N], ct, sl, id[N][N], sw, vis[N*N], ind[N*N];
vector<int> g[N*N], sg[N*N];
queue<pii> q;

int bfs() {
    memset(vis, 0, sizeof(vis));
    q.push(make_pair(id[h][t], 0));
    while (!q.empty()) {
        pii x = q.front(); q.pop();
        if (x.first == sw) return x.second;
        if (vis[x.first]) continue;
        vis[x.first] = 1;
        for (auto y : g[x.first]) q.push(make_pair(y, x.second + 1));
    }
    return -1;
}

int hs() {
    memset(vis, 0, sizeof(vis));
    while (!q.empty()) q.pop();
    for (int i = 1; i <= ct; ++i) {
        for (auto y : g[i]) {
            sg[y].push_back(i);
            ind[i]++;
        }
    }
    q.push(make_pair(sl, 0));
    while (!q.empty()) {
        pii x = q.front(); q.pop();
        if (x.first == id[h][t]) return x.second;
        for (auto y : sg[x.first]) {
            ind[y]--;
            if (!ind[y]) q.push(make_pair(y, x.second + 1));
        }
    }
    return -1;
}


void solve() {
    cin >> h >> t >> r;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> h1[i] >> t1[i];
    cin >> m;
    for (int i = 1; i <= m; ++i) cin >> h2[i] >> t2[i];
    sl = ++ct;
    for (int i = 0; i <= r; ++i) for (int j = 0; j <= r - i; ++j) id[i][j] = ++ct;
    sw = id[0][0];
    for (int i = 0; i <= r; ++i) {
        for (int j = 0; j <= r - i; ++j) {
            for (int k = 1; k <= min(n, i); ++k) {
                if (i - k + h1[k] + j + t1[k] > r) {
                    g[id[i][j]].push_back(sl);
                    vis[id[i][j]] = 1;
                } else {
                    g[id[i][j]].push_back(id[i - k + h1[k]][j + t1[k]]);
                }
            }
            for (int k = 1; k <= min(m, j); ++k) {
                if (i + h2[k] + j - k + t2[k] > r) {
                    if (!vis[id[i][j]]) g[id[i][j]].push_back(sl);
                } else {
                    g[id[i][j]].push_back(id[i + h2[k]][j - k + t2[k]]);
                }
            }
        }
    }

    int ta = bfs();
    if (ta != -1) {
        cout << "Ivan" << endl;
        cout << ta << endl;
        return;
    }
    ta = hs();
    if (ta != -1) {
        cout << "Zmey" << endl;
        cout << ta << endl;
    } else cout << "Draw" << endl;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    solve();

    return 0;
}