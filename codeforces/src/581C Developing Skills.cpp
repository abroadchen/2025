//
// Created by Psy.C on 2026/3/16.
//
/**
时间复杂度：O(n log n)（主要是排序）
空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5;
int n, k, a[N];
int main() {
    fast;
    cin >> n >> k;
    int sum = 0;//初始达到10分的个数
    for (int i = 0; i < n; ++i) {
        cin >> a[i];//每个学生的当前分数
        sum += a[i]/10;//当前有多少个完整的10分（每个10分算作1个单位）
        a[i] %= 10;//保留余数（0-9之间的部分）
    }
    //将余数按降序排列
    sort(a, a + n); reverse(a, a + n);
    for (int i = 0; i < n; ++i) {
        if (10 - a[i] <= k) {//如果能把当前分数提升到下一个10分
            sum++;//增加一个10分单位
            k -= 10 - a[i];//减少使用的分数
        }
    }
    cout << min(10*n, sum + k/10) << '\n';//最大可能的总分
    return 0;
}