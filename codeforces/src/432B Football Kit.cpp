//
// Created by Psy.C on 2026/2/6.
//
/**
 * c[N]记录每个值出现的次数，p[N]存储每个人喜欢的值
 *a表示人的编号
 *
*最大可能关系数：n - 1 + c[p[i]] (自身与其他n-1个人的连接数 + 所有喜欢相同值的人数)
最小可能关系数：n - 1 - c[p[i]] (自身与其他n-1个人的连接数 - 所有喜欢相同值的人数)
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100100
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int c[N]{}, p[N]{};
    for (int i = 0, a; i < n; ++i) {
        cin >> a >> p[i];
        c[a]++;
    }
    for (int i = 0; i < n; ++i)
        cout << n - 1 + c[p[i]] << ' ' << n - 1 - c[p[i]] << '\n';
    return 0;
}