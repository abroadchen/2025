//
// Created by Psy.C on 2026/10/22.
//
/**
N = 500：用于字符标记数组 p 的大小（覆盖 ASCII 字符范围）。
cmp：按字符的 ASCII 码（int(a)）‍从小到大比较，是排序用的比较器
n：字符串个数；cnt：统计到的不重复字符集合数。
mp：map<string,bool>，记录某个排序后的字符集合字符串是否出现过
读入一个字符串 s。
p[N+1]：标记每个字符是否出现过（p[字符] = 1 表示出现过）。fill(p+1, p+N, 0) 把下标 1..N-1 清零（下标 0 不清，但不影响）。
w[(N<<1)+1]：2N+1 大小的字符数组，用来顺序存放去重后得到的字符。
tp：去重后字符的个数（即 w 的有效长度）。
e：最终用于做 key 的、排序后的字符串
遍历字符串每个字符 s[j]：
若该字符尚未出现过（!p[s[j]]）：标记为已出现 p[s[j]]=1，并把它存入 w[++tp]（即添加到去重字符集合尾部）。
若已经出现过：跳过。
结果：w[1..tp] 就是这个字符串里出现的所有不同字符（顺序为首次出现顺序）
对 w[1..tp] 按 ASCII 升序排序。
把排序后的字符依次拼接成字符串 e。
排序的作用：让"相同字符集合但顺序不同"的字符串（如 abc 与 bca）归一到同一个 key（abc），从而正确去重
若 e 这个 key 在 mp 中尚未出现（mp[e]==0）：cnt++，并 mp[e]=1 标记。
若已出现过则忽略
输出不重复字符集合的个数
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 500;
bool cmp(char a, char b) { return int(a) < int(b); }

int n, cnt;
string s;
map<string, bool> mp;
int main() {
    fast;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        bool p[N+1]; fill(p+1, p+N, 0);
        char w[(N<<1)+1];
        int tp = 0;
        string e;
        for (int j = 0; j < s.length(); j++) {
            if (!p[s[j]]) { p[s[j]] = 1; w[++tp] = s[j]; }
        }
        sort(w+1, w+tp+1, cmp);
        for (int j = 1; j <= tp; j++) e += w[j];
        if (mp[e] == 0) { cnt++; mp[e] = 1; }
    }
    cout << cnt;
    return 0;
}