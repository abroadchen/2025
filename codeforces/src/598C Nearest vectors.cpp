//
// Created by Psy.C on 2026/3/20.
//
/**
n：点的数量
a1, a2：结果点的索引
vector<li> v：存储点的角度和原始索引
读取点的数量n
循环读取n个点的坐标(x,y)
atan2(y, x)：计算点(x,y)相对于原点的角度（弧度制）
ang.second = i + 1：存储原始索引（1-indexed）
将角度和索引存入向量v
按角度升序排序所有点
ans = 2*pi：初始化最小角度差为2π
循环遍历相邻的角度对（包括最后一个和第一个的相邻关系）
t = v[(i+1)%n].first - v[i].first：计算相邻两点的角度差
if (t < 0) t += 2*pi;：如果角度差为负，加上2π使其为正值（处理跨越0度的情况）
if (t < ans)：如果找到更小的角度差，更新结果
输出角度最接近的两个点的原始索引
时间复杂度：O(n log n)（主要是排序） 空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ld long double
#define li pair<ld, int>
using namespace std;
const ld pi = acos(-1.);

int n, a1, a2;
vector<li> v;
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        ld x, y; cin >> x >> y;
        li ang; ang.first = atan2(y, x); ang.second = i + 1;
        v.push_back(ang);
    }
    ranges::sort(v);
    ld ans = 2*pi;
    for (int i = 0; i < n; ++i) {
        ld t = v[(i+1)%n].first - v[i].first;
        if (t < 0) t += 2*pi;
        if (t < ans) {
            ans = t;
            a1 = v[i].second, a2 = v[(i+1)%n].second;
        }
    }
    cout << a1 << ' ' << a2 << '\n';
    return 0;
}