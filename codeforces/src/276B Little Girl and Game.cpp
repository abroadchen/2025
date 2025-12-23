//
// Created by Psy.C on 2025/12/23.
//
/*
*循环遍历字符串s的每个字符
s[i] - 'a'：将字符转换为索引（'a'→0, 'b'→1, ..., 'z'→25）
cnt[s[i] - 'a']++：对应字符的计数器加1
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    string s; cin>>s; ll cnt[30] = {}, od = 0;
    for (ll i = 0; i < s.length(); ++i) cnt[s[i] - 'a']++;
    for (ll i = 0; i < 26; ++i) if (cnt[i] & 1) od++;
    if (od == 0 || od&1) cout << "First" << '\n';//出现奇数次的字符数量为0或1
    else cout << "Second" << '\n';//移除字符才能构成回文
    return 0;
}