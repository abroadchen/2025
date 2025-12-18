//
// Created by Psy.C on 2025/12/18.
//
/*
*d[26]：差异数组，记录每种字符在a和b中的数量差异（a中数量-b中数量）
c[26]：计数数组，记录字符串a中每种字符的剩余数量
ans：记录最少需要替换的字符数
n：字符串长度
 *
*对每个位置i：
++c[a[i] - 'A']：统计字符a[i]在字符串a中的数量
++d[a[i] - 'A']：a中字符a[i]数量+1
--d[b[i] - 'A']：b中字符b[i]数量+1（等价于a中该字符数量-1）
最终d[i]表示字符('A'+i)在a中比在b中多出的数量
 *
*对于每种字符，如果在a中比b中多(d[i]>0)，则需要替换掉多余的
ans累加所有正的差值，得到最少需要替换的字符数
输出最少替换次数
 *
*k：指向当前字典序最小的、在a中数量不足的字符
内层while循环：找到第一个d[k]<0的字符（即在a中数量不足，需要补充的字符）
 *
* 条件：d[a[i] - 'A'] > 0 且满足以下之一：
a[i] - 'A' > k：当前字符字典序大于需要的字符
c[a[i] - 'A'] == d[a[i] - 'A']：当前字符a[i]在后面不再出现
如果满足条件：
--d[a[i] - 'A']：减少该字符的多余数量
--c[a[i] - 'A']：减少该字符的剩余计数
++d[k]：增加需要字符的数量
a[i] = static_cast<char>('A' + k)：将当前位置替换为需要的字符
否则：
--c[a[i] - 'A']：只是减少剩余计数
 *输出变换后的字符串a
 *
*时间复杂度：O(n)
空间复杂度：O(1)

 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    fast;
    string a, b; cin >> a >> b;
    int d[26] = {}, c[26] = {}, ans = 0;
    const int n = static_cast<int>(a.size());
    for (int i = 0; i < n; ++i) {
        ++c[a[i] - 'A']; ++d[a[i] - 'A']; --d[b[i] - 'A'];
    }
    for (int i : d) ans += max(i, 0);
    cout << ans << '\n';
    int k = 0;
    for (int i = 0; i < n; ++i) {
        while (k < 26 && d[k] >= 0) ++k;
        if (d[a[i] - 'A'] > 0 && (a[i] - 'A' > k ||
            c[a[i] - 'A'] == d[a[i] - 'A'])) {
            --d[a[i] - 'A']; --c[a[i] - 'A'];
            ++d[k];
            a[i] = static_cast<char>('A' + k);
        } else --c[a[i] - 'A'];
    }
    cout << a << '\n';
    return 0;
}