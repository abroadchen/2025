//
// Created by Psy.C on 2026/4/26.
//
/**
原始数组v和目标数组w
vv存储分段区间，kk存储操作序列

遍历目标数组w中的每个元素
尝试在原数组v中找到连续子序列，使其和等于w[i]
如果找不到匹配的和，则标记flag = 0
将找到的区间[l, p1-1]存储在vv中

时间复杂度：O(n²)，主要由于寻找最大值和生成操作序列
空间复杂度：O(n)，存储各种辅助数组和操作序列

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define ii pair<int, int>
using namespace std;

int n;
vector<ll> v, w;
vector<ii> vv, kk;
ll x;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x; v.push_back(x);
    }
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> x; w.push_back(x);
    }
    int p1 = 0, flag = 1;
    for (ll i : w) {
        ll now = 0;
        int l = p1;
        while (p1 < v.size() && now < i)
            now += v[p1++];
        if (now != i) { flag = 0; break; }
        vv.emplace_back(l, p1-1);
    }
    if (p1 != v.size()) flag = 0;//是否完全使用了原数组v的所有元素
    if (flag) {
        int ch = 1;
        for (int i = 0; i < vv.size(); ++i) {
            ll mx = -1;
            for (int j = vv[i].first; j <= vv[i].second; ++j)
                mx = max(mx, v[j]);//在每个分段中找到最大值
            int t = -1, dis = 0;
            if (vv[i].second == vv[i].first)
                t = vv[i].second;
            for (int j = vv[i].first; j <= vv[i].second; ++j) {
                if (v[j] != mx) continue;
                if (j != vv[i].first && v[j] > v[j-1]) {//找到最大值中满足条件的位置（大于相邻元素）
                    t = j, dis = 0;//向左移动
                    break;
                }
                if (j != vv[i].second && v[j] > v[j+1]) {
                    t = j, dis = 1;//向右移动
                    break;
                }
            }
            if (t == -1) { ch = 0; break; }
            int l = t - vv[i].first, r = vv[i].second - t;
            if (dis == 0) {
                while (l) {
                    kk.emplace_back(i+1+l, 0);//移动步数和方向
                    l--;
                }
                while (r--) kk.emplace_back(i+1, 1);
            } else {
                while (r--) kk.emplace_back(i+1+l, 1);
                while (l) {
                    kk.emplace_back(i+1+l, 0);
                    l--;
                }
            }
        }
        if (ch) {
            cout << "YES\n";
            for (auto &[fst, snd] : kk)
                cout << fst << ' ' << (snd ? "R" : "L") << '\n';
        } else cout << "NO\n";
    } else cout << "NO\n";
    return 0;
}