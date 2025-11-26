//
// Created by Psy.C on 2025/11/26.
//
/*
*order: 商品序号
price: 商品价格
kind: 商品类型（1表示可以享受折扣，其他值表示不可以）
 *
*相同类型时：按价格降序排列
类型1的商品优先于其他类型
其他情况返回false
 *
 *商品总数n和优惠门槛k
 *++v.begin() 跳过v[0]，从v[1]开始排序
 *
*前k-1个商品中，类型为1的商品享受5折优惠
其他商品按原价计算
 *如果第k个商品是类型1，则再减去最低价格的一半
 *
*前k-1个商品单独购买（"1 序号"）
从第k个开始的所有商品打包购买（"数量 序号列表"）
 */
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


struct node { int order, price, kind; };
bool cmp(const node a, const node b) {
    if (a.kind == b.kind) return a.price > b.price;
    if (a.kind == 1) return true;
    if (b.kind == 1) return false;
    return false;
}

int main() {
    fast;
    int n, k; cin >> n >> k;
    vector<node> v(n + 1);
    int mn = 1e9;
    for (int i = 1; i <= n; ++i) {
        v[i].order = i;
        cin >> v[i].price >> v[i].kind;
        if (v[i].price < mn) mn = v[i].price;
    }
    sort(++v.begin(), v.end(), cmp);
    double res = 0;
    for (int i = 1; i <= n; ++i) {
        if (v[i].kind == 1 && i < k) res += 0.5 * v[i].price;
        else res += v[i].price;
    }
    if (v[k].kind == 1) res -= 0.5 * mn;
    cout << fixed << setprecision(1) << res << '\n';
    for (int i = 1; i < k; ++i) cout << "1 " << v[i].order << '\n';
    cout << n - k + 1 << ' ';
    for (int i = k; i <= n; ++i) cout << v[i].order << ' ';
    cout << '\n';
    return 0;
}