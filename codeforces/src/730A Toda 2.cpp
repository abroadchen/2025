//
// Created by Psy.C on 2026/4/25.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
#define ii pair<int, int>
using namespace std;
constexpr int N = 1e4+7;

map<int, int> mp;///数组元素出现次数
int n, a[N];
int get() {
    mp.clear();
    for (int i = 1;i <= n; ++i) mp[a[i]]++;
    if (mp.size() > 2) return 0;//不同元素种类超过2个
    if (mp.size() == 1) return 1;//只有1种元素（所有元素相同)
    auto t = mp.begin(); ++t;
    if (t->second == 1) return 2;
    return 0;
}

priority_queue<ii> q;
int cnt, r[N];
set<int> st[N];///每个元素都是集合，存储操作涉及的索引
signed main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) q.emplace(a[i], i);//将数组元素和对应索引压入优先队列（大顶堆）
    while (true) {
        int op = get(); bool flag = true;//获取当前状态，设置标志位
        if (op == 1) break;//所有元素相同
        if (op == 2) {
            int x = max_element(a + 1, a + n + 1) - a;//找到最大元素的位置
            //在已有的操作中找一个不包含最大元素位置的操作，将其加入并减少该位置元素值
            for (int i = 1; i <= cnt; ++i)
                if (!st[i].contains(x)) {
                    st[i].insert(x); flag = false; a[x]--; break;
                }
        }
        if (op == 0 || flag) {
            auto u = q.top(); q.pop();//取出两个最大元素
            auto v = q.top(); q.pop();
            //将两个元素都减1（不低于0），更新原数组
            u.first = max(u.first-1, 0ll); v.first = max(v.first-1, 0ll);
            a[u.second] = u.first; a[v.second] = v.first;
            //将修改后的元素重新放入队列，增加操作计数，并记录本次操作涉及的索引
            q.push(u); q.push(v); cnt++;
            st[cnt].insert(u.second); st[cnt].insert(v.second);
        }
    }
    cout << a[1] << '\n' << cnt << '\n';//最终剩余的元素值和操作次数
    for (int i = 1; i <= cnt; ++i) {//二进制字符串表示该操作涉及哪些位置
        memset(r, 0, sizeof r);
        for (int j : st[i]) r[j] = 1;
        for (int j = 1; j <= n; ++j) cout << r[j];
        cout << '\n';
    }
    return 0;
}