//
// Created by Psy.C on 2025/9/23.
//
/*
 *
 *将棋盘坐标转换为数组索引：列用字母a-h对应0-7，行用数字1-8对应0-7
 *
 *
 *
 *
 *
 *
 *
 *
 */
#include <ios>
#include <cstdio>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int N = 8;

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    vector<vector<bool> > arr(N, vector<bool>(N, 1));
    string pos1; getline(cin, pos1);//从输入读取两行字符串到变量pos1和pos2中
    string pos2; getline(cin, pos2);

    int row = pos1[1] - '1', col = pos1[0] - 'a';
    for (int i = 0; i < N; ++i) arr[i][col] = 0;// 标记整列
    for (int i = 0; i < N; ++i) arr[row][i] = 0;// 标记整行
    int row2 = pos2[1] - '1', col2 = pos2[0] - 'a';
    arr[row2][col2] = 0;//马所在的位置被占用，标记为不安全

    int r, c;//声明变量用于存储临时的行列索引
    for (int i = 1; i <= 2; ++i) {
        for (int j = 1; j <= 2; ++j) {
            if (i + j != 3) continue;//条件i + j != 3确保只使用组合(1,2)和(2,1)
            r = row2 + i; c = col2 + j;//对于位于(row2, col2)的马，标记所有8个可能的攻击位置
            if (r < N && c < N) arr[r][c] = 0;//不安全(0)
            r = row2 - i; c = col2 + j;
            if (r >= 0 && c < N) arr[r][c] = 0;
            r = row2 + i; c = col2 - j;
            if (r < N && c >= 0) arr[r][c] = 0;
            r = row2 - i; c = col2 - j;
            if (r >= 0 && c >= 0) arr[r][c] = 0;
            r = row + i; c = col + j;//为车的位置标记相同的L形攻击模式
            if (r < N && c < N) arr[r][c] = 0;
            r = row - i; c = col + j;
            if (r >= 0 && c < N) arr[r][c] = 0;
            r = row + i; c = col - j;
            if (r < N && c >= 0) arr[r][c] = 0;
            r = row - i; c = col - j;
            if (r >= 0 && c >= 0) arr[r][c] = 0;
        }
    }


    int ans(0);
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j )
            ans += arr[i][j];
    }
    cout << ans << endl;
    return 0;
}