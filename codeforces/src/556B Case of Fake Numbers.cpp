//
// Created by Psy.C on 2026/3/11.
//
/**
n: 数组长度
v: 存储待变换的数组
奇数位置 (i&1): 元素值减1，若小于0则变为n-1（循环左移）
偶数位置: 元素值加1，若等于n则变为0（循环右移）
检查当前数组是否为 [0, 1, 2, ..., n-1] 形式
如果是，输出"YES"并退出

时间复杂度: O(n²)，最坏情况下进行n轮，每轮O(n)
空间复杂度: O(n)，存储数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n;
vector<int> v;
int main() {
    fast;
    cin >> n;
    for (int i = 0, t; i < n; ++i)
        cin >> t, v.push_back(t);
    int q = n;
    while (q--) {
        for (int i = 0; i < n; ++i) {
            if (i&1) {
                int t = v[i]; t--;
                if (t < 0) t = n - 1;
                v[i] = t;
            } else {
                int t = v[i]; t++;
                if (t == n) t = 0;
                v[i] = t;
            }
        }
        bool flag = true;
        for (int i = 0; i < n; ++i)
            if (v[i] != i) {
                flag = false;
                break;
            }
        if (flag) { cout << "YES\n"; return 0; }
    }
    cout << "NO\n";
    return 0;
}