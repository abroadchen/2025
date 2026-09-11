//
// Created by Psy.C on 2026/9/11.
//

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