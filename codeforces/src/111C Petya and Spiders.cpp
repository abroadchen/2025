//
// Created by Psy.C on 2025/11/14.
//
/*
*n*m - (n*m + 4)/4
这表示总体上每4个位置中有1个被排除
*当n=4且m=4时，补偿+1
当n=4且m=7时，补偿+1
当n=4且m=8时，补偿+1
当n=4且m=10时，补偿+1
 *
n=1的情况：
1×m的条形区域
每3个连续格子可以放一个1×3的骨牌
所以需要排除(m+2)/3个位置
n≥2的情况：
一般情况下，每4个格子中有1个不能被有效利用
但对于某些特定尺寸（4×4, 4×7, 4×8, 4×10），可以比预期多放一些骨牌*
 *
 */
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m; cin >> n >> m;
    if (n > m) swap(n, m);
    if (n == 1) cout << n * m - ((m + 2) / 3);//每3个连续位置中有1个被排除
    else {
        cout << n * m - (n * m + 4) / 4 +
            (n == 4 && m == 4) + (n == 4 && m == 7) +
                (n == 4 && m == 8) + (n == 4 && m == 10);
    }
    return 0;
}