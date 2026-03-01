//
// Created by Psy.C on 2026/3/1.
//
/**
n：矩形的总数
w, h：临时变量，用于读取矩形的宽度和高度
W(n)：存储n个矩形的宽度
H(n)：存储n个矩形的高度
s，用于存储所有矩形的高度，自动排序
总宽度：int ans = 0

s.find(H[i])：查找高度为H[i]的元素
s.erase(...)：删除找到的元素
*s.rbegin()：获取多重集合中最大的元素（反向迭代器指向最大值）
mxh * d，最大高度 × 剩余总宽度
将当前矩形高度重新插入集合

时间复杂度：O(n log n)，空间复杂度：O(n)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, w, h;
int main() {
    fast;
    cin >> n;
    vector<int> W(n), H(n);
    multiset<int> s;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> w >> h;
        s.insert(h); ans += w;
        W[i] = w; H[i] = h;
    }
    for (int i = 0; i < n; ++i) {
        s.erase(s.find(H[i]));
        const int mxh = *s.rbegin(), d = ans - W[i];
        cout << mxh*d << ' ';
        s.insert(H[i]);
    }
    cout << '\n';
    return 0;
}