//
// Created by Psy.C on 2026/3/10.
//
/**
存储最多N个字符串，每个字符串最长N个字符
n: 字符串的总数

mx = 0: 初始化最大出现次数为0
外层循环：遍历每个字符串作为基准
cnt = 0: 初始化当前字符串的计数器
内层循环：将当前字符串s[i]与所有字符串比较
strcmp(s[i], s[j]) == 0: 使用C标准库函数比较两个字符串是否相等
统计与s[i]相同的字符串数量
更新最大出现次数

时间复杂度
O(n² × m)，其中n是字符串数量，m是平均字符串长度
两层嵌套循环：O(n²)
每次字符串比较：O(m)
空间复杂度
O(n × m)，用于存储所有字符串

哈希表方法: 使用map<string, int>统计每个字符串的出现次数
map<string, int> cnt;
for(int i = 0; i < n; ++i) cnt[s[i]]++;
排序方法: 先排序，然后统计连续相同字符串的个数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
int n;
unordered_map<string, int> cnt;
int main() {
    fast;
    cin >> n;
    string str;
    for (int i = 0; i < n; ++i) {
        cin >> str; cnt[str]++;
    }
    int mx = 0;
    for (auto &val: cnt | views::values)
        mx = max(mx, val);
    cout << mx << '\n';
    return 0;
}