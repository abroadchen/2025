//
// Created by Psy.C on 2025/12/8.
//
/*
*构建最小质因数表：
p[i]：存储数字i的最小质因数
外层循环遍历2到N-1
如果!p[i]（i是质数）：
p[i] = i：质数的最小质因数是自身
内层循环标记所有i的倍数，将其最小质因数设为i
 *
*遍历数组a中的每个元素x
对每个x进行质因数分解：
p[x]：x的最小质因数
l[p[x]]++：增加该质因数的计数
x /= p[x]：除去这个质因数
循环直到x变为1
 *
*遍历数组b中的每个元素x
ans = 1：初始化结果
对x进行质因数分解：
如果该质因数在l中存在（l[p[x]]>0）：
将该质因数从l移到r（r[p[x]]++; l[p[x]]--）
否则：
将该质因数乘入结果（ans *= p[x]）
x /= p[x]：除去这个质因数
将结果ans加入向量t
 *
*遍历数组a中的每个元素x
ans = 1：初始化结果
对x进行质因数分解：
如果该质因数在r中存在（r[p[x]]>0）：
将该质因数从r移到l（l[p[x]]++; r[p[x]]--）
否则：
将该质因数乘入结果（ans *= p[x]）
x /= p[x]：除去这个质因数
将结果ans加入向量d
 */
#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 10000007
using namespace std;

int p[N];
void f() {
    for (int i = 2; i < N; ++i) if (!p[i]) {
        p[i] = i;
        for (int j = i + i; j < N; j += i) p[j] = i;
    }
}

int l[N], r[N];
int main() {
    fast; f();
    int n, m; cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];
    for (int x : a) while (x != 1) {
        l[p[x]]++; x /= p[x];
    }
    vector<int> t;
    for (int x : b) {
        int ans = 1;
        while (x != 1) {
            if (l[p[x]]) { r[p[x]]++; l[p[x]]--; }
            else ans *= p[x];
            x /= p[x];
        }
        t.push_back(ans);
    }
    vector<int> d;
    for (int x : a) {
        int ans = 1;
        while (x != 1) {
            if (r[p[x]]) { l[p[x]]++; r[p[x]]--; }
            else ans *= p[x];
            x /= p[x];
        }
        d.push_back(ans);
    }
    cout << n << ' ' << m << '\n';
    for (const int x : d) cout << x << ' ' << '\n';
    for (const int x : t) cout << x << ' ' << '\n';
    return 0;
}