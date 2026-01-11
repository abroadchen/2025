//
// Created by Psy.C on 2026/1/11.
//
/**
* num[j] > 1 意味着：
a[j] 至少有2个质因子
a[j] 不是质数（质数只有1个质因子）
a[j] 可以进一步分解为多个质因子的乘积
 */
#include <algorithm>
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 1000007
using namespace std;

bool pri[N];//每个数是否为素数
void init() {
    memset(pri, true, sizeof(pri));//初始化所有数为素数
    pri[1] = pri[0] = false;//0和1不是素数
    for (ll i = 2; i < N; ++i) if (pri[i]) {
        for (ll j = i * i; j < N; j += i) pri[j] = false;//所有倍数标记为非素数
    }
}

ll num[20];//每个数的质因子总数
ll get(ll x) {//x的质因子总数（包括重复的）
    ll ret = 0;
    for (ll i = 2; i * i <= x; ++i) {//遍历到√x，检查是否为x的质因子
        if (x % i) continue;
        if (!pri[i]) continue;
        while (x % i == 0) { x /= i; ret++; }//计算质因子i的个数
    }
    if (x > 1) ret++;//本身是一个质因子
    return ret;
}


int n;
ll ans, a[30];//输入的数组元素
bool mark[10];//哪些元素已被处理
void solve(const int x) {
    if (!mark[x]) ans++;//未被标记，答案加1
    ll t = a[x];//：复制当前元素值
    while (true) {
        int j = -1;
        for (int i = x + 1; i < n; ++i) {
            if (mark[i]) continue;
            if (t % a[i]) continue;
            //当前候选元素的质因子数量<当前考察元素的质因子数量
            if (j == -1 || num[j] < num[i]) j = i;//元素 i 拥有更多的质因子，更"有价值"
        }
        if (j == -1) break;
        t /= a[j];//除以找到的元素
        mark[j] = true;
        if (num[j] > 1) ans++;
    }
    if (!mark[x] && num[x] > 1) ans += num[x];
    mark[x] = true;
}



int main() {
    fast;
    init();
    cin >> n; ans = 0;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n, [](const ll a, const ll b) { return a > b; });
    for (int i = 0; i < n; ++i) num[i] = get(a[i]);
    memset(mark, false, sizeof(mark));
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (!mark[i]) cnt++;
        solve(i);//对每个元素调用solve函数处理
    }
    if (cnt > 1) ans++;//有多于一个独立的组
    cout << ans << '\n';
    return 0;
}