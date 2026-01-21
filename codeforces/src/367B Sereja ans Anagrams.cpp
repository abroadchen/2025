//
// Created by Psy.C on 2026/1/20.
//
/*
* n：数组长度
p：步长
a[N]：输入数组
m：模式长度
res：结果计数
mp：滑动窗口计数器
b：目标模式计数器
vis[N]：标记数组
O(p × (n/p) × m) = O(n × m)（最坏情况）
 */
#include <iostream>
#include <map>
#include <queue>
#include <ranges>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 200005
using namespace std;

int n, p, a[N], m, res;
map<int, int> mp, b;
bool vis[N];
void get(const int s) {//起始位置
    queue<int> q; mp.clear();
    for (int i = s; i <= n; i += p) {
        q.push(i); mp[a[i]]++;//当前位置加入队列和计数器
        if (q.size() == m) {//窗口大小达到m时
            if (mp == b) {//当前窗口的元素分布与目标模式相同
                vis[q.front()] = true;//标记起始位置
                res++;
            }
            const int t = q.front(); q.pop();//移除队首元素，更新计数器
            mp[a[t]]--;
            if (!mp[a[t]]) mp.erase(a[t]);
        }
    }
}

int main() {
    fast;
    cin >> n >> m >> p;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1, t; i <= m; ++i) {
        cin >> t;
        b[t]++;
    }
    for (int i = 1; i <= p; ++i) get(i);//从1到p的每个起始位置执行搜索
    cout << res << '\n';//匹配次数
    for (int i = 1; i <= n; ++i) if (vis[i]) cout << i << ' ';//匹配的起始位置
    return 0;
}