//
// Created by Psy.C on 2026/9/30.
//

/**
x = n/2（向下取整）。
初始 i=x, j=x+1，此时 i+j = 2x+1 = n（因为 n 为奇数，2*(n/2)+1 = n）。
所以第一对 (n/2, n/2+1) 恰好和等于 n。若它们互质，直接输出（最优解，和正好为 n）。
每次迭代 --i, ++j，i+j 保持 = n 不变，只是中点向左右外扩。找到第一对互质即输出
x = n/2。
偶数时不能取 i=j=n/2（那样 i==j，重复且通常不合 i<j）。于是从 i=x-1, j=x+1 开始，此时 i+j = 2x = n，同样和等于 n。
第一对 (n/2 - 1, n/2 + 1) 也和为 n。若互质则输出；否则 --i, ++j 外扩继续找
 */

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
int gcd(int p, int q) {
    return q == 0 ? p : gcd(q, p % q);
}

int main() {
    fast;
    int n; cin >> n;
    int i, j, x = n/2;
    if (n%2 == 1) {
        for (i = x, j = x+1; i >= 1 && j <= n-1; --i, ++j) {
            if (gcd(i, j) == 1) {
                cout << i << ' ' << j;
                break;
            }
        }
    } else {
        for (i = x-1, j = x+1; i >= 1 && j <= n-1; --i, ++j) {
            if (gcd(i, j) == 1) {
                cout << i << ' ' << j;
                break;
            }
        }
    }
    return 0;
}