//
// Created by Psy.C on 2025/11/5.
//
/*
*N: 最大字符串长度（200005）
M: 最大字符种类数（25，对应A-Z）
n: 输入字符串长度
k: 特殊字符数量
T: 时间限制
all: 位掩码，表示字符串中出现的所有字符
t[M]: 每个特殊字符的时间消耗
a[M][M]: 特殊字符间转换的时间消耗矩阵
can[M]: 对于每个特殊字符，跟踪它可以跟随哪些字符
f[1<<M]: 动态规划数组，f[mask]表示某个特殊字符子集的某种代价
s[N]: 输入字符串
 *
*将字符从'A'-'Z'转换为0-25的数字
构建位掩码all，表示字符串中所有唯一字符的集合
*初始化can数组为-1（所有位都置1）
初始化f数组：对于每个特殊字符i，设置f[1<<i] = t[i]（单个字符的消耗）
 *
*对于字符串中的每个位置：
对于每个特殊字符j：
如果can[j]有效（>= 0）：
如果特殊字符j和当前字符s[i]都不在can[j]集合中：
使用容斥原理更新f值（避免重复计算）
将当前字符s[i]添加到can[j]集合中
将can[s[i]]重置为0（空集）
*对于每个特殊字符i和每个子集j：
如果字符i在子集j中，将子集j去除i的消耗加到子集j的消耗上
 *
*对于每个可能的特殊字符子集：
如果这个子集只包含字符串中出现的字符（i&all==i）
并且总消耗在限制内（f[i] <= T）
并且它不是所有字符的集合（i != all）
那么增加答案计数器
 *
 *a[j][s[i]]: 从特殊字符j转换到字符s[i]的代价或消耗
 *
 *时间复杂度是O(nk + k2^k)，空间复杂度是O(2^k)
 */
#include <cstdio>
#include <cstring>
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

const int N = 200005, M = 25;
int n, k, T, all, t[M], a[M][M], can[M], f[1<<M];
char s[N];

int main() {
    scanf("%d%d%d%s", &n, &k, &T, s);
    rep(i,n) {
        s[i] -= 'A';
        all |= 1 << s[i];
    }
    rep(i,k) scanf("%d", &t[i]);
    rep(i,k) rep(j,k) scanf("%d", &a[i][j]);
    memset(can, -1, sizeof(can));
    rep(i,k) f[1<<i] = t[i];
    rep(i,n) {
        rep(j,k) if (can[j] >= 0) {
            if (!((can[j] >> j) & 1) && !((can[j] >> s[i]) & 1)) {
                f[can[j]] += a[j][s[i]];//给当前集合can[j]增加从特殊字符j到字符s[i]的转换代价
                f[can[j] | (1 << j)] -= a[j][s[i]];//从包含j的集合中减去这个代价（容斥原理的一部分）
                f[can[j] | (1 << s[i])] -= a[j][s[i]];//从包含s[i]的集合中减去这个代价
                f[can[j] | (1 << j) | (1 << s[i])] += a[j][s[i]];//给同时包含j和s[i]的集合加回这个代价
            }
            can[j] |= 1 << s[i];
        }
        can[s[i]] = 0;
    }
    rep(i,k) rep(j,1<<k) if ((j>>i)&1) f[j] += f[j^(1<<i)];
    int ans(0);
    rep(i,1<<k) if ((i&all)==i && f[i] <= T && i != all) ans++;
    printf("%d\n", ans);
    return 0;
}