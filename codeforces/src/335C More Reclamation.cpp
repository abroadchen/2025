/**
 *
* j：第一段的长度（从0到j-1）
i-j-1：第二段的长度（从j+1到i-1，不包含位置j）
SG[j][2]：第一段的SG值
SG[i-j-1][2]：第二段的SG值
SG[j][2]^SG[i-j-1][2]：两段组合的SG值（根据SG定理）
 *
 * SG[i][1] - 特殊状态
*计算方式依赖于类型2的状态
通常用于n=0的特殊情况
 *SG[i][2] - 单行/单列状态
*代表单行或单列的游戏状态
可以分割成类型3+类型2 或 类型4+类型2 的组合
 *SG[i][3] - 同行/同类状态
*代表同一类别的连续段
可以分割成类型3+类型3 或 类型4+类型4 的组合
 *SG[i][4] - 不同行/异类状态
*代表不同类别的连续段
可以分割成类型3+类型4 或 类型4+类型3 的组合
 */
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;
int SG[110][5];//用SG[i][j]表示长度为i类型为j的一段的SG值
map<int, bool> vis;
//其中SG[0][j] = 0
//注意SG[0][4]其实是不可取的, 因为河道被封死了

struct Die {
    int r{}, c{};
    Die()= default;
};
Die die[110];//障碍物信息

bool cmp(const Die d1, const Die d2) { return d1.r < d2.r; }

int main() {
    for(int i = 1; i <= 100; i++) {//长度为1到100的各种状态的SG值
        vis.clear();
        for(int j = 0; j < i; j++)
            vis[SG[j][2]^SG[i - j - 1][2]] = 1;//记录子游戏组合的SG值
        SG[i][1] = 0;
        while(vis[SG[i][1]]) SG[i][1]++;//找到最小的未出现值（Mex操作）

        vis.clear();
        for(int j = 0; j < i; j++)
            vis[SG[j][3]^SG[i - j - 1][2]] = 1;
        for(int j = 1; j < i; j++)//j从1开始因为SG[0][4]不可取, 以下同理
            vis[SG[j][4]^SG[i - j - 1][2]] = 1;
        SG[i][2] = 0;
        while(vis[SG[i][2]]) SG[i][2]++;

        vis.clear();
        for(int j = 0; j < i; j++)
            vis[SG[j][3]^SG[i - j - 1][3]] = 1;
        for(int j = 1; j < i - 1; j++)
            vis[SG[j][4]^SG[i - j - 1][4]] = 1;
        SG[i][3] = 0;
        while(vis[SG[i][3]]) SG[i][3]++;

        vis.clear();
        for(int j = 0; j < i - 1; j++)
            vis[SG[j][3]^SG[i - j - 1][4]] = 1;
        for(int j = 1; j < i; j++)
            vis[SG[j][4]^SG[i - j - 1][3]] = 1;
        SG[i][4] = 0;
        while(vis[SG[i][4]]) SG[i][4]++;
    }
    int row, n; scanf("%d %d", &row, &n);//行数 row 和障碍物数量 n
    if(n == 0) {//没有障碍物
        if(SG[row][1]) printf("WIN\n"); else printf("LOSE\n");//SG值非0则先手胜 使用 SG[row][1] 判断胜负
        return 0;
    }
    for(int i = 1; i <= n; i++) scanf("%d %d", &die[i].r, &die[i].c);//n个障碍物的坐标
    sort(die + 1, die + n + 1, cmp);
    int sg = 0;
    sg ^= SG[die[1].r - 1][2];//对于很多段段求游戏的和
    for(int i = 1; i < n; i++) {
        if(die[i].c == die[i + 1].c) sg ^= SG[die[i + 1].r - die[i].r - 1][3];//如果在同一列 使用类型3的SG值
        else sg ^= SG[die[i + 1].r - die[i].r - 1][4];
    }
    sg ^= SG[row - die[n].r][2];//最后一个障碍物之后到行末的SG值
    if(sg) printf("WIN\n"); else printf("LOSE\n");
    return 0;
}