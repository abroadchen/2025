//
// Created by Psy.C on 2026/5/8.
//
/**
n：元素总数
x：目标异或值
num[N]：存储输入的数字的数组
cnt[N<<1]：计数数组

对于任意两个数a和b，如果a ^ b = x，那么a ^ x = b
当我们遍历到数字num[i]时，我们想知道之前是否出现过数字num[i] ^ x
如果出现过，说明存在之前的某个数prev_num，使得prev_num ^ num[i] = x
cnt数组记录了每个数字出现的次数
每次查询cnt[num[i]^x]就是查找之前有多少个数能与当前数形成异或值为x的配对
时间复杂度为O(n)，空间复杂度为O(N)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 1e5+7;
int n, x, num[N], cnt[N<<1];
ll ans;
int main() {
    fast;
    cin >> n >> x;
    for (int i = 1; i <= n; ++i) {
        cin >> num[i];
        ans += cnt[num[i]^x];
        cnt[num[i]]++;
    }
    cout << ans << '\n';
    return 0;
}