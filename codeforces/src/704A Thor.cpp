//
// Created by Psy.C on 2026/4/18.
//
/**
n: 某个范围参数（代码中未实际使用）
q: 操作次数
qe[N]: N个队列，qe[i]存储发送到第i个频道的消息ID
qt: 总队列，存储{消息ID, 频道ID}对
vis[N]: 标记数组，标记消息是否已被处理
op: 操作类型
num: 操作参数
ant = 1: 消息ID计数器（从1开始）
ans = 0: 当前未处理消息总数

ans++: 未处理消息数加1
qe[num].push(ant): 将消息ID添加到第num个频道的队列
qt.emplace(ant, num): 将{消息ID, 频道}添加到总队列
ant++: 消息ID递增
清空第num个频道的所有消息
vis[qe[num].front()] = true: 标记消息为已处理
qe[num].pop(): 从频道队列中移除消息
ans--: 未处理消息数减1
处理总队列中ID ≤ num的所有消息
qt.front().first <= num: 检查消息ID是否≤指定值
if (!vis[qt.front().first]): 如果消息未被处理
qe[qt.front().second].pop(): 从对应频道队列中移除
ans--: 未处理消息数减1
qt.pop(): 从总队列中移除消息

每个消息最多被处理一次，总时间复杂度 O(Q)，其中Q是操作次数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
using namespace std;
constexpr int N = 3e5+5;
int n, q;
queue<int> qe[N];
queue<ii> qt;
bool vis[N];
int main() {
    fast;
    cin >> n >> q;
    int op, num, ant = 1, ans = 0;
    while (q--) {
        cin >> op >> num;
        if (op == 1) {
            ans++;
            qe[num].push(ant);
            qt.emplace(ant, num);
            ant++;
        } else if (op == 2) {
            while (!qe[num].empty()) {
                vis[qe[num].front()] = true;
                qe[num].pop();
                ans--;
            }
        } else {
            while (!qt.empty() && qt.front().first <= num) {
                if (!vis[qt.front().first]) {
                    qe[qt.front().second].pop();
                    ans--;
                }
                qt.pop();
            }
        }
        cout << ans << '\n';
    }
    return 0;
}