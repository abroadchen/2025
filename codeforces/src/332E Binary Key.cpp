//
// Created by Psy.C on 2026/1/10.
//
/**
 * getline 读取整行（包括空格）
 *
*循环处理 str1 的每个字符
x[i%k] += str1[i]：将字符按索引模 k 分配到不同的 x 数组元素中
ans = "2"：初始化结果为 "2"
 *
*外层循环：i 从 1 到 t
内层：清空 y 数组的前 t 个元素
将 str2 的字符按索引模 i 分配到 y 数组中
*从 k-1 到 0 倒序循环
如果 cur 不为0且 x[j] 等于 y[cur-1]：
添加 "1" 到结果
cur-- 减少计数器
否则添加 "0"
*if (!cur)：如果 cur 为0（匹配成功）
ranges::reverse(res)：反转结果字符串
ans = min(ans, res)：更新最小的字符串
*如果 ans 仍为初始值 "2"，设置为 "0"
输出结果
返回0表示程序结束
 *
 *将 str1 按 k 的周期分组到 x 数组
尝试不同的周期长度 i（从1到 min(k, l2)）
将 str2 按周期 i 分组到 y 数组
比较两组字符串，寻找匹配模式
返回最小的匹配结果字符串
 *
 */
#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2005
using namespace std;


int main() {
    fast;
    string str1, str2, x[N], y[N], ans;
    getline(cin,str1); getline(cin,str2);
    int l1 = static_cast<int>(str1.length()), l2 = static_cast<int>(str2.length());
    int k; cin >> k; int t = min(k, l2);
    for (int i = 0; i <= l1 - 1; ++i) x[i%k] += str1[i]; ans = "2";
    for (int i = 1; i <= t; ++i) {
        for (int j = 0; j <= t - 1; ++j) y[j] = "";
        for (int j = 0; j <= l2 - 1; ++j) y[j%i] += str2[j];
        int cur = i; string res;
        for (int j = k - 1; j >= 0; --j) {
            if (cur && x[j] == y[cur - 1]) res += "1", cur--; else res += "0";
        }
        if (!cur) {
            ranges::reverse(res);
            ans = min(ans, res);
        }
    }
    if (ans == "2") ans = "0";
    cout << ans << '\n';
    return 0;
}