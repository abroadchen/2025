//
// Created by Psy.C on 2026/2/18.
//
/**
s[4][3]: s[w][id]存储数字中因子w的个数（w=2,3），id=1,2表示两个数
a[3], b[3]: 两个矩形的边长数组（1-based）
c[4][3]: 调整操作计数
q1, q2: 两个矩形的面积

分解q1的因子2和3，结果存储在s[2][1]和s[3][1]中
分解q2的因子2和3，结果存储在s[2][2]和s[3][2]中


时间复杂度：O(log(max(a,b)))
空间复杂度：O(1)
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

int s[4][3];
void get(ll x, const int w, const int id) {//数字x中因子w的个数
    while (!(x%w)) {//x能被w整除
        s[w][id]++;
        x /= w;//去除一个因子w
    }
}

int a[3], b[3], c[4][3];
int main() {
    fast;
    cin >> a[1] >> b[1] >> a[2] >> b[2];
    const ll q1 = 1ll*a[1]*b[1], q2 = 1ll*a[2]*b[2];
    get(q1, 2, 1); get(q1, 3, 1);
    get(q2, 2, 2); get(q2, 3, 2);
    int sum = abs(s[3][1] - s[3][2]);//两个数中因子3个数的差异
    if (s[3][1] < s[3][2]) {
        c[3][2] = s[3][2] - s[3][1];//需要调整的次数到c[3][2]
        c[2][2] -= c[3][2];//调整因子2的计数
    } else if (s[3][1] > s[3][2]) {
        c[3][1] = s[3][1] - s[3][2];
        c[2][1] -= c[3][1];
    }
    const int h = abs((s[2][1] - c[2][1]) - (s[2][2] - c[2][2]));
    sum += h;//将因子2的差异加到总操作数
    if (s[2][1] - c[2][1] < s[2][2] - c[2][2]) {
        c[2][2] = h; c[2][1] = 0;
    } else {
        c[2][1] = h; c[2][2] = 0;
    }
    for (int w = 1; w <= 2; ++w)
        for (int i = 1; i <= c[3][w]; ++i) {//执行c[3][w]次操作
            if (!(a[w]%3)) a[w] = a[w]/3*2;
            else if (!(b[w]%3)) b[w] = b[w]/3*2;
        }
    for (int w = 1; w <= 2; ++w)
        for (int i = 1; i <= c[2][w]; ++i) {
            if (!(a[w]%2)) a[w] /= 2;
            else if (!(b[w]%2)) b[w] /= 2;
        }
    if (1ll*a[1]*b[1] != 1ll*a[2]*b[2]) cout << "-1";
    else cout << sum << '\n' << a[1] << ' ' << b[1] << '\n' << a[2] << ' ' << b[2];
    return 0;
}