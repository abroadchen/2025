//
// Created by Psy.C on 2025/11/13.
//
/*
*x：目标序号
b[N]：阶乘数组
n：元素个数
q：约束条件数
i,j：循环变量
a[N][N]：约束关系矩阵
p[N]：排列结果数组
f[N]：标记数组（是否已使用）
 *
*定义深度优先搜索函数，参数k表示当前处理第k个位置：
如果k>n（处理完所有位置）：
x减1，如果x变为0则输出结果并退出
否则返回
*确定当前位置k的取值范围[l,r]：
初始范围为[1,n]
根据约束条件调整范围：
如果存在约束a[i][k]（i<k），则p[k] > p[i]，所以l = max(l, p[i]+1)
如果存在约束a[k][i]（i<k），则p[k] < p[i]，所以r = min(r, p[i]-1)
 *
*在合法范围内尝试每个未使用的数字：
如果数字l未被使用：
将l放在位置k
标记l已使用
递归处理下一个位置
回溯：取消标记
 *
 *计算阶乘数组b：b[i] = i!
 *x减去M，如果超过n!则输出错误信息并退出
*如果没有约束条件（q=0）：
使用康托展开的逆运算直接计算第x个排列
从高位到低位确定每个位置的数字
如果当前数字的阶乘小于剩余序号，则跳过该数字
否则选择该数字并更新剩余序号
 *
*读入q个约束条件，设置约束矩阵a
从第1个位置开始DFS搜索
如果搜索结束还没找到结果，则输出错误信息
 *
*无约束情况（q=0）：
使用康托展开的逆运算直接计算
时间复杂度：O(n²)
有约束情况（q>0）：
使用DFS回溯搜索所有满足约束的排列
按字典序生成排列，找到第x个
时间复杂度：取决于约束的严格程度

初始化：i = n
条件判断：i--       （非0为真）后缀递减的特性
更新表达式：空（在条件判断中完成） 在循环结束后执行


 */
#include <cstdio>
#include <cstdlib>
using namespace std;

typedef long long ll;
const int N = 20, M = 2000;
ll x, b[N];
int n, q, i, j, a[N][N], p[N];
bool f[N];

void print() {//输出特定信息并退出程序
    puts("The times have changed");
    exit(0);
}

void print2() {//输出排列结果并退出程序
    for (i = 1; i <= n; ++i) printf("%d ", p[i]);
    exit(0);
}

void dfs(int k) {
    if (k > n) { if (!--x) print2(); return; }
    int l(1), r(n);
    for (i = 1; i < k; ++i) {
        if (a[i][k]) l = p[i] < l ? l : p[i] + 1;
        if (a[k][i]) r = p[i] > r ? r : p[i] - 1;
    }
    for (; l <= r; ++l) if (!f[l]) {
        p[k] = l;
        f[l] = 1;
        dfs(k + 1);
        f[l] = 0;
    }
}

int main() {
    scanf("%d%lld%d", &n, &x, &q);
    for (*b=i=1; i <= n; ++i) b[i] = i * b[i - 1];
    if ((x -= M) > b[n]) print();
    if (!q) {
        for (i = n; i--;) {
            for (j = 1; j <= n; ++j) if (!f[j]) {
                if (b[i] < x) x -= b[i];
                else {
                    printf("%d ", j);
                    f[j] = 1;
                    j = n;
                }
            }
        }
        return 0;
    }
    for (; q--; a[i][j] = 1) scanf("%d%d", &i, &j);//同时完成计数和设置标记的功能
    dfs(1), print();
    return 0;
}