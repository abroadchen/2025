//
// Created by Psy.C on 2025/12/23.
//

#include <iostream>
#include <vector>
#include <queue>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200003
#define ii pair<int, int>
using namespace std;


int main() {
    fast;
    int n, m, deg[N]; cin >> n >> m;
    int pre = m + 1;//跟踪当前使用的节点编号
    ii a[N];//存储值和索引的对 原始列号（从1开始）
    vector<int> e[N];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) { cin >> a[j].first; a[j].second = j + 1;}
        sort(a, a + m);
        int cnt = pre;
        for (int j = 0; j < m;) {//遍历排序后的数组
            if (a[j].first == -1) { j++; continue; }//值为-1，跳过该元素
            int k = j;//开始处理相同值的连续区间
            while (a[k].first == a[j].first) {//相同值的连续区间
                e[a[k].second].push_back(cnt);//在图中添加边：从原始列号到虚拟节点
                deg[cnt]++;//更新虚拟节点的入度
                if (cnt > pre) {//如果不是第一个虚拟节点，添加反向边
                    e[cnt - 1].push_back(a[k].second);
                    deg[a[k].second]++;//更新原始列号的入度
                }
                k++;//移动到下一个元素
            }
            cnt++;//为下一个值组准备新编号
            j = k;//将j更新为k的位置，跳过已处理的相同值区间 准备处理下一个不同的值
        }
        pre = cnt;//下一行的虚拟节点编号起始点
    }
    queue<int> q; bool used[N]; int ans[N];
    for (int i = 1; i <= m; ++i) if (deg[i] == 0) q.push(i);
    int len = 0;
    while (!q.empty() && len < m) {//拓扑排序主循环，直到队列为空或找到m个元素
        const int u = q.front(); q.pop();
        used[u] = true;
        if (u <= m) ans[len++] = u;//如果是原始列节点，加入结果数组
        for (int v : e[u]) {
            if (!used[v]) {
                deg[v]--;
                if (deg[v] == 0) q.push(v);
            }
        }
    }
    if (len < m) cout << "-1\n";//没有找到m个元素
    else {//否则输出拓扑排序结果
        for (int i = 0; i < len; ++i) cout << ans[i] << (i==len-1 ? '\n' : ' ');
    }
    return 0;
}