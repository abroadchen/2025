//
// Created by Psy.C on 2026/10/17.
//
/**
t[N]：存放去重后的字符集（实际是原串所有字符，稍后用途）；mn：字符集里的最小字符。
cmp(x,y) { return x>y; }：自定义比较，用于 降序排序。
find(i)：在 t（降序数组）里从大到小找第一个严格大于 s[i] 的字符并返回。因为 t 已降序排列，从尾部（最大）往回扫，找到第一个 t[j] > s[i] 即最小的大于 s[i] 的字符
读入原始长度 n、目标长度 k、原始串 s。
把 s 的所有字符拷进 t[]，同时求最小字符 mn。
sort(t, t+n, cmp)：降序排列 t，于是 t[0] 是最大字符，t[1..] 依次递减，t[n-1] 是最小字符（应等于 mn）
分支1：k > n（目标长度比原始长）
输出原串 s，再在后面补 k-n 个最小字符 mn。
逻辑：长度不足，最省事、字典序又最小的做法就是原串 + 用最小字符补足。这一定大于等于原串且长度正好 k
分支2：k == n（长度不变）
这是求字典序"下一个"字符串（长度不变）：
从右往左找第一个不是最大字符（t[0]）‍的位置 i（最大字符没法再加，改不了更大）。
对找到的 i：前缀 s[0..i-1] 不变，第 i 位换成 find(i)（比 s[i] 大的最小字符），i 之后全部填最小字符 mn。
这样得到的就是字典序紧接着原串（大于原串且尽量小）的同长度串。
若整个串所有位都是最大字符（找不到 i），则什么都不输出——实际上这种"全是最大字符"时不存在更大的同长串，正确行为应是"无解/回绕"，但本代码未处理该情形
分支3：k < n（目标长度更短）
目标长度 k < n。只保留原串前 k 位对应的"下一个串"：
只在前 k 个位置（下标 0..k-1）里，从右往左找第一个非最大字符位置 i，把第 i 位换成 find(i)（比 s[i] 大的最小字符），前 i 位原样，num 统计已输出的位数。
找到后：第 i 位输出 find(i)，此时已输出 i+1 位（num = i+1）。
若 num < k，说明前面用的位数不足 k（可能在原串前 k 位找不到可增大的位置，或已输出位不足），用 mn 补到 k 位。
目的：输出一个恰好 k 位、且字典序大于等于/大于原串前 k 为基准的字符串（本质也是"下一个"逻辑在截短版本上的应用）。这里只扫描前 k 位而不是全 n 位，是因为目标长度只有 k
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5;

bool cmp(char x, char y) { return x > y; }

int n;
char t[N];
string s;
char find(int i) {
    for (int j = n-1; j >= 0; j--)
        if (t[j] > s[i]) return t[j];
}

int k;
char mn = 'z'+1;
int main() {
    fast;
    cin >> n >> k >> s;
    for (int i = 0; i < n; i++) {
        t[i] = s[i]; mn = min(mn, s[i]);
    }
    sort(t, t+n, cmp);
    if (k > n) {
        cout << s;
        for (int i = 1; i <= k-n; i++) cout << mn;
    } else if (k == n) {
        for (int i = n-1; i >= 0; i--) {
            if (s[i] != t[0]) {
                for (int j = 0; j < i; j++) cout << s[j];
                cout << find(i);
                for (int j = i+1; j < n; j++) cout << mn;
                break;
            }
        }
    } else {
        int num = 0;
        for (int i = k-1; i >= 0; i--) {
            if (s[i] != t[0]) {
                for (int j = 0; j < i; j++, num++) cout << s[j];
                cout << find(i);
                num++;
                break;
            }
        }
        if (num < k) {
            for (int i = 1; i <= k-num; i++) cout << mn;
        }
    }
    return 0;
}