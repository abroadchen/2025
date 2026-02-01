//
// Created by Psy.C on 2026/2/1.
//
///时间复杂度：O(n)，单次遍历
///空间复杂度：O(n)，存储方向数组
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 3005
using namespace std;


int main() {
    fast;
    int n, d[N]={}; cin >> n;//方向数组
    char c;
    for (int i = 1; i <= n; ++i) {
        cin >> c;
        if (c == 'L') d[i] = -1;
        if (c == 'R') d[i] = 1;
    }
    int dir = -1, cnt = 0, ans = 0;//当前方向 连续0的数量计数器
    for (int i = 1; i <= n; ++i) {
        if (d[i] == 0) cnt++;//遇到0，增加计数
        else if (d[i] == -1 && dir == 1) ans += cnt % 2;//R→L变化，奇数个0贡献1
        else if (d[i] == 1 && dir == -1) ans += cnt;//L→R变化，所有0都贡献
        if (d[i] != 0) cnt = 0, dir = d[i];//更新方向和计数
    }
    if (dir == -1) ans += cnt;//最后方向是左（-1），将剩余的连续0计入答案
    cout << ans;
    return 0;
}