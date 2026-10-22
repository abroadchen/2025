//
// Created by Psy.C on 2026/10/22.
//
/**
N = 15，实际使用下标 1..14（N-1 = 14）。
a[N]：原始输入数组；b[N]：重排后的临时数组。
mx：最终答案（最大值）。
cnt, sum, num, r, ans：辅助变量。
p[N]：置换/映射数组，记录每个下标对应的新位置
外层遍历 i = 1..14。
if (!a[i]) continue;：跳过值为 0 的元素（只对非零的 a[i] 做处理）。
memset(b,0,sizeof(b))：清空重排数组。
cnt = 0：重置映射计数。
sum = a[i]：把这一轮的"总和基准"设为 a[i]
这里构造一个置换：把数组下标重新编号。

第一段：j = i+1 .. 14 依次分配 p[j] = 1, 2, ...（即先映射 i 之后的下标）。
第二段：j = 1 .. i 依次分配 p[j] = cnt+1, ...。
综合效果：p 是一个把 {1..14} 重新排列的映射，其中 p[i+1], p[i+2], ..., p[14], p[1], ..., p[i] 依次对应 1,2,...,14——本质上是从下标 i+1 开始的"环形顺序"给每个原始下标重新编号。

也就是：原始下标 i+1→1, i+2→2, ..., 14→14-i, 1→15-i, ..., i→14。
可确证：p 把下标按"i+1..14 再 1..i"的顺序重新编号，构成一个置换
对每个下标 j（除了 j==i），把 a[j] 放到 b[p[j]]（按映射放到新位置）。
注意：a[i] 没有放进 b，因为 j==i 被跳过了。
b 中下标 p[i]（即 14 号位置）对应原始 a[i] 的位置会是空的（是 0，因为 memset 清空过）。实际上 sum 已经被单独取为 a[i]，b 里其余 13 个位置放其它 13 个数（其中一个是 0 空位）
num = sum / 14（商），r = sum % 14（余数）。
给 b[1..14] 每个元素都加 num。
再给前 r 个位置（b[1..r]）各额外加 1，把余数分配掉。
效果：b[1..14] 总和在原 sum 基础上再加了 14*num + r = sum，即每个位置均匀地加了一份，总和变成原若干数之和 + sum
遍历 j = 1..14。
取 b[p[j]]（按映射回到原始下标对应的 b 值），判断其是否为偶数（%2==0）。
若是偶数，累加到 ans。
注意这里映射回 p[j]，即统计的是按原始下标 j 来看其对应 b 值的偶数元素和
用当前这一轮算出的 ans 更新全局最大值 mx
输出所有可能轮次中的最大 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i=1; i<=n; i++)
#define ll long long
using namespace std;

constexpr int N = 15;

ll a[N], b[N], mx, cnt, sum, num, r, ans;
int p[N];
int main() {
    fast;
    rep(i,N-1) cin>>a[i];
    rep(i,N-1) {
        if (!a[i]) continue;
        memset(b,0,sizeof(b)); cnt = 0; sum = a[i];
        for (int j = i+1; j <= N-1; j++) p[j] = ++cnt;
        rep(j,i) p[j] = ++cnt;
        rep(j,N-1) if (j != i) b[p[j]] = a[j];
        num = sum/(N-1), r = sum%(N-1);
        rep(j,N-1) b[j] += num;
        rep(j,r) b[j] += 1;
        ans = 0;
        rep(j,N-1) if (b[p[j]]%2 == 0) ans += b[p[j]];
        mx = max(mx, ans);
    }
    cout << mx;
    return 0;
}