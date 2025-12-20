//
// Created by Psy.C on 2025/12/20.
//
/*
*a[N]：存储生成的特殊数的数组
n：数组a中有效元素的个数
tot：素数的个数
pri[101]：存储素数的数组
 *
*用于生成所有不超过x的、只包含指定素数的数
num：当前生成的数
s：当前考虑的素数起始索引（避免重复）
x：上界
a[++n] = num：将当前数存入数组a
循环遍历从索引s开始的素数
if (num > x / pri[i]) break：剪枝，如果num*pri[i]会超过x则停止
递归调用，继续生成更大的数
 *
*ok[101]：用于素数筛选的标记数组
flag[N]：标记数组，标记满足条件的数
 *
*使用线性筛法生成小于p的所有素数：
外层循环从2到p-1
if (!ok[i]) pri[++tot] = i：如果i未被标记，则i是素数
内层循环用已知素数标记合数
if (pri[j] * i >= p) break：超出范围则停止
ok[i * pri[j]] = true：标记i*pri[j]为合数
if (i % pri[j] == 0) break：关键优化，避免重复标记
 *
 *f[N]：动态规划数组，存储每个数的某种"代价"
*dfs(1, 1, r)：从1开始生成所有不超过r的特殊数
sort(a + 1, a + n + 1)：对生成的数组从索引1到n进行排序
*memset(f, 127>>1, sizeof f)：将f数组初始化为很大的值(0x3f3f3f3f)
f[1] = 0：设置初始状态，1的代价为0
 *
*双重循环进行动态规划：
外层循环遍历所有小于p的数i
内层循环遍历生成的数组a
if (a[j] % i == 0)：如果a[j]能被i整除
while (a[k] < a[j] / i) k++：找到a[k] = a[j]/i的位置
f[j] = min(f[j], f[k] + 1)：更新动态规划状态
if (f[j] + i <= p) flag[j] = true：如果满足条件则标记
 *遍历所有生成的数，如果在查询范围内[l,r]且被标记，则计数器加1
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 2944731
using namespace std;

int a[N], n, tot, pri[101];
void dfs(const int num, const int s, const int x) {
    a[++n] = num;
    for (int i = s; i <= tot; ++i) {
        if (num > x / pri[i]) break;
        dfs(num * pri[i], i, x);
    }
}

int main() {
    fast;
    int l, r, p; cin >> l >> r >> p;
    bool ok[101], flag[N];
    for (int i = 2; i < p; ++i) {
        if (!ok[i]) pri[++tot] = i;
        for (int j = 1; j <= tot; ++j) {
            if (pri[j] * i >= p) break;
            ok[i * pri[j]] = true;
            if (i % pri[j] == 0) break;
        }
    }
    int f[N], ans = 0;
    dfs(1, 1, r); sort(a + 1, a + n + 1);
    memset(f, 127>>1, sizeof f); f[1] = 0;
    for (int i = 2; i < p; ++i) for (int j = 1, k = 1; j <= n; ++j) {
        if (a[j] % i == 0) {
            while (a[k] < a[j] / i) k++;
            f[j] = min(f[j], f[k] + 1);
            if (f[j] + i <= p) flag[j] = true;
        }
    }
    for (int i = 1; i <= n; ++i) if (a[i] >= l && flag[i]) ans++;
    cout << ans << '\n';
    return 0;
}