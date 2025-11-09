//
// Created by Psy.C on 2025/11/9.
//
/*
*N = 26：最多26个寄存器（对应a-z）
M = 64：每条指令字符串的最大长度
n：目标数值
reg[N]：寄存器数组，存储每个寄存器的当前值
ans：最少指令数
st[N][M]：存储生成的汇编指令
 *
*dep：当前深度（指令数）
如果当前寄存器值等于目标值n，返回true（找到解）
 *如果深度超过当前最优解，或当前值超过目标值，返回false
 *
*dep++：进入下一层
双重循环遍历之前的所有寄存器组合(i,j)
k循环遍历1,2,4,8（左移位1,2,3,4位）
计算reg[i] + k * reg[j]并存储到reg[dep]
如果找到解，生成对应的lea指令字符串
 *
*循环遍历之前的寄存器i
计算k * reg[i]并存储到reg[dep]
如果找到解，生成对应的lea指令字符串
 *
 *
*读取目标数值n
初始化寄存器数组，reg[0]=1（初始值为1）
迭代增加ans直到dfs(0)返回true（找到解）
输出最少指令数和所有指令
 */
#include <cstdio>
#include <cstring>
#define rep(i,n) for(int i=0;i<(n);++i)
using namespace std;

const int N = 26, M = 64;
int n, reg[N], ans;
char st[N][M];

bool dfs(int dep) {
    if (reg[dep] == n) return true;
    if (dep >= ans || reg[dep] > n) return false;
    dep++;
    rep(i,dep) rep(j,dep) {
        for (int k = 1; k <= 8; k <<= 1) {
            reg[dep] = reg[i] + k * reg[j];
            if (dfs(dep)) {
                sprintf(st[dep], "lea e%cx, [e%cx + %d*e%cx]",
                    dep + 'a', i + 'a', k, j + 'a');
                return true;
            }
        }
    }
    rep(i,dep) {
        for (int k = 1; k <= 8; k <<= 1) {
            reg[dep] = k * reg[i];
            if (dfs(dep)) {
                sprintf(st[dep], "lea e%cx, [%d*e%cx]",
                    dep + 'a', k, i + 'a');
                return true;
            }
        }
    }
    return false;
}

int main() {
    scanf("%d", &n);
    memset(reg, 0, sizeof(reg));
    reg[0] = 1;
    for (ans = 0; !dfs(0); ans++);
    printf("%d\n", ans);
    for (int i = 1; i <= ans; ++i) printf("%s\n", st[i]);
    return 0;
}