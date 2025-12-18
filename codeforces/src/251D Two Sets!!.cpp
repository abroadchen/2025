//
// Created by Psy.C on 2025/12/17.
//
/*
*b[M]：存储每一位（第i位为1）的数字位置信息 M个bitset，每个长度为N，用于记录每个二进制位上为1的元素位置
f[M]：线性基矩阵，用于高斯消元
p[N]：记录每个位置对应的基础方程索引
ans[N]：存储最终每个位置的解（1或2）
 *
 *时间复杂度约为O(n×M)，空间复杂度为O(n×M)
 *
*n存储元素个数，tot计数线性基中向量个数
x临时存储输入的数字，sum存储所有数字的异或和
 *
 *构建线性基
*外层循环先处理bit=0再处理bit=1
内层循环从最高位(M-1)到最低位(0)
选择那些在sum中第i位等于bit的位进行处理
将b[i]复制到f[++tot]，同时设置增广矩阵的最后一列f[tot][n+1] = bit^1
bit^1表示对调：如果原位是0则变为1，如果是1则变为0
 *
 *高斯消元过程
*对于当前向量f[tot]，检查每个位置j
如果位置j已经被某个基础向量p[j]占据且当前向量在该位置为1
则通过异或操作消除该位置的1（线性代数中的行变换）
 *
 *确定主元
*寻找当前向量中第一个非零位置t
如果全为0（t=0），说明这是线性相关的向量，减少计数器
否则将位置t标记为由第tot个基础向量控制
 *
 *回代求解
*从后向前处理每个基础位置i
如果位置i被基础向量p[i]控制，则ans[i]就是该向量增广列的值
然后更新所有在位置i上有值的基础向量，通过异或操作消除影响
 *
 *for (int i = M - 1; ~i; --i)  for (int i = M - 1; i >= 0; --i)
*当i = 0时，~i = ~0 = -1（全1），在布尔上下文中为true
当i = -1时，~i = ~(-1) = 0，在布尔上下文中为false
因此循环会在i变为-1时终止
 *
 *for (int i = n; i; --i) for (int i = n; i > 0; --i) for (int i = n; i != 0; --i)
*当i > 0时，条件为true，循环继续
当i = 0时，条件为false，循环终止
 */
#include <iostream>
#include <bitset>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
#define N 100005
#define M 62
using namespace std;


int main() {
    fast;
    int n, tot = 0; cin>>n;
    ll x, sum = 0;
    bitset<N> b[M], f[M];
    for (int i = 1; i <= n; ++i) {//构建初始矩阵
        cin>>x;
        sum ^= x;
        for (int j = M - 1; ~j; --j)//对于每个数字x，检查其每个二进制位j（从高位到低位）
            if (x>>j&1) b[j][i] = true;//记录第j位为1的数字位置 b[j]的第i位置设为true，表示第i个数字在第j位上有贡献
    }
    int p[N], ans[N];
    for (int bit = 0; bit <= 1; ++bit) for (int i = M - 1; ~i; --i) {
        if ((sum>>i&1) == bit) {
            f[++tot] = b[i];
            f[tot][n+1] = bit^1;
            for (int j = 1; j <= n; ++j) if (p[j] && f[tot][j]) {
                f[tot] ^= f[p[j]];
            }
            int t = 0;
            for (int j = 1; j <= n; ++j) if (f[tot][j]) { t = j; break; }
            if (!t) --tot; else p[t] = tot;
        }
    }
    for (int i = n; i; --i) if (p[i]) {
        ans[i] = f[p[i]][n+1];
        for (int j = i - 1; j; --j) if (f[p[j]][i]) {
            f[p[j]][n+1] = f[p[j]][n+1] ^ ans[i];
        }
    }
    for (int i = 1; i <= n; ++i) cout << (ans[i] ? 1 : 2) << ' ';
    return 0;
}