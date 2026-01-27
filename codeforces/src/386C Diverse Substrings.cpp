//
// Created by Psy.C on 2026/1/27.
//
/**
* cnt[26]: 记录26个小写字母的出现次数
m: 记录当前不同字符的数量
 *
*r2 - r1: 以l为左边界，包含恰好k个不同字符的子串数量
(m1.m < k): 如果m1无法达到k个字符，则减1
累加到d[k]

在字符串中，索引是从0开始的，所以：
当前窗口左边界：str[l-1] （例如：l=3 时是 str[2]）
前一个窗口左边界：str[l-2] （例如：l=3 时是 str[1]）

 *
*外层循环：O(D)
内层滑动窗口：O(n)
总体：O(D×n)，其中D是不同字符数
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

struct node {
    int cnt[26]{}, m;
    node() { memset(cnt, 0, sizeof(cnt)); m = 0; }
};

int get(node m) {//不同字符的数量
    int ans = 0;
    for (const int i : m.cnt) ans += i > 0;//i > 0，说明该字符存在
    return ans;
}

string str;
int n;
ll d[27];//每种不同字符数的子串数量
void T(const int k) {//恰好包含k个不同字符的子串数量
    int r1 = 1, r2 = 1;//两个右边界指针
    node m1;
    m1.cnt[str[0] - 'a']++; m1.m = 1; node m2 = m1;
    for (int l = 1; l <= n; ++l) {
        if (l > 1) {//移除前一个左边界字符 从m1和m2中移除字符，如果计数变为0，则减少不同字符数m
            m1.cnt[str[l-2] - 'a']--;
            if (!m1.cnt[str[l-2] - 'a']) m1.m--;
            m2.cnt[str[l-2] - 'a']--;
            if (!m2.cnt[str[l-2] - 'a']) m2.m--;
        }
        while (m1.m < k && r1 < n) {//扩展m1直到包含k个不同字符 [l, r1)是包含恰好k个不同字符的最短子串
            if (!m1.cnt[str[r1] - 'a']) m1.m++;
            m1.cnt[str[r1++] - 'a']++;
        }
        while (m2.m <= k && r2 <= n) {//扩展m2直到包含k+1个不同字符 [l, r2)是包含k+1个不同字符的最短子串
            if (!m2.cnt[str[r2] - 'a']) m2.m++;
            m2.cnt[str[r2++] - 'a']++;
        }
        d[k] += r2 - r1 - (m1.m < k);
    }
}

int main() {
    fast;
    cin >> str;
    node M; n = static_cast<int>(str.length());
    for (int i = 0; i < n; ++i) M.cnt[str[i] - 'a']++;
    memset(d, 0, sizeof(d));
    const int D = get(M);
    for (int i = 1; i <= D; ++i) T(i);
    cout << D << '\n';
    for (int i = 1; i <= D; ++i) cout << d[i] << '\n';
    return 0;
}