//
// Created by Psy.C on 2026/3/27.
//
/**
k表示当前匹配的前缀长度-1
第一个位置的失配函数值
如果完全失配或字符匹配
增加匹配长度，记录最长公共前后缀长度
失配时，向前回溯到更短的匹配位置
a[N]: 记录所有匹配位置的起始下标

时间复杂度：O(|s| + |t|)，其中|s|和|t|分别是主串和模式串的长度
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+5, M = 31;

char t[M];
int nxt[M], tl;
void get() {
    int j = 0, k = -1; nxt[0] = -1;
    while (j < tl) {
        if (k == -1 || t[j] == t[k])
            nxt[++j] = ++k;
        else k = nxt[k];
    }
}

char s[N];
int sl, a[N], cnt;
void solve() {
    get();
    int i = 0, j = 0;
    while (true) {
        while (i < sl && j < tl) {//当还有字符未比较时
            if (j == -1 || s[i] == t[j])//字符匹配或完全失配
                i++, j++;//同时前进
            else j = nxt[j];
        }
        //完整匹配成功
        if (j == tl) a[cnt++] = i - tl, j = 0;//记录匹配起始位置 重置模式串指针，继续寻找下一个匹配
        if (i >= sl) break;
    }
}

int main() {
    fast;
    cin >> s >> t; sl = strlen(s), tl = strlen(t);
    solve();
    int ans = 0;//删除计数
    for (int i = 0; i < cnt;) {
        int k = a[i] + tl - 1;//当前匹配结束位置
        i++;
        while (i < cnt && a[i] <= k)//后续重叠的匹配 下一个匹配起始位置在当前匹配范围内
            i++, ans++;//移动指针并计数需要删除的重叠匹配
    }
    cout << cnt - ans << '\n';//不重叠的独立匹配数
    return 0;
}