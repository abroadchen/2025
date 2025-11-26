//
// Created by Psy.C on 2025/11/26.
//
/*l[i]表示以位置i为左端点的回文串数量
r[i]表示以位置i为右端点的回文串数量
 *
*遍历每个位置i作为回文中心
第一个内层循环处理奇数长度回文（以i为中心）
a和b从i开始，分别向左右扩展
当a>=0且b<n且s[a]==s[b]时继续扩展
每找到一个回文串，增加l[a]和r[b]的计数
第二个内层循环处理偶数长度回文（以i和i+1之间为中心）
a从i开始，b从i+1开始，向两侧扩展
 *
*初始化结果变量res为0
从右到左累加l数组，使l[i]表示位置i及其右侧所有位置作为左端点的回文串总数
 *
 *第一个回文串以位置i结尾 且 第二个回文串从位置i+1开始
 *时间复杂度：O(n²) 空间复杂度：O(n)
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

typedef long long ll;

int main() {
    fast;
    string s; cin>>s;
    const auto n = s.size();
    vector<ll> l(n, 0), r(n, 0);

    for (int i = 0; i < n; ++i) {
        for (int a = i, b = i; a >= 0 && b < n && s[a] == s[b]; --a, ++b) {
            ++l[a]; ++r[b];
        }
        for (int a = i, b = i + 1; a >= 0 && b < n && s[a] == s[b]; --a, ++b) {
            ++l[a]; ++r[b];
        }
    }
    ll res(0);
    for (int i = static_cast<int>(n) - 2; i >= 0; --i) l[i] += l[i + 1];
    for (int i = 0; i < n - 1; ++i) res += r[i] * l[i + 1];
    cout << res << '\n';
    return 0;
}