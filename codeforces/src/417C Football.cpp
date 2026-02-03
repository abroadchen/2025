//
// Created by Psy.C on 2026/2/3.
//
/**
* 时间复杂度：O(n*k)
空间复杂度：O(1)（只输出边，不存储）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k; cin >> n >> k;
    if (n <= k<<1) cout << "-1\n";//节点数不够时，无法构造满足条件的图
    else {
        cout << n*k << '\n';//n*k 条边
        for (int i = 1, x; i <= n; ++i) {//遍历每个节点
            x = 0;//当前节点i连接的边数
            for (int j = i + 1; j <= n<<1; ++j) {
                x++;
                //构造边：i 与 (j%n == 0 ? n : j%n) 连接
                cout << i << ' ' << (j%n == 0 ? n : j%n) << '\n';//将 j 映射到 1~n 的范围内
                if (x == k) break;//每个节点最多连接 k 条边
            }
        }
    }
    return 0;
}