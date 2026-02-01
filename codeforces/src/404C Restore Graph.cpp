//
// Created by Psy.C on 2026/2/1.
//
/**
 * n（节点数）、k（度数限制）、mx（最大距离）
 *v[i]存储距离为i的节点
 *读入每个节点的距离，按距离分组
 *
 *距离0的节点必须有且仅有1个（根节点）
 *根节点的子节点数不能超过k
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define ii pair<int, int>
using namespace std;


int main() {
    fast;
    int n, k, dis[N], mx; cin >> n >> k;
    vector<int> v[N];
    for (int i = 1; i <= n; ++i) {
        cin >> dis[i];
        v[dis[i]].push_back(i);//数组的数组
        mx = max(mx, dis[i]);
    }
    if (v[0].size() != 1 || v[0].size() * k < v[1].size()) return cout << "-1\n", 0;
    if (n == 1) return cout << "0\n", 0;//只有1个节点
    vector<ii> ans; ans.reserve(v[1].size());
    for (int i = 0; i < v[1].size(); ++i) ans.emplace_back(v[0][0], v[1][i]);//添加根节点到距离为1的节点的边
    for (int i = 2; i <= mx; ++i) {
        if (v[i].empty()) return cout << "-1\n", 0;//不能有空层
        //上一层的节点必须足够连接当前层（每个上层节点最多连接k-1个下层节点）
        if (v[i-1].size()*static_cast<long long>(k - 1) < v[i].size() && i != 1) return cout << "-1\n", 0;
        for (int j = 0; j < v[i].size(); ++j) ans.emplace_back(v[i-1][j/(k-1)], v[i][j]);//添加上一层到当前层的边
    }
    cout << ans.size() << '\n';//边的数量
    for (auto &[fst, snd] : ans) cout << fst << ' ' << snd << '\n';//所有边
    return 0;
}