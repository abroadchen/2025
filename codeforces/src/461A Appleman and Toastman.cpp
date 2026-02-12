//
// Created by Psy.C on 2026/2/12.
//
/**
最初我们有所有元素的和
在每次迭代中，我们取最小元素并"翻转它的符号"
翻转后，该元素对总和的贡献变为负数
这个过程持续到只剩下最大的元素保持不变
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 300005
using namespace std;

int a[N], n;
ll sum, ans;

int main() {
    fast;
    cin>>n;
    for (int i = 0; i < n; ++i) {
        cin>>a[i]; sum+=a[i];
    }
    ans=sum; sort(a, a+n);
    for (int i = 0; i < n-1; ++i) {
        ans -= a[i];
        sum += a[i] + ans;
    }
    cout << sum << '\n';
    return 0;
}