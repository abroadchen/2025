//
// Created by Psy.C on 2025/9/18.
//
/*
*adj[maxn]: 正向邻接表，adj[i]存储从节点i指向的节点
rev[maxn]: 反向邻接表，rev[i]存储指向节点i的节点
cmp_pro[maxn]: 存储每个连通分量的信息，first是起点，second是终点
connect_cmp_cnt: 连通分量计数器
visited[maxn]: 访问标记数组
 *
 *
 */
#include <ios>
#include <iostream>
#include <vector>
using namespace std;

const int maxn = 100001;
vector<int> adj[maxn], rev[maxn];
pair<int, int> cmp_pro[maxn];
int connect_cmp_cnt;
bool visited[maxn] = {false};

void dfs(int u) {
    visited[u] = true;
    vector<int>::iterator it;
    for (it = adj[u].begin(); it != adj[u].end(); ++it) {
        int v = *it;
        if (!visited[v]) dfs(v);
        else cmp_pro[connect_cmp_cnt].second = v;
    }
}




int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);
    
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        int to; cin >> to;
        adj[i].push_back(to);
        rev[to].push_back(i);
    }

    //寻找入度为0的节点（没有节点指向它）
    //将其作为连通分量的起点，执行DFS
    for (int i = 1; i <= n; ++i) {
        if ((rev[i].size()) == 0) {
            cmp_pro[connect_cmp_cnt].first = i;
            dfs(i);
            connect_cmp_cnt++;
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            cmp_pro[connect_cmp_cnt].first = i;
            dfs(i);
            connect_cmp_cnt++;
        }
    }
    //如果只有一个连通分量且起点终点相同（即整个图已强连通），输出0
    if (connect_cmp_cnt == 1 && cmp_pro[0].first == cmp_pro[0].second) {
        puts("0");
        return 0;
    }

    //构造环形连接：将每个连通分量的终点连接到下一个连通分量的起点
    //最后一个连通分量的终点连接到第一个连通分量的起点
    vector<pair<int, int> > ans;
    for (int i = 0; i < connect_cmp_cnt - 1; ++i)
        ans.push_back(make_pair(cmp_pro[i].second, cmp_pro[i + 1].first));
    ans.push_back(make_pair(cmp_pro[connect_cmp_cnt - 1].second, cmp_pro[0].first));

    cout << (int)ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i)
        cout << ans[i].first << " " << ans[i].second << endl;
    return 0;
}