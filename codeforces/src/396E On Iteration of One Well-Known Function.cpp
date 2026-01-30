//
// Created by Psy.C on 2026/1/30.
//
/**
* pri[N]：最小质因子数组，pri[i]表示i的最小质因子
p[N]：质数数组，存储所有质数
cnt：质数计数器
mp[N]：映射数组，mp[p[i]]=i，将质数映射到其在p数组中的索引
 *
*如果pri[i]为0，说明i是质数
设置pri[i]=i，将i加入质数数组p[++cnt]
建立映射关系mp[i]=cnt
*枚举已知质数，用i和质数p[j]的乘积筛掉合数
设置pri[t]=p[j]记录最小质因子
当i%p[j]==0时break，保证线性筛的性质
 *
 *
*l[i]表示第i个质数的"剩余次数"
s[i]表示第i个质数的"冷却时间"
 *
*如果设为 t，那么下次循环时冷却时间就变成0了，可以立即操作
设为 t-1，意味着至少要经过 t-1 次循环后才能再次操作
 *
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000005
using namespace std;

int pri[N], p[N], cnt, mp[N];
void get() {
    for (int i = 2; i < N; ++i) {
        if (!pri[i]) pri[i] = i, p[++cnt] = i, mp[i] = cnt;
        for (int j = 1; j <= cnt && i * p[j] < N; ++j) {
            const int t = i * p[j];
            pri[t] = p[j];
            if (i%p[j] == 0) break;
        }
    }
}


int main() {
    fast;
    get();
    int m; cin >> m;//查询数量
    ll a[N];//系数数组
    for (int i = 1, q[N]; i <= m; ++i) {
        cin >> q[i];//读取质数
        cin >> a[mp[q[i]]];//在对应质数的位置设置系数
    }
    ll k, l[N], s[N]={}; cin >> k;
    for (int i = 1; i <= cnt; ++i) l[i] = k;
    bool flag = true;
    while (flag) {
        flag = false;
        for (int i = 1; i <= cnt; ++i) {
            if (a[i]) {
                if (!l[i]) continue;
                const ll t = min(a[i], l[i]);//本次处理的数量
                a[i] -= t, l[i] -= t;
                s[i] += t - 1, flag = true;
                int tmp = p[i] - 1;//处理p[i]-1的质因数分解
                while (tmp != 1) {
                    const int id = mp[pri[tmp]];//获取tmp最小质因子的索引
                    a[id] += t;//将t分配给p[i]-1的每个质因子对应的a数组位置
                    tmp /= pri[tmp];//除以tmp的最小质因子
                }
            } else if (s[i]) s[i]--;
            else if (l[i]) l[i]--;
        }
    }
    int ans = 0;
    for (int i = 1; i <= cnt; ++i) if (a[i]) ans++;
    cout << ans << '\n';
    for (int i = 1; i <= cnt; ++i) if (a[i]) cout << p[i] << ' ' << a[i] << '\n';
    return 0;
}