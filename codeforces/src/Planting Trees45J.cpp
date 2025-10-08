//
// Created by Psy.C on 2025/9/30.
//
/*
*按照(i+j)的奇偶性来决定填入的数字
奇数位置填入从1开始递增的数字
偶数位置填入从(n×m/2)+1开始递增的数字
形成一种棋盘状的分布模式
 *
 */
#include <ios>
#include <iostream>
using namespace std;



void solve() {
    int n, m; cin >> n >> m;
    if (n * m == 1) cout << 1 << '\n';//如果矩阵只有一个元素(1×1)，直接输出1并换行
    else if (n + m < 5) cout << -1 << '\n';
    else {
        int cnt(0), tot(n*m/2);//矩阵元素总数的一半
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((i + j) % 2 == 0) cout << ++tot;
                else cout << ++cnt;
                cout << " \n"[j==m-1];
            }
        }
    }
}


int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    solve();
    return 0;
}