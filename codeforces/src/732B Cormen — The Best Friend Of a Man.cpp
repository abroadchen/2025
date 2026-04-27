//
// Created by Psy.C on 2026/4/26.
//
/**
n: 元素总数
k: 每对相邻元素之和的最小值要求
t: 临时输入变量
cnt: 需要增加的数量统计
将第一个 t 添加到向量 v 中
当前元素 t 与前一个元素 v[i-1] 的和是否小于 k
调整当前元素：如果和小于k，则将当前元素设置为 k - v[i-1]，确保相邻两元素之和等于k
累计调整量：将需要增加的数量 k - (t + v[i-1]) 加到计数器 cnt 中
如果相邻元素之和不小于k，则直接将原值 t 添加到向量中
输出调整总量：打印总共需要增加的数量
输出修改后的数组：按顺序输出调整后的所有元素，以空格分隔
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

ll n, k, t, cnt;
vector<ll> v;
int main() {
    fast;
    cin >> n >> k >> t; v.push_back(t);
    for (int i = 1; i < n; ++i) {
        cin >> t;
        if (t + v[i-1] < k) {
            v.push_back(k - v[i-1]);
            cnt += k - (t + v[i-1]);
        } else v.push_back(t);
    }
    cout << cnt << '\n';
    for (int i = 0; i < n; ++i) cout << v[i] << ' ';
    cout << '\n';
    return 0;
}