//
// Created by Psy.C on 2025/12/13.
//
/*
 *人数n和高度差h
*x：个人的身高
id：原始编号（用于最后恢复顺序）
val：策略选择（0表示策略2，1表示策略1）
 *
*对于n≥3的情况，比较两种策略的优劣：
策略A：第1个人选择策略1（增加h），其他人选择策略2
最大值：max(a[n].x + a[n-1].x, a[1].x + a[n].x + h)
最小值：min(a[1].x + a[2].x + h, a[2].x + a[3].x)
差值：最大值 - 最小值
策略B：所有人都选择策略2
差值：a[n].x + a[n-1].x - a[1].x - a[2].x
如果策略A更优（差值更小），则设置第1个人选择策略1
 *
 *输出两种策略中的最优结果（较小的差值）
 *按原始编号重新排序，恢复输入顺序
*a[i].val == 0 输出2（策略2）
a[i].val == 1 输出1（策略1）
" \n"[i==n] 巧妙地处理输出格式：如果不是最后一个元素输出空格，否则输出换行
 *
 *
*全部选择策略2：
最大和：a[n] + a[n-1]
最小和：a[1] + a[2]
差值：(a[n] + a[n-1]) - (a[1] + a[2])
第1个人选择策略1，其余选择策略2：
可能的最大和：max(a[n] + a[n-1], a[1]+h + a[n])
可能的最小和：min(a[1]+h + a[2], a[2] + a[3])
差值：最大和 - 最小和
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100010
using namespace std;


int main() {
    fast;
    int n, h; cin >> n >> h;
    struct node { int x, id, val; } a[N];
    for (int i = 1; i <= n; ++i) cin >> a[i].x, a[i].id = i, a[i].val = 0;
    sort(a + 1, a + n + 1, [](const node& o1, const node& o2) {
        return o1.x < o2.x;//按身高升序排序数组（从索引1到n）
    });
    if (n == 2) cout << "0\n1 1\n";//如果只有2个人，最大差值总是0，两人都选择策略1
    else {
        if (max(a[n].x + a[n-1].x, a[1].x + a[n].x + h) -
            min(a[1].x + a[2].x + h, a[2].x + a[3].x) <
            a[n].x + a[n-1].x - a[1].x - a[2].x) a[1].val = 1;
        cout << min(max(a[n].x + a[n-1].x, a[1].x + a[n].x + h) -
            min(a[1].x + a[2].x + h, a[2].x + a[3].x),
            a[n].x + a[n-1].x - a[1].x - a[2].x) << '\n';
        sort(a + 1, a + n + 1, [](const node& o1, const node& o2) {
            return o1.id < o2.id;
        });
        for (int i = 1; i <= n; ++i) cout << (a[i].val == 0 ? 2 : 1) <<
            " \n"[i==n];
    }
    return 0;
}