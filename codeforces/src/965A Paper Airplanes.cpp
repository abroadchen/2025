//
// Created by Psy.C on 2026/10/21.
//
/**
n / s：需要消耗总量 n，每个单元能供 s 人/次（或其他单位）——得到"总共需要的份数/次数"。
ceil(n / s)：向上取整。因为次数必须是整数（不能有半次），只要不整除就要多加一次，所以取天/次数的上界。
* k：结合系数 k（比如每份需要 k 个……），得到中间总量。
/ p：除以每包装/批次含 p 个的上限，得到需要多少包/批。
外层 ceil(...)：再向上取整，得到最终需要的整数包数/批数。
static_cast<int>(...)：把 double 结果强转成 int 输出（去掉小数部分，但此时外层 ceil 已经保证是整数）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

double k, n, s, p;
int main() {
    fast;
    cin >> k >> n >> s >> p;
    cout << static_cast<int>(ceil(ceil(n / s) * k / p));
    return 0;
}