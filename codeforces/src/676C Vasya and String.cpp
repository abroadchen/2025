//
// Created by Psy.C on 2026/4/13.
//
/**
n: 字符串长度
k: 最多可以改变的字符数
st: 当前窗口的起始位置
ans: 最长满足条件的子串长度
s: 输入字符串
q: 双端队列，存储需要改变的字符位置

第一次处理（将'b'变成'a'）
遍历字符串每个位置i：
if (s[i] == 'b') q.push_back(i): 如果是'b'，将其位置加入队列
if (q.size() > k): 如果需要改变的字符数超过k：
st = q.front() + 1: 更新窗口起点为最早需要改变的字符的下一个位置
q.pop_front(): 移除最早的位置
ans = max(ans, i - st + 1): 更新最长子串长度
这个过程维护了一个滑动窗口，窗口内最多包含k个'b'字符。

第二次处理（将'a'变成'b'）
清空队列，重置起始位置
遍历字符串每个位置i：
if (s[i] == 'a') q.push_back(i): 如果是'a'，将其位置加入队列
if (q.size() > k): 如果需要改变的字符数超过k：
st = q.front() + 1: 更新窗口起点
q.pop_front(): 移除最早的位置
ans = max(ans, i - st + 1): 更新最长子串长度
这次是维护一个最多包含k个'a'字符的窗口

时间复杂度O(n)，空间复杂度O(k)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, k, st, ans;
string s;
deque<int> q;
int main() {
    fast;
    cin >> n >> k;
    cin >> s;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'b') q.push_back(i);
        if (q.size() > k) {
            st = q.front() + 1;
            q.pop_front();
        }
        ans = max(ans, i - st + 1);
    }
    q.clear(); st = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'a') q.push_back(i);
        if (q.size() > k) {
            st = q.front() + 1;
            q.pop_front();
        }
        ans = max(ans, i - st + 1);
    }
    cout << ans << '\n';
    return 0;
}