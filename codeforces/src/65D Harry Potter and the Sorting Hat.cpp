//
// Created by Psy.C on 2025/10/30.
//
/*
*r[4]：四个学院的缩写字符
house[4][12]：四个学院的完整名称
*p[4]：权重数组，用于编码四个学院的人数
q[4]：临时数组，存储各学院当前人数
mn：最小人数
t：临时变量，用于编码状态
 *声明整型变量n，表示字符串长度
 *声明字符数组str，存储输入字符串
 *声明集合数组s，每个位置存储可能的状态编码
 *声明布尔数组f，标记各学院是否可能成为最终结果
*p[3] = 1：Slytherin学院权重
p[2] = M：Ravenclaw学院权重
p[1] = M²：Hufflepuff学院权重
p[0] = M³：Gryffindor学院权重
 *
 *读取字符串长度n和字符串，从str[1]开始存储
 *在字符串末尾添加'?'，作为结束标记
 *在初始状态插入0，表示四个学院人数都为0
 *
 *循环处理每个字符位置（包括添加的结束标记）
 *遍历前一位置的所有可能状态
*解码当前状态，提取四个学院的人数，并找到最少人数：
(*it) / p[j]) % M：从编码中提取第j个学院的人数
mn = min(mn, q[j])：更新最少人数
*根据当前字符决定如何分配新生：
如果是'?'，只考虑人数最少的学院
如果是指定字符，只考虑对应学院
 *
 *将新生分配给选定的学院
 *编码新的状态
 *如果新状态不存在，则插入到当前状态集合中
*恢复q[j]的值
如果是最后一个位置，标记该学院可能成为结果
 *
 *输出所有可能成为结果的学院名称
 */
#include <cmath>
#include <cstdio>
#include <set>
#include <algorithm>
#include <cstring>
using namespace std;

typedef long long ll;
const int N = 1e6+5;
const ll M = 10001;
const char r[4] = {'G','H','R','S'},
house[4][12] = {"Gryffindor", "Hufflepuff", "Ravenclaw", "Slytherin"};

ll p[4], q[4], mn, t;
int n;
char str[N];
set<ll> s[N];
bool f[4];

int main() {
    p[3] = 1; p[2] = M; p[1] = pow(M, 2); p[0] = pow(M, 3);
    scanf("%d%s", &n, str + 1);
    str[n + 1] = '?';
    s[0].insert(0);

    memset(f, false, sizeof(f));

    for (int i = 1; i <= n + 1; ++i) {
        for (set<ll>::iterator it = s[i - 1].begin(); it != s[i - 1].end(); ++it) {
            mn = 1ll << 60;
            for (int j = 0; j < 4; ++j) {
                q[j] = ((*it) / p[j]) % M;
                mn = min(mn, q[j]);
            }
            for (int j = 0; j < 4; ++j) {
                if (str[i] == '?') { if (q[j] != mn) continue; }
                else { if (str[i] != r[j]) continue; }
                q[j]++;
                t = q[0] * p[0] + q[1] * p[1] + q[2] * p[2] + q[3];
                if (s[i].find(t) == s[i].end()) s[i].insert(t);
                q[j]--;
                if (i == n + 1) f[j] = true;
            }
        }
    }

    for (int i = 0; i < 4; ++i) {
        if (!f[i]) continue;
        puts(house[i]);
    }
    return 0;
}