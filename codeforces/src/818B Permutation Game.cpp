//
// Created by Psy.C on 2026/9/22.
//
/**
a[i]：记录"从数字 i 出发"应走的步长；初始全 0 表示未确定。
b[x]：标记步长 x 是否已经分配出去
读入 n（数值范围 1..n）、m（序列长度 p 的元素个数），先读入首项 last。
对之后的每个 l，计算从 last 到 l 在环上的步数差：x = (l - last + n) % n，得到结果在 [0, n)；如果为 0，说明差为整圈，固定取 x = n（即转一整圈，步长记作 n 而非 0）。这样 x 落在 [1, n]。
含义：a[last] = x，代表"从 last 这个数出发，走 x 步到达 l"
对每条相邻关系做两重检查：

若 a[last] 已被赋过值，则这次推出的 x 必须和它完全一致，否则说明走法序列自相矛盾 → 输出 -1。
若 a[last] 还没赋值，就占用这个步长 x；前提是 x 尚未被别的位置使用（b[x]），否则同样矛盾。
这样保证了两件事：a 的每一项都确定且互不冲突，且收敛到 1..n 的排列（不会重复用同一个步长）。

最后更新 last = l，继续下一条相邻关系
遍历 i = 1..n：

若 a[i] 已确定（≠0），直接输出其值。
若 a[i] 未确定（=0），则从 now 指针起，找到第一个还没被使用过的步长 j 填入并输出，同时把 now 更新为 j+1，避免重复使用。
now 是一个贪心指针，保证前面填过的数不会被再次找到，因此最后 a[1..n] 必然恰好是 1..n 的一个排列
 */
#include <bits/stdc++.h>
using namespace std;
constexpr int N = 105;
int a[N];
bool b[N];
int main() {
    int last,x;
    int n,m;
    int l;
    scanf("%d%d",&n,&m);
    scanf("%d",&last);
    for(int i=1;i<m;++i) {
        scanf("%d",&l);
        x=l-last+n;
        x%=n;
        if(x==0) x=n;
        if(a[last]!=0) {
            if(x!=a[last]) {
                printf("-1");
                return 0;
            }
        } else {
            if(b[x]) {
                printf("-1");
                return 0;
            }
            b[x]=1;
            a[last]=x;
        }
        last=l;
    }
    int now=1;
    for(int i=1;i<=n;++i) {
        if(a[i]!=0) printf("%d ",a[i]);
        else {
            for(int j=now;j<=n;++j) {
                if(!b[j]) {
                    printf("%d ",j);
                    now=j+1;
                    break;
                }
            }
        }
    }
    return 0;
}