//
// Created by Psy.C on 2025/12/22.
//
/*
*k：允许的最大'0'字符数量
a[N]：前缀和数组，用于快速计算区间内'0'的数量
s1, s2：两个输入字符串
 *
*s1[0] - 'a'：获取s1第一个字符对应的字母索引(0-25)
s2[s1[0] - 'a']：获取s2中对应位置的字符
判断该字符是否为'0'，是则a[0]=1，否则a[0]=0
 *
*对于每个位置i，a[i] = a[i-1] + 当前字符映射到s2后是否为'0'
这样a[i]就表示从位置0到位置i有多少个映射为'0'的字符
 *
*如果i==j，表示只有一个字符的子串
(s2[s1[j] - 'a'] == '0') <= k：检查该字符映射后是否为'0'且不超过k限制
如果满足条件，将字符值插入set中
*a[j] - a[i]：区间(i,j]中'0'的数量
(s2[s1[i] - 'a'] == '0')：加上位置i处是否为'0'
如果超过k限制，则跳出内层循环（因为继续扩展只会增加'0'的数量）
*使用多项式滚动哈希方法计算子串哈希值
s1[j] % 3：选择三个seed中的一个
将新的哈希值插入set中
 *
 *时间复杂度：O(n²)，其中n是字符串s1的长度
 */
#include <iostream>
#include <set>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 10010
using namespace std;

constexpr ll mod = 1000000007;
ll seed[3] = { 13131, 10007, 11137 };

int main() {
    fast;
    int k, a[N];
    string s1, s2; cin >> s1 >> s2 >> k;
    a[0] = s2[s1[0] - 'a'] == '0';
    for (int i = 1; i < s1.size(); ++i)
        a[i] = a[i-1] + (s2[s1[i] - 'a'] == '0');
    set<ll> st;//存储唯一的哈希值
    for (int i = 0; i < s1.size(); ++i) {
        ll x = s1[i] - 'a' + 1;//初始化当前子串的哈希值，为起始字符的数值。
        for (int j = i; j < s1.size(); ++j) {//枚举子串的结束位置j
            if (i == j && (s2[s1[j] - 'a'] == '0') <= k)
                st.insert(s1[j] - 'a');
            else {
                if (a[j] - a[i] + (s2[s1[i] - 'a'] == '0') > k) break;
                x += (x * seed[s1[j] % 3] + s1[j] - 'a') % mod;
                st.insert(x);
            }
        }
    }
    cout << st.size() << '\n';
    return 0;
}