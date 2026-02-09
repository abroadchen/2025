//
// Created by Psy.C on 2026/2/9.
//
///s[i] - 'a'：将字符转换为索引（'a'=0, 'b'=1, ..., 'z'=25）
/*
检查t是否是s的子序列（按顺序匹配）
i遍历s，j遍历t
当s[i] == t[j]时，j前进
当j达到lt时，说明t是s的子序列，aut ^= 1将aut翻转为0，跳出循环

arr &= cnt[i] == 0：如果所有cnt[i]都等于0，arr为true
表示s和t的字符完全相同（数量也相同）
both &= cnt[i] >= 0：如果所有cnt[i]都非负，both为true
表示s中每个字符的数量都不少于t中的数量

automaton：可以通过删除s中某些字符得到t
array：可以通过重新排列s得到t
both：既可以删除也可以重排
need tree：以上方法都不行

时间复杂度：O(|s| + |t|) 空间复杂度：O(1)（固定大小数组）
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 110
using namespace std;

char s[N], t[N];
int cnt[N];

void out() {
    const int ls = strlen(s), lt = strlen(t);
    memset(cnt, 0, sizeof cnt);
    for (int i = 0; i < ls; ++i) cnt[s[i] - 'a']++;
    for (int i = 0; i < lt; ++i) cnt[t[i] - 'a']--;//减去t中字符的出现次数
    int arr, both; int aut = arr = both = 1;
    for (int i = 0, j = 0; i < ls; ++i) {
        if (s[i] == t[j]) j++;
        if (j == lt) { aut ^= 1; break; }
    }
    for (int i = 0; i < 26; ++i) {
        arr &= cnt[i] == 0;
        both &= cnt[i] >= 0;
    }
    if (!aut) cout << "automaton\n";//t是s的子序列
    else if (arr) cout << "array\n";//字符完全相同且t不是s的子序列
    else if (both) cout << "both\n";//s包含t的所有字符且t不是s的子序列
    else cout << "need tree\n";
}

int main() {
    fast;
    cin >> s >> t; out();
    return 0;
}