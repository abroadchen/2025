//
// Created by Psy.C on 2025/10/25.
//
/*
 *定义长整型别名ll，常量N=19表示最大位数，声明全局变量ans(最优解长度)、
 *ansa和ansb(最优解的两个加数)，以及数组mi用于存储10的幂次
 *
*a,b,c: 当前处理的三个数字
cura,curb: 已经构造出的两个加数
ca: 当前进位值
curl: 当前已使用的总字符数
p: 当前处理的位数位置
 *
 *剪枝：如果当前长度已经不优于已知最优解，则直接返回
 *递归终止条件：当所有原始数字都处理完且无进位时，更新最优解并返回
 *特殊情况处理：当c为0时，计算剩余部分的和，并直接处理完所有数字
 *如果当前位满足加法关系（考虑进位），则正常处理下一位数字
*如果不满足加法关系，则尝试三种操作：

在a前面添加一个数字
在b前面添加一个数字
在c前面添加一个数字
 *
 */
#include <cstdio>
using namespace std;

typedef long long ll;
const int N = 19;
ll ans, ansa, ansb, mi[N];


void dfs(ll a, ll b, ll c, ll cura, ll curb, ll ca, int curl, int p) {
    if (curl >= ans) return;
    if (a == 0 && b == 0 && c == 0 && ca == 0) {
        ans = curl;
        ansa = cura;
        ansb = curb;
        return;
    }
    if (c == 0) {
        ll s = a + b + ca; int tot(0);
        ll tmp = s;
        while (tmp) { tot++; tmp /= 10; }
        if (s == 0) tot = 0;
        dfs(0, 0, 0, cura + a * mi[p], curb + b * mi[p], 0, curl + tot, p);
        return;
    }
    if ((a + b + ca) % 10 == c % 10) {
        dfs(a / 10, b / 10, c / 10, cura + (a % 10) * mi[p], curb + (b % 10) * mi[p],
            (a % 10 + b % 10 + ca) / 10, curl, p + 1);
    } else {
        dfs(a * 10 + (c % 10 + 10 - (b % 10) - ca) % 10, b, c, cura, curb, ca, curl + 1, p);
        dfs(a, b * 10 + (c % 10 + 10 - (a % 10) - ca) % 10, c, cura, curb, ca, curl + 1, p);
        dfs(a, b, c * 10 + (a + b + ca) % 10, cura, curb, ca, curl + 1, p);
    }
}



int main() {
    int x, y, z; scanf("%d+%d=%d", &x, &y, &z);
    ans = 12; mi[0] = 1;
    for (int i = 1; i <= N - 1; ++i) mi[i] = mi[i - 1] * 10;
    dfs(x, y, z, 0, 0, 0, 0, 0);
    printf("%lld+%lld=%lld\n", ansa, ansb, ansa + ansb);
    return 0;
}