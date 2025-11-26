//
// Created by Psy.C on 2025/11/26.
//
/*
*a[i] = s[i] - '0'：前n个字符转换为数字存入向量a
b[i] = s[n + i] - '0'：后n个字符转换为数字存入向量b
 *
 *如果两个排序后数组的最小值相等，则答案为"NO"
*如果a的最小值小于b的最小值：
检查其余元素是否都满足a[i] < b[i]
如果有任何一个a[i] >= b[i]，则答案为"NO"
 *
 *时间复杂度为O(n log n)
 *
 */
#include <iostream>
#include <algorithm>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    vector<int> a(n), b(n);
    string s; cin >> s;
    for (int i = 0; i < n; ++i) { a[i] = s[i] - '0'; b[i] = s[n + i] - '0'; }
    sort(a.begin(), a.end()); sort(b.begin(), b.end());
    string ans = "YES";
    if (a[0] == b[0]) ans = "NO";
    else if (a[0] < b[0]) {
        for (int i = 1; i < n; ++i) if (a[i] >= b[i]) {
            ans = "NO"; break;
        }
    } else if (a[0] > b[0]) {
        for (int i = 1; i < n; ++i) if (a[i] <= b[i]) {
            ans = "NO"; break;
        }
    }
    cout << ans << '\n';
    return 0;
}