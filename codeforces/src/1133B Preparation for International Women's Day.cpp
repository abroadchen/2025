//
// Created by Psy.C on 2026/11/26.
//

/**
真正学会的起点..
读入 n 个数和除数 k。
对每个数取模 x % k，统计各余数出现次数
余数 0：0 + 0 ≡ 0 (mod k)，自身成对，取 cnt[0]/2（两个一组）。
余数 k/2（仅当 k 为偶数）‍：k/2 + k/2 = k ≡ 0，也能自身配对，取 cnt[k/2]/2。
其余余数 i（1 ≤ i < k/2）‍：i 必须和 k-i 配对（因 i + (k-i) = k ≡ 0）。能配的对数取两者较小值 min(cnt[i], cnt[k-i])。
循环范围 i = 1..(k-1)/2 是为了避免重复统计（i 和 k-i 只数一次）。

最后 res 是配对的对数，res*2 是总用掉的数字个数（若题目问用掉多少个数则乘 2）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 110;
int n, k, cnt[N],res;
int main() {
    fast;
    cin >> n >> k;
    for (int i = 0, x; i < n; i++) { cin >> x; cnt[x%k]++; }
    res += cnt[0]/2;
    if (k%2 == 0) res += cnt[k/2]/2;
    for (int i = 1; i <= (k-1)/2; i++) res += min(cnt[i],cnt[k-i]);
    cout << res*2;
    return 0;
}