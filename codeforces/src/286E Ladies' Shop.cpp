//
// Created by Psy.C on 2025/12/28.
//
/**
* len：FFT处理的数组长度
rev[N]：用于位逆置换的数组
 *定义数组类，包含复数数组a[N]
*FFT函数，tp为1表示正变换，-1表示逆变换
执行位逆置换，将数组元素按rev数组重新排列
*进行FFT迭代，i为当前块大小，从2开始每次翻倍
I为当前块的一半
计算单位根w
*外层循环：遍历每个大小为i的块
内层循环：处理每个块中的元素
使用蝴蝶变换公式更新数组值
 *如果是逆变换，将结果除以长度len
 *
 将已计算的位逆序结果整体右移一位，为新的最低位腾出空间* rev[i>>1]>>1
 *把当前数字的最低位放到最高位的位置  (i&1)<<(sz-1)
 *
 *
 *
 */
#include <iostream>
#include <complex>
#include <cmath>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define com complex<double>
#define N 1<<21
#define pi acos(-1)
using namespace std;

int len, rev[N];
class arr {
public:
    com a[N];
    void fft(const int tp) {
        for (int i = 0; i <= len - 1; ++i) if (rev[i] < i) swap(a[rev[i]], a[i]);
        for (int i = 2; i <= len; i <<= 1) {
            const int I = i>>1;
            com w(cos(pi/I), tp * sin(pi/I));
            for (int j = 0; j < len; j += i) {
                com W(1, 0);
                for (int k = j; k < j + I; ++k, W = W * w) {
                    com A = a[k], B = a[k + I];
                    a[k] = A + B * W;
                    a[k + I] = A - B * W;
                }
            }
        }
        if (tp == -1) for (int i = 0; i <= len - 1; ++i) a[i] /= len;
    }
} tr;

int main() {
    fast;
    int n, m, a[N], sz = 0; cin >> n >> m;
    for (int i = 1; i <= n; ++i) cin >> a[i];
    while ((1<<sz) < m) ++sz; ++sz; len = 1<<sz;//计算满足条件的最小2的幂次
    for (int i = 0; i <= len - 1; ++i) rev[i] = rev[i>>1]>>1|(i&1)<<(sz-1);
    bool ans[N];
    //将输入的数字在FFT数组中设置为1，同时在ans中标记为true
    for (int i = 1; i <= n; ++i) tr.a[a[i]] = com(1, 0), ans[a[i]] = true;
    tr.fft(1);//执行正向FFT变换
    for (int i = 0; i <= len - 1; ++i) tr.a[i] = tr.a[i] * tr.a[i];
    tr.fft(-1);
    for (int i = 1; i <= m; ++i) if (tr.a[i].real() + 0.5 >= 1) {
        if (!ans[i]) { cout << "NO\n"; return 0; }//某个值在FFT结果中存在但不在原数组中
        ans[i] = false;//将已确认的值标记为false
    }
    cout << "YES\n";
    int sum = 0;
    for (int i = 1; i <= m; ++i) if (ans[i]) sum++;//统计剩余元素个数并输出
    cout << sum << '\n';
    for (int i = 1; i <= m; ++i) if (ans[i]) cout << i << ' ';//输出所有剩余元素
    cout << '\n';
    return 0;
}