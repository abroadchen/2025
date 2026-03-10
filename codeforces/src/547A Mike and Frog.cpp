//
// Created by Psy.C on 2026/3/8.
//
/**
计算从h开始，通过变换h = (h*x + y) % mod，需要多少步才能到达a
flag：特殊标志，当为true且h==a时返回0
最多迭代mod次，防止无限循环

找到变换序列中的循环点
st[N]：状态数组，记录访问状态
cnt：访问计数器
返回循环的起始点

计算向上取整：ceil(x/y)
如果x%y不为0，加1

(h1,a1,x1,y11) 和 (h2,a2,x2,y2)
分别代表两个线性同余序列的参数

计算分别到达目标的步数
如果任一序列无法到达目标，输出-1
p1, p2：两个序列的循环起始点
r1, r2：两个序列的循环长度
f1, f2：从起点到循环点的步数
d1, d2：在循环内部还需要的步数

如果两个序列都在循环前就到达目标，比较步数是否相等
如果其中一个序列在循环前到达目标，检查另一个序列能否在相同步数到达
如果两个序列都在循环中到达目标
使用中国剩余定理的思想
枚举第一个序列在循环中的位置，检查是否与第二个序列匹配


++cnt：增加计数器，确保本次搜索使用的标记值与其他搜索不同
st[h] = cnt：标记初始状态h为当前搜索过程(cnt)
h = (h*x + y) % mod：执行线性同余变换
if (st[h] == cnt) return h;：如果当前h已经被本次搜索标记过，说明找到了循环点，返回
st[h] = cnt;：标记当前状态为本次搜索

p = f1 + d1：p是序列1到达目标所需的总步数（循环前步数 + 循环内步数）
这是在序列1的循环中的一个可能解
将p调整为不小于f2的值
因为序列2需要至少f2步才能进入循环
每次增加r1（序列1的循环长度），保持序列1仍处于目标状态
循环最多r2+1次（保证覆盖所有可能的余数情况）
每次p增加r1（保持序列1处于目标状态）
检查条件：(p - f2) % r2 == d2
p - f2：从序列2进入循环后的步数
(p - f2) % r2：在这个循环中的位置
d2：序列2需要在循环中的目标位置


 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int mod;
int get(int h, int a, int x, int y, bool flag=false) {
    int cnt = 0;
    if (flag && h == a) return 0;
    do {
        cnt++;
        h = (h*x + y) % mod;
        if (cnt > mod) return -1;
    } while (h != a);
    return cnt;
}
constexpr int N = 1e6;
int st[N], cnt;
int find(int h, int x, int y) {
    ++cnt;
    st[h] = cnt;
    while (true) {
        h = (h*x + y) % mod;
        if (st[h] == cnt) return h;
        st[h] = cnt;
    }
}

int calc(int x, int y) {
    return x/y + 1ll*(bool(x%y));
}

int h1, a1, x1, y11, h2, a2, x2, y2;
signed main() {
    fast;
    cin >> mod >> h1 >> a1 >> x1 >> y11 >> h2 >> a2 >> x2 >> y2;
    int n1 = get(h1, a1, x1, y11), n2 = get(h2, a2, x2, y2);
    if (n1 == -1 || n2 == -1) { cout << -1 << '\n'; return 0; }
    int p1 = find(h1, x1, y11), p2 = find(h2, x2, y2);
    int r1 = get(p1, p1, x1, y11), r2 = get(p2, p2, x2, y2);
    int f1 = get(h1, p1, x1, y11, true), f2 = get(h2, p2, x2, y2, true);
    int d1 = n1 - f1, d2 = n2 - f2;
    if (d1 < 0 && d2 < 0) {
        if (n1 == n2) cout << n1 << '\n';
        else cout << -1 << '\n';
        return 0;
    }
    if (d1 < 0) {
        if (n1 - f2 >= 0 && (n1 - f2) % r2 == d2) cout << n1 << '\n';
        else cout << -1 << '\n';
        return 0;
    }
    if (d2 < 0) {
        if (n2 - f1 >= 0 && (n2 - f1) % r1 == d1) cout << n2 << '\n';
        else cout << -1 << '\n';
        return 0;
    }
    int p = f1 + d1;
    while (p < f2) p += r1;
    for (int i = 1; i <= r2 + 1; ++i, p += r1)
        if ((p - f2) % r2 == d2) {
            cout << p << '\n';
            return 0;
        }
    cout << -1 << '\n';
    return 0;
}