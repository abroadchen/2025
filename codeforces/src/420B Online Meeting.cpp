//
// Created by Psy.C on 2026/2/4.
//
/**
* 时间复杂度：O(m log m)，主要是set操作的时间复杂度
空间复杂度：O(n + m)，存储ans数组、操作记录和set
 */
#include <iostream>
#include <set>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1000010
using namespace std;


int main() {
    fast;
    int n, m; cin>>n>>m;
    int ans[N];
    for (int i = 1; i <= n; ++i) ans[i] = 1;//激活
    int s = 0, t = 0, id[N];
    char op[N];
    for (int i = 1; i <= m; ++i) {
        cin >> op[i] >> id[i];
        //赋值语句而不是累加语句，所以i越大，t的值越新
        if (op[i] == '-' && ans[id[i]]) t = id[i];//最后一次'-'操作的id值
        ///!s 条件，这意味着只有当s还没有被赋值时（s=0）才进行赋值
        if (op[i] == '+' && !s) s = id[i];//第一个'+'操作的目标ID
        ans[id[i]] = 0;//非激活
    }
    set<int> q;
    ///优先选择最后一次'-'操作的元素作为特殊元素x
    ///如果没有'-'操作，则选择第一次'+'操作的元素
    ///将特殊元素x重新设为激活状态
    const int x = t ? t : s; q.insert(x); ans[x] = 1;
    for (int i = 1; i <= m; ++i) {
        if (op[i] == '+') {
            q.insert(id[i]);
            if (!q.contains(x)) ans[x] = 0;
        } else {
            q.erase(id[i]);
            if (!q.empty() && !q.contains(x)) ans[x] = 0;
        }
    }
    int sum = 0;
    for (int i = 1; i <= n; ++i) sum += ans[i];
    cout << sum << '\n';
    for (int i = 1; i <= n; ++i) if (ans[i]) cout << i << ' ';
    cout << '\n';
    return 0;
}