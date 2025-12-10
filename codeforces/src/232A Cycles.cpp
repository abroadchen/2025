//
// Created by Psy.C on 2025/12/10.
//
/*
 *
*a[N][N]: 构造的对称矩阵
cnt: 当前处理的行/列号，从1开始
当还有1需要放置时(n>0)：
在第cnt行和第cnt列上放置1
内层循环从i=0开始，每次在位置(i,cnt)和(cnt,i)放置1
每放置i个1就从n中减去i
当i等于cnt时停止（避免在对角线上重复放置）
cnt递增，处理下一行/列
 *
*输出矩阵的大小cnt
输出整个矩阵（未显式初始化的位置默认为0）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

constexpr int N = 110;

signed main() {
    fast;
    int n; cin>>n;
    int a[N][N]={}, cnt = 1;
    while (n > 0) {
        for (int i = 0; i <= n; ++i) {
            if (i == cnt) break;
            a[i][cnt] = 1;
            a[cnt][i] = 1;
            n -= i;
        }
        cnt++;
    }
    cout << cnt << '\n';
    for (int i = 0; i < cnt; ++i) {
        for (int j = 0; j < cnt; ++j) {
            cout << a[i][j];
        }
        cout << '\n';
    }
    return 0;
}