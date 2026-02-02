//
// Created by Psy.C on 2026/2/2.
//
/**
* n：字符串长度
k：起始位置（1-indexed）
s：输入字符串（0-indexed）
 *
*如果起始位置靠近左边
k：到左边界的距离
n-k：到右边界的距离
 *
*. 贪心策略
选择较短路径到字符串的任一端
避免不必要的往返移动
2. 双向遍历
左优先：从左端开始，向右遍历
右优先：从右端开始，向左遍历
3. 最优性保证
总移动步数 = min(k-1, n-k) + (n-1)
         = 达到端点的最短距离 + 遍历整个字符串的距离

 *
*时间复杂度：O(n)
空间复杂度：O(1)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, k; char s[105]; cin >> n >> k >> s;
    if (k <= n - k) {
        for (int i = 1; i < k; ++i) cout << "LEFT\n";
        cout << "PRINT " << s[0] << '\n';
        for (int i = 1; i < n; ++i) {
            cout << "RIGHT\n";
            cout << "PRINT " << s[i] << '\n';
        }
    } else {
        for (int i = 0; i < n - k; ++i) cout << "RIGHT\n";
        cout << "PRINT " << s[n-1] << '\n';
        for (int i = n - 2; i >= 0; --i) {
            cout << "LEFT\n";
            cout << "PRINT " << s[i] << '\n';
        }
    }
    return 0;
}