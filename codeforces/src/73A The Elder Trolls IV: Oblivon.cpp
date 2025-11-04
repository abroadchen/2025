//
// Created by Psy.C on 2025/11/3.
//
/*
 *定义常量N为3，表示三维空间
 *x,y,z表示三维空间的尺寸，m表示要放置的点的数量，a,b,c是分配给各维度的点数
 *创建一个大小为N(3)的整型向量dim，用于存储排序后的维度
 *
 *
 *将m平均分成3份赋给a，但如果a超过了最小维度减1，则将a设为最小维度减1
 *将剩余的(m-a)分成2份赋给b，但如果b超过了第二小维度减1，则将b设为第二小维度减1
 *c等于剩余的点数，但如果c超过了最大维度减1，则将c设为最大维度减1
 *
 */
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 3;
int x, y, z, m, a, b, c;
vector<int> dim(N);
ll ans;

int main() {
    scanf("%d %d %d %d", &x, &y, &z, &m);
    dim[0] = x; dim[1] = y; dim[2] = z;
    sort(dim.begin(), dim.end());

    a = m / 3;
    if (a > dim[0] - 1) a = dim[0] - 1;
    b = (m - a) / 2;
    if (b > dim[1] - 1) b = dim[1] - 1;
    c = m - a - b;
    if (c > dim[2] - 1) c = dim[2] - 1;

    ans = (1ll + a) * (1ll + b) * (1ll + c);
    printf("%lld\n", ans);
    return 0;
}