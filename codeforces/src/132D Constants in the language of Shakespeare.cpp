//
// Created by Psy.C on 2025/11/19.
//
/*
 *
*从字符串末尾开始向前遍历：
i：当前索引，从s.size()-1开始
p：前一个处理位的奇偶性状态，初始为0
~i：等价于i >= 0，当i为-1时循环结束
s[i] & 1：获取字符对应数字的最低位（奇偶性）
p ^ s[i] & 1：检查当前位与前一位的奇偶性是否不同
如果奇偶性不同：
(p=s[i-1]&1)：更新p为前一位的奇偶性
如果p为1（奇数），操作符为'-'
如果p为0（偶数），操作符为'+'
指数为s.size()-i-1（从右往左的位数）
将{操作符, 指数}添加到ans向量中
 */
#include <vector>
#include <iostream>
using namespace std;

string s;
vector<pair<char, int>> ans;

int main() {
    cin.tie(0)->sync_with_stdio(false);
    cin >> s; s = "00" + s;
    for (int i = s.size() - 1, p = 0; ~i; --i) if (p ^ s[i] & 1) {
        ans.push_back({(p=s[i-1]&1)?'-':'+', s.size()-i-1});
    }
    cout << ans.size() << '\n';
    for (auto it : ans) cout << it.first << "2^" << it.second << '\n';
    return 0;
}