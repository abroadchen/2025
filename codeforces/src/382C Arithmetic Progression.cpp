//
// Created by Psy.C on 2026/1/26.
//

#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100100
#define inf 0x3f3f3f3f
using namespace std;

int minn(const int a, const int b) { return a < b ? a : b; }

int main() {
    fast;
    int n, a[N]; cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a, a + n);
    if (1 == n) cout << "-1\n";//只有一个元素时，可以插入无限多个元素形成等差数列
    else if (n == 2) {//插入1个相同元素
        if (const int k = a[1] - a[0]; !k) cout << "1\n" << a[0] << '\n';
        else if (k&1) {
            cout << "2\n";
            cout << a[0] - k << ' ' << a[1] + k << '\n';
        } else {
            cout << "3\n";
            cout << a[0] - k << ' ' << a[0] + (k>>1) << ' ' << a[1] + k << '\n';
        }
    } else {
        int cnt = 0, k = inf;
        for (int i = 1; i < n; ++i) k = minn(k, a[i] - a[i - 1]);//相邻元素间的最小差值
        bool ok = true, flag = false;
        for (int i = 1; i < n; ++i) {
            if (k == a[i] - a[i - 1]) continue;
            if (flag) { ok = false; break; }
            //最多只有一个间隔是2k（其他都是k)
            if (k<<1 == a[i] - a[i - 1]) { flag = true, cnt = a[i - 1] + k; }
            else { ok = false; break; }
        }
        if (!ok) cout << "0\n";//不可能构成等差数列
        else if (!k) cout << "1\n" << a[0] << '\n';//所有元素相等，插入任意一个相同元素
        else if (flag) cout << "1\n" << cnt << '\n';//有一个间隔是2k，可在中间插入1个元素
        else {//在首尾各插入1个元素
            cout << "2\n";
            cout << a[0] - k << ' ' << a[n - 1] + k << '\n';
        }
    }
    return 0;
}