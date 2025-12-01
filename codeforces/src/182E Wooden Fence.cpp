//
// Created by Psy.C on 2025/12/1.
//
/*
*f[i][j]: 表示达到长度为i且以第j个元素结尾的方案数
f[i - a[j]][k]: 表示达到长度为(i - a[j])且以第k个元素结尾的方案数
转移过程:
我们可以通过在长度为(i - a[j])的序列后面添加一个长度为a[j]的段来构成长度为i的序列
这里的a[j]表示第j个元素的"长度"或"权重"
k表示能够转移到j状态的前驱状态
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 210
#define M 3010
#define mod 1000000007
#define rep(i,n) for(int i=1;i<=n;++i)
using namespace std;

int n, l, cnt, a[N], b[N], c[N], f[M][N], ans;

int main() {
    fast;
    cin >> n >> l;
    rep(i,n) {
        c[++cnt] = i;//cnt自增1，然后将当前i值赋给c[cnt]
        cin >> a[cnt] >> b[cnt];
        if (a[cnt] != b[cnt]) {
            c[++cnt] = i;
            a[cnt] = b[cnt - 1];//交换前一个元素的a和b值
            b[cnt] = a[cnt - 1];
        }
    }
    rep(i,l) rep(j,cnt) {
        for (int k = 0; k <= cnt; ++k) {
            if (c[j] == c[k]) continue;//种类相同
            if (!k && a[j] == i) f[i][j]++;//当前已是第一块木板
            else if (a[j] == b[k] && i > a[j])
                f[i][j] = (f[i][j] + f[i - a[j]][k]) % mod;
        }
    }
    rep(i,cnt) ans = (ans + f[l][i]) % mod;
    cout << ans;
    return 0;
}