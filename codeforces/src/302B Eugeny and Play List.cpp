#include <iostream>
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#define ll long long
#define N 100005
using namespace std;

struct node { ll cs, time; } a[N];

int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i].cs >> a[i].time;
    ll s[N];
    for (int i = 0; i < m; ++i) cin >> s[i];
    int sum = 0, j = 0, flag = 0;
    for (int i = 1; i <= n; ++i) {
        sum += a[i].cs * a[i].time;
        while (s[j] <= sum) {
            cout << i << '\n';//输出当前的节点编号 i，并换行
            j++;//处理下一个查询
            if (j >= m) { flag = 1; break; }//是否已处理完所有查询
        }
        if (flag) break;//如果标志位被设置，跳出外层循环
    }
    return 0;
}