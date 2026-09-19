//
// Created by Psy.C on 2026/9/19.
//
/**
k：允许的段数上限（最多分成 k 段）。
s：一长串文本，含 -（连字符）和空格作为合法的断点
遍历整行，遇到 - 或空格视为可切分点。
记录每两个断点之间的长度 i-p（存入 a[]），即不可拆分的最小块长度。
最后一段长度 i-p-1（末尾无断点需 -1）。
mx = 所有块长度的最大值。
关键理解：a[] 中每个元素是一个最小不可分割的单元（一个单词或带连字符的词），co 是单元数量
给定每段最大长度 x，贪心地把连续单元累加。
一旦 sum 超过 x 就另起一段（c++），段数计数。
返回在"每段 ≤ x"下，最少需要的段数
下界 l = mx（每段至少要能装下最长的不可分块）。
上界 r = len（整段一行）。
二分：若 get(mid) <= k（段数不超 k，可行）→ 收缩右界；否则扩大左界。
最终 l 是在段数 ≤ k 的前提下，能实现的最小的"每段最大长度"
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e6+1;

int co, a[N];
int get(int x) {
    int c = 1, sum = 0;
    for (int i = 0; i < co; ++i) {
        sum += a[i];
        if (sum > x) { c++; sum = a[i]; }
    }
    return c;
}

int k, mx;
string s;
int main() {
    scanf("%d", &k); getchar(); getline(cin, s);
    int p = -1, len = s.size(), i;
    for (i = 0; i < len; ++i) {
        if (s[i] == '-' || s[i] == ' ') {
            mx = max(mx, i-p);
            a[co++] = i - p;
            p = i;
        }
    }
    a[co++] = i - p - 1;
    mx = max(mx, i-p-1);
    int l = mx, r = len;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (get(mid) <= k) r = mid-1; else l = mid+1;
    }
    printf("%d\n", l);
    return 0;
}