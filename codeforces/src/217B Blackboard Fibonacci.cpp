//
// Created by Psy.C on 2025/12/7.
//
/*
*n：字符串长度
r：参数，通常表示某种比例或目标值
ans：记录最小连续相同字符对数
a[N]：临时字符串数组
res[N]：结果字符串数组
 *
*构造字符串：
参数t和b代表T和B的相对比例
从后向前构造字符串（逆向欧几里得算法）
如果t == b，无法继续区分，返回
如果t > b，说明需要更多T，记录'T'，更新t = t - b
如果b > t，说明需要更多B，记录'B'，更新b = b - t
如果最后t和b不都是1，说明不是有效的互质对，返回
 *
*第一个字符设为'T'
统计连续相同字符对的数量cnt
如果比当前最小值更小，更新答案和结果字符串
 *
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e6+10, inf = 0x3f3f3f3f;
int n, r, ans;
char a[N], res[N];

void f(int t, int b) {
    for (int i = n - 1; i > 0; --i) {
        if (t == b) return;
        if (t > b) { t -= b; a[i] = 'T'; }
        else { b -= t; a[i] = 'B'; }
    }
    if (t != 1 || b != 1) return;
    a[0] = 'T';
    int cnt = 0;
    for (int i = 1; i < n; ++i) if (a[i-1]==a[i]) cnt++;
    if (cnt < ans) {
        ans = cnt;
        memcpy(res, a, sizeof(a[0]) * n);//复制n个字符
        res[n] = 0;//添加字符串终止符
    }
}


int main() {
    fast;
    cin >> n >> r; ans = inf;
    for (int i = 1; i <= r; ++i) { f(i, r); f(r, i); }
    if (ans == inf) cout << "IMPOSSIBLE\n";
    else cout << ans << '\n' << res << '\n';
    return 0;
}