//
// Created by Psy.C on 2025/9/20.
//
/*
*循环读取n*(n-1)/2-1场比赛结果（总共有n*(n-1)/2场比赛，这里少读了一场）
x和y是获胜和失败队伍的编号（从1开始）
--x和--y将编号转换为从0开始的索引
将结果记录到win和lose集合中

 *初始化两个变量a和b为-1，用于存储未比赛的两个队伍
 *
*遍历所有队伍
如果队伍i参与的比赛数(胜利+失败) >= n-1，说明已和其他所有队伍比赛过，跳过
找到第一个未完成所有比赛的队伍赋给a
找到第二个未完成所有比赛的队伍赋给b
 *
 *
*遍历所有队伍i来判断a和b之间的胜负关系
如果a战胜了队伍i且b败给了队伍i，说明a胜b，保持a,b顺序不变
如果a败给了队伍i且b战胜了队伍i，说明b胜a，交换a和b的位置
找到决定性证据后跳出循环
 *
 *
 *输出两个队伍的编号（加1是因为内部使用0索引，但题目要求输出1索引）
 *
 *
 *
 *
 *
 */
#include <cstdio>
#include <set>
#include <vector>
using namespace std;

int main() {
    int n; scanf("%d",&n);//存储队伍数量
    vector<set<int>> win(n);
    vector<set<int>> lose(n);

    for (int i = 1; i < n * (n - 1) / 2; ++i) {
        long x, y; scanf("%ld %ld",&x,&y);
        --x;--y;
        win[x].insert(y); lose[y].insert(x);
    }

    int a(-1), b(-1);
    for (int i = 0; i < n; ++i) {
        if (win[i].size() + lose[i].size() >= n - 1) continue;
        if (a < 0) a = i;
        else if (b < 0) b = i;
    }

    for (long i = 0; i < n; ++i) {
        if (win[a].count(i) && lose[b].count(i)) break;
        else if (lose[a].count(i) && win[b].count(i)) {
            int t = a;
            a = b;
            b = t;
            break;
        }
    }

    printf("%d %d\n",a + 1,b + 1);
    
    return 0;
}