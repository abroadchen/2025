//
// Created by Psy.C on 2026/1/19.
//
/*
* 排序：O(m log m)
检查连续三元组：O(m)
总体：O(m log m)
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 3010
using namespace std;


int main() {
    fast;
    int n, m, a[N]; cin >> n >> m;
    for (int i = 1; i <= m; ++i) cin >> a[i];
    sort(a + 1, a + 1 + m);//a[1]到a[m]的范围
    if (a[1] == 1 || a[m] == n) cout << "NO\n"; else {//最小值等于1或最大值等于n 边界元素出现在数组
        int flag = 0;
        for (int i = 1; i <= m - 2; ++i) {
            if (const int j = a[i]; j + 1 == a[i + 1] && j + 2 == a[i + 2]) {//是否存在连续的三个数
                flag = 1;
                break;
            }
        }
        if (flag) cout << "NO\n"; else cout << "YES\n";
    }
    return 0;
}