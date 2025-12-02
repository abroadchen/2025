//
// Created by Psy.C on 2025/12/2.
//

#include <iostream>
#include <cstring>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1010
using namespace std;

struct node { int i, d; } a[N];
int flag[N];

int main() {
    fast;
    int n;
    while (cin >> n) {
        memset(flag, 1, sizeof(flag));
        flag[1] = 0; flag[n] = 0;//不可用
        for (int i = 1; i <= n; ++i) {
            cin >> a[i].d;
            a[i].i = i;
        }
        sort(a + 1, a + n + 1, [](const node a, const node b) {
            if (a.d != b.d) return a.d < b.d;
            return a.i < b.i;
        });
        int res = 0;
        for (int i = 1; i <= n; ++i) {//遍历排序后的数组
            //如果当前位置已被标记为不可用，则记录当前值作为结果并跳出循环
            if (flag[a[i].i] == 0) { res = a[i].d; break; }
            flag[a[i].i] = 0;//当前位置及其左右相邻位置为不可用
            flag[a[i].i - 1] = 0;
            flag[a[i].i + 1] = 0;
        }
        cout << res << '\n';
    }
    return 0;
}