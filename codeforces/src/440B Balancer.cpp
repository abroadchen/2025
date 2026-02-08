//
// Created by Psy.C on 2026/2/7.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 50010
using namespace std;


int main() {
    fast;
    int n; cin >> n;
    ll num[N], sum = 0, k, ans = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> num[i]; sum += num[i];
    }
    sum /= n;//平均值
    for (int i = 1; i <= n; ++i) {
        if (num[i] == sum) continue;
        if (num[i] > sum) {
            k = num[i] - sum;//超额
            ans += k;//添加到总移动
            num[i+1] += k;//转移到下一个元素
        }
        else if (num[i] < sum) {
            k = sum - num[i];//不足
            ans += k;
            num[i+1] -= k;//从下一个元素取
        }
    }
    cout << ans << '\n';
    return 0;
}