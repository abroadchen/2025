//
// Created by Psy.C on 2026/4/20.
//
/**
a, b: 第一个等差数列的首项和公差
a1, b1: 第二个等差数列的首项和公差
l, r: 查询区间范围
t: 用于分块计算的阈值
p: 临时变量
f: 最小公倍数
L: 起始点
ans: 结果计数
如果第一个数列的公差小于第二个，交换两个数列的参数
这样确保a ≥ a1，便于后续处理
当a ≤ t时，采用枚举方法
遍历i从-2t到2t，计算第一个数列中的元素p = b + a*i
检查p是否也属于第二个等差数列，即是否存在整数k使得p = b1 + a1*k
即检查|b1 - p|是否能被a1整除
计算两数列公差的最小公倍数，即两个等差数列交集的公差
计算起始查找点L，取b、l、b1的最大值
调整p使其成为满足条件且大于等于L的第一个值
如果找到的起始点超出右边界，输出0
否则输出[p, r]区间内满足条件的数的个数
当a > t时，直接遍历第一个等差数列中的元素
检查每个元素是否同时满足：
在区间[l, r]内
属于第二个等差数列（即(i - b1) % a1 == 0）
统计满足条件的元素个数


b: 第一个等差数列的首项（因为数列是b, b+a, b+2a...）
l: 查询区间的左边界
b1: 第二个等差数列的首项
至少是第一个等差数列中的数（≥ b）
在查询区间内（≥ l）
是第二个等差数列中的数（≥ b1）

第一步：p += (L - p)/f*f + f;
(L - p)/f: 计算从当前p到达L大约需要多少个步长f
(L - p)/f*f: 计算需要跳跃的实际距离
+ f: 再额外加一个f，确保跳过L
这一步让p跳到一个超过L的值
第二步：p = L + (p - L) % f;
(p - L) % f: 计算p相对于L的余数偏移
L + (p - L) % f: 调整p使其成为大于等于L且符合等差规律的值

p 是找到的第一个符合条件的公共解
f 是公共解的公差（最小公倍数）

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int a, b, a1, b1, l, r, t, p, f, L, ans;
signed main() {
    fast;
    t = sqrt(4e9);//√(4×10⁹)，约等于63245
    cin >> a >> b >> a1 >> b1 >> l >> r;
    if (a < a1) swap(a, a1), swap(b, b1);
    if (a <= t) {
        for (int i = -2*t; i <= 2*t; ++i) {
            p = b + a*i;
            if (abs(b1 - p) % a1 == 0) {
                f = a*a1/__gcd(a, a1);
                L = max(max(b, l), b1);
                if (p < L) {
                    p += (L - p)/f*f + f;
                    p = L + (p - L) % f;
                } else p = L + (p - L) % f;
                if (p > r) cout << '0';
                else cout << (r - p) / f + 1;
                return 0;
            }
        }
        cout << '0';
    } else {
        for (int i = b; i <= r; i += a)
            if (l <= i && i >= b1 && (i - b1) % a1 == 0)
                ans++;
        cout << ans;
    }
    return 0;
}