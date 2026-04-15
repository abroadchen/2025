//
// Created by Psy.C on 2026/4/15.
//
/**
s[15]: 临时字符串，存储操作命令
t[30]: 临时字符串，用于格式化输出
v: 存储操作序列的向量
n: 操作数量
q: 最小堆（优先队列），实现multiset功能

s[0] == 'i': 判断是否为insert操作
sprintf(t, "insert %d", x): 格式化字符串
v.emplace_back(t): 添加操作记录
q.push(x): 将元素插入堆中
s[0] == 'r': 判断是否为remove操作
if (q.empty()): 如果堆为空，先插入一个元素
v.emplace_back("removeMin"): 添加删除操作记录
q.pop(): 从堆中删除最小元素

获取最小值操作
读入目标值x
循环直到堆顶等于x：
q.empty() || q.top() > x: 如果堆为空或堆顶>x，插入x
q.top() == x: 如果堆顶等于x，退出循环
else: 如果堆顶<x，删除堆顶
添加"getMin x"操作记录

输出操作序列长度
输出每个操作
时间复杂度：O(n log n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

char s[15], t[30];
vector<string> v;
int n;
priority_queue<int, vector<int>, greater<>> q;
int main() {
    fast;
    cin >> n;
    for (int i = 0, x; i < n; ++i) {
        cin >> s;
        if (s[0] == 'i') {
            cin >> x;
            sprintf(t, "insert %d", x);
            v.emplace_back(t);
            q.push(x);
        } else if (s[0] == 'r') {
            if (q.empty()) {
                v.emplace_back("insert 1");
                q.push(1);
            }
            v.emplace_back("removeMin");
            q.pop();
        } else {
            cin >> x;
            while (true) {
                if (q.empty() || q.top() > x) {
                    q.push(x);
                    sprintf(t, "insert %d", x);
                    v.emplace_back(t);
                } else if (q.top() == x) break;
                else {
                    v.emplace_back("removeMin");
                    q.pop();
                }
            }
            sprintf(t, "getMin %d", x);
            v.emplace_back(t);
        }
    }
    cout << v.size() << '\n';
    for (const auto& i : v) cout << i << '\n';
    return 0;
}