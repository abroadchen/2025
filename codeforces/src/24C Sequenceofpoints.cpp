//
// Created by Psy.C on 2025/9/19.
//

/*
*定义Point数组a[maxn]存储n个变换点
定义Point变量m存储待变换的点
 *
*n：变换点的数量
j：变换次数
 *
*关键优化：j %= 2 * n
这是因为经过2*n次变换后，点会回到原始位置
所以只需要计算j % (2*n)次变换即可
 *
*每次变换是将点m关于点a[i%n]进行反射：
反射公式：如果点P关于点A反射得到点P'，则：
P'.x = 2 * A.x - P.x
P'.y = 2 * A.y - P.y
使用i%n确保变换点循环使用
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */
#include <cstdio>

using namespace std;

static const int maxn = 1e5+10;

struct Point {
    int x, y;
    void input() { scanf("%d%d", &x, &y); }
} a[maxn], m;

int n;
long long j;


int main() {

    scanf("%d%lld", &n, &j); m.input();

    for (int i = 0; i < n; ++i) a[i].input(); j %= 2 * n;
    for (int i = 0; i < j; ++i) {
        m.x = 2 * a[i % n].x - m.x;
        m.y = 2 * a[i % n].y - m.y;
    }

    printf("%d %d\n", m.x, m.y);
    return 0;
}