//
// Created by Psy.C on 2025/11/21.
//
/*
*预处理：统计模式串s1中每个字母的出现次数
滑动窗口：在主串s上维护一个长度为sz1的滑动窗口
匹配检查：对于每个窗口位置，检查是否可以通过替换'?'字符来匹配模式串
关键判断：只有当窗口中每个字母的数量都不超过模式串中对应字母的数量时，才能匹配
 *时间复杂度：O(|s| × 26) = O(|s|)
 */
#include <iostream>
#define l(s) s.size()
#define rep(i,n) for(ll i=0; i<n; ++i)
using namespace std;

typedef long long ll;
const int N = 1e5+6;

ll cnt[N], tot[N], ans;
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s, s1; cin >> s >> s1;//s为主串，s1为模式串
    ll sz, sz1; sz = l(s), sz1 = l(s1);
    rep(i,sz1) tot[s1[i] - 'a']++;//统计模式串s1中每个字符的出现次数
    rep(i,sz) {
        if (s[i] != '?') cnt[s[i] - 'a']++;//如果当前字符不是'?',则在当前窗口中统计该字符
        if (i - sz1 + 1 >= 0) {//当窗口大小达到模式串长度时开始检查匹配
            ans++;//默认认为当前窗口匹配成功
            rep(j,26) if (cnt[j] > tot[j]) { ans--; break; }//如果窗口中某个字符的数量超过了模式串中该字符的数量
            if (s[i-sz1+1] != '?') cnt[s[i-sz1+1] - 'a']--;//移除窗口左边界的字符
        }
    }
    cout << ans << '\n';
    return 0;
}