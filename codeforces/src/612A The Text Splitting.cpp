//
// Created by Psy.C on 2026/3/24.
//
/**
n：输入字符串的长度
p：第一种分割块的大小
q：第二种分割块的大小
a：表示使用p大小块的数量
b：表示使用q大小块的数量
用i个p大小的块和j个q大小的块恰好能够组成长度为n的字符串

输出a个大小为p的块
外层循环：i从0到a-1，处理每个p大小的块
内层循环：j从0到p-1，输出第i个p大小块中的每个字符
s[p*i+j]：第i个p大小块的第j个字符位置
每输出一个完整的p大小块后换行

输出b个大小为q的块
外层循环：i从0到b-1，处理每个q大小的块
内层循环：j从0到q-1，输出第i个q大小块中的每个字符
s[p*a+q*i+j]：前a个p大小块占用位置p*a，然后第i个q大小块的第j个字符位置
每输出一个完整的q大小块后换行

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 105;
int n, p, q;
char s[N];
int main() {
    fast;
    cin >> n >> p >> q;
    cin >> s;
    int a = -1, b = -1;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= n; ++j)
            if (i*p + j*q == n) {
                a = i; b = j;
                break;
            }
    if (a == -1) cout << "-1\n";
    else {
        cout << a + b << '\n';
        for (int i = 0; i < a; ++i) {
            for (int j = 0; j < p; ++j)
                cout << s[p*i+j];
            cout << '\n';
        }
        for (int i = 0; i < b; ++i) {
            for (int j = 0; j < q; ++j)
                cout << s[p*a+q*i+j];
            cout << '\n';
        }
    }
    return 0;
}