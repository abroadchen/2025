//
// Created by Psy.C on 2026/10/30.
//

/**
真正学会的起点..
c[N]：颜色（字符编号，cl）。
v[N]：数值（该段连续字符的数量，即"游程长度"）。
nxt[N]：链表后继指针。
add(cl, tot, nx)：在链表尾部新建一个节点，记录颜色、长度、后继，返回新节点下标。
这是一套游程编码 + 静态链表结构，用于高效合并连续相同字符的段
遍历字符串 s，做游程压缩：相邻相同字符合并成一个节点，v[p] 累计长度。
每遇到不同字符就新建节点，len[f] 记录该字符串的段数。
head[0]、head[1] 分别指向两个字符串的链表头。
三个函数都返回 abs(关于 x 的某个差值)，用于量化"把 a 段的 x 个元素转移到 b 段后，两边长度差"，x 是转移数量。
它们分别对应三种不同操作/合并情形下的成本，用来决定最优的 x
遍历链表 f，返回节点总数（段数）。用于链表很短时重新精确计数（因为手动维护的 len[f] 可能失准）
n：操作次数计数器。
ans[i][0], ans[i][1]：第 i 次操作的参数（两个数值，记录在 L、R 两个指针所指的位置）。
init(l, r)：记录一次操作及其两个参数
读入两个字符串，分别构建游程链表。
只要较长的链表段数 > 1，就不断收缩（即不停合并）
始终让 L 指向段数较多的那条链表（使得 L ≥ R）
分支一：颜色头相同 且 R>1 且 L>2
两条链表开头颜色相同，且 R>1、L>2。
通过枚举 x1、x2 计算让 f1 最小的转移数 x，限制在 [1, a/2]
沿 L 链表走 2x-1 段，累加得到 tot，记录一次操作 (tot, v[head[R]])
复杂的链表重组：把 L 的前 x*2 段与 R 的头进行拼接合并（把 R 的头拼到 L 段上，并合并相邻同色段），同时更新 L、R 两链表结构和长度。len[L] 减 2x，len[R] 加 2x-2
分支二：头颜色相同（但不符合分支一条件）
头颜色相同、但不满足分支一条件时，计算最优 x（用 min，未做 max(1,...) 下限），记录操作 (tot, 0)。
进行另一套链表交换/合并：交换两链表头、把 L 的 x*2 段并入 R 头，合并相邻同色。
若 len 很小（<3）则用 get() 精确重算，否则按公式更新长度
分支三：头颜色不同
头颜色不同时，用 f2 计算最优 x，记录操作 (tot, v[head[R]])。
另一套链表重组：把 R 头与 L 的 x*2 段交错合并（v[head[R]] += v[nxt[p]] 等），并交换两链表头、合并相邻同色段。
同样更新两链表长度，短时用 get() 重算。
输出操作总次数 n，再逐行输出每次操作的参数 (ans[i][0], ans[i][1])
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e6+5;

int cnt, c[N], v[N], nxt[N];
int add(int cl, int tot, int nx) {
    c[++cnt] = cl; v[cnt] = tot; nxt[cnt] = nx;
    return cnt;
}

int head[2], len[2];
void build(int f, char s[]) {
    int n = strlen(s+1), p = add(s[1]-'a', 1, 0);
    head[f] = p, len[f] = 1;
    for (int i = 2; i <= n; i++) {
        if (s[i] == s[i-1]) v[p]++;
        else p = nxt[p] = add(s[i]-'a', 1, 0), len[f]++;
    }
}

int f0(int x, int a, int b) { return abs((a-2*x-1)-(b+2*x)); }
int f1(int x, int a, int b) { return abs((a-2*x)-(b+2*x-2)); }
int f2(int x, int a, int b) { return abs((a-2*x-1)-(b+2*x-1)); }
int get(int f) {
    int tot = 0;
    for (int p = head[f]; p; p = nxt[p]) tot++;
    return tot;
}

int n, ans[N][2], L(0), R(1);
void init(int l, int r) {
    n++;
    ans[n][L] = l, ans[n][R] = r;
}

char s1[N], s2[N];
int main() {
    fast;
    scanf("%s%s", s1+1, s2+1); build(0,s1); build(1,s2);
    while (max(len[L], len[R]) > 1) {
        if (len[L] < len[R]) swap(L, R);
        if (c[head[L]] == c[head[R]] && len[R] > 1 && len[L] > 2) {
            int a = len[L], b = len[R], x1 = (a-b+2)/4, x2 = x1 + 1;
            int x = max(1, min(f1(x1,a,b) <= f1(x2,a,b) ? x1 : x2, a/2));
            int tot = v[head[L]], p = head[L];
            for (int i = 1; i <= x*2-1; i++) p = nxt[p], tot += v[p];
            init(tot, v[head[R]]);
            int l = head[L], r = head[R];
            v[head[L]=nxt[p]] += v[r]; head[R] = l; nxt[p] = nxt[nxt[r]]; v[p] += v[nxt[r]];
            len[L] -= x*2, len[R] += x*2-2;
            continue;
        }
        if (c[head[L]] == c[head[R]]) {
            int a = len[L], b = len[R], x1 = (a-b-1)/4, x2 = x1 + 1;
            int x = min(f0(x1,a,b) <= f0(x2,a,b) ? x1 : x2, (a-1)/2);
            int tot = v[head[L]], p = head[L];
            for (int i = 1; i <= x*2; i++) p = nxt[p], tot += v[p];
            init(tot, 0); swap(head[R], head[L]); swap(nxt[p], head[L]);
            v[p] += v[nxt[p]]; nxt[p] = nxt[nxt[p]];
            len[L] = len[L]<3 ? get(L) : len[L]-(x*2+1);
            len[R] = len[R]<3 ? get(R) : len[R]+x*2;
        } else {
            int a = len[L], b = len[R], x1 = (a-b-1)/4, x2 = x1 + 1;
            int x = min(f2(x1,a,b) <= f2(x2,a,b) ? x1 : x2, (a-1)/2);
            int tot = v[head[L]], p = head[L];
            for (int i = 1; i <= x*2; i++) p = nxt[p], tot += v[p];
            init(tot, v[head[R]]);
            v[head[R]] += v[nxt[p]]; v[p] += v[nxt[head[R]]]; swap(nxt[head[R]], nxt[p]);
            nxt[head[R]] = nxt[nxt[head[R]]]; nxt[p] = nxt[nxt[p]]; swap(head[L], head[R]);
            len[L] = len[L]<3 ? get(L) : len[L]-(x*2+1);
            len[R] = len[R]<3 ? get(R) : len[R]+(x*2-1);
        }
    }
    cout << n << '\n';
    for (int i = 1; i <= n; i++) cout << ans[i][0] << ' ' << ans[i][1] << '\n';
    return 0;
}