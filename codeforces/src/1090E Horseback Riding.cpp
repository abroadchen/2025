//
// Created by Psy.C on 2026/11/17.
//

/**
真正学会的起点..
N：答案数组 ans 的容量上限。
node：一次三元查询的记录，x,y,z 是查询的三个下标，s 是这次查询返回的和。
a[20]：最多存 10 条记录，因为一个 5 元素窗口里有 C(5,3)=10 组三元查询
枚举窗口内 5 个下标的全部 C(5,3)=10 个三元组，向交互系统发出 ? i j k，把返回的和存入 a[num].s，同时记录下标
按查询返回的和从小到大对 10 条记录排序。
取排序后的第 1、第 9、第 10 个和
用“相等即折叠”的三目嵌套来猜 s15
代数拼凑出另两个“和”，再求 s135 = (s13+s15+s35)/2
用这些“和”做差值反推出 5 个元素的值
把算出的 5 个值排序存回。这一步会丢失“哪个值属于哪个下标”的对应关系，靠后面暴力重排来找回
对每条查询记录，取三元组里最小+最大，判断是否等于该次查询返回的和 a[i].s
校验失败就 next_permutation 暴力枚举 5 个数的全部排列（最多 5!=120 种）来重新尝试，直到某排列“碰巧满足”

*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,j,k) for (int i=j; i<=k; ++i)
#define int long long
using namespace std;

constexpr int N = 6e5+5;
struct node { int x, y, z, s; } a[20];

int ans[N];
void solve(int l, int r) {
    int num = 0;
    rep(i,l,r) rep(j,i+1,r) rep(k,j+1,r) {
        cout << "? " << i << ' ' << j << ' ' << k << endl;
        cin >> a[++num].s;
        a[num].x = i, a[num].y = j, a[num].z = k;
    }
    sort(a+1,a+num+1,[&](node x, node y) { return x.s < y.s; });
    int s13 = a[1].s, s25 = a[9].s, s35 = a[10].s;
    int s15 = a[4].s == a[5].s ? a[4].s : a[5].s == a[6].s ? a[5].s : a[4].s;
    int s24 = a[4].s + a[5].s + a[6].s + a[7].s - s15*3;
    int s135 = (s13+s15+s35)/2;
    ans[l] = s135 - s35; ans[l+2] = s135 - s15; ans[l+4] = s135 - s13;
    ans[l+1] = s25 - ans[l+4]; ans[l+3] = s24 - ans[l+1];
    sort(ans+l, ans+l+5);
    for (;;) {
        int flg = 1;
        rep(i,1,num) if (min({ans[a[i].x],ans[a[i].y], ans[a[i].z]})+
            max({ans[a[i].x],ans[a[i].y],ans[a[i].z]}) != a[i].s) { flg = 0; break; }
        if (flg) return;
        next_permutation(ans+l,ans+l+5);
    }
}


int n;
signed main() {
    fast;
    cin >> n;
    for (int i = 1; i+4 < n; i += 5) solve(i,i+4);
    solve(n-4,n);
    cout << "! ";
    rep(i,1,n) cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}
