//
// Created by Psy.C on 2025/11/27.
//
/*
*nb[0]: 上方是否有点(相同x坐标，y更小)
nb[1]: 下方是否有点(相同x坐标，y更大)
nb[2]: 左方是否有点(相同y坐标，x更小)
nb[3]: 右方是否有点(相同y坐标，x更大)
 *
*遍历每个点作为检查对象
获取当前点的坐标
重置四个方向的标记为false
*内层循环遍历所有其他点
如果是同一个点则跳过
 *
 *时间复杂度为O(n²)，适用于点数不是特别大的情况
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    vector<pair<int,int>> p;
    int x = 0, y = 0;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;
        p.emplace_back(x, y);
    }
    bool nb[4] = {}; int cnt = 0;
    for (int i = 0; i < n; ++i) {
        x = p[i].first, y = p[i].second;
        nb[0] = nb[1] = nb[2] = nb[3] = false;
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            if (p[j].first == x && p[j].second < y) nb[0] = true;
            else if (p[j].first == x && p[j].second > y) nb[1] = true;
            else if (p[j].first < x && p[j].second == y) nb[2] = true;
            else if (p[j].first > x && p[j].second == y) nb[3] = true;
            if (nb[0] && nb[1] && nb[2] && nb[3]) { ++cnt; break; }
        }
    }
    cout << cnt << '\n';
    return 0;
}