//
// Created by Psy.C on 2025/11/20.
//
/*
*p[N], q[N]: 预计算的数组
t[N][N]: 二维数组，存储某种组合数
a[M]: 存储输入数据
ans[2][N]: 双缓冲数组，用于动态规划
**t 等价于 t[0][0]
*p 等价于 p[0]
*q 等价于 q[0]
 *
*p[i]: 降幂排列，p[i] = p[i-1] * (m-i+1) % mod
q[i]: 阶乘，q[i] = q[i-1] * i % mod
 *
*s
累积和变量，存储前一轮计算的总和
代表之前所有状态的累计结果
2. p[j]
预计算的降幂排列数
p[j] = m * (m-1) * (m-2) * ... * (m-j+1)
表示从m个元素中选取j个元素的排列数
3. s * p[j]
将累积结果乘以排列数
在组合数学中，这通常表示"总的可能情况数"
4. ans[~i&1][j]
双缓冲数组中的前一状态
i&1 得到当前缓冲区索引(0或1)
~i&1 得到前一个缓冲区索引(与当前相反)
ans[~i&1][j] 表示前一轮j状态的值
5. q[j]
预计算的阶乘
q[j] = j! = 1 * 2 * 3 * ... * j
表示j个元素的全排列数
6. ans[~i&1][j] * q[j]
前一状态值乘以阶乘
通常用于消除重复计数或进行归一化处理
 *
*s*p[j]: 总的计数（包含可能的重复）
ans[~i&1][j]*q[j]: 需要排除的重复计数
相减: 得到净计数（去除重复后的结果）
 *
 *a[i]（当前处理的元素）和 j（状态索引）
*新增元素可以独自创建一个新组：t[i-1][j-1] 种方式
新增元素可以加入到已有的 j-1 个特定组中的任意一个：(j-1) × t[i-1][j] 种方式
 *
 *ans[i&1] 实际上是一个指向该行首元素的指针
 *向后偏移 a[i] + 1 个位置
*a[i - 1] 存储了前一次处理的数据规模
a[i - 1] + 1 表示需要清空的数组元素个数（包括索引0）
 *
 *
 */
#include <algorithm>
#include <cstdio>
#include <numeric>
#define rep(i, n) for(int i=1;i<=n;++i)
using namespace std;

typedef long long ll;
const int N = 5001, M = 1e6+1;
ll p[N], q[N];
int t[N][N], a[M], ans[2][N];


int main() {
    int n, m, mod, s = **t = *p = *q = 1;
    scanf("%d%d%d", &n, &m, &mod);
    rep(i,N-1) {
        rep(j,i) t[i][j] = (t[i-1][j-1]+t[i-1][j]*(j-1ll)) % mod;
        p[i] = p[i-1] * (m - i + 1) % mod;
        q[i] = q[i-1] * i % mod;
    }
    rep(i,n) {
        scanf("%d", a + i);
        rep(j,min(a[i], m)) ans[i&1][j] = ((s*p[j]-ans[~i&1][j]*q[j])%mod+mod)
            *t[a[i]][j]%mod;
        s = accumulate(ans[i&1], ans[i&1] + a[i] + 1, 0ll) % mod;//计算当前层所有状态的和
        fill_n(ans[~i&1], a[i - 1] + 1, 0);//清空前一层的数据
    }
    printf("%d\n", s);
    return 0;
}