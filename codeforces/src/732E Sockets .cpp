//
// Created by Psy.C on 2026/4/26.
//
/**
n, m: 输入的两个整数
r1[N]: 存储第i个查询需要的操作次数
r2[N]: 存储第i个原始数被替换成了哪个查询数
a1, a2: 分别统计匹配成功的数量和总操作次数
mp: 存储原始数值及其位置的多重映射
b[N]: 存储查询数据的数组
将每个原始数值和其位置插入到multimap中
读取查询值并将其原始索引保存在second中

外层循环遍历每个查询
内层循环不断对查询值进行变换直到找到匹配项或变为1
j表示变换次数
如果在map中找到当前查询值，就记录匹配关系并删除该元素
否则将查询值按公式(x+1)/2变换，继续查找
直到找到匹配或值变为1时停止内循环
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int,int>
using namespace std;
constexpr int N = 2e5+7;
int n, m, r1[N], r2[N], a1, a2;
multimap<int, int> mp;
ii b[N];
int main() {
    fast;
    cin >> n >> m;
    for (int i = 1, x; i <= n; ++i) cin >> x, mp.emplace(x, i);
    for (int i = 1; i <= m; ++i) cin >> b[i].first, b[i].second = i;
    sort(b + 1, b + m + 1);
    for (int i = 1; i <= m; ++i)
        for (int j = 0; ; ++j) {
            if (auto it = mp.find(b[i].first); it != mp.end()) {
                r1[b[i].second] = j; r2[it->second] = b[i].second;
                a1++; a2 += j; mp.erase(it);
                break;
            }
            if (b[i].first == 1) break;
            b[i].first = (b[i].first + 1) / 2;
        }
    cout << a1 << ' ' << a2 << '\n';
    for (int i = 1; i <= m; ++i) cout << r1[i] << ' ';
    cout << '\n';
    for (int i = 1; i <= n; ++i) cout << r2[i] << ' ';
    return 0;
}