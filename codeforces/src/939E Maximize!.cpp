//
// Created by Psy.C on 2026/10/17.
//
/**
a[N]：存操作加入的值；q：操作次数；i：当前已加入元素的位置计数（指向 a[] 末尾）；j：一个前向指针/游标；cnt：用于计算的"计数"，初值 1；sum：总和（long long）
读入总操作数 q，循环处理每条操作。
op == 1（添加元素）：

cin >> a[++i];：读入一个数并存入 a[++i]（i 自增后写入），即把新值追加到数组末尾。
sum += a[i] - a[i-1];：sum 增加 a[i] - a[i-1]。注意 a[i-1] 是上一个加入的值——所以这里 sum 不是简单的"所有元素之和"，而是差分累加，其语义下面分析。
op == 2（查询）：

先跑一个 while：
条件 j+1 < i（还有下一个元素可用）并且 1ll*a[j+1]*cnt < sum。
成立则执行 cnt++ 和 sum += a[++j]——即前向推进：把 a[++j] 的贡献并入 sum，同时 cnt 加 1。
然后输出：
a[i] - 1.0L*sum/cnt，用 fixed << setprecision(10) 保留 10 位小数。a[i] 是当前加入的最大/最新值，sum/cnt 是一个平均值
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 5e5+5;

int a[N], q, i, j, cnt(1);
long long sum;
int main() {
    fast;
    cin >> q;
    while (q--) {
        int op; cin >> op;
        if (op == 1) {
            cin >> a[++i];
            sum += a[i] - a[i-1];
        } else {
            while (j+1 < i && 1ll*a[j+1]*cnt < sum) cnt++, sum += a[++j];
            cout << fixed << setprecision(10) << a[i]-1.0L*sum/cnt << '\n';
        }
    }
    return 0;
}