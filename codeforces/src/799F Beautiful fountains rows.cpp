//
// Created by Psy.C on 2026/9/18.
//
/**
mt19937_64：C++11 起的 64 位梅森旋转随机数生成器。
用当前时间 chrono::high_resolution_clock 做种子，保证每次运行结果不同（防 hack）。
用途：给每条线段一个随机 64 位哈希值，后续用异或做"区间出现奇偶/是否出现"的判断
d[i]：差分数组，用于求覆盖点 i 的线段数量。
sum[i]：前缀异或数组（哈希前缀）。
A[i]：辅助动量数组
d[l]++, d[r+1]--：经典差分，之后前缀和得到每个点被覆盖的次数。
now = rnd()：为这条线段生成随机哈希。
sum[l] ^= now：在该线段起点 XOR 上哈希。
A[l] ^= now, A[r+1] ^= now：构造辅助差分（区间异或差分
把 A 变成点覆盖的异或前缀：A[i] 经过处理表示"点 i 被哪些线段覆盖的哈希异或"。
若某个点被正好一条线段覆盖，则 A[i] 等于该线段的随机哈希；被多条或 0 条则不确定/为 0。
这里 sum 会演化成"到 i 为止所有被覆盖点的哈希异或"
d[i] += d[i-1]：得到覆盖数量前缀，d[i] 现在是"点 i 被覆盖的次数"。
sum[i] ^= sum[i-1]：得到哈希前缀数组 sum[i] = 点 1..i 覆盖哈希异或。
tot/cnt 是 map，记录每个哈希值出现的位置信息。
ans += cnt[sum[i]]*i - tot[sum[i]]：统计有多少个"前缀哈希相同"的位置对——即哪些区间 [L,R] 满足 sum[L-1] == sum[R]，即区间内哈希异或为 0。
这一步实际上在做：找出所有"相邻线段哈希成对抵消"的区间对 → 由于每条线段哈希随机，哈希相同基本意味着"该线段出现偶数次/被抵消"。
深一层：如果两线段 [l1,r1] 与 [l2,r2] 对某个点恰好把哈希抵消（同一随机值出现偶数次），说明这两条在计数上"配对"了。统计这些配对数，用于后续剔除
找到不被任何线段覆盖的点（d[i]==0）的连续段，长度 t。
用公式 t*(t+1)*(t+2)/6 减去这些空段的配对组合数：因为空段（覆盖数为 0）处哈希为 0，它们之间会形成大量"哈希相同"的对，但实际上这些不是有效答案，需要剔除
输出时再减掉末尾可能残留的空段计数
*/
#include <bits/stdc++.h>
#define ull unsigned long long
using namespace std;
constexpr int N = 2e5+5;
mt19937_64 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

int n, m, d[N], t;
ull now, sum[N], A[N], ans(0);
map<ull, ull> tot, cnt;
int main() {
    n = rd(), m = rd();
    for (int i = 1, l, r; i <= n; ++i) {
        l = rd(), r = rd(), d[l]++, d[r+1]--, now = rnd();
        sum[l]^=now, A[l]^=now, A[r+1]^=now;
    }
    for (int i = 1; i <= m; ++i) A[i]^=A[i-1], sum[i]^=A[i];
    for (int i = 1; i <= m; ++i) {
        d[i] += d[i-1], sum[i] ^= sum[i-1];
        tot[sum[i]] += i-1, cnt[sum[i]]++;
        ans += cnt[sum[i]]*i - tot[sum[i]];
    }
    for (int i = 1; i <= m; ++i) {
        if (d[i] == 0) t++;
        else ans -= 1ll*t*(t+1)*(t+2)/6, t = 0;
    }
    printf("%llu", ans-1ll*t*(t+1)*(t+2)/6);
    return 0;
}