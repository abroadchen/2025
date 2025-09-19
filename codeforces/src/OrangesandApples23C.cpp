//
// Created by Psy.C on 2025/9/18.
//
/*
*ll: 长整型别名，用于处理大数
n: 物品对数（需要选择n个物品，总共2n-1个物品）
Ds结构体表示物品：
a, o: 两种属性值
sit: 物品的原始位置编号
read(): 读取函数
 *比较函数：按属性a升序排序，a相同时按属性o升序排序
 *
*读取物品对数n
读取所有物品信息，记录原始位置，计算两种属性的总和sa和so
 *
 *选择奇数位置的物品（第1,3,5,...个），计算它们的属性和aa和ao
 *
*检查第一种选择方案是否满足条件：
aa >= (sa+1)/2 且 ao >= (so+1)/2
 *
*如果第一种方案不满足，尝试第二种方案：
aa = sa - aa, ao = so - ao：计算偶数位置物品的属性和
遍历奇数位置的每个物品，尝试将其加入偶数位置的选择中
检查是否满足条件，如果满足则输出结果
 *
 *
 *
 *
 *
 *
 *
 */
#include <algorithm>
#include <cstdio>
using namespace std;

typedef long long ll;
int n;

struct Ds {
    int a, o, sit;
    void read() {
        scanf("%d%d", &a, &o);
    }
} p[200004];

inline bool cmp(Ds A, Ds B) {
    return A.a == B.a ? A.o < B.o : A.a < B.a;
}

int solve() {
    scanf("%d", &n);
    ll sa = 0, so = 0;
    for (int i = 1; i <= 2*n-1; ++i) {
        p[i].read();
        p[i].sit = i;
        sa += p[i].a;
        so += p[i].o;
    }
    sort(p+1, p+2*n, cmp);

    ll aa = 0, ao = 0;
    for (int i = 1; i <= 2*n-1; i += 2) {
        aa += p[i].a;
        ao += p[i].o;
    }

    if (aa >= sa / 2 + (sa % 2) && ao >= so / 2 + (so % 2)) {
        puts("YES");
        for (int i = 1; i <= 2*n-1; i += 2) {
            printf("%d ", p[i].sit);
        }
        puts("");
        return 0;
    }

    aa = sa - aa, ao = so - ao;
    for (int i = 1; i <= 2*n-1; i += 2) {
        ll na = aa + p[i].a, no = ao + p[i].o;
        if (na >= sa/2 + (sa % 2) && no >= so/2 + (so % 2)) {
            puts("YES");
            for (int j = 2; j <= 2*n-1; j += 2) {
                printf("%d ", p[j].sit);
            }
            printf("%d\n", p[i].sit);
            return 0;
        }
    }
    puts("NO");
    return 0;
}




int main() {

    int t; scanf("%d", &t);
    while(t--) {
        solve();
    }
    
    return 0;
}