//
// Created by Psy.C on 2026/1/24.
//

#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 3001000
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    int a[N], p[N];
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        p[i] = i;
    }
    //基于a中对应值对数组p进行排序
    sort(p, p + n, [&a](const int i, const int j) {
        return a[i] < a[j];
    });
    int k = a[p[0]] + 1;//跟踪要分配的下一个值
    for (int i = 1; i < n; ++i) {
        if (a[p[i]] < k) a[p[i]] = k++;//当前值小于k，分配k并递增k
        else k = a[p[i]] + 1;//将k更新为当前值+1
    }
    //输出变换后的数组，保持原始顺序
    for (int i = 0; i < n - 1; ++i) cout << a[i] << ' ';
    cout << a[n - 1] << '\n';
    return 0;
}