//
// Created by Psy.C on 2026/10/31.
//

/**
真正学会的起点..
n：字符串长度。
a, b：两串 01 字符串。
四个 ll 计数变量（必须用 long long，因为答案可能超过 int 范围）：
n00：a[i]='0' 且 b[i]='0' 的位置数；
n01：a[i]='0' 且 b[i]='1' 的位置数；
n10：a[i]='1' 且 b[i]='0' 的位置数；
n11：a[i]='1' 且 b[i]='1' 的位置数
读入长度 n、字符串 a、字符串 b
遍历每个下标 i，根据 a[i] 和 b[i] 的组合，分类累加到对应的计数变量：

a[i]='0'：b[i]='0' 则 n00++，否则 n01++；
a[i]='1'：b[i]='0' 则 n10++，否则 n11++。
这一步实质上是把 (a,b) 在两串同一位置上的 4 种组合数量分别统计出来
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j) for(int i=0, i##_end_=(j); i<i##_end_; ++i)
#define ll long long
using namespace std;

int n;
string a, b;
ll n01, n10, n11, n00;
int main() {
    fast;
    cin >> n >> a >> b;
    rep(i,a.size()) {
        if (a[i] == '0') {
            if (b[i] == '0') n00++; else n01++;
        } else if (a[i] == '1') {
            if (b[i] == '0') n10++; else n11++;
        }
    }
    cout << n00*n10+n01*n10+n11*n00 << '\n';
    return 0;
}