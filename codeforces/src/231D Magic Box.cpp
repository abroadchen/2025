//
// Created by Psy.C on 2025/12/10.
//
/*
*(x, y, z): 点的三维坐标
p, q, r: 长方体在x, y, z三个维度上的最大坐标值
*a, b: y方向的权重（y<0和y>q时的代价）
c, d: z方向的权重（z<0和z>r时的代价）
e, f: x方向的权重（x<0和x>p时的代价）
 *
*a * (y < 0): 如果y坐标小于0，贡献代价a（否则贡献0）
b * (y > q): 如果y坐标大于q，贡献代价b（否则贡献0）
c * (z < 0): 如果z坐标小于0，贡献代价c（否则贡献0）
d * (z > r): 如果z坐标大于r，贡献代价d（否则贡献0）
e * (x < 0): 如果x坐标小于0，贡献代价e（否则贡献0）
f * (x > p): 如果x坐标大于p，贡献代价f（否则贡献0）
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;


int main() {
    fast;
    int x, y, z, p, q, r; cin >> x >> y >> z >> p >> q >> r;
    int a, b, c, d, e, f; cin >> a >> b >> c >> d >> e >> f;
    cout << a * (y < 0) + b * (y > q) + c * (z < 0) + d * (z > r) +
        e * (x < 0) + f * (x > p) << '\n';
    return 0;
}