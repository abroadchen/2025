//
// Created by Psy.C on 2026/1/9.
//
/**
* n: 数组长度
a[N]: 存储输入数组
l, r: 记录最优区间的左右端点
ans[N]: 存储结果索引
*mp: 映射值到其在数组中出现位置的向量
s[N]: 前缀和数组（只统计正数）
sum: 当前最大和，初始化为负无穷
s[0] = 0: 前缀和数组的初始值
mp.clear(): 清空映射
 *将值 a[i] 对应的所有位置存入 mp
 *
*遍历每个值及其出现位置
fst: 当前值，snd: 该值出现的所有位置
x: 该值出现次数，只有出现2次或以上才处理
t: 从第一次出现到最后一次出现之间（含边界）的正数和
if (fst < 0) t += fst << 1;: 如果值是负数，将该负值加两次（因为要计算重复值的收益）
更新最大和及对应的区间
 *
*k: 结果数组的大小计数器
第一段：从1到l-1的所有索引
第二段：在区间(l,r)内所有负值的索引
第三段：从r+1到n的所有索引
 *
*输出最大和和结果数组大小
输出结果数组中的所有索引
 *
*s[snd[x - 1]]: 到最后一个出现位置的正数前缀和
s[snd[0] - 1]: 到第一次出现位置之前的正数前缀和
两者相减得到区间 [snd[0], snd[x-1]] 内的正数总和
 */
#include <iostream>
#include <map>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 333333
#define inf 111111111111
using namespace std;


int main() {
    fast;
    int n, a[N], l = 0, r = 0, ans[N]; cin >> n;
    map<int, vector<int>> mp;
    ll s[N], sum = -inf; s[0] = 0; mp.clear();
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] > 0) s[i] = s[i-1] + a[i]; else s[i] = s[i-1];
        mp[a[i]].push_back(i);
    }
    for (auto &[fst, snd] : mp) {
        if (const int x = static_cast<int>(snd.size()); x >= 2) {
            ll t = s[snd[x - 1]] - s[snd[0] - 1];
            if (fst < 0) t += fst << 1;
            if (t > sum) {
                sum = t, l = snd[0], r = snd[x-1];
            }
        }
    }
    int k = 0;
    for (int i = 1; i < l; ++i) ans[k++] = i;
    for (int i = l + 1; i < r; ++i) if (a[i] < 0) ans[k++] = i;
    for (int i = r + 1; i < n + 1; ++i) ans[k++] = i;
    cout << sum << ' ' << k << '\n';
    for (int i = 0; i < k; ++i) cout << ans[i] << ' ';
    return 0;
}