//
// Created by Psy.C on 2026/2/8.
//
/**
s[i] - 96: 将'a'-'z'映射为1-26（ASCII码'a'=97，所以减96）
r = r*26 + s[i] - 96: 26进制字符串哈希

s[N]: 主字符串
a[5], b[5]: 临时字符串（最大长度4）
mp[500009]: 哈希值到ID的映射
len[N]: 每个ID对应字符串的长度
p[5][N]: p[len][pos]表示从位置pos开始长度为len的子串的ID
h[N]: 重频子串的处理标记
f[331][N]: 预处理结果表
v[N]: 每个子串ID在主串中出现位置的列表

l = 1到4: 遍历所有长度为1-4的子串
j = n - l + 2: 循环的结束条件
k = get(s + i, l): 计算从位置i开始长度为l的子串的哈希值
if (!mp[k]): 如果该哈希值第一次出现
v[p[l][i]=mp[k]].push_back(i): 将位置i添加到对应子串的出现位置列表

遍历所有子串ID
只处理出现次数超过500的子串
h[i] = ++ct: 为当前高频子串i分配一个新的处理编号ct
u = len[i]: 获取当前子串的长度
memset(f[ct], 9, id+2<<2): 将f[ct]数组初始化为大值
id+2<<2 = (id+2)*4，因为int是4字节
9在这里代表一个大值（类似INF）
for (k = 1; k < j; ++k): 遍历相邻的两个出现位置
x = v[i][k-1], y = v[i][k]: x和y是相邻的两个出现位置
for (z = x; z < y; ++z): 遍历x到y-1之间的所有位置
for (l = 1; l < 5; ++l): 遍历长度为1-4的所有子串
p[l][z]: 从位置z开始长度为l的子串ID
z + l - x: 从位置z的l长度子串到位置x的u长度子串的距离
max(z + l - x, u): 两个子串间的某种距离度量
max(y + u - z, l): 从z到右边位置y的距离度量
min(...)：取两种距离的较小值
f[ct][p[l][z]]: 更新该子串与其他高频子串的最小距离
z = x = v[i][j-1]: 从该高频子串最后一次出现位置开始
z <= n: 处理到字符串末尾
max(z + l - x, u): 计算从末尾出现位置x到位置z的l长度子串的距离
z = 1, y = v[i][0]: 从字符串开头到该高频子串第一次出现位置
max(y + u - z, l): 计算从位置z的l长度子串到第一次出现位置y的距离

x = mp[get(a, strlen(a))]: 获取字符串a的ID
y = mp[get(b, strlen(b))]: 获取字符串b的ID
if (!x || !y) puts ("-1"): 如果任一子串不存在，输出-1
if (h[x]) printf ("%d\n", f[h[x]][y]): 如果x是高频子串，直接查表
else if (h[y]) printf ("%d\n", f[h[y]][x]): 如果y是高频子串，直接查表
最后一个else分支：两个都是低频子串，暴力计算最小距离

j = v[x].size(): x子串在主串中的出现次数
k = v[y].size() - 1: y子串出现次数-1（作为最大索引）
l = len[x]: x子串的长度
u = len[y]: y子串的长度
z = 0: 指向y子串出现位置的指针，初始化为0
o = 1e9: 初始化为无穷大，用于记录最小距离

for (i = 0; i < j; ++i): 遍历x子串的所有出现位置
while (z < k && v[y][z] < v[x][i]) ++z;: 二分查找优化
在y子串的出现位置中找到第一个 ≥ x[i] 的位置
由于v[x]和v[y]都是有序的，可以用双指针优化

y子串在位置v[y][z]出现，且该位置 ≥ x子串在v[x][i]的位置
v[y][z] + u - v[x][i]: 从x子串结束位置到y子串开始位置的距离
v[y][z] + u: y子串的结束位置
v[x][i]: x子串的开始位置

如果z > 0（存在前一个y子串出现位置）
v[x][i] + l - v[y][z-1]: 从y子串前一个出现位置到x子串结束位置的距离
v[x][i] + l: x子串的结束位置
v[y][z-1]: y子串前一个出现位置

当前找到的y子串位置 < x子串位置
v[x][i] + l - v[y][z]: 从y子串位置到x子串结束位置的距离
取计算出的最小距离和两个子串长度的最大值

高频子串：O(1)查询
低频子串：O(|occ_a| * log|occ_b|)查询
 */
#include <bits/stdc++.h>
#define N 70009
using namespace std;

//将字符串转换为哈希值
inline int get(const char *s, const int l) {
    int r = 0;
    for (int i = 0; i < l; ++i) r = r*26 + s[i] - 96;
    return r;
}

char s[N], a[5], b[5];
int mp[500009], len[N], p[5][N], h[N], f[331][N];
vector<int> v[N];


int main() {
    int q, n, l, i, j, k, id=0, ct=0, u, x, y, z, o;
    scanf ("%s%d", s + 1, &q); n = strlen(s + 1);
    for (l = 1; l < 5; ++l) for (i = 1, j = n - l + 2; i < j; ++i) {
        k = get(s + i, l);
        if (!mp[k]) mp[k] = ++id, len[id] = l;
        v[p[l][i]=mp[k]].push_back(i);
    }
    for (i = 1; i <= id; ++i) if (j = v[i].size(), j > 500) {
        h[i] = ++ct, u = len[i], memset(f[ct], 9, id+2<<2);
        for (k = 1; k < j; ++k) {
            x = v[i][k-1], y = v[i][k];
            for (z = x; z < y; ++z) for (l = 1; l < 5; ++l)
                f[ct][p[l][z]] = min(f[ct][p[l][z]],
                    min(max(z + l - x, u), max(y + u - z, l)));
        }
        for (z = x = v[i][j-1]; z <= n; ++z) for (l = 1; l < 5; ++l)
            f[ct][p[l][z]] = min(f[ct][p[l][z]], max(z + l - x, u));
        for (z = 1, y = v[i][0]; z < y; ++z) for (l = 1; l < 5; ++l)
            f[ct][p[l][z]] = min(f[ct][p[l][z]], max(y + u - z, l));
    }
    while (q--) {
        scanf ("%s%s", a, b), x = mp[get(a, strlen(a))], y = mp[get(b, strlen(b))];
        if (!x || !y) puts ("-1");
        else if (h[x]) printf ("%d\n", f[h[x]][y]);
        else if (h[y]) printf ("%d\n", f[h[y]][x]);
        else {
            j = v[x].size(), k = v[y].size() - 1, l = len[x], u = len[y], z = 0, o = 1e9;
            for (i = 0; i < j; ++i) {
                while (z < k && v[y][z] < v[x][i]) ++z;
                if (v[y][z] >= v[x][i]) {
                    o = min(o, v[y][z] + u - v[x][i]);
                    if (z) o = min(o, v[x][i] + l - v[y][z-1]);
                } else o = min(o, v[x][i] + l - v[y][z]);
            }
            printf ("%d\n", max(o, max(l, u)));
        }
    }
    return 0;
}