//
// Created by Psy.C on 2025/12/8.
//
/*
*a[N]：存储位置映射的数组
b[N]：存储第二个序列的数组
s：多重集合，用于存储差值
 *
*读取n个数字x
将数组a中索引为x的元素设置为i
这建立了从数值到其位置的映射关系
 *
*读取n个数字存储到数组b中
计算i - a[b[i]]并插入到多重集合s中
a[b[i]]表示数值b[i]在第一个序列中的位置
i - a[b[i]]表示位置差值 //当前位置与原始位置的差值
 *
 *p = s.lower_bound(i)：在集合中找到大于等于i的第一个元素
 */
#include <iostream>
#include <set>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100005
#define inf 0x3f3f3f3f
using namespace std;

int a[N], b[N];
multiset<int> s;

int main() {
    fast;
    int n; cin>>n;
    for (int i = 0, x; i < n; ++i) { cin>>x; a[x] = i; }
    for (int i = 0; i < n; ++i) { cin>>b[i]; s.insert(i - a[b[i]]); }
    for (int i = 0; i < n; ++i) {
        auto p = s.lower_bound(i); int ans = inf;
        if (p != s.end()) ans = min(ans, *p - i);//正向距离
        if (p != s.begin()) ans = min(ans, i - *(--p));//反向距离
        cout << ans << '\n';
        p = s.find(i - a[b[i]]); s.erase(p);
        s.insert(i - a[b[i]] + n);//插入更新后的差值
    }
    return 0;
}