//
// Created by Psy.C on 2026/2/17.
//
/**
n: 字符串数量
l: 每个字符串的长度
t: 2^l，即所有可能的位掩码数量
tag[N]: 标记数组
s[55][22]: 存储输入字符串的二维数组
ans[N]: 存储结果的数组

遍历所有字符串对(i,j)，其中i<j
计算每对字符串在哪些位置字符相同
sum表示相同字符位置构成的二进制掩码
ans[sum] |= (1ll<<i)|(1ll<<j)：在对应掩码位置记录这对字符串
从高位到低位遍历所有掩码
对于每个包含位置j的掩码i，将其信息传播到i^(1<<j)（去掉位置j）
tag[i] = n - dfs(ans[i])：计算在位置集合i上不同的字符串对数量

bit = dfs(i): 当前已选择的位置数
tot = n - tag[i]: 剩余未区分的字符串对数
x = dp[i]/(l-bit): 当前状态下的转移概率
遍历所有未选择的位置j
k = i^(1<<j): 在位置j做出选择后的新状态
a = 1.*(tag[k] - tag[i])/tot: 在该步完成的概率
更新dp[k]和p[bit+1]

dp[i]: 到达当前状态的概率
l-bit: 剩余可选择的位置数量
x = dp[i]/(l-bit): 在当前状态下选择任一未选位置的概率

tag[k] - tag[i]: 选择位置j后新增的已区分字符串对数量
tot: 当前状态下的待区分字符串对总数
a: 在此步完成（减少待区分对数）的概率
a的含义：当我们选择位置j时，有多少比例的字符串对会因此被区分

第一行：更新dp数组
x * (1 - a): 选择位置j但没有在此步完成的概率贡献
dp[k] += ...: 累加到新状态k的概率
(1 - a): 继续搜索的概率（还有字符串对未被区分）
第二行：更新p数组
x * a: 选择位置j并在此步完成的概率贡献
p[bit+1] += ...: 累加到恰好在第bit+1步完成的概率
a: 在当前步骤就完成的概率


状态定义：
dp[i]: 到达状态i的概率
p[s]: 在第s步恰好完成的概率
转移过程：
从状态i转移到状态k（增加一个选择的位置）
每次转移有两种可能结果：
继续搜索：概率为 (1-a)，更新 dp[k]
在此步完成：概率为 a，更新 p[bit+1]
概率计算：
x = dp[i]/(l-bit): 从状态i选择任一未选位置的条件概率
a: 选择特定位置j后立即完成的概率



时间复杂度：O(n²l + 2^l × l)
空间复杂度：O(2^l)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = (1<<20)+5;

///二进制表示中1的个数（汉明重量）
inline ll dfs(const ll x) {
    return x ? dfs(x>>1) + (x&1) : 0;//x右移一位的结果加上最低位
}

int n, l, t, tag[N];//在位置集合i上仍然无法区分的字符串对数量
char s[55][22];
ll ans[N];//相同位置掩码为索引的数组
void get() {
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j) {//每对字符串只比较一次，避免重复
            int sum = 0;
            for (int k = 0; k < l; ++k)//遍历字符串的每一位
                sum += (s[i][k] == s[j][k])<<k;//第k位字符相同 布尔值左移到第k位
            ans[sum] |= (1ll<<i)|(1ll<<j);//第i位和第j位为1 累积所有具有相同掩码的字符串对
        }
    for (int i = t-1; i >= 0; --i) {//保证处理掩码i时，其所有超集都已处理完毕
        for (int j = 0; j < l; ++j) if (i&(1<<j))//掩码i的第j位是否为1
            //将掩码i的第j位翻转
            ans[i^(1<<j)] |= ans[i];//将掩码i的信息传播到它的子集
        tag[i] = n - dfs(ans[i]);//剩余未被标记的字符串数量
    }
}

///到达每个状态的概率
double dp[N], p[55];//每一步完成的概率
int main() {
    fast;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> s[i];
    l = strlen(s[0]), t = 1<<l; get(); dp[0] = 1.;
    for (int i = 0; i < t; ++i) {//i: 当前状态的位掩码，表示已经选择的位置集合
        const int bit = dfs(i), tot = n - tag[i];
        const double x = dp[i]/(l-bit);
        if (tot == 0) continue;//所有字符串对都已经可以区分
        for (int j = 0; j < l; ++j) if ((i&(1<<j)) == 0) {//位置j是否尚未被选择 只考虑未选择的位置
            const int k = i^(1<<j);//新状态，是在当前状态i的基础上选择了位置j
            const double a = 1.*(tag[k] - tag[i])/tot;
            dp[k] += x * (1 - a);
            p[bit+1] += x * a;
        }
    }
    double res = 0;
    for (int i = 1; i < l+1; ++i) res += p[i] * i;//每步i的概率乘以步数i
    printf("%.9f\n", res);//期望步数
    return 0;
}