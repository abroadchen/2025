//
// Created by Psy.C on 2026/3/17.
//
/**
n：数组长度
a[N]：输入数组
flag[N]：标记数组，记录某个位置是否已被访问
cur：当前位置索引
x：移动方向（1表示向右，-1表示向左）
cnt：已收集的不同元素个数
ans：操作次数（反转方向的次数）
tag：是否完成标志

内层循环：
遍历n次，每次移动一步（向左或向右）
cur += x：根据当前方向移动
检查条件：当前位置未被标记 且 a[cur] <= cnt 当前元素的值不大于已收集的元素个数
如果条件满足：
增加已收集元素计数
标记当前位置为已访问
如果已收集全部n个元素，设置完成标志
方向切换：
如果未完成任务，反转方向(x = -x)
增加操作计数(ans++)
继续下一轮扫描

时间复杂度：
最坏情况下可能需要多次往返扫描
O(k×n)，其中k是完成所需的轮数
空间复杂度：
O(n)，主要消耗在flag数组上
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1005;
int n, a[N];
bool flag[N];
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    int cur = 0, x = 1, cnt = 0, ans = 0; bool tag = false;
    while (true) {
        for (int i = 1; i <= n; ++i) {
            cur += x;
            if (!flag[cur] && a[cur] <= cnt) {
                cnt++;
                if (cnt == n) { tag = true; break; }
                flag[cur] = true;
            }
        }
        if (tag) break;
        cur += x; x = -x; ans++;
    }
    cout << ans;
    return 0;
}