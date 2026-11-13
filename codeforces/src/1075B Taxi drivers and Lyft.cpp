//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
n 个服务点，m 个用户
输入分两轮：第一轮坐标，第二轮类型。
a[] 按出现顺序存服务点坐标，cnt 是服务点总数
从开头扫描，直到第一个服务点为止，这些用户坐标都小于等于第一个服务点（最左边），所以全部分给服务点 k=1。
num[1] 统计这些最左侧用户
if (p[i].second == 1) { k++; continue; }：扫描到服务点，则切换到下一个服务区（k 自增），用户点不用处理。
if (k < cnt)：当前用户有待比较的左右两个服务点。
比较到左边 a[k] 和右边 a[k+1] 的距离。
等距时判给左边（<=），即偏左，符合 Voronoi 左闭右开的分界约定。
否则划给右边的 k+1。
else（k == cnt，当前是最后一个服务区）：之后的所有用户都在最后一个服务点右侧，全归第 cnt 个服务点。
依次输出每个服务点服务（分到）的用户数。
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=(n); i++)
#define ii pair<int, int>
using namespace std;

constexpr int N = 1e5+5;

int n, m, cnt, a[N], num[N];
ii p[N*3];
int main() {
    fast;
    cin >> n >> m;
    rep(i,n+m) cin >> p[i].first;//读所有点（服务点+用户）坐标
    rep(i,n+m) {
        cin >> p[i].second;//读标记：1=服务点，0=用户（类型）
        if (p[i].second == 1) a[++cnt] = p[i].first;//记录服务点坐标到 a[]
    }
    int k = 1, i;
    for (i = 1; i <= n+m; i++) {
        if (p[i].second == 1) break;//遇到第一个服务点就停
        num[k]++;//在第一个服务点左侧的用户划给它
    }
    i++;//跳过刚才已找到的第一个服务点
    for (; i <= n+m; i++) {
        if (p[i].second == 1) { k++; continue; }//遇到新服务点，当前服务区切换
        if (k < cnt) {
            //不是最后一个服务点：比较到左服务点 a[k] 和右服务点 a[k+1] 的距离
            if (abs(p[i].first-a[k]) <= abs(p[i].first-a[k+1])) num[k]++;//离左边近（或平局给左边）
            else num[k+1]++;//离右边近
        } else num[k]++;//最后一个服务点，右侧全归它
    }
    for (i = 1; i <= cnt; i++) cout << num[i] << ' ';
    cout << '\n';
    return 0;
}