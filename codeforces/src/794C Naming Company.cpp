//
// Created by Psy.C on 2026/9/16.
//
/**
len：串长（两人字符数相等，各 len/2 或近似）。
l1/r1：s1 的左右指针。升序串里 l1 指向还没用过的最小的，r1 指向还没用过的最大的。
l2/r2：s2 的左右指针。降序串里 l2 指向最大的，r2 指向最小的。
注意初始化的取整：
r1 = (len+1)/2 - 1
r2 = len/2 - 1
这跟"轮到每个人各操作、最终长度"有关，先留个印象，后面到了取字符逻辑再对应。
l,r：结果串 str 的左右光标，交替往里填

由于是交替取，整个构造长度 len，s1 会被走到 ceil(len/2) 次、s2 走到 floor(len/2) 次。
所以 s1 只会用它的前 (len+1)/2 个和小后端的一部分；s2 只用前 len/2 个。
指针初始就把"不会被用到的"后端部分屏蔽掉——r1 从 (len+1)/2-1 开始向左走，
r2 从 len/2-1 开始向左走
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+10;
char str[N];
bool cmp(char a, char b) { return a > b; }
string s1, s2;
int main() {
    fast;
    cin >> s1 >> s2;
    ranges::sort(s1); ranges::sort(s2, cmp);
    int len = s1.length(), l1(0), l2(0), r1 = (len+1)/2-1, r2 = len/2-1, l(0), r(len-1);
    for (int i = 0; i < len; ++i) {
        if (s1[l1] >= s2[l2]) {
            if (i%2 == 0) str[r--] = s1[r1--];//轮到 s1：把自己最大的放尾部
            else str[r--] = s2[r2--];//轮到 s2：把自己最小的放尾部
        } else {
            if (i%2 == 0) str[l++] = s1[l1++];//轮到 s1：把自己最小的放头部
            else str[l++] = s2[l2++];//轮到 s2：把自己最大的放头部
        }
    }
    str[len] = '\0';
    cout << str << '\n';
    return 0;
}