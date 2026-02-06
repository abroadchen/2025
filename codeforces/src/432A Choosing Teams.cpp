//
// Created by Psy.C on 2026/2/6.
//
/**
 * n表示学生总数，k表示额外加分
 *将每个学生原始成绩w加上加分k后存储到数组a中
 *
*如果某个学生的最终成绩≤5，则计数器sum加1
当sum达到3时(即找到了3个成绩≤5的学生组成一个队伍)，清零sum并使队伍数ans加1
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100000
using namespace std;


int main() {
    fast;
    int n, k, a[N]{}, ans = 0; cin >> n >> k;
    for (int i = 0, w; i < n; ++i) {
        cin >> w;
        a[i] = w + k;
    }
    for (int i = 0, sum = 0; i < n; ++i) {
        if (a[i] <= 5) sum++;
        if (sum == 3) {
            sum = 0;
            ans++;
        }
    }
    cout << ans << '\n';
    return 0;
}