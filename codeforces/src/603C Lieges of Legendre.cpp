//
// Created by Psy.C on 2026/3/21.
//
/**
每个状态都有一个SG值
多个独立游戏的组合：SG总值 = 各子游戏SG值的异或
SG=0表示必败态，SG≠0表示必胜态
每个数的SG值计算：O(log x)（递归深度）
总体：O(n × log(max_value))
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int dfs(int x) {//计算状态x的SG值
    if (x < 5) {
        if (x&1) return 1;
        return x/4*2;
    }
    if (x&1) return 0;//大于等于5的奇数返回0
    if (dfs(x/2) == 1) return 2;
    return 1;
}

int n, k;
int main() {
    fast;
    cin >> n >> k;
    int sg = 0;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        if (k&1) sg ^= dfs(x);//k为奇数时，使用SG函数
        else if (x <= 2) sg ^= x;//k为偶数且x<=2时，SG值为x本身
        else if (~x&1) sg ^= 1;//k为偶数且x为偶数时，SG值为1
    }
    if (sg) cout << "Kevin\n"; else cout << "Nicky\n";
    return 0;
}