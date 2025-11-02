//
// Created by Psy.C on 2025/11/2.
//
/*
 *
*将读取的数值t加到数组f的相应位置
i%3计算i除以3的余数，结果只能是0、1或2
这样实现了将输入的数字按顺序累加到f[0]、f[1]、f[2]中
 *
*检查f[0]、f[1]、f[2]中是否有任何一个不为0
如果至少有一个不为0，则输出"NO"
如果全部为0，则输出"YES"
 *
 */
#include <cstdio>
using namespace std;

int f[3] = {0}, t(0), n;

int main() {
    scanf("%d", &n);
    for (int i = 0; i < 3 * n; ++i) {
        scanf("%d", &t);
        f[i%3] += t;
    }
    (f[0] || f[1] || f[2]) ? printf("NO") : printf("YES");
    return 0;
}