//
// Created by Psy.C on 2025/9/19.
//
/*
 *定义二维数组d存储图的邻接矩阵（最短距离）
 *
*计算所有点对之间最短距离的总和
由于矩阵是对称的，实际使用时需要除以2
 *
*读取节点数n
读取n×n的邻接矩阵，表示初始图的边权
 *
*使用Floyd算法计算所有点对间的最短路径
通过中间节点k来更新i到j的最短距离
 *
*读取查询次数t
对每个查询读取边的两个端点x,y和新的边权l
如果当前x到y的最短距离已经小于l，说明新边不会改善最短路径，直接输出当前总和
 *
 *
*更新边(x,y)的权重为l
只需要以x和y作为中间节点运行Floyd算法来更新最短路径
输出更新后的最短路径总和（除以2因为矩阵对称）
 *
*初始Floyd：O(n³)
每次查询：O(n²)
总体：O(n³ + t×n²)
 *
 */
#include <ios>
#include <iostream>
#include <iomanip>
#include <algorithm>
#define rep(i,s,n) for(int i=s;i<n;++i)
using namespace std;
typedef long long ll;
const int N = 3e2+5;
ll d[N][N];


ll get_num(int n) {
    ll sum = 0;
    rep (i, 1, n + 1) rep (j, 1, n + 1) sum += d[i][j];
    return sum;
}


void solve() {
    int n; cin >> n;

    rep (i, 1, n + 1) rep (j, 1, n + 1) cin >> d[i][j];

    rep (k, 1, n + 1) {
        rep (i, 1, n + 1) rep (j, 1, n + 1) {
            d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        }
    }

    int t; cin >> t;
    rep (q, 0, t) {
        int x, y, l; cin >> x >> y >> l;

        if (d[x][y] < l) {
            cout << get_num(n) / 2 << " ";
            continue;
        }
        d[x][y] = d[y][x] = l;

        for (auto k : { x, y }) {
            rep (i, 1, n + 1) rep (j, 1, n + 1) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
        cout << get_num(n) / 2 << " ";
    }
}



int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int test = 1;
    while (test--) {
        solve();
    }
    
    return 0;
}