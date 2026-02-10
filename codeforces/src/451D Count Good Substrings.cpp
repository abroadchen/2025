//
// Created by Psy.C on 2026/2/10.
//
/**
oa：偶数位置上的'a'个数
ob：偶数位置上的'b'个数
ea：奇数位置上的'a'个数
eb：奇数位置上的'b'个数

时间复杂度：O(n)，其中n是字符串长度
空间复杂度：O(1)，除了输入存储
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
using namespace std;

ll get(const ll a) { return a * (a - 1) / 2; }

char str[N];
ll oa, ob, ea, eb;

int main() {
    fast;
    cin >> str; oa = ob = ea = eb = 0;
    for (int i = 0; i < strlen(str); ++i) {
        if (str[i] == 'a') {
            if (i&1) ea++; else oa++;
        } else {
            if (i&1) eb++; else ob++;
        }
    }
    const ll anse = oa*ea + ob*eb, anso = get(oa) + get(ea) + get(ob) + get(eb) + strlen(str);
    cout << anse << ' ' << anso << '\n';
    return 0;
}