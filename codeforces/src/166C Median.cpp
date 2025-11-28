//
// Created by Psy.C on 2025/11/28.
//
/*
*n: 数组元素个数
x: 目标值
a[N]: 存储输入数据的数组
ans: 答案计数器
j, k: 两个计数变量
 *标记目标值x是否已经在数组中存在
 *
*如果目标值x不存在于原数组中：
将x添加到数组末尾
数组长度n增加1
答案计数ans增加1（表示需要添加一次操作）
 *
 *将排序后的数组元素依次加入双端队列p的尾部
*当队列q的中位数不等于x且队列大小小于N时循环：
计数器j增加1
在队列前端插入值1
这样会使中位数向右移动，趋向于目标值x
*当队列r的中位数不等于x且队列大小小于N时循环：
计数器k增加1
在队列后端插入值M(100000)
这样会使中位数向左移动，趋向于目标值x
 *输出结果：初始添加操作数ans加上两种策略中较小的操作次数
 */
#include <iostream>
#include <deque>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 2e3, M = 1e5;
int n, x, a[N], ans, j, k;
bool flag = false;

int main() {
    fast;
    cin >> n >> x;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] == x) flag = true;
    }
    if (!flag) { a[n++] = x; ans++; }
    sort(a, a + n);
    deque<int> p, r;
    for (int i = 0; i < n; ++i) p.push_back(a[i]);
    deque<int> q = r = p;
    while (q[(q.size()-1)/2] != x && q.size() < N) { j++; q.push_front(1); }
    while (r[(r.size()-1)/2] != x && r.size() < N) { k++; r.push_back(M); }
    cout << ans + min(j, k) << '\n';
    return 0;
}