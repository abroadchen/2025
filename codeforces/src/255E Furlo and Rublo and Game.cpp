//
// Created by Psy.C on 2025/12/18.
//
/*N = 1000006：数组大小
M = 1000000：最大值限制
a[N]：存储输入数据
v[N]：辅助数组，用于计算Mex函数
f[N]：存储每个数字的Mex值（Grundy数）
ans：最终答案（异或和）
mx：当前最大未出现的数字（Mex值
*add(x)：将数字x加入集合，更新Mex值
v[x]++：增加x的计数
while (v[mx]) ++mx：找到下一个未出现的最小非负整数
del(x)：从集合中删除数字x，更新Mex值
v[x]--：减少x的计数
如果x的计数变为0，则更新mx为min(mx, x)
 *
*l, r：左右指针，维护当前的有效区间
v[0] = 1：初始化，表示0已经在集合中
 *
*对于每个数字i（从2到M）：
ql = ceil(i^(1/4))：左边界
qr = sqrt(i)：右边界
使用滑动窗口技术维护区间[ql, qr]内所有f值的Mex
while (r < qr) add(f[++r])：扩展右边界
while (l < ql) del(f[l++])：收缩左边界
f[i] = mx：当前i的Mex值就是mx
 *
 *重置辅助数组和指针，为处理大数据做准备
*遍历每个输入数字a[i]：
如果a[i] ≤ M，直接使用预处理的f[a[i]]值
否则，现场计算其Mex值：
计算区间边界ql和qr
使用滑动窗口维护区间内f值的Mex
将当前Mex值异或到ans中
 *
*如果ans为0，输出"Rublo"
否则输出"Furlo"
 *
 */
#include <iostream>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;

constexpr int N = 1e6+6, M = 1e6;
ll a[N], v[N], f[N], ans;
int mx;
void add(const int x) { v[x]++; while (v[mx]) ++mx; }
void del(const int x) { v[x]--; if (!v[x]) mx = min(mx, x); }

int main() {
    fast;
    int n; cin>>n;
    for (int i = 1; i <= n; ++i) cin>>a[i];
    sort(a + 1, a + n + 1);
    int l = 0, r = 0; v[0] = 1;
    for (int i = 2; i <= M; ++i) {
        const int ql = ceil(pow<long double>(i, 1./4)),
        qr = static_cast<int>(sqrt(i));
        while (r < qr) add(static_cast<int>(f[++r]));
        while (l < ql) del(static_cast<int>(f[l++]));
        f[i] = mx;
    }
    for (int i = 1; i <= M; ++i) v[i] = 0;
    mx = 0; l = 0, r = 0; v[0] = 1;
    for (int i = 1; i <= n; ++i) {
        if (a[i] <= M) { ans ^= f[a[i]]; continue; }
        const int ql = ceil(pow<long double>(
            static_cast<double>(a[i]), 1./4)),
        qr = static_cast<int>(sqrt(a[i]));
        while (r < qr) add(static_cast<int>(f[++r]));
        while (l < ql) del(static_cast<int>(f[l++]));
        ans ^= mx;
    }
    if (!ans) cout << "Rublo"; else cout << "Furlo";
    return 0;
}