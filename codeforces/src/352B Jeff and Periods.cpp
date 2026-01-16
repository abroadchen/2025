//
// Created by Psy.C on 2026/1/16.
//
/**
 * 存储每个数值及其在序列中出现的所有位置
 *
*ll k = fst;: 声明局部变量k并初始化为fst
snd.size() == 1: 如果该值只出现一次
v.emplace_back(k, 0);: 添加(值, 0)对（0表示无周期）
else: 如果该值出现多次
*循环计算相邻位置的差值
snd[i] - snd[i - 1]: 计算相邻出现位置的间隔
abs(...): 取绝对值
s.insert(...): 插入到set中（自动去重并排序）
 *
*s.size() == 1: 如果所有间隔都相同（只有一种间隔值）
v.emplace_back(k, *s.begin());: 添加(值, 间隔)对
*s.begin(): 获取set中的唯一元素
 *
 *输出结果对的总数
 *循环输出每个(值, 周期)对
 */
#include <iostream>
#include <map>
#include <vector>
#include <set>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n, i, x; cin >> n;
    map<ll, vector<ll>> mp;
    for (i = 0; i < n; ++i) {
        cin >> x;
        mp[x].push_back(i);//将位置i添加到值x对应的位置列表中
    }
    vector<pair<ll, ll>> v;//(值, 周期)对
    for (auto&[fst, snd] : mp) {
        if (ll k = fst; snd.size() == 1) v.emplace_back(k, 0); else {
            set<ll> s;//存储相邻位置的差值
            for (i = 1; i < snd.size(); ++i)
                s.insert(abs(snd[i] - snd[i - 1]));
            if (s.size() == 1) v.emplace_back(k, *s.begin());
        }
    }
    cout << v.size() << '\n';
    for (i = 0; i < v.size(); ++i) cout << v[i].first << ' ' << v[i].second << '\n';
    return 0;
}