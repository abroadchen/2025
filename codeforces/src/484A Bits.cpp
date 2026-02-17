//
// Created by Psy.C on 2026/2/17.
//
/**
从低位到高位，尝试把l中原本为0的位改为1
但要保证修改后的数值不超过r
最终得到的就是区间[l,r]内二进制表示中1最多的那个数

每个测试用例：O(log r)（位数级别）
总时间复杂度：O(n * log r)
空间复杂度：O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int n;
ll x, l, r;

int main() {
    fast;
    cin >> n;
    while (n--) {
        x = 1;
        cin >> l >> r;
        while (true) {
            if ((l|x) <= r) l |= x;//将x的位设置到l中
            else break;
            x <<= 1;
        }
        cout << l << '\n';
    }
    return 0;
}