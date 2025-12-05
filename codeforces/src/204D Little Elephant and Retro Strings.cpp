//
// Created by Psy.C on 2025/12/5.
//
/*
*初始化cnt=1, sum=0
正向遍历字符串：
如果当前字符是'W'，重置连续长度len为0，否则len递增
如果连续长度小于k，pre[i]保持前一个值
否则根据复杂公式计算pre[i]值，涉及cnt、sum和前面pre值的差分
*当索引大于等于k时：
如果第(i-k+1)个字符是'X'，则cnt和sum都翻倍并对p取模
更新sum值，加上pre数组的差分值
 *
*重置cnt=1, sum=0，初始化答案ans=0
反向遍历字符串：
如果当前字符是'B'，重置连续长度len为0，否则len递增
如果连续长度小于k，suf[i]保持后一个值
否则根据类似前缀的公式计算suf[i]值
*当索引小于等于n-k+1时：
如果第(i+k-1)个字符是'X'，cnt和sum翻倍并对p取模
更新sum值，加上suf数组的差分值
累加到最终答案ans中，使用pre数组差分值与sum的乘积
 *
*单点贡献: pre 数组是一个前缀和数组，所以相邻两项的差 pre[x] - pre[x-1] 实际上就是位置 x 处的原始值（而非累积值）
特定位置的权重: 在这个算法中，pre[i+k-2] - pre[i+k-3] 表示位置 (i+k-2) 处的某种计数或权重值
 *与sum的乘积: 这个差值随后与 sum 相乘，说明它代表了某种需要被加权计算的量
 *
*pre[i-1] + cnt - sum - pre[i-1] + pre[i-k]
= cnt - sum + pre[i-k]
*pre[i-1]: 位置(i-1)处的前缀和
cnt: 计数或乘数变量，可能代表有效组合或状态的数量
sum: 累积和，需要被减去的量（可能是为了避免重复计算）
(pre[i-1] - pre[i-k]): 这是前缀和的差值，表示从位置(i-k+1)到(i-1)的元素之和
 *
*suf[x] 表示从位置x到末尾的所有元素的累加和
因此 suf[i+k-1] - suf[i+k] 实际上就等于原数组在位置 (i+k-1) 处的单个元素值
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000005
using namespace std;

constexpr ll p = 1e9+7;
int n, k;
string s;
ll pre[N], suf[N];

int main() {
    fast;
    cin>>n>>k>>s; s = ' ' + s;//索引从1开始
    ll cnt = 1, sum = 0;
    for (int i = 1, len = 0; i <= n; ++i) {
        len = s[i] == 'W' ?  0 : len + 1;
        if (len < k) pre[i] = pre[i-1];
        else pre[i] = (pre[i-1]+cnt-sum-(pre[i-1]-pre[i-k]))%p;
        if (i >= k) {
            if (s[i-k+1] == 'X') cnt=cnt*2%p, sum=sum*2%p;
            sum += pre[i-k+1] - pre[i-k];
        }
    }
    cnt = 1, sum = 0; ll ans = 0;
    for (int i = n, len = 0; i; --i) {
        len = s[i] == 'B' ?  0 : len + 1;
        if (len < k) suf[i] = suf[i+1];
        else suf[i] = (suf[i+1]+cnt-sum-(suf[i+1]-suf[i+k]))%p;
        if (i <= n - k + 1) {
            if (s[i+k-1] == 'X') cnt=cnt*2%p, sum=sum*2%p;
            sum += suf[i+k-1] - suf[i+k];
            ans += (pre[i+k-2]-pre[i+k-3])*sum%p;
        }
    }
    cout << (ans % p + p) % p << '\n';
    return 0;
}