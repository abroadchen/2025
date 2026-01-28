//
// Created by Psy.C on 2026/1/28.
//
/**
* 时间复杂度
O(n²) = O(p²)，用于输出邻接矩阵
空间复杂度
O(n²) = O(p²)，用于存储邻接矩阵
 */
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1005
using namespace std;


int main() {
    fast;
    int k; cin >> k;//目标路径数
    if (k == 1) {
        cout << "2\nNY\nYN\n";
        return 0;
    }
    //k-1 的二进制位数 构造图的节点数
    const int p = static_cast<int>(log2(k - 1) + 1), n = 3 * p + 2;
    //r[i][j] = 1 表示存在边 i→j
    int r[N][N], i, x;
    //创建双向边：连接 (1,3), (4,6), (7,9), ..., (3p-2, 3p)
    for (x = 1, i = 1; i <= p + 1; ++i, x += 3)
        r[x][x+2] = r[x+2][x] = 1;
    r[1][4] = r[4][1] = 1;//添加边 1↔4
    //添加边：(3,7), (6,10), (9,13), ..., (3i, 3i+4)
    for (i = 1, x = 3; i <= p; ++i, x += 3)
        r[x][x+4] = r[x+4][x] = 1;
    r[1][5] = r[5][1] = 1;//添加边 1↔5
    //添加边：(5,8), (8,11), ..., (3i+2, 3i+5)
    for (i = 1, x = 5; i <= p - 1; ++i, x += 3)
        r[x][x+3] = r[x+3][x] = 1;
    r[x][2] = r[2][x] = 1;//添加边到终点（节点2）
    //添加长距离边：(3,6), (4,7), ..., (3p, 3p+3)
    for (i = 3; i <= 3 * p; ++i) r[i][i+3] = r[i+3][i] = 1;
    for (i = 0; i < p; ++i) if (1ll<<i&k-1) {//如果第 i 位为1，添加相应的边
        const int x1 = (i+1)*3 + 1, y1 = (i+2)*3+2;
        //根据位置添加边到终点或下一节点
        if (i == p-1) r[x1][2] = r[2][x1] = 1;
        else r[x1][y1] = r[y1][x1] = 1;
    }
    cout << n << '\n';//输出节点数
    for (i = 1; i <= n; ++i) {//输出邻接矩阵（1显示为'Y'，0显示为'N'）
        for (int j = 1; j <= n; ++j) cout << (r[i][j]?"Y":"N");
        cout << '\n';
    }
    return 0;
}