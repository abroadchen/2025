//
// Created by Psy.C on 2026/9/11.
//
/**
每条记录 (a, b, h)，可理解为区间 [a, b) 或 [a, b]，权值为 h。
排序规则：先按 b（右端点）升序，b 相同再按 a 升序
按 b 升序排序后，把 b 相同的记录合并（权值相加成一个节点）。
同时把所有 a、b 值收集到 tmp 数组（用于后续离散化）
对 tmp（所有 a、b 端点）排序去重，得到 lenn 个不同值。
把每条记录的 a、b 映射为 1..lenn 的离散下标。这是坐标压缩，用于线段树索引
mx 线段树维护区间最大权值和。
update(tar, val)：单点更新，取 max。
query(L, R)：查询区间 [L, R] 的最大值

从右往左遍历，因为按 b 升序排，从后往前就是 b 从大到小）：

对当前区间 i（右端点 b 最大的一批先处理…实际这里按 b 降序处理）：
res = query(1, b-1)：查询所有右端点 < 当前 b 的已处理区间中，能接在"不与当前区间重叠"位置的最大权值和。若当前区间是 [a, b]，与它不重叠的前驱区间须满足 右端点 < a（或 < b 视题意），这里查询 [1, b-1] 的 mx。
用 res + h 作为"选当前区间时可达的最大权和"，更新到 a 位置。
更新答案 ans。
注意顺序：update(ary[i].a, ...) 把值放在 a 处；而后续 b 更大的区间用 query(1, b-1) 查 ≤ b-1 的所有位置的最大值，涵盖了这个 a ≤ b-1 的贡献（因为 a < b 时 a ≤ b-1）。这样实现了带权最大不重叠区间选法的经典 DP：

dp[区间] = h + max{ dp[前驱区间] }，前驱区间右端点 < 当前左端点
用线段树把 max 的查询优化为 O(log n)
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;
constexpr int N = 1e5+10;

struct node { ll h; int a, b; } ary[N];
bool cmp(node o1, node o2) {
    if (o1.b == o2.b) return o1.a < o2.a;
    return o1.b < o2.b;
}

ll mx[N<<3];
void push_up(int x) { mx[x] = max(mx[x<<1], mx[x<<1|1]); }

void update(int tar, ll val, int l, int r, int cur) {
    int m;
    if (l == r) {
        mx[cur] = max(mx[cur], val);
        return;
    }
    m = (l+r)>>1;
    if (tar <= m) update(tar, val, l, m, cur<<1);
    else update(tar, val, m+1, r, cur<<1|1);
    push_up(cur);
}

ll query(int L, int R, int l, int r, int cur) {
    ll res;
    int m;
    if (L <= l && r <= R) { return mx[cur]; }
    res = 0, m = (l+r)>>1;
    if (L <= m) res = max(res, query(L, R, l, m, cur<<1));
    if (R > m) res = max(res, query(L, R, m+1, r, cur<<1|1));
    return res;
}

int n, len, tmp[N<<1], lenn;
int main() {
    ll res,ans;
    int i;
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d%d%lld",&ary[i].a,&ary[i].b,&ary[i].h);
    }
    sort(ary+1,ary+n+1,cmp);
    for(i=1;i<=n;i++){
        if(len==0||ary[len].b!=ary[i].b){
            ary[++len]=ary[i];
            tmp[2*len-1]=ary[len].a,tmp[2*len]=ary[len].b;
        }
        else{
            ary[len].h+=ary[i].h;
        }
    }
    sort(tmp+1,tmp+2*len+1);
    lenn=unique(tmp+1,tmp+2*len+1)-tmp-1;
    for(i=1;i<=len;i++){
        ary[i].a=lower_bound(tmp+1,tmp+lenn+1,ary[i].a)-tmp;
        ary[i].b=lower_bound(tmp+1,tmp+lenn+1,ary[i].b)-tmp;
    }
    ans=0;
    for(i=len;i>=1;i--){
        if(ary[i].b>1){
            res=query(1,ary[i].b-1,1,lenn,1);
            update(ary[i].a,res+ary[i].h,1,lenn,1);
            ans=max(ans,res+ary[i].h);
        }
    }
    printf("%lld\n",ans);
    return 0;
}