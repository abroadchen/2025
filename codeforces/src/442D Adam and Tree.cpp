//
// Created by Psy.C on 2026/2/8.
//
/**
mx[i][0]最大值，mx[i][1]次大值
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000007
using namespace std;

int n, fa[N], mx[N][2], dp[N];

int main() {
    fast;
    cin >> n;
    //节点1为根的树
    for (int i = 2; i <= n + 1; ++i) cin >> fa[i];
    for (int i = 2; i <= n + 1; ++i) {
        int x = i;// 从当前节点i开始向上更新
        while (true) {
            //到达根节点 或者当前dp值已经不小于更新后的值
            if (x == 1 || dp[x] >= max(mx[x][0], mx[x][1] + 1)) break;
            dp[x] = max(mx[x][0] , mx[x][1] + 1);//更新当前节点的dp值
            if (dp[x] >= mx[fa[x]][0]) {//当前值大于等于父节点最大值
                mx[fa[x]][1] = mx[fa[x]][0];//次大值更新为原最大值
                mx[fa[x]][0] = dp[x];//最大值更新为当前值
            } else if (dp[x] > mx[fa[x]][1]) {//当前值只大于次大值
                mx[fa[x]][1] = dp[x];//只更新次大值
            }
            x = fa[x];// 向上移动到父节点
        }
        cout << mx[1][0] << ' ';//输出根节点的最大值
    }
    cout << '\n';
    return 0;
}