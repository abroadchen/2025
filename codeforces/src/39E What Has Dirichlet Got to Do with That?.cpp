//
// Created by Psy.C on 2025/9/24.
//
/*
*0：当前玩家必败
1：当前玩家必胜
2：特殊情况（Missing）
 *
 *
 */
#include <cstdio>
using namespace std;
typedef long long ll;

//判断a^b是否小于n
bool kp(ll a, ll b, ll n) {
    ll r(1);//初始化结果为1
    while (b) {//当指数b不为0时继续
        if (b & 1) r = r * a;//如果b的最低位是1，将当前a乘入结果
        if (r >= n || a >= n) return 0;//如果中间结果或底数超过n，返回false
        a = a * a;//底数平方
        b >>= 1;//指数右移一位
    }
    return 1;
}
//博弈搜索
//k1判断(a+1)^b是否小于n k2判断a^(b+1)是否小于n
int dfs(ll a, ll b, ll n) {
    bool k1 = kp(a + 1, b, n), k2 = kp(a, b + 1, n);
    if (a == 1 && !k1) return 2;//如果a=1且无法进行(a+1)^b操作，返回2（Missing状态）
    if (k2 && !dfs(a, b + 1, n)) return 1;//如果可以进行a^(b+1)操作，且对手在该状态下会输，则当前玩家赢，返回1
    if (k1 && !dfs(a + 1, b, n)) return 1;//如果可以进行(a+1)^b操作，且对手在该状态下会输，则当前玩家赢，返回1
    if (k1 && dfs(a + 1, b, n) == 2) return 2;//如果可以进行(a+1)^b操作，且该状态是Missing，则返回2
    if (k2 && dfs(a, b + 1, n) == 2) return 2;//如果可以进行a^(b+1)操作，且该状态是Missing，则返回2
    return 0;
}




int main() {

    ll a, b, n; scanf("%lld%lld%lld", &a, &b, &n);
    int t = dfs(a, b, n);
    if (t == 1) printf("Masha\n");
    else if (t == 0) printf("Stas\n");
    else printf("Missing\n");
    return 0;
}