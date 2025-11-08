//
// Created by Psy.C on 2025/11/7.
//
/*
*k[3]: 三种机器的数量限制
t[3]: 三种机器的处理时间
st[N]: 存储任务的开始时间（已排序）
v[3][N]: 三维状态数组，v[j][i]表示第j种机器处理第i个任务的完成时间
f[N]: f[i]表示处理第i个任务的最终完成时间
 *
*n: 任务数量
i, j: 循环变量
lst: 临时变量，表示上一个时间点
mx: 最大延迟时间
 *
*如果当前任务索引i大于等于机器数量k[j]
并且第j种机器处理第(i-k[j])个任务的完成时间大于lst
则更新lst为该完成时间（表示需要等待机器空闲）
 *
*完成时间 = 开始时间(lst) + 处理时间(t[j])
更新lst为当前机器的完成时间，作为下一台机器的输入
 *处理完三种机器后，f[i]存储最终完成时间lst
 *
 *计算完成时间与开始时间的差值（即延迟时间）
 */
#include <algorithm>
#include <cstdio>
#define rep(i,n) for(i=0;i<n;++i)
using namespace std;

typedef long long ll;
const int N = 100005;

ll k[3], t[3], st[N], v[3][N], f[N];

int main() {
    ll n, i, j, lst, mx;
    rep(i,3) scanf("%lld",&k[i]);
    rep(i,3) scanf("%lld",&t[i]);
    scanf("%lld",&n);
    rep(i,n) scanf("%lld",&st[i]);
    sort(st,st+n);
    rep(i,n) {
        lst = st[i];
        rep(j,3) {
            if (i >= k[j] && v[j][i-k[j]] > lst)
                lst = v[j][i-k[j]];
            v[j][i] = lst + t[j];
            lst = v[j][i];
        }
        f[i] = lst;
    }
    mx = 0;
    rep(i,n) if (f[i] - st[i] > mx) mx = f[i] - st[i];
    printf("%lld\n",mx);
    return 0;
}