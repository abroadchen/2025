//
// Created by Psy.C on 2026/1/31.
//
/**
* d：当前处理的质因数索引
x：当前的符号和倍数
y：上界
当处理完所有质因数时，计算等差数列和并返回商
递归调用：包含当前质因数和不包含当前质因数两种情况
 *
*分解整数a为质因数
将a的唯一质因数存储到p中
清空sum，如有剩余大于sqrt(a)的质因数也要加入
调用dfs计算结果
 *
 *m、n（矩形尺寸），P（模数）
*计算在圆内满足条件的点数
ii+yy <= x*x - a：确定y的上界
对每个i，找到合适的y值
调用get计算包含i的符合条件的点数
累加结果并取模
 *
*如果l=1，计算初始边界点数
ans = n*(m+1) + m*(n+1)：矩形边界上的整数点数
 *
 *
*t*(m+1)
(m+1) 是一个固定值（矩形的高度+1）
t*(m+1) 可能是计算某种基础贡献
t*(m+1) - sum
sum 是在 get 函数中计算的一个累积值
从 t*(m+1) 中减去 sum，得到净贡献
(n-i+1)
从第 i 列到第 n 列的列数：n - i + 1
这是一个水平方向的扩展因子
 *
*f(r, 0)
计算在半径为 r 的圆内满足条件的点数
即：满足 i² + j² ≤ r² 的整点 (i,j) 的数量
a = 0：没有额外修正
f(l, 1)
计算在半径为 l 的圆内满足条件的点数
a = 1：有小的修正项，使得条件变为 i² + j² ≤ l² - 1
这实际上是 i² + j² < l²，即严格小于 l²
f(r, 0) - f(l, 1)
差分计算：得到满足 l² ≤ i² + j² ≤ r² 的点数
即：在环形区域内（外圆半径r，内圆半径l）的整点数量

 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

vector<int> p;//存储质因数
ll sum;
ll dfs(const ll d, const ll x, const ll y) {
    if (d == p.size()) {
        const ll n = abs(y/x);
        //x*1, x*2, x*3, ..., x*n （其中 n = floor(|y/x|)）
        sum += n * (n + 1) / 2 * x;
        return y/x;
    }
    return dfs(d + 1, x, y) + dfs(d + 1, -x*p[d], y);//减去包含多个条件的重复计算
}

int get(ll a, const ll y) {
    p.clear();
    for (ll i = 2; i*i <= a; ++i) if (a%i==0) {
        p.push_back(static_cast<int>(i));
        while (a%i==0) a /= i;
    }
    sum = 0;
    if (a != 1) p.push_back(static_cast<int>(a));
    return static_cast<int>(dfs(0, 1, y));
}

ll m, n, P;
ll f(const ll x, const int a) {
    ll y = x, ret = 0;
    for (ll i = 1; i <= x; ++i) {
        while (y && i*i+y*y > x*x - a) y--;
        if (y >= m) y = m;
        if (i <= n && y > 0) {
            const ll t = get(i, y);//在 [1, y] 范围内，与 i 互质的数的个数
            ///对于给定的 i 值，从第 i 列到第 n 列，在垂直方向上有 t*(m+1)-sum 种有效选择的贡献。
            ///[i,n] × [1,m] 中满足条件的点数
            ret += (n-i+1)*(t*(m+1)-sum);
            ret %= P;
        }
    }
    return ret;
}


int main() {
    fast;
    cin >> n >> m;
    ll l, r, ans = 0; cin >> l >> r >> P;
    if (l == 1) ans = n * (m + 1) + m * (n + 1);
    ans %= P;
    ans += (f(r, 0) - f(l, 1)) << 1;
    while (ans < 0) ans += P;
    ans %= P;
    cout << ans << '\n';
    return 0;
}