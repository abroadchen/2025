//
// Created by Psy.C on 2026/4/25.
//
/**
n：字符串长度
a, b：题目参数
k：未使用的变量
s[N]：输入的字符串数组
ans：存储符合条件的位置

从索引1开始遍历字符串
v = s[i] - '0' 将字符转换为数字
如果当前字符是'0' (!v为真)：
计数器num增加
当计数达到或超过b时：
将当前位置i加入结果向量
重置计数器(num -= b)
如果当前字符不是'0'，重置计数器为0

输出ans.size() - a + 1个结果（即从第a个开始的所有位置）
输出这些位置的索引值
时间复杂度：O(n) 空间复杂度：O(位置数量)
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 2e5+7;
int n, a, b, k;
char s[N];
vector<int> ans;
int main() {
    ans.clear();
    cin >> n >> a >> b >> k;
    scanf("%s", s + 1);
    for (int i = 1, num = 0; i < n+1; ++i) {
        int v = s[i] - '0';
        if (!v) {
            num++;
            if (num >= b) ans.push_back(i), num -= b;
        } else num = 0;
    }
    cout << ans.size() - a + 1 << '\n';
    for (int i = 0; i < ans.size() - a + 1; ++i)
        cout << ans[i] << ' ';
    return 0;
}