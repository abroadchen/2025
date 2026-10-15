//
// Created by Psy.C on 2026/10/15.
//
/**
读入 n（元素个数）、v1、v2（两个阈值）。
读入 n 个数，与下标组成 pair（值, 原编号）。
按数值从小到大排序（pair 默认先按 first 再按 second）。
排序是核心——较大的数放在一起能更快满足阈值
挑一段区间 [i, h] 作为第 1 组，剩下的 [h+1, n] 作为第 2 组。

t = (v1-1)/a[i].first + 1：这是向上取整 ceil(v1 / a[i].first)，即用当前数 a[i] 作"基准"时，第 1 组最少需要多少个元素才能让"元素数 × a[i]" 达到 v1（因为组内若干数，用最保守的下界估计：每个元素至少 a[i] 大小）。
h = i + t - 1：第 1 组取 a[i..h] 共 t 个元素。
边界判断 i+t-1 > n：若所需数量超出总元素，跳过。
验证第 2 组：a[h+1].first * (n-h) 表示第 2 组（[h+1,n] 共 n-h 个元素，它们都 ≥ a[h+1]）的最保守下界（元素数 × 最小元素）。若该下界 ≥ v2，则第 2 组必然满足 v2 阈值。
若成立则输出 Yes，并打印：第 1 组大小 h-i+1、第 2 组大小 n-h，以及两组各自的原始编号（a[j].second），然后结束。
这里用最坏情况估计（下界）‍来保证正确性：只要"下界 ≥ 阈值"就必然满足，属于"充分性验证"
与上一步完全对称：这次让 [i, h] 这段小值区间作为满足 v2 的一组，剩下的 [h+1, n] 作为满足 v1 的一组。
阈值互换：t=(v2-1)/a[i].first+1，验证条件是 a[h+1].first*(n-h) >= v1。
成立则输出 Yes，但输出顺序是先打印第 2 组大小 n-h、再第 1 组大小 h-i+1，并对应输出两组的编号
两轮尝试都没找到合法分割，输出 No
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ii pair<int, int>
#define int long long
using namespace std;

constexpr int N = 3e5+5;
inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}


int n, v1, v2;
ii a[N];//(数值, 原始下标)
signed main() {
    fast;
    n = rd(), v1 = rd(), v2 = rd();
    for(int i=1;i<=n;i++) a[i]={rd(),i};
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        int t=(v1-1)/a[i].first+1;
        if(i+t-1>n) continue;
        int h=i+t-1;
        if(a[h+1].first*(n-h)>=v2){
            cout<<"Yes\n";
            cout<<h-i+1<<' '<<n-h<<endl;
            for(int j=i;j<=h;j++) cout<<a[j].second<<' ';
            cout<<endl;
            for(int j=h+1;j<=n;j++) cout<<a[j].second<<' ';
            return 0;
        }
    }
    for(int i=1;i<=n;i++){
        int t=(v2-1)/a[i].first+1;
        if(i+t-1>n) continue;
        int h=i+t-1;
        if(a[h+1].first*(n-h)>=v1){
            cout<<"Yes\n";
            cout<<n-h<<' '<<h-i+1<<endl;
            for(int j=h+1;j<=n;j++) cout<<a[j].second<<' ';
            cout<<endl;
            for(int j=i;j<=h;j++) cout<<a[j].second<<' ';
            return 0;
        }
    }
    cout << "No";
    return 0;
}