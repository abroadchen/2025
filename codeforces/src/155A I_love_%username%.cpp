//
// Created by Psy.C on 2025/11/24.
//
/*
 *对于每个新读入的分数
*如果小于当前最小值：更新最小值记录，计数器加1
如果大于当前最大值：更新最大值记录，计数器加1
否则：分数在当前范围内，不更新任何记录
 *
 *
*时间复杂度：O(n)，只需遍历一次
空间复杂度：O(1)，只使用常数额外空间
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int main() {
    fast;
    int n; cin >> n;
    int score; cin >> score; n--;
    int mn = score,  mx = score, cnt = 0;
    while (n--) {
        cin >> score;
        if (score < mn) { mn = score; cnt++; }
        else if (score > mx) { mx = score; cnt++; }
    }
    cout << cnt << '\n';
    return 0;
}