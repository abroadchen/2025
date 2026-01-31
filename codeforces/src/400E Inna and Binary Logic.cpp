//
// Created by Psy.C on 2026/1/31.
//
///时间复杂度：预处理O(18n)，每次更新O(18*(左右扩展长度))
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
using namespace std;


int main() {
    fast;
    int n, m, a[N]; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    ll sum = 0;
    for (int i = 0; i < 18; ++i) {//遍历0到17位（处理32位整数的低18位）
        const int k = 1<<i;//表示第i位
        int cnt = 0;
        for (int j = 1; j <= n; ++j) {//统计连续包含第i位的元素个数
            if (k&a[j]) cnt++; else {//当前元素的第i位为1
                sum += 1ll*cnt*(cnt+1)/2*k;//长度为cnt的连续段包含的子段数量
                cnt = 0;
            }
        }
        if (cnt) sum += 1ll*cnt*(cnt+1)/2*k;//处理最后一段连续的包含第i位的元素
    }
    while (m--) {
        int p, v; cin >> p >> v;//位置p和新值v
        for (int i = 0; i < 18; ++i) {
            const int k = 1<<i;
            if ((k&v) == (k&a[p])) continue;//第i位在新旧值中相同
            int l = 0, r = 0;
            for (int j = p - 1; j >= 1; --j) {//位置p左侧连续包含第i位的元素数量l
                if (a[j]&k) l++; else break;//遇到不包含第i位的元素就停止
            }
            for (int j = p + 1; j <= n; ++j) {//位置p右侧连续包含第i位的元素数量r
                if (a[j]&k) r++; else break;
            }
            ///l：包含p的左侧单个子段
            ///r：包含p的右侧单个子段
            ///l*r：跨越p的左右子段
            ///1：仅包含p的子段
            const ll t = (l+r+1ll*l*r+1)*k;
            ///如果新值的第i位为1，总和增加t
            ///如果新值的第i位为0，总和减少t
            if (k&v) sum += t; else sum -= t;
        }
        a[p] = v;//更新数组值
        cout << sum << '\n';
    }
    return 0;
}