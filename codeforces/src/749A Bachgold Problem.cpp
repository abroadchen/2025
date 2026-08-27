//
// Created by Psy.C on 2026/8/27.
//

#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int a;
int main() {
    fast;
    cin >> a;
    //因为int类型是将算出的结果自动向下取整，所以奇数和偶数都可以用a/2来解决
    cout << a/2 << '\n';
    if (a % 2 == 0) {//重复输出a/2遍2
        for (int x = 1; x <= a/2; ++x) cout << 2 << ' ';
    } else {
        //先输出a/2-1个2
        for (int x = 1; x <= a/2-1; ++x) cout << 2 << ' ';
        cout << 3;//最后将3输出
    }
    return 0;
}