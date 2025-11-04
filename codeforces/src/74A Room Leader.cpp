//
// Created by Psy.C on 2025/11/4.
//
/*
*声明变量n用于存储参赛人数
读取n值，\n用于消耗换行符
创建map容器scores，用于存储姓名和对应分数的映射关系
*
循环处理每个参赛者的信息
声明字符数组name存储姓名（最多19个字符+结束符）
读取姓名
声明临时变量t和总分变量tot，初始值都为0
*读取第一个数值t，将其乘以100加到总分上（可能是加分项）
读取第二个数值t，将其乘以50从总分中减去（可能是扣分项）
 *循环读取5个数值，每个数值直接加到总分上（可能是5道题的得分）
*读取换行符，准备下一轮输入
将姓名和总分作为键值对插入到scores映射中
 *
*声明映射迭代器it，指向第一个元素
初始化结果姓名r为第一个参赛者的姓名
初始化最高分m为第一个参赛者的分数
*遍历所有参赛者：
如果当前参赛者的分数高于当前最高分
更新最高分持有者姓名和最高分值
 */
#include <cstdio>
#include <string>
#include <map>
using namespace std;

int main() {
    int n; scanf("%d\n", &n);
    map<string, int> scores;

    for (int i = 0; i < n; ++i) {
        char name[20]; scanf("%s", name);
        int t(0), tot(0);
        scanf("%d", &t); tot += 100 * t;
        scanf("%d", &t); tot -= 50 * t;
        for (int j = 0; j < 5; ++j) {
            scanf("%d", &t);
            tot += t;
        }
        scanf("\n");
        scores.insert(pair<string, int>(string(name), tot));
    }

    map<string, int>::iterator it = scores.begin();
    string r = it->first;
    int m = it->second;

    for (it = scores.begin(); it != scores.end(); ++it) {
        if (it->second > m) {
            r = it->first;
            m = it->second;
        }
    }
    printf("%s\n", r.c_str());
    return 0;
}