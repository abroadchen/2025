//
// Created by Psy.C on 2025/11/14.
//
/*
*base：存储找到的基础素数
如果x>=2，则使用埃拉托斯特尼筛法找出所有不超过x的素数：
创建布尔数组f，初始化为true
0和1不是素数，设为false
从2开始遍历到x：
如果f[i]为true，则i是素数，加入base数组
标记i的所有倍数为非素数（从i²开始，步长为i）
 *
*cnt：计数器，记录符合条件的数字个数
分段处理大区间[l,r]，每段大小为seg：
low：当前段的起始位置
h：当前段的结束位置（不超过r）
len：当前段的长度
f：布尔数组，标记当前段中哪些数字需要被筛除
 *
*遍历所有基础素数p（除了2）：
如果p² > h，说明该素数在当前段无法产生合数，跳出循环
计算k = ⌈low/p⌉，即从low开始第一个p的倍数
s = max(k,p)，确保从p本身或更大的倍数开始
 *
*根据素数p模4的余数，调整起始倍数s，使其满足特定的模4条件：
如果p ≡ 1 (mod 4)：调整s使其满足特定条件
如果p ≡ 3 (mod 4)：调整s使其满足特定条件
这是为了筛选出特定形式的数字
 *
*从调整后的起始倍数s开始，以步长4遍历：
计算x = p * k
如果x小于当前段起始位置，跳过
否则将f[x-low]标记为false（表示该数字被筛除）
 *
*遍历当前段的所有数字i：
如果i等于2或者i模4余1：
且i大于1且未被筛除(f[i-low]为true)：
计数器加1
 */
#include <cmath>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;
const ll seg = 1e6;

int main() {
    cin.tie(0)->sync_with_stdio(0);
    ll l, r; cin >> l >> r; ll x = sqrt(r) + 1;
    vector<int> base;
    if (x >= 2) {
        vector<bool> f(x + 1, true);
        f[0] = f[1] = false;
        for (int i = 2; i <= x; ++i) {
            if (f[i]) {
                base.push_back(i);
                for (ll j = (ll)i*i; j <= x; j += i) f[j] = false;
            }
        }
    }
    ll cnt = 0;
    for (ll low = l; low <= r; low += seg) {
        ll h = min(low + seg - 1, r), len = h - low + 1;
        vector<bool> f(len, true);

        for (int p : base) {
            if (p == 2) continue;
            if ((ll)p*p > h) break;
            ll k = (low + p - 1) / p, s = max(k, (ll)p);

            if (p % 4 == 1) {
                ll r = s % 4;
                if (r == 0) s += 1;
                else if (r == 2) s += 3;
                else if (r == 3) s += 2;
            } else {
                ll r = s % 4;
                if (r == 0) s += 3;
                else if (r == 1) s += 2;
                else if (r == 2) s += 1;
            }

            for (ll k = s; p * k <= h; k += 4) {
                ll x = p * k;
                if (x < low) continue;
                f[x - low] = false;
            }
        }

        for (ll i = low; i <= h; ++i) {
            if (i == 2 || (i % 4 == 1)) {
                if (i > 1 && f[i - low]) cnt++;
            }
        }
    }
    cout << cnt << '\n';
    return 0;
}