//
// Created by Psy.C on 2025/11/20.
//
/*
*s[N]: 输入字符串
buf[5]: 临时缓冲区，用于读取字符
k, L, R: 输入参数
idx[N]: 记录每个位置在对应字母序列中的索引
cnt[N]: 计数数组，记录每个位置符合条件的约束数量
in: 当前满足条件(L≤cnt[i]≤R)的位置数量
pos[M]: 每个字母在字符串中出现的所有位置
con[M]: 每个字母对应的约束条件列表
 *
*add1(x): 增加位置x的计数，维护满足条件的位置数in
sub1(x): 减少位置x的计数，维护满足条件的位置数in
当计数达到L时，满足条件的位置数加1
当计数超过R时，满足条件的位置数减1
 *
*遍历字符串，记录每个字母出现的位置：
v = s[i] - 'a': 将字符转换为0-25的数字
将位置i添加到对应字母的位置列表中
记录位置i在该字母序列中的索引
 *
*读取k个约束条件
每个约束包括一个字符和范围[l,r]
将约束添加到对应字母的约束列表中
 *
*对字符串中每个位置i进行处理
v: 当前字符对应的数字(0-25)
p: 当前位置在该字符序列中的索引
*计算位置i初始满足的约束数量：
对于每个字母val的每个约束t[l,r]：
如果val不是当前字符v，检查0是否在[l,r]范围内
如果val是当前字符v，检查1是否在[l,r]范围内
如果位置i的计数在[L,R]范围内，增加满足条件的位置数
 *
*处理当前字符v的每个约束[t.l, t.r]：
计算需要减少计数的区间[a,b]
对该区间内的每个位置调用sub1减少计数
*计算需要增加计数的区间[a,b]
对该区间内的每个位置调用add1增加计数
将当前满足条件的位置数加到答案中
 */
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;

typedef long long ll;
const int N = 100005, M = 26;
char s[N], buf[5];
int k, L, R, idx[N], cnt[N], in;
vector<int> pos[M];
struct node { int l, r; };
vector<node> con[M];

void add1(int x) {
    cnt[x]++;
    if (cnt[x] == L) in++;
    if (cnt[x] == R + 1) in--;
}

void sub1(int x) {
    cnt[x]--;
    if (cnt[x] == R) in++;
    if (cnt[x] == L - 1) in--;
}

int main() {
    scanf("%s",s); int n = strlen(s);
    scanf("%d %d %d", &k, &L, &R);
    rep(i,n) {
        int v = s[i] - 'a';
        pos[v].push_back(i);
        idx[i] = pos[v].size() - 1;
    }
    int l, r;
    rep(i,k) {
        scanf("%s %d %d", buf, &l, &r);
        con[buf[0] - 'a'].push_back({l, r});
    }
    ll ans = 0;
    rep(i,n) {
        int v = s[i] - 'a', p = idx[i];
        cnt[i] = 0;
        rep(val,M) {
            for (auto& t : con[val]) {
                if (val != v) {
                    if (0 >= t.l and 0 <= t.r) cnt[i]++;
                } else {
                    if (1 >= t.l and 1 <= t.r) cnt[i]++;
                }
            }
        }
        if (cnt[i] >= L and cnt[i] <= R) in++;
        for (auto& t : con[v]) {
            l = t.l; r = t.r;
            int a, b;
            if (p - r - 1 >= 0) a = pos[v][p - r - 1] + 1; else a = 0;
            if (p - r >= 0) b = pos[v][p - r]; else b = -1;
            b = min(b, i - 1);
            if (b >= a and a >= 0 and a <= n - 1 and b >= 0 and b <= n - 1) {
                for (int x = a; x <= b; ++x) sub1(x);
            }
            if (p - l >= 0) a = pos[v][p - l] + 1; else a = 0;
            if (p - l + 1 >= 0) b = pos[v][p - l + 1]; else b = -1;
            b = min(b, i - 1);
            if (b >= a and a >= 0 and a <= n - 1 and b >= 0 and b <= n - 1) {
                for (int x = a; x <= b; ++x) add1(x);
            }
        }
        ans += in;
    }
    printf("%lld\n", ans);
    return 0;
}