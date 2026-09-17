//
// Created by Psy.C on 2026/9/17.
//
/**
把字符串 s 向左轮转（旋转）k 位。
s.substr(k, len-k)：取从下标 k 到末尾的部分（长度 len-k）。
s.substr(0, k)：取开头 k 个字符。
拼接 → 得到 s 左移 k 位的结果。
a[i]：存储 n 个字符串

读入 n 个字符串。
flag = 1：标记是否可行。
ans = inf：记录最小总操作数。
以第一个字符串 a[0] 的长度作为所有字符串的统一长度 len（题目约定所有串等长）
外层枚举 k：假设最终所有字符串都变成 a[0] 旋转 k 位后的结果 tmp。
对每个目标 tmp，计算所有串变成 tmp 的最小总操作数 sum，取最小值
对第 i 个串，尝试所有可能的旋转位移 j（0..len-1）。
计算 get(a[i], j, len) 即左移 j 位，若等于目标 tmp，则代价累积 j，break。
若遍历完所有 j 都没有一个位移能让它变成 tmp（j == len），说明该串无法变成目标 → flag = 0，整体不可行
若任何一个串无法旋转到某个目标，flag=0，直接输出 -1。
否则输出最小总代价 ans
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

string get(const string& s, int k, int len) {
    return s.substr(k, len-k) + s.substr(0, k);
}
constexpr int N = 55, inf = 0x7fffffff;
string a[N];
int main() {
    fast;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    int flag = 1, ans = inf;
    string t1 = a[0];
    int len = t1.length();
    for (int k = 0; k < len; ++k) {
        string tmp = get(t1, k, len);//把第 1 个串旋转 k 位，作为"目标串"
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int j = 0;
            string tt;
            for (; j < len; ++j) {
                tt = get(a[i], j, len);
                if (tt == tmp) { sum += j; break; }
            }
            if (j == len) { flag = 0; break; }
        }
        if (!flag) break;
        ans = min(ans, sum);
    }
    if (!flag) cout << "-1\n"; else cout << ans << '\n';
    return 0;
}