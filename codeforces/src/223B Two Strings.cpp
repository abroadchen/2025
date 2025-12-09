//
// Created by Psy.C on 2025/12/8.
//
/*
*正向遍历字符串s：
如果当前字符与t中第j个字符匹配，则记录该字符在t中的位置，并递增j
pre[i]记录s中第i个字符在t中最远匹配到的位
 *重置j为t的最后一个索引位置
 *
*反向遍历字符串s：
如果当前字符与t中第j个字符匹配，则记录相对位置，并递减j
suf[i]记录s中第i个字符从后往前能匹配到的位置信息
 *
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 500005
using namespace std;

string s, t;
int pos[N], pre[N], suf[N];

int main() {
    fast;
    cin>>s>>t;
    const int ls = static_cast<int>(s.length()),
    lt = static_cast<int>(t.length()); int j = 0;
    memset(pos,0,sizeof(pos));
    for (int i = 0; i < ls; ++i) {
        if (j < lt && s[i] == t[j]) { pos[s[i]] = j; j++; }
        pre[i] = pos[s[i]];
    }
    j = lt - 1;
    memset(pos,0,sizeof(pos));
    for (int i = ls - 1; i >= 0; --i) {
        if (j >= 0 && s[i] == t[j]) { pos[s[i]] = lt - j; j--; }
        suf[i] = pos[s[i]];
    }
    for (int i = 0; i < ls; ++i) {
        if (pre[i] + suf[i] < lt) { cout << "No\n"; return 0; }
    }
    cout << "Yes\n";
    return 0;
}