//
// Created by Psy.C on 2025/9/19.
//
/*
*读取边的数量n
定义两个集合in和out，用于跟踪节点的入度和出度状态
定义totalCost记录所有边的总权重，cost记录选择的边的总权重
 *
 *
*循环处理每条边，n减到0时结束
读取边的起点a、终点b和权重c
累加到总权重totalCost
关键逻辑判断：
如果起点a已经在in集合中，或者终点b已经在out集合中
说明这条边需要被"覆盖"，将权重加到cost
将a加入out集合，b加入in集合
否则
不需要立即处理这条边
将a加入in集合，b加入out集合
这个贪心策略试图构建一个最小的点覆盖
 *
 *
*比较选择的边权重和未选择的边权重
取较小值作为最终结果（这是基于二分图最小点覆盖的对偶性质）
输出最小成本
 *
 *
 *
 *
 *
 *
 */
#include <cstdio>
#include <set>
using namespace std;

int main() {
    int n; scanf("%d\n",&n);
    set<int> in, out;
    long totalCost(0), cost(0);

    while (n--) {
        int a, b, c; scanf("%d %d %d\n",&a,&b,&c);
        totalCost += c;
        if (in.count(a) || out.count(b)) {
            cost += c;
            out.insert(a);
            in.insert(b);
        } else {
            in.insert(a);
            out.insert(b);
        }
    }

    if (totalCost - cost < cost) cost = totalCost - cost;
    printf("%ld\n",cost);
    
    return 0;
}