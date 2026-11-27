//
// Created by Psy.C on 2026/11/27.
//

/**
真正学会的起点..
n	排列长度
a[N]	差值数组（长度为 n-1）
p[N]	构造出的排列
cnt[N]	统计每个值出现次数，用于验证是否为排列
cnt[i]=0	清空计数
p[1]=mid	假设第一个数是 mid
cnt[mid]++	标记 mid 出现一次

p[i] = p[i-1] + a[i-1]	由前一项加差值得到后一项
p[i] < 1 → 返回 2	值小于 1，越界，说明首项偏小
p[i] > n → 返回 3	值大于 n，越界，说明首项偏大
cnt[p[i]]++	记录当前值出现次数
cnt[i] != 1	检查每个值 1..n 是否恰好出现一次
flg 变 0	出现重复或缺失值，则不是排列
返回 1	是合法排列
返回 2	不是排列（当作"需右移"处理）
l=1, r=n	首项取值范围 [1, n]
mid=(l+r)>>1	二分猜测中间值作为首项
t==1	合法 → 输出排列并结束
t==2	下界越界（首项太小）→ 首项要更大，l=mid+1
t==3	上界越界（首项太大）→ 首项要更小，r=mid-1
循环结束无解	输出 -1
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(int i=1;i<=n;i++)
using namespace std;

constexpr int N = 2e5+10;

int n, cnt[N], p[N], a[N];
int check(int mid) {
    rep(i,n) cnt[i] = 0;
    p[1] = mid; cnt[mid]++;
    for (int i = 2; i <= n; i++) {
        p[i] = p[i-1] + a[i-1];
        if (p[i] < 1) return 2;
        if (p[i] > n) return 3;
        cnt[p[i]]++;
    }
    int flg = 1;
    rep(i,n) if (cnt[i] != 1) { flg = 0; break; }
    return flg == 1 ? flg : 2;
}

int main() {
    fast;
    cin >> n;
    rep(i,n-1) cin >> a[i];
    int l = 1, r = n;
    while (l <= r) {
        int mid = (l+r)>>1;
        int t = check(mid);
        if (t == 1) {
            rep(i,n) cout << p[i] << ' ';
            return 0;
        }
        if (t == 2) l = mid + 1;
        else if (t == 3) r = mid - 1;
    }
    cout << "-1";
    return 0;
}