//
// Created by Psy.C on 2026/11/7.
//

/**
真正学会的起点..
ksm(a, mod-2) 是在模素数下求 a 的乘法逆元（费马小定理：a^(p-1)≡1，故 a^(p-2) 为逆元）。
用于后面算组合数的除法取模
init 用递推求出所有阶乘及其逆元，供组合数 C(n,m) 用 O(1) 查询。
C 里对非法参数做了兜底：n<m 或 m<0 返回 0；n<0&&m<0 返回 1（特例）
数组 c[4] 统计相邻两位组成的二元组 00, 01, 10, 11 的出现次数。索引 o = b[i+1]<<1 | b[i] 正是把相邻两位编码成 0-3。
c[0b00]/c[0b01]/c[0b10]/c[0b11] 分别对应二元组 00/01/10/11 的个数。
n>L：直接走公式路线（闭合表达式）——用 c[0b10]、c[0b01] 等算两个组合数乘积，不逐位枚举。
n==L：逐位从高位向低位扫描（i=n-1 到 1）：
若当前位 b[i] 为 1，尝试把它改为 0（对应 b[i]^1），看是否仍能构成合法方案，能则累加组合数；
然后实际回退该位，更新 c；
若某二元组计数变负 → 非法，置 f=0 中断

读入两个二进制字符串 sa、sb 和四种二元组的期望计数。
L = sum(c)+1：若一个长度为 L 的串要正好包含给定的二元组计数，且任意相邻二元组独立统计，则 n 个位置有 n-1 个相邻对，故 L = 总数+1
字符串反转存储，A[1] 是最高位……这样后续按位处理。
这里给 A 做了**"减 1"（二进制减法借位），这是为了让 func(B) - func(A) 得到闭区间** [A, B] 的计数（经典的"前缀和差"技巧：count(A..B) = count(≤B) - count(≤A-1)）。
--la 压缩掉前导零
合法性剪枝：10 与 01 是某种"一进一出"的配对，若它们计数失衡（10 比 01 多超过 1，或 10 比 01 少），则整体必无合法方案，直接输出 0
最终结果 = func(B) - func(A)（取模处理负数）。
即统计满足给定二元组计数的、落在 [A, B] 区间内的二进制串数量。


只有当前上界这一位是 1 时，才能把它改成 0（改成 0 才比上界小）。
b[i]^1 把这位变成 0。
o = b[i+1]<<1 | (b[i]^1) = 高位 b[i+1]、低位 0 构成的二元组。
c[o] -= 1：因为我们把这一位改成 0，会实际用掉一个 'b[i+1]0' 型二元组的配额，先记下来
检查剩下的 01 与 10 两种"配对"二元组的配额：
c[0b01] >= c[0b10]：01 不能少于 10；
c[0b01]-c[0b10] <= 1：最多多 1。
这本质是括号序列可达性约束（类比 01=左括号位序、10=右括号位序，需保持平衡守卫），不满足则说明后面无论怎么排都无解，跳过
当 0b10 这种"分隔"配对的次数确定后，剩余 0b00 和 0b11 类元素如何在空隙中分布，等价于经典星条隔板法：
C(c[0b00]+c0-1, c0-1)：把 c0 个"分隔槽"之间分配 0b00 元素；
C(c[0b11]+c1-1, c1-1)：类似处理 0b11。
两个组合数相乘 = 在当前后缀自由位中，能凑齐剩余所有配额配比的合法排列总数，一次性加进 ans（这是把大量枚举压缩成 O(1) 组合数的关键）
恢复上一步 c[o] -= 1，因为"改成 0"只是其中一种计数方案，统计完后要还原，不能影响后续真实路径的扫描
这就是"贴住上界 b[i] 继续走"：这一位保持和上界相同（b[i] 本来就是上界的值），因此会真实消耗一个 b[i+1]b[i] 型二元组的配额。
若该配额已经用完（c[o] < 0）→ 说明即使全程贴着上界，也凑不够所需的二元组计数 → 上界本身不合法 → 置 f=0 并跳出
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+10, mod = 1e9+7;

int ksm(int a, int b=mod-2) {
    int res = 1;
    for (; b; a=1ll*a*a%mod, b>>=1)
        if (b&1) res=1ll*res*a%mod;
    return res;
}

int fac[N], ifac[N];
void init(int n=N-8) {
    for (int i = fac[0] = 1; i <= n; i++)
        fac[i] = 1ll*fac[i-1]*i%mod;
    ifac[n] = ksm(fac[n]);
    for (int i = n; i > 0; i--) ifac[i-1] = 1ll*ifac[i]*i%mod;
}
int C(int n, int m) {
    return n < 0 && m < 0 ? 1 : (n < m || m < 0 ? 0 : 1ll*fac[n]*ifac[m]%mod*ifac[n-m]%mod);
}

int L, c[4];
int func(bool b[], int n) {
    if (n < L) return 0;
    if (n > L) {
        int c0 = c[0b10], c1 = c[0b01] + 1;
        return 1ll*C(c[0b00] + c0 - 1, c0 - 1)*C(c[0b11] + c1 - 1, c1 - 1) % mod;
    }
    static int c[4]; memcpy(c, ::c, sizeof c);
    int ans = 0; bool f = 1;
    for (int i = n-1; i >= 1; i--) {
        if (b[i]) {
            int o = b[i+1]<<1|b[i]^1; c[o] -= 1;
            if (c[0b01] - c[0b10] <= 1 && c[0b01] >= c[0b10]) {
                int c0 = c[0b10] + 1, c1 = c[0b01];
                ans += 1ll*C(c[0b00] + c0 - 1, c0 - 1)*C(c[0b11] + c1 - 1, c1 - 1) % mod;
                ans %= mod;
            }
            c[o] += 1;
        }
        int o = b[i+1]<<1|b[i]; c[o] -= 1;
        if (c[o] < 0) { f = 0; break; }
    }
    if (f) (ans += 1) %= mod;
    return ans;
}

char sa[N], sb[N];
int la, lb;
bool A[N], B[N];
int main() {
    fast;
    init();
    cin >> sa >> sb >> c[0b00] >> c[0b01] >> c[0b10] >> c[0b11];
    L = c[0b00] + c[0b01] + c[0b10] + c[0b11] + 1;
    la = strlen(sa); lb = strlen(sb);
    for (int i = 0; i < la; i++) A[la-i] = sa[i] - '0';
    for (int i = 0; i < lb; i++) B[lb-i] = sb[i] - '0';
    int p = 1;
    while (A[p] == 0) A[p++] = 1; A[p] = 0;
    while (la && !A[la]) --la;
    if (c[0b10] - c[0b01] > 1 || c[0b10] < c[0b01]) {
        cout << "0\n";
        return 0;
    }
    cout << (func(B,lb) - func(A,la) + mod) % mod << '\n';
    return 0;
}