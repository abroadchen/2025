//
// Created by Psy.C on 2025/11/18.
//
/*
*string(size_t n, char c) 是string类的一个构造函数
第一个参数 i 表示字符串的长度（字符个数）
第二个参数 s[0] 表示要重复的字符
 *
 */
#include <vector>
#include <iostream>
#include <string>
#define sz(x) ((int)(x).size())
using namespace std;

typedef long long ll;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    string s; int k; cin >> s >> k;
    int n = sz(s);
    ll tot = 1ll * n * (n + 1) / 2;//所有子串的总数
    if (tot < k) { cout << "No such line." << '\n'; return 0; }//不存在第k小的子串
    bool f = true;//标记字符串是否全为相同字符
    //检查是否所有字符都与第一个字符相同
    for (int i = 1; i < n; ++i) if (s[i] != s[0]) { f = false; break; }
    if (f) {//如果字符串全为相同字符，则第k小子串就是由前i个相同字符组成的字符串
        for (int i = 1; i <= n; ++i) {
            ll c = 1ll * i * n - 1ll * i * (i - 1) / 2;//前i个字符能产生的子串数量
            if (c >= k) { cout << string(i, s[0]) << '\n'; return 0; }
        }
    }
    vector<int> v;
    for (int i = 0; i < n; ++i) v.push_back(i);//初始化为0到n-1的所有索引值
    string ans;
    while (k > 0) {
        if (v.empty()) { cout << "No such line." << '\n'; return 0; }
        vector<int> nxt[26];//对应26个小写字母
        //对于v中的每个索引i，将以s[i]开头的子串的下一个位置(i+1)加入对应字母的向量中
        for (int i : v) if (i < n) nxt[s[i] - 'a'].push_back(i + 1);
        int c;
        for (c = 0; c < 26; ++c) {
            if (nxt[c].empty()) continue;//当前字母对应的向量为空
            ll cnt = 0;
            for (int j : nxt[c]) cnt += n - j + 1;//当前字母开头的所有子串数量
            if (k > cnt) k -= cnt;//减去这个数量继续查找
            else {
                ans += char('a' + c);//将数字0-25映射到字母a-z
                if (k <= sz(nxt[c])) { cout << ans << '\n'; return 0; }
                k -= nxt[c].size(); v = nxt[c]; break;
            }
        }
        if (c == 26) { cout << "No such line." << '\n'; return 0; }
    }
    cout << ans << '\n';
    return 0;
}