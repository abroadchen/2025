//
// Created by Psy.C on 2025/11/15.
//
/*
*h, m, k: 输入参数，h和m定义范围，k是某种计数条件
h1, m1, h2, m2: 起始和结束时间（小时和分钟）
lm, lh: m-1和h-1的位数
dm, dh: m-1和h-1中非零数字的个数
cm: 某种中间计算结果
 *
*计算在0到x范围内，至少包含t个连续9的数字个数
边界情况处理：负数返回0，t<=0返回x+1，t>10返回0
核心思想：形如999...9的数每隔base个数出现一次
 *
 *
*当x不为0时循环：
如果x的最后一位不是0，计数器加1
将x除以10去掉最后一位
这样遍历x的所有数位
 *
 */
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;
ll h, m, k, h1, m1, h2, m2,
lm, lh, dm, dh, cm;

//计算非零数字个数
int cntn0(ll x) {
    if (x == 0) return 0; int cnt = 0;
    while (x) {//通过不断除以10检查每一位是否为非零
        if (x % 10 != 0) cnt++;
        x /= 10;
    }
    return cnt;
}
//计算包含特定数目9的数字个数
ll cnt9(ll x, int t) {
    if (x < 0) return 0;
    if (t <= 0) return x + 1;//（因为从0到x共有x+1个数）
    if (t > 10) return 0;//（因为最多只有10位数）
    ll base(1);//计算base = 10^t，即t位数的基数
    for (int i = 0; i < t; ++i) base *= 10;
    ll ans = base - 1;//ans = 10^t - 1，这是最小的包含t个连续9的数（如t=2时为99）
    if (x < ans) return 0;//范围内没有满足条件的数
    return (x - ans) / base + 1;//形如99..9, 199..9, 299..9, ...的数每隔base个出现一次
}
//在分钟范围内计数
ll cntbr(ll l, ll r) {
    l = max(l, 0ll), r = min(r, m - 2);//限制范围在[0, m-2]之间
    if (l > r) return 0;
    return cnt9(r, k - 1) - cnt9(l - 1, k - 1);//[0,r]的个数减去[0,l-1]的个数
}

//第一类计数
ll cnta(ll l, ll r) {
    if (l > r) return 0;
    ll x = l / m, y = r / m;//计算l和r所在的"小时段" x是l所在小时，y是r所在小时
    if (x == y) return cntbr(l % m, r % m);//如果在同一小时内，直接调用cntbr计算分钟部分
    ll tot = 0;//起始小时剩余部分、中间完整小时、结束小时部分
    tot += cntbr(l % m, m - 2);//加上起始小时从l%m到m-2的计数
    tot += (y - x - 1) * cm;//每个完整小时的计数是cm
    tot += cntbr(0, r % m);//加上结束小时从0到r%m的计数
    return tot;
}
//范围内计数
ll cntar(ll l, ll r, int t) {//条件参数为t
    if (l > r) return 0;
    if (t <= 0) return r - l + 1;//返回区间长度
    return cnt9(r, t - 1) - cnt9(l - 1, t - 1);
}
//第二类计数
ll cntb(ll l, ll r) {
    if (r < m - 1) return 0;//因为最小的有效值是m-1
    ll mn;
    if (l <= m - 1) mn = 0;//起始小时为0
    else mn = (l - (m - 1) + m - 1) / m;//l对应的小时
    ll mx = (r - (m - 1)) / m;//计算结束小时
    mn = max(mn, 0ll);
    mx = min(mx, h - 2);//限制小时范围在[0, h-2]之间
    if (mn > mx) return 0;
    return cntar(mn, mx, k - dm);
}

//特殊情况计数
ll cntc(ll l, ll r) {//最大时间点是否在范围内且满足条件
    ll t = (h - 1) * m + m - 1;
    if (t >= l && t <= r && dm + dh >= k) return 1;
    return 0;
}

//总计数函数
ll cntr(ll l, ll r) {
    if (l > r) return 0;
    return cnta(l, r) + cntb(l, r) + cntc(l, r);
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> h >> m >> k;
    cin >> h1 >> m1; cin >> h2 >> m2;//读入起始时间h1:m1和结束时间h2:m2
    //计算m-1和h-1的字符串长度，即位数
    lm = to_string(m - 1).size(); lh = to_string(h - 1).size();
    dm = cntn0(m - 1); dh = cntn0(h - 1);//m-1和h-1中非零数字的个数
    if (k - 1 > lm) cm = 0;
    else cm = cnt9(m - 2, k - 1);//0到m-2范围内包含k-1个连续9的数的个数
    //将时间转换为线性表示（分钟数）
    ll l = h1*m+m1, r = h2*m+m2, tot = 0, totm = h*m;//总的时间范围
    if (l <= r) tot = cntr(l, r - 1);//根据时间范围是否跨越午夜分别处理
    else tot = cntr(l, totm - 1) + cntr(0, r - 1);//跨越了时间周期的边界，需要分两部分计算
    cout << tot << '\n';
    return 0;
}