//
// Created by Psy.C on 2025/11/4.
//
/*
*pre[i]: 第i个数组的前缀最大和
suf[i]: 第i个数组的后缀最大和
mid[i]: 第i个数组的子数组最大和(最大子段和)
sum[i]: 第i个数组的总和
 *
*循环处理每个数组：
读取第i个数组的长度k
创建大小为k的数组a
读取数组a的所有元素
 *计算数组a的总和并存储在sum[i]中
*计算前缀最大和pre[i]：
从左到右累加元素
记录过程中前缀和的最大值
*计算后缀最大和suf[i]：
从右到左累加元素
记录过程中后缀和的最大值
*计算最大子段和mid[i]（Kadane算法）：
对于每个位置，决定是否延续之前的子数组或重新开始
记录过程中的最大子段和
 *
*循环处理m个选择的数组：
读取数组编号x（转换为0索引）
更新结果res，考虑三种情况的最大值：
当前结果res
当前累积和+新数组前缀最大和(cur + pre[x])
新数组内部的最大子段和(mid[x])
更新当前累积和cur：
要么是之前的累积和加上整个数组(sum[cur + sum[x]])
要么是从新数组的某个后缀开始(max(suf[x]))
 *
 */
#include <algorithm>
#include <ios>
#include <iostream>
#include <numeric>
#include <vector>
using namespace std;

typedef long long ll;
const int inf = 1e9;

int main() {

    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin>>n>>m;
    vector<ll> pre(n, -inf), suf(n, -inf), mid(n, -inf), sum(n);
    for (int i = 0; i < n; ++i) {
        int k; cin>>k;
        vector<int> a(k);
        for (int j = 0; j < k; ++j) cin >> a[j];
        sum[i] = accumulate(a.begin(), a.end(), 0);
        ll s(0);
        for (int j = 0; j < k; ++j) {
            s += a[j];
            pre[i] = max(pre[i], s);
        }
        s = 0;
        for (int j = k - 1; j >= 0; --j) {
            s += a[j];
            suf[i] = max(suf[i], s);
        }
        s = 0;
        for (int j = 0; j < k; ++j) {
            s = max(0ll, s) + a[j];
            mid[i] = max(mid[i], s);
        }
    }

    ll cur(0), res(-inf);
    for (int i = 0; i < m; ++i) {
        int x; cin>>x; x--;
        res = max({res, cur + pre[x], mid[x]});
        cur = max(cur + sum[x], suf[x]);
    }
    cout << res << '\n';
    return 0;
}