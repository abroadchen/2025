//
// Created by Psy.C on 2025/10/23.
//
/*
 *读入整数n，创建包含n个pair元素的vector，每个pair存储字符串和索引
 *初始化l为一个大数(1000007)，r为0，用于记录字符串长度的最小值和最大值
*循环读入n个字符串：
将字符串存入v[i].first
将索引i存入v[i].second
更新最短字符串长度l和最长字符串长度r
 *
*为每个字符串末尾添加字符s
将每个字符串按长度分类插入到对应的set中
 *对vector v按字符串字典序排序
 *
*初始化x为0，循环处理所有字符串：
标记当前字符串已处理
输出当前字符串
*计算目标长度ans
移除已处理过的字符串
 *
*取出目标字符串和索引
标记该字符串已处理
输出去除添加字符s后的字符串
输出换行符
 *跳过已处理的字符串，继续处理下一个未处理的字符串
 */
#include <vector>
#include <ios>
#include <iostream>
#include <set>
#include <algorithm>
#define sz(s) int((s).size())
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
    int n; cin >> n;
    vector<pair<string,int>> v(n);

    int l(1e6+7), r(0);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].first; v[i].second = i;
        l = min(l, sz(v[i].first));
        r = max(r, sz(v[i].first));
    }
    int d = l + r; char s; cin >> s;
    vector<set<pair<string, int>>> a(11);
    vector<bool> f(n, 0);
    for (int i = 0; i < n; ++i) {
        v[i].first += s;
        a[v[i].first.size() - 1].insert({v[i].first, i});
    }
    sort(v.begin(), v.end());

    int x(0);
    while (x < n) {
        f[v[x].second] = 1;
        cout << v[x].first;

        int ans = d - v[x].first.size() + 1;
        while (f[(*a[ans].begin()).second]) a[ans].erase(a[ans].begin());

        auto [str, idx] = *a[ans].begin();
        a[ans].erase(a[ans].begin());
        f[idx] = 1;
        for (char& c : str) if (c != s) cout << c;
        cout << '\n';
        while (x < n && f[v[x].second]) x++;
    }
    return 0;
}