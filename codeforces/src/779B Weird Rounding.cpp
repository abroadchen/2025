//
// Created by Psy.C on 2026/9/12.
//
/**
读入字符串（1-indexed）和 k。
num = 整个字符串中 '0' 的个数
num==1 && len==1：整个串就一个 "0"，本身就是 0，末尾本来有 1 个零，若 k 也匹配则直接输出 0。这是 k 相关的边界（一般这种题 k≥1，这里处理单字符 "0"）。
num < k && num：0 的总个数不足 k 个，但又有 0 存在。此时无论怎么删，末尾最多 num 个零，达不到 k。这种情况贪心答案是把非零全部删除只剩... 输出 len-1（把除一个 0 外的全部删掉，就剩 0，即 len-1 次操作）。当 num == 0（全非零）时不会进入此分支（num 为假
从最右端往左扫描：
遇到 '0'：cnt++（已经收集到的末尾零计数）。
遇到非零：ans++（需要删除这个非零字符）。
当 cnt >= k（末尾已经凑够 k 个零）时停止。
最终 ans 就是最少删除操作次数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2e5+10;
char ch[N];
int k, ans;
int main() {
    fast;
    scanf("%s%d", ch+1, &k);
    int len = strlen(ch+1), num(0);
    for (int i = 1; i <= len; ++i)
        if (ch[i] == '0') num++;
    if (num == 1 && len == 1) { cout << "0\n"; return 0; }
    if (num < k && num) { cout << len-1 << '\n'; return 0; }
    for (int i = len, cnt = 0; i; --i) {
        if (ch[i] == '0') ++cnt; else ++ans;
        if (cnt >= k) break;
    }
    cout << ans << '\n';
    return 0;
}