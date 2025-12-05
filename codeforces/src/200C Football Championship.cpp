//
// Created by Psy.C on 2025/12/4.
//
/*
*str1, str2, str3：临时字符串用于解析输入
s[N]：存储队伍名称的数组（"BERLAND"固定在索引3）
mp：将队伍名称映射到索引的映射表
num[N]：每支队伍的比赛场次
gs[N]：每支队伍的进球数
gm[N]：每支队伍的失球数
sc[N]：每支队伍的积分
mn：找到的最小净胜球差
tsg[N], tmg[N]：临时数组存储进球/失球
ax, ay：最终的答案坐标（比分）
 *
*判断在给定积分情况下BERLAND是否能晋级：
创建积分数组的副本并排序
t[]：排序后的积分副本
rank[]：存储排序后对应原队伍索引
vis[]：访问标记数组
r：BERLAND在排序后的位置（初始为0）
 *将排序后的积分映射回原来的队伍索引
 *找到BERLAND在排名中的位置
*处理积分相同情况下的排名规则：
比较净胜球数
如果还相同，比较总进球数
如果还相同，按队名字母顺序排列
 *如果BERLAND排在前两名（索引2或3，因为0索引），返回1表示可以晋级，否则返回0
 *
 *找出没有打满3场比赛的队伍（即BERLAND的对手)
*尝试所有BERLAND进球数大于对手的比分组合(i>j)：
模拟比赛结果
更新临时统计数据
根据比赛结果计算积分（胜3分，平1分，负0分）
 *检查此比分下BERLAND是否能晋级，如果是且净胜球更少，则更新最佳解
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for(i=0;i<n;++i)
using namespace std;

constexpr int N = 4, M = 100, inf = 999999999;
string str1, s[N], str2, str3;
map<string, int> mp;
int num[N], gs[N], gm[N], sc[N], mn;
int tsg[N], tmg[N];
int ax, ay;

int ok(int x[]) {
    int t[N], rank[N], vis[N], i, j, r = 0;
    memcpy(t, x, sizeof t);
    memset(rank, 0, sizeof rank);
    memset(vis, 0, sizeof vis);
    sort(t, t+N);
    rep(i,N) rep(j,N) if (t[i] == x[j] && !vis[j]) {
        rank[i] = j; vis[j] = 1; break;
    }
    rep(i,N) if (rank[i] == 3) r = i;
    rep(i,N) {
        if (i != r && t[i] == t[r]) {
            if (tsg[3] - tmg[3] > tsg[rank[i]] - tmg[rank[i]]) {
                if (i > r) swap(rank[i], rank[r]), r = i;
            }
            if (tsg[3] - tmg[3] == tsg[rank[i]] - tmg[rank[i]]) {
                if (tsg[3] > tsg[rank[i]]) if (i > r) {
                    swap(rank[i], rank[r]), r = i;
                }
                if (tsg[3] == tsg[rank[i]]) {
                    if (s[3] < s[rank[i]]) if (i > r) {
                        swap(rank[i], rank[r]), r = i;
                    }
                    if (s[3] > s[rank[i]]) if (i < r) {
                        swap(rank[i], rank[r]), r = i;
                    }
                }
                if (tsg[3] < tsg[rank[i]]) if (i < r) {
                    swap(rank[i], rank[r]), r = i;
                }
            }
            if (tsg[3] - tmg[3] < tsg[rank[i]] - tmg[rank[i]]) if (i < r) {
                swap(rank[i], rank[r]), r = i;
            }
        }
    }
    if (r >= 2) return 1;
    return 0;
}

void f() {
    int i, k = 0, j, x, y;
    rep(i,N) if (i != 3 && num[i] != 3) k = i;
    int ts[N];
    rep(i,M+1) rep(j,M+1) {
        if (i <= j) continue;
        x = i, y = j;
        memcpy(ts, sc, sizeof ts);
        memcpy(tsg, gs, sizeof gs);
        memcpy(tmg, gm, sizeof gm);
        tsg[3] += i, tmg[3] += j;
        tsg[k] += j, tmg[k] += i;
        if (x == y) ts[3]++, ts[k]++;
        if (x > y) ts[3] += 3;
        if (x < y) ts[k] += 3;
        if (ok(ts)) if (mn > i - j) {
            ax = i, ay = j;
            mn = i - j;
        }
    }
}

int main() {
    fast;
    int c1 = 0, c2 = 0, i, k, x, y;
    while (cin >> str1) {
        mp.clear();//清空之前的数据并初始化队伍名称
        rep(i,N-1) s[i] = "";
        s[3] = "BERLAND";
        rep(k,N+1) {//读取比赛结果。特殊处理第一场比赛（没有第一个队伍）
            if (k > 0) cin >> str1 >> str2 >> str3;
            else cin >> str2 >> str3;
            if (str1 == s[3]) c1 = 3;
            if (str2 == s[3]) c2 = 3;
            if (str1 != s[3]) {//识别队伍并分配索引，将新队伍添加到列表中
                rep(i,N-1) if (s[i] == str1) { c1 = i; break; }
                if (i == 3) {
                    rep(i,N-1) if (s[i].empty()) {
                        s[i] = str1; c1 = i; break;
                    }
                }
            }
            if (str2 != s[3]) {
                rep(i,N-1) if (s[i] == str2) { c2 = i; break; }
                if (i == 3) {
                    rep(i,N-1) if (s[i].empty()) {
                        s[i] = str2; c2 = i; break;
                    }
                }
            }
            x = str3[0] - '0', y = str3[2] - '0';//解析比赛比分并更新统计
            num[c1]++, num[c2]++;
            gs[c1] += x, gm[c1] += y;
            gs[c2] += y, gm[c2] += x;
            if (x == y) sc[c1]++, sc[c2]++;
            if (x > y) sc[c1] += 3;
            if (x < y) sc[c2] += 3;
        }
        mn = inf;
        f();
        if (mn != inf) cout << ax << ':' << ay << '\n';
        else cout << "IMPOSSIBLE\n";
        memset(sc, 0, sizeof sc);//重置数组
        memset(num, 0, sizeof num);
        memset(gs, 0, sizeof gs);
        memset(gm, 0, sizeof gm);
    }
    return 0;
}
