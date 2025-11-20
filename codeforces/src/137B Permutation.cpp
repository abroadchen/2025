//
// Created by Psy.C on 2025/11/20.
//
/*
 *O(n)：需要读取n个数据并遍历1到n
 *O(5500)：固定大小的计数数组
 */
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    int n; cin>>n;
    vector<int> cnt(5500, 0);//数字i出现的次数
    for (int i = 0, d; i < n; ++i) { cin>>d; cnt[d]++; }
    int ans = 0;
    for (int i = 1; i <= n; ++i) if (!cnt[i]) ans++;
    cout << fixed << setprecision(15) << ans;
    return 0;
}