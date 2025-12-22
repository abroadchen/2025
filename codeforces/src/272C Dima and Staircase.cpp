//
// Created by Psy.C on 2025/12/22.
//
/*
 *n：存储列数（墙面的宽度）
 * m：存储操作次数
 *w：临时变量，存储当前操作的列号
 *h：临时变量，存储当前方块的高度
 * l = 0：初始化为0，表示当前的基准高度（水平面高度）
 *h1 = 0：初始化为0，表示上一个方块的高度
 *
*l + h1：之前累积的基准高度加上上一个方块的高度
a[w]：第w列的基础高度（但w可能超出有效索引范围）
max(...)：取两者中的较大值作为新的基准高度
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;


int main() {
    fast;
    ll n, m, w, h, l = 0, h1 = 0; cin >> n;
    vector<ll> a(n + 1);
    for (ll i = 1; i <= n; ++i) cin >> a[i];
    cin >> m;
    while (m--) {
        cin >> w >> h;
        l = max(l + h1, a[w]);
        cout << l << '\n';//输出当前的基准高度l
        h1 = h;//更新h1为当前方块的高度h，供下次循环使用
    }
    return 0;
}