//
// Created by Psy.C on 2026/9/4.
//
/**
外层：从字符串最右端 i = len-1 开始，向前（左）切分。这保证了低位在右、高位在左的进制顺序。
内层：从右往左（j = i 递减）贪心地尽可能多取字符组成当前段：
num：当前已拼出的段值（初始 0）。
ten：十进制位权，初始 1，每并一位乘 10。
tot：已并入的位数。
循环条件要处理两种越界：
位数越界 tot > cnt：段位数超过
n
n 的十进制位数，必然导致值
≥
n
≥n，停下（其实 tot == cnt 后再多一位就超，所以条件写作 tot > cnt 利用 break 时机）；
值越界 (num + ten*(s[j]-'0')) >= n：若并入当前字符后段值
≥
n
≥n，则不合法，break。
满足条件则 num += ten*(s[j]-'0')（把当前字符作为十进制数字并入），tot++，ten *= 10。

关键的前导零处理：如果不加这段，贪心可能与"规范进制表示无前导零"规则冲突，导致不是最优解。
解释：前一层内层循环可能因为"并入后值
≥
n
≥n"而在某个位置 break，j 停在使 num < n 的最后并入位置的前一位。此时继续往左多并入一个 0 不会改变 num 的值（十进制里数字 0 在该最高位贡献为 0），却能减小这一位的权值（因为)……实际上正确性在于：判断 j+1（即 break 位置再往左一个字符）是否为 0，若是 0，说明我们可以把最高位让给一个多余的 0，从而降低该段实际贡献、进而让低位（右边）能取到更大的数，整体使最终结果更大。
具体：条件 j+1 < i && j+1 < len 保证 s[j+1] 仍在本次段内是合法位置；s[j+1]=='0' 说明并入这个 0 不影响段值。于是 j++ 把断点再往左移一个字符（吃掉这个前导 0，使右边这一位更靠右、权更低、更接近最优

i = j：把外层指针移到新的切分位置，继续处理更左边（更高位）的部分。
res += b*num：把当前段值 num 乘以其位的权重 b（当前位的
n
n 次幂）累加进结果。
b *= n：权重升到下一阶（乘
n
n），对应下一位（更高位）
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 300;

char s[N];
int main() {
    fast;
    ll n, res = 0; cin >> n >> s;
    int len = strlen(s);
    ll b = 1, cnt = 0, x = n;
    while (x) x /= 10, cnt++;//统计n的十进制位数
    for (int i = len-1; i >= 0;) {
        ll num = 0, ten = 1;
        int j, tot = 0;
        for (j = i; j >= 0; --j) {
            if (tot > cnt || (num+ten*(s[j]-'0')) >= n) break;
            num += ten*(s[j]-'0');
            tot++;
            ten *= 10;
        }
        while (j + 1 < i && j + 1 < len && s[j+1] == '0') j++;
        i = j;
        res += b*num;
        b *= n;
    }
    cout << res << '\n';
    return 0;
}