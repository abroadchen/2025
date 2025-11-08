//
// Created by Psy.C on 2025/10/29.
//
/*
*定义宏bit(x,k)：用于检查数字x的第k位是否为1
(x)>>k：将x右移k位
&1：与1进行按位与运算，得到最低位的值
 *
*
定义数组r，表示每行的有效格子数：
第0行：0个格子（占位符）
第1行：3个格子
第2行：4个格子
第3行：5个格子
第4行：4个格子
第5行：3个格子
这形成了一个六边形棋盘布局
 *
*定义方向向量：
dx[0]=0, dy[0]=1：向右移动
dx[1]=1, dy[1]=0：向下移动
dx[2]=1, dy[2]=1：向右下移动
 *
*mask：表示当前棋盘状态的位掩码
id[N][N]：给每个格子分配唯一ID
f[1<<N]：记忆化搜索的DP数组
 *
 *定义函数isvalid，检查位置(i,j)在状态x下是否有效
 *检查行列索引是否越界
 *检查列是否超出该行范围，或该位置在状态x中是否为空
 *
 *定义递归函数ok，使用记忆化搜索判断当前状态x的胜负情况
 *如果该状态已计算过，直接返回结果
 *如果棋盘为空（游戏结束），当前玩家失败，返回0
 *遍历棋盘上的每个位置
 *如果当前位置有棋子
 *尝试三种方向移
 *初始化临时变量：y为当前状态，(u,v)为当前位置
 *沿着选定方向最多移动6步
 *
*读取棋盘状态并初始化：
外层循环遍历行（0到5）
内层循环遍历每行的格子
读取字符到a[i][j]
给每个格子分配唯一ID
如果是'O'则在mask中对应位置设为1
初始化DP数组f为-1，表示尚未计算
调用ok函数判断初始状态的胜负：
如果返回1（当前玩家必胜），输出"Karlsson"
否则输出"Lillebror"
 */
#include <cstring>
#include <iostream>
#define bit(x,k) ((x)>>(k)&1)
using namespace std;

const int N = 19;
const int r[] = {0,3,4,5,4,3},
dx[] = {0,1,1}, dy[] = {1,0,1};

int mask(0), id[N][N], f[1<<N];
char a[N][N];//存储棋盘状态

bool isvalid(int i, int j, int x) {
    if (i < 1 || j < 1 || i > 5) return false;
    if (j > r[i] || !bit(x, id[i][j])) return false;
    return true;
}

int ok(int x) {
    if (f[x] != -1) return f[x];
    if (x == 0) return f[x] = 0;
    for (int i = 1; i <= 5; ++i) {
        for (int j = 1; j <= r[i]; ++j) {
            if (bit(x, id[i][j])) {
                for (int t = 0; t < 3; ++t) {
                    int y = x, u = i, v = j;
                    for (int s = 0; s <= 5; ++s) {
                        y ^= 1 << id[u][v];//移除当前位置的棋子（异或操作切换该位）
                        if (ok(y) == 0) return f[x] = 1;//如果下一步状态对手必败，则当前玩家必胜，返回1
                        u += dx[t], v += dy[t] - (t > 0 && u >= 4);//移动到下一个位置，特殊处理第4行以后的坐标变化
                        if (!isvalid(u, v, y)) break;//如果新位置无效则停止该方向的移动
                    }
                }
            }
        }
    }
    return f[x] = 0;//如果找不到获胜策略，返回0表示当前玩家必败
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);

    for (int i = 0, cur = 0; i <= 5; ++i) {
        for (int j = 1; j <= r[i]; ++j) {
            cin >> a[i][j];
            id[i][j] = cur++;
            mask += ((a[i][j] == 'O') << id[i][j]);
        }
    }
    memset(f, -1, sizeof(f));
    cout << (ok(mask) == 1 ? "Karlsson" : "Lillebror") << '\n';
    return 0;
}