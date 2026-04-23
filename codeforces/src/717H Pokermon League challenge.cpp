//
// Created by Psy.C on 2026/4/22.
//
/**
N：最大顶点数
M：最大颜色数
bel[N]：每个顶点所属的颜色
c[M]：每种颜色的二进制值（0或1）
n：顶点数量
t[N][25]：每个顶点可选择的颜色列表
T：最大颜色编号
e：边的数量

对每个顶点i，从其可用颜色列表中随机选择一个颜色
t[i][0]：顶点i的可用颜色数量
rand()%t[i][0]+1：随机选择1到t[i][0]之间的索引
为每种颜色分配一个随机二进制值（0或1）
rand()&1：生成0或1
统计两端颜色不同的边的数量
c[bel[a[i].first]]：边的第一个端点的二进制颜色值
c[bel[a[i].second]]：边的第二个端点的二进制颜色值
如果两者不相等，res增加1
检查满足条件的边数是否至少为总边数的一半
res*2 >= e 等价于 res >= e/2

使用固定字符串的ASCII值之和作为随机种子
保证每次运行结果的一致性（如果需要可重现结果）
读入顶点数n和边数e
读入所有边
读入每个顶点的可用颜色列表，并更新最大颜色编号T
不断尝试随机方案直到找到满足条件的解
由于随机算法的期望性能，这个循环通常会很快结束
输出每个顶点分配的具体颜色
输出每种颜色的最终二进制值（注意输出时加1，变为1或2）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+7, M = 1e6+7;
int bel[N], c[M], n, t[N][25], T, e;
pair<int, int> a[N];//存储边的信息，每条边连接两个顶点
bool get() {
    for (int i = 1; i <= n; ++i)
        bel[i] = t[i][rand()%t[i][0]+1];
    for (int i = 1; i <= T; ++i) c[i] = rand()&1;
    int res = 0;
    for (int i = 1; i <= e; ++i)
        res += c[bel[a[i].first]] != c[bel[a[i].second]];
    return res*2 >= e;
}

int main() {
    fast;
    srand('S' + 'J' + 'Y' + ' ' + 'A' + 'K' + ' ' + 'I' + 'O' + 'I');
    cin >> n >> e;
    for (int i = 1; i <= e; ++i) cin >> a[i].first >> a[i].second;
    for (int i = 1; i <= n; ++i) {
        cin >> t[i][0];
        for (int j = 1; j <= t[i][0]; ++j)
            cin >> t[i][j], T = max(T, t[i][j]);
    }
    while (!get()) {}
    for (int i = 1; i <= n; ++i) cout << bel[i] << ' ';
    cout << '\n';
    for (int i = 1; i <= T; ++i) cout << c[i]+1 << ' ';
    return 0;
}