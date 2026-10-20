//
// Created by Psy.C on 2026/10/20.
//
/***
对每个类别 i，如果它有 c= cnt[i] 个物品，那么"从这个类别选 t 个"的方案数：选 0 个（1 种）、选 1 个……选 c 个（各 1 种）。对应的生成函数是：

(1 + x + x² + ... + x^c)
即一个系数全为 1、长度为 c+1 的多项式。

总方案数 = 把这些多项式全部相乘得到的多项式，其中 x^k 的系数就是"总共选 k 个"的方案数。

所以问题变成：把 m 个 (1+x+...+x^cnt[i]) 多项式相乘，输出 x^k 的系数 mod 1009
叶子返回"类别 i 的生成函数"：cnt[i]+1 个系数全为 1 的多项式。
分治把 m 个多项式两两相乘到根，根节点返回所有类别的总生成函数。
每个卷积结果都要 % P（mod 1009）并取整
标准迭代 FFT：

先做位反转（bit-reversal permutation）。
三层循环做蝶形变换，x=1 时为正变换，x=-1 时为逆变换。
注意蝶形那行写法有点特殊但等价于标准公式：

c[i+j] += c[i+j+k] * w;
c[i+j+k] = c[i+j] - c[i+j+k]*w - c[i+j+k]*w;  // 注意此处 c[i+j] 已是加过后的新值
这里实际是：先 c[i+j] += c[i+j+k]*w，然后 c[i+j+k] = (新的c[i+j]) - 原来的c[i+j+k]*w - 较小的c[i+j+k]*w... 实际正确写法应为 tmp = c[i+j] 先暂存，这里写法上依赖了更新顺序，属于一种紧凑写法（结果等价于标准 FFT
标准的 FFT 卷积流程：补齐 2 的幂长度 → 正变换 → 点乘 → 逆变换 → 除以长度得到结果多项式
ans[k] 就是 x^k 的系数，即"选恰好 k 个元素"的方案数 mod 1009

分治产生 O(m) 次卷积，采用启发式（平分区间）总卷积复杂度约 O(n log² n) 或 O(total · log m) 量级（具体取决于各 cnt 之和）。
每层卷积用 FFT O(L log L)，L 为当前多项式长度


p[]：位反转（bit-reversal）表，FFT 重排用。
f[], g[]：两个进行卷积的多项式的频域/时域工作数组。
n, m：工作变量（两个输入多项式长度）
FFT（快速傅里叶变换），把多项式系数从时域变到频域（或逆变换回来）
进入蝶形运算前，把输入按位反转顺序重排。p[i] 存的是 i 的位反转值。if (i < p[i]) swap(...) 保证每个位置只交换一次。这是迭代 FFT 的经典第一步
外层循环控制当前蝶形运算的"块大小" b（每轮翻倍），k = b/2 是每块内旋转因子的个数。
t 是单位根 ω = cos(2π/b) + i·sin(2π/b)·x。x=1 表示正变换，x=-1 表示逆变换（逆变换用共轭单位根）。
w 是当前旋转因子，初始值为 1（即 1+0i)
中层循环：按块遍历整个数组，每处理完一个块就把 w 重置为 1（下一块重新开始本级旋转因子递推）
内层循环：每个块内做 k 次蝶形运算。
c[i+j] += c[i+j+k]*w;：此时 c[i+j] 还是旧值（未修改），把"后半部分 × w"累加到前半。
c[i+j+k] = c[i+j] - c[i+j+k]*w - c[i+j+k]*w;：此时 c[i+j] 已经变成累加后的新值，而 c[i+j+k]*w 仍是旧值（还没改）。所以标准蝶形公式：
新前半 = 旧前半 + 旧后半·w ✓（第一行已实现）
新后半 = 旧前半 − 旧后半·w = (旧前半 + 旧后半·w) − 2·(旧后半·w) ✓（第二行用更新后的前半减两次后半·w）
这是一种紧凑的写法，结果与标准 FFT 完全一致

若任一多项式为空，返回空 vector
l：卷积结果长度为 n+m-1，把它向上取整到大于等于该值的最小的 2 的幂（FFT 要求长度是 2 的幂）
把 a、b 分别拷贝到 f[]、g[]，不足 l 的补 0。
同时递推计算位反转表 p[i]：p[i>>1] >> 1 是 i 去掉最低位后的位反转左移，再根据 i 的奇偶决定最高位是 0 还是 l>>1。这是 O(l) 算位反转的标准递推
更新 n = n+m-1（卷积结果长度）。
对 f、g 分别做正变换（时域 → 频域）
频域中逐点相乘（卷积定理：时域卷积 = 频域点乘）
对 f 做逆变换（x=-1），回到时域，得到卷积系数
逆变换后每个点要除以 l 才是真实系数（FFT 逆变换的归一化）。取 real() 得到实数部分（浮点），收集到 ret 并返回

cnt[i]：类别 i 的物品个数
递归出口：区间只剩一个类别 l，其生成函数是 (1 + x + x² + ... + x^cnt[l])，即 cnt[l]+1 个系数全为 1 —— vi(cnt[l]+1, 1) 创建长度为 cnt[l]+1、值全为 1 的 vector
分治：取中点，递归求左右两个半区间的生成函数乘积，分别存在 t1、t2
用 FFT 卷积把 t1、t2 相乘，得到当前区间的生成函数
卷积结果是浮点数组 t，需要转成整数并对 P 取模：对每个系数 round() 四舍五入成整数，取 % P（1009）
释放中间变量内存（swap 一个空临时对象以清空）。
返回当前区间的生成函数 ret

左值 = 可取地址、有名字、能长期存在的对象；右值 = 临时的、不可取地址的值
。move 就是把"左值"包装成"可被移动的右值"传给移动构造/移动赋值。


读入：n 物品总数、m 类别数、k 要求选出的数量
读 n 个物品的类别号 x，cnt[x]++ 统计每个类别的物品数量
dfs(1, m) 计算 1..m 所有类别生成函数的乘积（总生成函数）。
ans[k] 就是 x^k 的系数，即"选恰好 k 个物品"的方案数 mod 1009。
输出
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define pi acos(-1)
#define cpx complex<double>
#define vd vector<double>
#define vi vector<int>
using namespace std;

constexpr int N = 2.7e5+10, M = 2e5+10, P = 1009;

namespace Poly {
    int p[N], n, m;
    cpx f[N], g[N];
    void fft(int n, cpx *c, int x=1) {
        for (int i = 0; i < n; ++i) if (i < p[i]) swap(c[i], c[p[i]]);//位反转重排
        for (int b = 2, k = 1; b <= n; b <<= 1, k <<= 1) {
            cpx t(cos(2*pi/b), sin(2*pi/b)*x), w(1, 0);
            for (int i = 0; i < n; i += b, w = 1) {
                for (int j = 0; j < k; ++j, w *= t) {
                    c[i+j] += c[i+j+k]*w;
                    c[i+j+k] = c[i+j] - c[i+j+k]*w - c[i+j+k]*w;
                }
            }
        }
    }
    vd con(const auto &a, const auto &b) {
        if (!a.size() || !b.size()) return vd(); n = a.size(); m = b.size();
        int l = 1<<(int)ceil(log2(n+m-1));
        for (int i = 0; i < l; ++i) {
            f[i] = i < n ? a[i] : 0, g[i] = i < m ? b[i] : 0;
            p[i] = (p[i>>1]>>1)|(i&1?l>>1:0);
        }
        n += m-1, fft(l, f), fft(l, g);//正变换
        for (int i = 0; i < l; ++i) f[i] *= g[i];//频域相乘
        fft(l, f, -1);//逆变换
        vd ret;
        for (int i = 0; i < n; ++i) ret.emplace_back(f[i].real()/l);//除以 l 得到卷积系数
        return ret;
    }
}

int cnt[M];
vi dfs(int l, int r) {
    if (l == r) return vi(cnt[l]+1, 1);//叶子：类别 l 的多项式 (1+x+...+x^cnt[l])
    int mid = (l+r)>>1;
    vi t1 = dfs(l, mid), t2 = dfs(mid+1, r), ret;//左右子区间乘积
    auto t = Poly::con(t1, t2);//用 FFT 做两多项式卷积
    for (auto x : t) ret.emplace_back((long long)round(x)%P);
    vi().swap(t1), vi().swap(t2); vd().swap(t);
    return move(ret);
}

int n, m, k, x;
int main() {
    fast;
    cin >> n >> m >> k;
    for (int i = 1; i <= n; ++i) cin >> x, ++cnt[x];
    vi ans = dfs(1, m);
    cout << ans[k] << '\n';
    return 0;
}