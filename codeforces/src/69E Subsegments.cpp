//
// Created by Psy.C on 2025/11/2.
//
/*
*n: 数组长度
k: 滑动窗口大小
i: 循环变量
cnt: 哈希表，用于统计当前窗口中每个数字的出现次数
q: 最大堆优先队列，用于快速获取当前窗口中的最大值
 *
*如果这是该元素第一次出现（计数变为1），将其加入优先队列
emplace是在C++11中引入的方法，比push更高效
 *
*当处理的元素数量超过窗口大小k时，需要移除窗口最左边的元素
a[i-k]是需要移除的元素（窗口滑动）
将该元素的计数减1
如果该元素的计数变为1（说明之前重复但现在不重复了），重新加入优先队列
 *
 *当处理了至少k-1个元素时，窗口已经形成，开始输出结果
*清理优先队列中的无效元素
如果队列顶部元素的计数不是1（即不是唯一元素），则弹出
持续此过程直到找到计数为1的最大元素，或者队列为空
 *
*如果队列不为空，输出队列顶部元素（当前窗口中唯一的最大值）
如果队列为空，说明当前窗口中没有唯一元素，输出"Nothing"
 *
 *
 *时间复杂度约为O(n log n)，空间复杂度为O(n)
 *
 */
#include <iostream>
#include <unordered_map>
#include <queue>
using namespace std;

int n, k, i;
unordered_map<int, int> cnt;
priority_queue<int> q;


void solve() {
    cin >> n >> k;
    int a[n];
    for (i = 0; i < n; ++i) cin >> a[i];
    for (i = 0; i < n; ++i) {
        cnt[a[i]]++;//将当前元素a[i]的计数加1
        if (cnt[a[i]] == 1) q.emplace(a[i]);
        if (i >= k) {
            cnt[a[i - k]]--;
            if (cnt[a[i - k]] == 1) q.emplace(a[i - k]);
        }
        if (i >= k - 1) {
            while (!q.empty() && cnt[q.top()] != 1) q.pop();
            if (!q.empty()) cout << q.top() << "\n";
            else cout << "Nothing\n";
        }
    }
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    solve();
    return 0;
}