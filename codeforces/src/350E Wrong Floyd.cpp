//
// Created by Psy.C on 2026/1/15.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 3123
using namespace std;

bool vis[N];//标记哪些节点是特殊节点（被访问过）
int get(const int n, const bool flag=false) {
    for (int i = 1; i <= n; ++i) {
        if (flag ? vis[i] : !vis[i]) return i;
    }
    return -1;
}

vector<pair<int, int>> ans;//最终要输出的边（用整数对表示）

//尝试构造m条边，返回是否成功
bool ok(const int n, int m) {
    int st;//获取第一个未访问节点
    if ((st = get(n)) == -1) return false;//找不到未访问节点（返回-1
    int lef = get(n, true);//获取第一个已访问节点（特殊节点）
    m--;//减少一条边的需求
    ans.emplace_back(lef, st);//特殊节点到未访问节点的边
    for (int i = 1; i <= n; ++i) {
        if (i == lef) continue;//跳过特殊节点lef
        for (int j = i + 1; j <= n; ++j) {//遍历所有大于i的节点j
            if (j == lef) continue;//跳过特殊节点j（避免与lef连接）
            if (m > 0) {//如果还需要边(m>0)，就添加边(i,j)并减少m
                m--;
                ans.emplace_back(i, j);
            }
        }
    }
    for (int i = 1; i <= n; ++i) {//连接剩余节点到特殊节点lef
        if (i == lef || i == st) continue;//跳过lef和st节点
        if (m > 0 && !vis[i]) {//还需要边且节点i未被标记，连接i到lef
            m--;
            ans.emplace_back(i, lef);
        }
    }
    return m == 0;//成功构造了所需的边数
}


int main() {
    fast;
    int n, m, k, x; cin >> n >> m >> k;//n(总节点数), m(需要的边数), k(特殊节点数)
    while (k--) { cin >> x; vis[x] = true; }//读入k个特殊节点编号，标记在vis数组中
    if (!ok(n, m)) cout << "-1\n"; else {
        for (auto [fst, snd] : ans) {//遍历ans向量，输出所有边
            cout << fst << ' ' << snd << '\n';
        }
    }
    return 0;
}