//
// Created by Psy.C on 2026/2/9.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int fa[55];
int find(const int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

bool join(int x, int y) {
    x = find(x); y = find(y);
    if (x != y) { fa[x] = fa[y]; return true; }
    return false;
}

int n, m, x, y;

int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) fa[i] = i;
    int t = n;//连通分量数
    while (m--) {
        cin >> x >> y;//边的两个端点
        if (join(x, y)) t--;
    }
    //n-t是合并操作的次数（也是多余的边数）需要的最少边数才能让图连通（即形成树）
    ///图的生成树的数量
    cout << (1ll<<(n-t)) << '\n';
    return 0;
}