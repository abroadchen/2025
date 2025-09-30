//
// Created by Psy.C on 2025/9/28.
//
/*
*如果是第一次循环（ans=0）：
将m减少(n-2)
ans增加4
继续下一轮循环
 *
*如果n/2=1（即n=2或n=3），输出"-1"并退出
这表示另一种无解情况
 *
 *
*时间复杂度：O(log(min(m,n))) 类似于欧几里得算法
空间复杂度：O(1)
 *
 *
 */
#include <ios>
#include <iostream>
using namespace std;


int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int m, n; cin>>m>>n;

    if (n == 1) return cout << "-1\n", 0;
    if (n == 2 && m == 3 || m == 5 && n == 3) return cout << "11\n", 0;
    int ans(0);
    while (1) {
        if (n >= 2*m) return cout << ans + 1 << "\n", 0;
        if (n >= m) return cout << ans + 3 + (n==m)*2 << "\n", 0;//(n==m)*2：如果n=m则加2，否则加0
        if (!ans) {
            m -= n - 2;
            ans += 4;
            continue;// 跳过后续所有代码，直接回到while(1)判断
        }
        if (n / 2 == 1) return cout << "-1\n", 0;
        ans += 2;
        m -= n / 2 - 1;
    }

    return 0;
}