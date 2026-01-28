//
// Created by Psy.C on 2026/1/28.
//
/**
* 时间复杂度
O(m log m)，其中m是所有中间元素的总数
主要是排序的时间复杂度
空间复杂度
O(m)，用于存储中间元素
 */
#include <algorithm>
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int s1 = 0, s2 = 0;//两个部分的累计和
    vector<int> a;//存储所有中间元素的向量
    for (int i = 0, k, x; i < n; ++i) {
        cin >> k;//当前组的元素个数
        for (int j = 1; j <= k>>1; ++j) {//前半部分的元素个数
            cin >> x;
            s1 += x;
        }
        if (k&1) { cin >> x; a.push_back(x); }
        for (int j = 1; j <= k>>1; ++j) {
            cin >> x;
            s2 += x;
        }
    }
    ranges::sort(a, [](const int u, const int v) {
        return u > v;
    });//优先将大的元素分配给较小的部分，有助于平衡两部分的和
    for (int i = 0; i < a.size(); ++i) {
        if (i&1) s2 += a[i];
        else s1 += a[i];
    }
    cout << s1 << ' ' << s2 << '\n';
    return 0;
}