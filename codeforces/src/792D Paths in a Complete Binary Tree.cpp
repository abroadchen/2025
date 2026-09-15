//
// Created by Psy.C on 2026/9/15.
//
/**
v[i] = 2^i。
get(x) 返回第一个 i 使得 x 能被 2^i 整除但不能被 2^(i+1) 整除
某节点的左孩子 = u - 2^(du-1)
某节点的右孩子 = u + 2^(du-1)
向上一层（父亲）的判断：
若 (u / 2^du + 1) % 4 == 2，说明 u 是右孩子，父亲 = u + 2^du；
否则 u 是左孩子，父亲 = u - 2^du。
根节点：root = (n + 1) / 2
L / R：向下移动（到左/右孩子）

只有当前节点不是根（du != 0）才能往下走（根没有孩子）。
走到孩子：du-- 表示深度 +1（因子2个数减1），然后：
L：u -= v[du]
R：u += v[du]
因为 du 已自减为 du-1，所以 v[du] = 2^(du-1)，正对应上述"左孩子 = u - 2^(du-1)、右孩子 = u + 2^(du-1)"。

U：向上移动（到父亲）

根没有父亲，u == root 时不操作。
用 (u / v[du] + 1) % 4 == 2 判断 u 是左还是右孩子：
是右孩子 → 父亲 = u + v[du]（du++ 表示深度 -1）
是左孩子 → 父亲 = u - v[du]


根 = (n+1)/2。
du = get(u) 是 u 最低位 1 的位置（末尾 0 的个数）。
u / v[du] = 把 u 末尾的 du 个 0 全部去掉 → 得到非零奇数（最低位一定是奇数位的样子）。
判断左右孩子的核心：

若 u / v[du] 模 4 等于 2（即去掉末尾0后是 ...10₂ 形式，倒数第二位是 1）→ u 是右孩子。
否则（去掉末尾0后 ...01₂，倒数第二位是 0）→ u 是左孩子
等价于判断去除末尾 0 后倒数第二位是否为 1（右孩子）
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 1e5+5;

ll v[100];
void init() {
    v[0] = 1;
    for (int i = 1; i <= 61; i++) v[i] = v[i-1]*2;
}

int get(ll x) {
    for (int i = 0; i <= 60; i++)
        if (x % v[i] == 0 && x % v[i+1] != 0)
            return i;
}

ll n, u;
char s[N];
int q;
int main() {
    init();
    scanf("%lld%d", &n, &q);
    ll root = (n + 1) / 2;
    while (q--) {
        ll u;
        scanf("%lld%s", &u, s + 1);
        int len = strlen(s + 1);
        int du = get(u);
        for (int i = 1; i <= len; i++)
            if (s[i] == 'L') {
                if (du != 0) {//不是根（根没有左右孩子，这里的层级判断）
                    du--;//进入下一层
                    u -= v[du];//到左孩子：u 减去 2^(du-1)（du 已先自减）
                }
            }
            else if (s[i] == 'R') {
                if (du != 0) {
                    du--;
                    u += v[du];//到右孩子：u 加上 2^(du-1)
                }
            }
            else {
                if (u != root) {
                    if ((u / v[du] + 1) % 4 == 2) {
                        u += v[du]; du++;
                    }
                    else {
                        u -= v[du]; du++;
                    }
                }
            }
        printf("%lld\n", u);
    }
    return 0;
}