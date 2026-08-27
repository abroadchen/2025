//
// Created by Psy.C on 2026/8/27.
//
/**
- n ：数组元素总数。
- k ：目标阈值（需要选取的至少数量）。
- a[N] ： 计数数组 ， a[x] 存储值为 x 的元素个数（ x 为元素值）

- for (int i = 1; i <= n; ++i) ：遍历每个元素。
- a[x=rd()]++ ：读入元素值 x ，同时将 a[x] 计数加1。
- sum += x ：累计所有元素的总和
if (sum < k) ：若所有元素值之和都小于 k ，则不可能满足要求，输出 -1 （无解）
- sum = 0 ：重置累计计数器。
- for (int i = N-5; i >= 1; --i) ：从最大元素值（约 [ o bj ec tO bj ec t ] 1 0 7 ） 从大到小 遍历到1
if (a[i]) ：仅当存在值为 i 的元素时才处理（剪枝优化）
sum += a[i] ：将值为 i 的所有元素计入 sum （优先选大值元素）
当处理值 i 时，需要扣除 值为 2i 和 2i-1 的元素数
a[i] 被拆分成了 a[2i] 和 a[2i-1] ，所以在处理 i 时，之前可能已经把这些拆分出来的元素算过一次了，需要减去避免重复
if (i == 1) sum += a[i] ：当 i=1 时， i*2=2 ，需要加回来（避免多减）
- 若累计数量 sum ≥ k ，说明 值≥当前 i 的元素已经足够 k 个 ，直接输出 i 作为答案。
- 此时 i 是能满足条件的 最大值 （因为从大到小遍历，第一个满足条件的 i 就是最大的）

将值为 i 的所有元素 拆分 到更小值的位置：
- i/2 和 (i+1)/2 是 i 的 两个子节点 （二叉树视角）。
- 例如： i=10 → 10/2=5 , (10+1)/2=5 （两个子节点相同，只加一次）。
- 例如： i=9 → 9/2=4 , (9+1)/2=5 （奇数拆分成不同的两个子节点）。
- 拆分意味着：如果无法通过值为 i 的元素凑够 k 个，就把它们拆成更小的值，尝试用更小值的元素继续凑
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;
constexpr int N = 1e7+5;//数组大小上限，支持最大元素值为 [ o bj ec tO bj ec t ] 1 0 7
int n, k, a[N];

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

void out(int x) {
    if (x < 0) putchar('-'), x = -x;
    if (x > 9) out(x / 10);
    putchar(x % 10 + '0');//输出最低位（数字+48转ASCII码）
}

signed main() {
    fast;
    n = rd(), k = rd();
    int sum = 0, x;
    for (int i = 1; i <= n; ++i) a[x=rd()]++, sum += x;
    if (sum < k) out(-1);
    else {
        sum = 0;
        for (int i = N-5; i >= 1; --i) {
            if (a[i]) {
                sum += a[i];
                if (i * 2 <= N-5) sum -= a[i*2] + a[i*2-1];
                if (i == 1) sum += a[i];
                if (sum >= k) { out(i); return 0; }
                a[i/2] += a[i];
                a[(i+1)/2] += a[i];
            }
        }
    }
    return 0;
}