//
// Created by Psy.C on 2026/4/13.
//
/**
n: 输入数字的个数
vis[100]: 标记数组，记录某个数字是否出现过

sum: 计数器，记录处理了多少个数字
now: 当前连续未出现数字的个数
从1到90遍历每个数字：
sum++: 总计数器+1
if (vis[i]) now = 0; else now++:
如果数字i出现过(vis[i] == 1)，重置连续未出现计数器
否则(vis[i] == 0)，连续未出现计数器+1
if (now == 15) break;: 当连续未出现数字达到15个时，停止循环
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, vis[100];
int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x; vis[x] = 1;
    }
    int sum = 0;
    for (int i = 1, now = 0; i <= 90; ++i) {
        sum++;
        if (vis[i]) now = 0; else now++;
        if (now == 15) break;
    }
    cout << sum << '\n';
    return 0;
}