//
// Created by Psy.C on 2025/9/20.
//
/*
*r: map容器，存储每个城市的邻接城市列表（图的邻接表表示）
num: map容器，存储每个城市的度数（连接的边数）
 *
 *x和y表示连接的两个城市
 *
*构建无向图的邻接表：
如果城市x第一次出现，创建包含城市y的邻接列表
否则将城市y添加到城市x的邻接列表中
对城市y执行相同操作（因为是无向边）
 *
*统计每个城市的度数：
如果城市x第一次出现，度数设为1
否则度数加1
对城市y执行相同操作
 *
*寻找度数为1的城市作为起始点
在树结构中，度数为1的节点是叶子节点
找到第一个叶子节点作为遍历起点
 *
*创建set容器been用于记录已访问的城市
将起始城市标记为已访问
 *
*进行n次遍历（因为有n条边，需要访问n+1个节点）
获取当前城市的所有邻接城市
遍历邻接城市列表，找到第一个未访问的城市
将该城市作为下一个访问城市，输出并标记为已访问
 *
 *
 */
#include <cstdio>
#include <map>
#include <vector>
#include <set>
using namespace std;

int main() {
    long n; scanf("%ld", &n);
    map<long, vector<long>> r;
    map<long, int> num;

    for (long i = 0; i < n; ++i) {
        long x, y; scanf("%ld %ld", &x, &y);
        if (r.count(x) == 0) r[x] = vector<long>(1, y);
        else r[x].push_back(y);

        if (r.count(y) == 0) r[y] = vector<long>(1, x);
        else r[y].push_back(x);

        if (num.count(x) == 0) num[x] = 1; else ++num[x];
        if (num.count(y) == 0) num[y] = 1; else ++num[y];
    }

    long city(-1);
    for (map<long, int>::iterator it = num.begin(); it != num.end(); ++it) {
        if (it->second == 1) {
            city = it->first;
            break;
        }
    }

    printf("%ld ", city);
    set<long> been; been.insert(city);

    for (long i = 0; i < n; ++i) {
        vector<long> v = r[city];
        for (long j = 0; j < v.size(); ++j) {
            if (been.count(v[j]) > 0) continue;
            else {
                city = v[j];
                printf("%ld ", city);
                been.insert(city);
                break;
            }
        }
    }
    puts("");

    return 0;
}