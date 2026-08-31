//
// Created by Psy.C on 2026/8/31.
//
/**
i long long 阶段 1 的循环变量（当前探测的数字 0~9 ）
a long long 系统返回的 bulls 数 （位置和数字都对的个数）
b long long 系统返回的 cows 数 （数字对但位置不对的个数）
j long long 内层循环变量
v vector<int> 隐藏数字的 multiset ：存储隐藏数字中所有数字的集合（重复出现的数字多次 push）

第一步：向系统发送探测
把当前数字 i 重复 4 次 后输出：
- i=0 → 输出 0000
- i=1 → 输出 1111
- ...
- i=9 → 输出 9999
第二步：接收系统回复
系统返回两个整数：
- a （bulls）：在刚才输出的 "iiii" 中， 位置和数字都与隐藏数字匹配 的个数。
- b （cows）：在刚才输出的 "iiii" 中， 数字存在但位置不对 的个数。
- a+b ：隐藏数字中，数字 i 总共出现的次数（位置对的 + 存在但位置不对的 = 总数）。
- 把数字 i push 进 v 数组 a+b 次。
- next_permutation 会把数组变成 下一个字典序更大的排列 。
- 返回值：如果成功生成了下一个排列，返回 true ；如果已经到了最后一个排列，返回 false ，同时数组被重置为 最小排列 。
- do-while 先执行一次（输出当前排列），然后尝试生成下一个排列
遍历 v 数组，把每个数字依次输出（无分隔符，拼成一个 4 位字符串）。
- const auto &it ：C++11 范围-based for， it 是 v 中元素的 常量引用 （不拷贝，更快，也不允许修改）。
- 输出后 endl 换行。
系统返回当前候选答案的 bulls 和 cows
- a == 4 ：4 个位置 全部 位置对且数字对（bulls=4）。
- b == 0 ：没有 cows（没有数字对但位置不对的）。
- 两者同时满足 → 候选答案就是正确的隐藏数字 ！直接 break 跳出循环
- 如果没找到答案，就调用 next_permutation 把 v 变成下一个排列。
- 返回 false 时（所有排列都试过了），循环终止
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int i, a, b, j;
vector<int> v;
signed main() {
    fast;
    for (i = 0; i < 10; ++i) {
        cout << i << i << i << i << endl;
        cin >> a >> b;
        for (j = 1; j <= a+b; ++j) v.push_back(i);
    }
    do {
        for (const auto &it : v) cout << it;
        cout << endl;
        cin >> a >> b;
        if (a == 4 && b == 0) break;
    } while (next_permutation(v.begin(), v.end()));
    return 0;
}