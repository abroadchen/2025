//
// Created by Psy.C on 2025/12/22.
//
/*
 *131072
 *
*遍历排序后的数组：
如果当前元素能被 k 整除：
检查 a[i]/k 是否已经在结果向量中（使用二分查找）
如果不存在，则将当前元素加入结果向量
如果不能被 k 整除：直接将当前元素加入结果向量
 */
#include <iostream>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1<<17
using namespace std;


int main() {
    fast;
    int n, k; cin>>n>>k;
    if (k == 1) { cout << n << '\n'; return 0; }
    int a[N];
    for (int i = 0; i < n; ++i) cin>>a[i];
    sort(a,a+n);
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        if (a[i] % k == 0) {
            if (!binary_search(ans.begin(), ans.end(), a[i] / k))
                ans.push_back(a[i]);
        } else ans.push_back(a[i]);
    }
    cout << ans.size() << '\n';
    return 0;
}