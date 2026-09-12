//
// Created by Psy.C on 2026/9/12.
//
/**
S[i][j]：第 i 行、第 j 位的数字（-1 表示 '?'）。
m：数字串的行数（除第 0 行模式串以外的个数）。
rk[]：行的一个排序/置换，用于后续按某列排序
st[0] 是"模式串"（含 '?' 的主串），其余 m 行是数字。
n = 所有串的最大长度 +1（多留一位处理进位）。
把所有串右对齐放进 S[i][j+n-len[i]]（即末位对齐，前面补空）。
'?' 记为 -1（之后 DP 时用 0..9 试填）
V[d]：该位数字为 d 时获得的收益值
l..r：模式串第 n 位的可选数字范围（已确定则取该值，'?' 则 0..9）。
枚举第 n 位填 i：统计这一列所有 m 个数 + i 的和 ≥10 的次数 cnt（进位计数），以及和的个位对应收益 V 之和 tot。
F[n][cnt]：最低位，进位次数为 cnt 的最大收益。
这是竖式加法的逐位 DP：F[i][cnt] = 处理到第 i 位、到目前为止累计进位次数为 cnt 时的最大总收益
init(i+1)：按低位（i+1 列）‍对 m 行做稳定排序，使 rk 中"低位数字相同"的行相邻，便于对收益做前缀的增量更新。
l, r：模式串第 i 位可填范围；若这是模式串的最高有效位且低位是可为 0 时，强制 l++（最高位不能是 0，即结果大数最高位非零）。
rep(num, l, r)：枚举这一位模式串填 num。
第一个内层循环：统计所有行在该位有有效数字（max(len[j],len[0]) >= n-i+1，即该行长度够到这一位）时，S[j][i]+num 的个位收益累加到 tot，以及 ≥10 进位次数累加到 cnt。
第二层 rep(j,1,m+1)：这是关键优化——利用 rk 排序，增量式地尝试"第 i 位是否因为低位进位而多产生一次进位"：
F[i][cnt] = max(F[i][cnt], F[i+1][j-1] + tot)：把高位（i+1）状态 j-1 转移过来，加本列收益。
接下来一行通过 rk[j] 遍历行：判断该行在"第 i+1 位 + num + 1（多一位进位）"和"+num"两种情况下的收益差，增量更新 tot，并在某行因进位从 9 变 10 时 cnt++。
这实际上是"枚举进位链"：因为竖式加法里，某一位是否进位会影响下一位参数，所以对"低位进位数 j"做 DP，用排序让收益能滑动更新
取最高位（第 1 位）在所有进位次数下的最大收益 ans 输出
 */
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define per(i,a,b) for(int i=a; i>=b; --i)
using namespace std;
constexpr int N = 1e3, inf = 1e9;
int num[10], m, S[N+5][N+5], now[N+5], rk[N+5];
void init(int pos) {
    memset(num, 0, sizeof(num));
    rep(i, 1, m) num[S[i][pos]]++;//统计该列每个数字的词频
    per(i, 9, 1) num[i-1] += num[i];//前缀和（计数排序）
    per(i, m, 1) now[num[S[rk[i]][pos]]--] = rk[i];//稳定排序到 now
    rep(i, 1, m) rk[i] = now[i];//更新排序结果
}

inline int rd() {
    int f = 0, ch = 0; int x = 0;
    for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 1;
    for (; isdigit(ch); ch = getchar()) x = (x<<1)+(x<<3)+(ch&15);
    if (f) x = -x;
    return x;
}

char st[N+5][N+5];
int len[N+5], V[10], F[N+5][N+5];
int main() {
    scanf("%s", st[0]+1);
    int n = len[0] = strlen(st[0]+1); m = rd();
    rep(i, 1, m) scanf("%s", st[i]+1), len[i] = strlen(st[i]+1), n = max(n, len[i]);
    n++;
    rep(i, 0, m) rep(j, 1, len[i]) S[i][j+n-len[i]] = st[i][j] == '?' ? -1 : st[i][j] - '0';
    rep(i, 0, 9) V[i] = rd();//每个数字一位的收益
    rep(i, 1, n) rep(j, 0, m) F[i][j] = -inf;//DP 表初始化
    int l = S[0][n] == -1 ? 0 : S[0][n], r = S[0][n] == -1 ? 9 : S[0][n];
    rep(i, l, r) {
        int cnt = 0, tot = 0;
        rep(j, 1, m) {
            if (i + S[j][n] >= 10) cnt++;//进位次数
            tot += V[(i+S[j][n])%10];
        }
        F[n][cnt] = max(F[n][cnt], tot);
    }
    rep(i, 1, m) rk[i] = i; rk[m+1] = m+1;
    per(i, n-1, 1) {
        init(i+1);
        int l = S[0][i] == -1 ? 0 : S[0][i], r = S[0][i] == -1 ? 9 : S[0][i];
        if (n-i+1 == len[0] && l == 0) l++;//模式串最高位不能为 0
        rep(num, l, r) {
            int cnt = 0, tot = 0;
            rep(j, 1, m) {
                if (max(len[j], len[0]) < n-i+1) continue;//该行在此位无有效数字
                tot += V[(S[j][i]+num)%10];
                cnt += S[j][i] + num >= 10;
            }
            rep(j, 1, m+1) {
                F[i][cnt] = max(F[i][cnt], F[i+1][j-1] + tot);
                tot += (max(len[rk[j]], len[0]) >= n-i+1 ||
                    (S[rk[j]][i]+num+1)?V[(S[rk[j]][i]+num+1)%10]:0)-
                        (max(len[rk[j]], len[0]) >= n-i+1 ||
                            (S[rk[j]][i]+num)?V[(S[rk[j]][i]+num)%10]:0);
                cnt += S[rk[j]][i] + num + 1 == 10;
            }
        }
    }
    int ans = 0;
    rep(i, 0, m) ans = max(ans, F[1][i]);
    printf("%d\n", ans);
    return 0;
}