//
// Created by Psy.C on 2026/1/20.
/*时间复杂度
O(n)：只需遍历数组一次
空间复杂度
O(n)：存储输入数组
*/
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    if (n == 1) { cout << 1; return 0; }
    int a[N], ans = 2;//斐波那契序列最少需要2个数
    //cnt = 2：当前连续满足斐波那契条件的长度计数器
    for (int i = 1, cnt = 2; i <= n; ++i) {
        cin >> a[i];
        if (i >= 3) {//从第3个元素开始检查
            if (a[i] == a[i-1] + a[i-2]) cnt++; else cnt = 2;//当前元素和前一个元素组成新的序列
            ans = max(ans, cnt);//更新最大长度
        }
    }
    cout << ans;
    return 0;
}