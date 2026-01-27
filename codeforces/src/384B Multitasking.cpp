//
// Created by Psy.C on 2026/1/27.
//
/**
* n: 节点总数
m: 边的数量
k: 控制输出顺序的参数
 *
 *从m个元素中选2个的组合数
 *两层循环生成了所有 1 ≤ i < j ≤ m 的数对
 *
*循环生成的边
这个双重循环生成了完全图 K_m 中的所有边：

对于每个 i ∈ [1, m]，j ∈ [i+1, m]
生成边 (i, j)，总共 C(m,2) = m*(m-1)/2 条边
k 参数的作用
当 k = 0 时：输出 (i, j) 形式的边
当 k ≠ 0 时：输出 (j, i) 形式的边
本质上只是改变了边的方向，不影响边的数量
 *
 *O(m²)，需要输出 C(m,2) ≈ m²/2 条边
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, m, k; cin >> n >> m >> k;
    cout << (((m-1)*m)>>1) << '\n';
    for (int i = 1; i <= m; ++i) for (int j = i + 1; j <= m; ++j) {
        if (k == 0) cout << i << ' ' << j << '\n';
        else cout << j << ' ' << i << '\n';
    }
    return 0;
}