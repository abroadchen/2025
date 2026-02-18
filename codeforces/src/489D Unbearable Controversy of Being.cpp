//
// Created by Psy.C on 2026/2/18.
//
/**
固定a和c
找到所有满足以下条件的b：
a→b有边
b→c有边
b≠a且b≠c
如果有r个这样的b，那么这些b之间可以形成r*(r-1)/2个三角形

时间复杂度：O(n² + n*m) ≈ O(n² + nm)
空间复杂度：O(n²)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3001;
int n, m;
bool g[N][N];//i到j是否有边
vector<int> v[N];//从i出发的邻居节点
int main() {
    fast;
    cin >> n >> m;
    for (int i = 0, a, b; i < m; ++i) {
        cin >> a >> b;
        g[a][b] = true; v[a].push_back(b);//在邻接矩阵中标记边 在邻接表中添加边
    }
    int ans = 0;
    for (int a = 1; a <= n; ++a)//枚举节点a
        //枚举节点c
        for (int c = 1, r; c <= n; ++c) if (a != c) {
            r = 0;
            for (int b = 0; b < v[a].size(); ++b)//遍历a的所有邻居
                //邻居b不能是a自己 邻居b不能是c  b到c必须有边
                if (v[a][b] != a && v[a][b] != c && g[v[a][b]][c])
                    r++;//满足条件的b的数量
            ans += r*(r-1)/2;//从r个元素中选2个的组合数
        }
    cout << ans << '\n';
    return 0;
}