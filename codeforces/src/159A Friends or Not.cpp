//
// Created by Psy.C on 2025/11/25.
//
/*
*p[i]: 第i条消息记录，包含(发送者, 接收者, 时间戳)
s: 符合条件的用户对集合（自动去重和排序）
 *
 *身份互换条件
 *i的发送者 = j的接收者 i的接收者 = j的发送者
 *时间窗口条件
 *时间差不超过d j发生在i之后
 *
 *确保用户对按字典序排列，避免(A,B)和(B,A)被当作不同对
 *
*时间复杂度
暴力枚举：O(n²)
每对检查：O(1)
总体：O(n²)
空间复杂度
存储消息：O(n)
存储结果：O(k)，k为符合条件的用户对数
set容器的优势
自动去重：相同用户对只存储一次
自动排序：输出时按字典序排列
高效查找：插入和查找都是O(log k)
 */
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;

int main() {
    fast;
    ll n, d; cin>>n>>d;

    vector<tuple<string,string,ll>> p(n);
    for (int i = 0; i < n; ++i) {
        string a,b; ll time;
        cin>>a>>b>>time;
        p[i] = {a, b, time};
    }
    set<pair<string,string>> s;
    for (int i = 0; i < n - 1; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (get<0>(p[i]) == get<1>(p[j]) &&
                get<1>(p[i]) == get<0>(p[j])) {
                if (get<2>(p[j]) - get<2>(p[i]) <= d &&
                    get<2>(p[j]) - get<2>(p[i]) > 0) {
                    string a = min(get<0>(p[j]), get<1>(p[j])),
                    b = max(get<0>(p[j]), get<1>(p[j]));
                    s.insert({a, b});
                }
            }
        }
    }
    cout << s.size() << '\n';
    if (!s.empty()) {
        for (const auto& it : s)
            cout << it.first << ' ' << it.second << '\n';
    }
    return 0;
}