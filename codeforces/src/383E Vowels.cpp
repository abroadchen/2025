//
// Created by Psy.C on 2026/1/27.
//
/**
* f[1<<24]={}: 定义大小为 2^24 的整型数组 f，全部初始化为 0
1<<24 等于 16777216，足够存储24个小写字母的所有子集
f[mask] 表示字符集为 mask 的字符串个数
 * s，用于临时存储输入的字符串
 * x 用于存储掩码
 *
*遍历字符串 s 中的每个字符 c
c-'a': 将字符转换为数字索引（a->0, b->1, ..., z->25）
1<<(c-'a'): 创建第 (c-'a') 位为1的掩码
x |= 1<<(c-'a'): 将该位设置为1，表示字符 c 在字符串中存在
最终 x 表示字符串中所有字符组成的集合的二进制掩码
*将对应掩码 x 的计数加1
统计具有相同字符集的字符串数量
 *
*外层循环：枚举每一位 j（从0到23，对应字母a到x）
内层循环：枚举所有可能的掩码 i（从1到 2^24-1）
*i>>j&1: 检查掩码 i 的第 j 位是否为1
如果第 j 位为1，则执行以下操作：
i^1<<j: 将掩码 i 的第 j 位翻转（原来是1变成0）
f[i] += f[i^1<<j]: 将不包含第j位的子集的计数加到包含第j位的集合上
这一步是SOS DP的核心，计算每个掩码包含的所有子集的总和
 *
*遍历数组 f 中的每个计数值 i
n - i: 表示与当前字符集不冲突的字符串数量
(n - i) * (n - i): 计算配对数
ans ^= (n - i) * (n - i): 对结果进行异或运算
 *
 *时间复杂度：O(24 * 2^24)，空间复杂度：O(2^24)
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int n, f[1<<24]={}; cin >> n;
    string s;
    for (int i = 1, x; i <= n; ++i) {
        cin >> s, x = 0;
        for (const auto c : s) x |= 1<<(c-'a');
        f[x]++;
    }
    for (int j = 0; j < 24; ++j) for (int i = 1; i < 1<<24; ++i) {
        if (i>>j&1) f[i] += f[i^1<<j];
    }
    int ans = 0;
    for (const int i : f) ans ^= (n - i) * (n - i);
    cout << ans << '\n';
    return 0;
}