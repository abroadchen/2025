//
// Created by Psy.C on 2026/3/25.
//
/**
字符串T和S，分别代表模板串和目标串
ch[][]: 字典树结构，ch[x][y]表示节点x通过字符y转移到的节点
cnt: 节点计数器
fr[]: 每个字典树节点对应子串的起始位置
to[]: 每个字典树节点对应子串的结束位置
v[]: 标记数组，v[i]=1表示字符串S的前i个字符可以被分解
d[]: DP数组，d[i]表示分解S[1..i]所需的最少子串数量

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 2100;

char T[N], S[N];
int ch[N*N][26], cnt, fr[N*N], to[N*N], v[N], d[N];

///重构解路径
void dfs(int x) {
    if (x <= 0) return;
    //递归访问前一个状态，前一个状态的位置是
    dfs(x - abs(fr[v[x]] - to[v[x]]) - 1);
    printf("%d %d\n", to[v[x]], fr[v[x]]);
}

int main() {
    fast;
    scanf("%s%s", T+1, S+1);
    int i;
    //构建包含T的所有子串的字典树（正向遍历）
    for (i = 1; T[i]; ++i) {
        int x = 0;//当前字典树节点
        for (int j = i; T[j]; ++j) {//从位置i开始的所有后缀
            int y = T[j] - 'a';
            if (ch[x][y] == 0) ch[x][y] = ++cnt;//如果不存在转移，则创建新节点
            x = ch[x][y];//移动到下一个节点
            fr[x] = i, to[x] = j;//记录这个节点对应T中的子串范围 [i,j]
        }
    }
    for (--i; i >= 1; --i) {//从最后一个字符开始向前遍历
        int x = 0;
        for (int j = i; j >= 1; --j) {//从位置i开始向前的所有子串
            int y = T[j] - 'a';
            if (ch[x][y] == 0) ch[x][y] = ++cnt;
            x = ch[x][y];
            fr[x] = i, to[x] = j;
        }
    }
    v[0] = 1;//空字符串可以被分解
    for (i = 1; S[i]; ++i) {//遍历字符串S的每个位置
        int x = 0;
        for (int j = i; j >= 1; --j) {//从位置i向前尝试所有可能的子串S[j..i]
            int y = S[j] - 'a';
            if (ch[x][y] == 0) break;//在字典树中找不到匹配
            x = ch[x][y];
            if (v[j-1]) {//S的前j-1个字符可以被分解
                if (d[i] == 0 || d[i] > d[j-1] + 1) {
                    d[i] = d[j-1] + 1;
                    v[i] = x;//到达i位置使用的字典树节点
                }
            }
        }
    }
    if (d[i-1] == 0) { printf("-1"); return 0; }//无法分解整个字符串S
    printf("%d\n", d[i-1]);//分解所需的最少子串数量
    dfs(i-1);//重构并输出具体的分解方案
    return 0;
}