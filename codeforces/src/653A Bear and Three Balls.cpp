//
// Created by Psy.C on 2026/4/7.
//
// n为输入数字个数，a为去重后的数组，num为去重后元素个数
// flag标记某个数字是否出现，tag标记是否存在连续三个数
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1005, M = 55;
int n, a[M], num;
bool flag[N], tag;
int main() {
    fast;
    cin >> n;
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        if (!flag[x]) {//如果这个数字之前没出现过
            flag[x] = true;//标记这个数字已出现
            a[num++] = x;//添加到去重数组中，同时增加计数
        }
    }
    sort(a, a + num);
    for (int i = 0; i <= num-3; ++i)//确保至少还有两个元素可检查
        if (flag[a[i]+1] && flag[a[i]+2]) {//当前数字的下一个和下两个数字是否存在
            tag = true;//存在连续三个数字，设置标记
            break;
        }
    if (tag) cout << "YES\n"; else cout << "NO\n";
    return 0;
}