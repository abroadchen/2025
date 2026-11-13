//
// Created by Psy.C on 2026/11/13.
//

/**
真正学会的起点..
mp 是一个哈希表，键是字符，值是该字符在当前子串中出现的次数
mid = s.length() >> 1：子串长度的一半（整除，/2）。
for (auto &val : mp | views::values)：用 C++20 的 range 视图（std::views）‍ 遍历 mp 的所有值（即每种字符的出现次数），求出最大值存入 mx。
返回 mx <= mid。
逻辑含义：判断该子串中出现次数最多的那个字符，不超过子串总长度的一半（即"没有任何一个字符占了超过一半"）。

注：由于长度为偶数时 mid = len/2、奇数时 mid = (len-1)/2（向下取整），所以条件"最多频次 ≤ len/2（向下取整）"
scanf("%*d")：读取并丢弃一个整数（用 %*d 抑制赋值），通常是题目给出的字符串长度 n，本程序不需要。
外层循环 i：子串左端点从 0 到末尾。
内层循环 j：子串右端点从 i 延伸到最后，逐步把 s[j] 追加进 now，同时更新 mp[s[j]] 的频次。
每构造出一个新子串，立刻调用 check(now, mp)：
若满足 → 输出 YES + 该子串，终止整个程序（return 0）。
不满足 → 继续扩大子串（j++）。
外层换一个起点 i 时：mp.clear() 清空频次表、now="" 重置子串
找到第一个满足条件的子串就输出并退出；全部枚举完都没找到，输出 NO
*/
#include <bits/stdc++.h>
using namespace std;

inline bool check(const string &s, unordered_map<char,int> &mp) {
    int mid = s.length()>>1, mx = 0;
    for (auto &val : mp | views::values)
        mx = max(val, mx);
    return mx <= mid;
}

string s, now;
unordered_map<char,int> mp;
int main() {
    scanf("%*d");//先读掉一个整数（题目给的 n，本程序忽略）
    cin >> s;
    int len = s.length(); len--;
    for (int i = 0; i <= len; i++) {
        mp.clear(); now = "";
        for (int j = i; j <= len; j++) {
            now += s[j]; mp[s[j]]++;
            if (check(now, mp)) {
                cout << "YES\n";
                cout << now << '\n';
                return 0;
            }
        }
    }
    cout << "NO\n";
    return 0;
}