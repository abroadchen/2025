//
// Created by Psy.C on 2026/10/8.
//
/**
n 是组数（本题题意是 3），每组 6 个数。
mp[i][x]=1 记录第 i 组包含数字 x
逐个数 v，看能否用各组的数字拼出
一位数 v（1-9）
只要三组中任一组单独含有数字 v，就算可拼（continue 表示"能拼出，继续下一个 v"）
两位数 v（10-99）
两位数需要两组拼：一组提供十位 a，另一组提供个位 b。枚举哪两组配合，顺序可交换（正序/反序），只要有一种组合成立即可 continue（可拼）
三位数 v（100-999）
三位数需要三组各出一个数字（百/十/个位），枚举三组在三个位上的所有排列（
3
!
=
6
3!=6 种），任一种成立即可拼
一旦某个 v 走完所有分支都没 continue（即不可拼），就输出 v-1 并退出——也就是"能拼出的最大连续整数"
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

map<int, bool> mp[5];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1, x; j <= 6; ++j) {
            cin >> x; mp[i][x] = 1;
        }
    }
    for (int v = 1; v <= pow(10, n)-1; ++v) {
        if (v <= 9) {
            if (mp[1][v] || mp[2][v] || mp[3][v]) continue;
        } else if (v <= 99) {
            int a = v/10, b = v%10;
            if ((mp[1][a] && mp[2][b]) || (mp[1][a] && mp[3][b]) || (mp[2][a] && mp[3][b])) continue;
            if ((mp[1][b] && mp[2][a]) || (mp[1][b] && mp[3][a]) || (mp[2][b] && mp[3][a])) continue;
            int i = v/100, j = v/10%10, k = v%10;
            if ((mp[1][i] && mp[2][j] && mp[3][k]) || (mp[1][i] && mp[3][j] && mp[2][k])) continue;
            if ((mp[2][i] && mp[1][j] && mp[3][k]) || (mp[2][i] && mp[3][j] && mp[1][k])) continue;
            if ((mp[3][i] && mp[1][j] && mp[2][k]) || (mp[3][i] && mp[2][j] && mp[1][k])) continue;
        }
        cout << v-1;
        break;
    }
    return 0;
}