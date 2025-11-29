//
// Created by Psy.C on 2025/11/29.
//
/*
*p[N]: 存储原始数据
d[N]: 存储差分数组
 *
*只累加d数组中正值元素
这通常表示需要进行的操作次数或成本
 *
*将右指针位置的值增加1
将左指针位置的值减少1
保持总体和不变，但使d[r]趋向非负
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;
constexpr int N = 1e5+100;
int p[N], d[N];

int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
        d[i] = p[i] - p[i-1];//相邻元素的差值
    }
    d[n+1] = -p[n]; ll ans = 0;
    for (int i = 1; i <= n; ++i) if (d[i] > 0) ans += d[i];
    cout << ans << '\n';
    n++;//将n增加1，扩展数组长度（因为之前设置了d[n+1]）
    for (int r = 1, l = 1; r <= n; ++r) {
        while (d[r] < 0) {
            while (d[l] <= 0) l++;//移动左指针，跳过所有非正值的位置，找到第一个正值位置
            d[r]++, d[l]--;
            cout << l << ' ' << r - 1 << '\n';
        }
    }
    return 0;
}