//
// Created by Psy.C on 2026/11/21.
//

/**
真正学会的起点..
n：字符串长度；k：需要连续多少个相同字符才算一个块。
a[]：长度 26（后面只用到 a[0..25]），记录每种字母形成的有效块数。
ch[]：读入的字符串
读入长度、阈值、字符串
res：当前连续相同字符的计数器（初始 1）。
从头到尾扫描字符串
特殊情况 k == 1：因为"连续 1 个相同字符"就是每一个字符本身，所以每种字母每出现一次就计 1 个块。直接对
ch[i] 对应字母的计数 +1
一般情况 k > 1：
若当前字符 ch[i] 与下一个 ch[i+1] 相同 → res++（连续长度累加）；否则 res = 1（重新开始新的一段连续段）。
若 res == k（当前连续字符达到 k 个）→ 这是一个有效块：对应字母计数 +1，res 重置为 1，并且 i += 1（跳过 1 个位置——因为 i 循环末尾还会 +1，这里多跳一个，相当于一次消费掉 k 个字符里的后 2 个，实现"k 个一组打包"）。
解释 i += 1：当前已连续 k 个字符被当作一个块，且循环正常会推进 1 步，再加 1 共前进 2，从而把这一块的内部字符跳过，从块后面继续。这样保证每个字符最多被归入一个块，不重叠计数。
对 26 个字母的块计数组 a[0..25] 按降序排序。
输出最大值 a[0]，即块数最多的那种字母能形成的有效块数量
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e6+10;
bool cmp(int a, int b) { return a > b; }

int n, k, a[N];
char ch[N];
int main() {
    fast;
    cin >> n >> k >> ch;
    int res = 1;
    for (int i = 0; i < n; i++) {
        if (k == 1) a[ch[i]-'a']++;
        else {
            if (ch[i] == ch[i+1]) res++; else res = 1;
            if (res == k) { a[ch[i]-'a']++; res = 1; i += 1; }
        }
    }
    sort(a,a+26,cmp);
    cout << a[0] << '\n';
    return 0;
}