//
// Created by Psy.C on 2025/9/19.
//
/*
*如果x是根节点(v[x] == x)，直接返回x
否则递归查找根节点，并将路径上的节点直接连接到根节点
 *
*读取节点数n
创建大小为n+1的并查集数组f，初始化f[i] = i（每个节点初始时是自己的父节点）
 *
*创建向量rem存储多余的边
读取n-1条边（理论上树应该有n-1条边）
对每条边(x,y)：
找到x和y所在的集合的根节点r和s
如果r == s，说明x和y已经在同一集合中，这条边是多余的，加入rem
否则将两个集合合并：f[s] = r
 *
*创建向量add存储需要添加的边
从节点2开始遍历所有节点
如果节点i与节点1在同一个集合中，跳过
否则将节点i所在集合的根节点与节点1所在集合连接
记录这条连接边，并合并两个集合
 *
 *
*输出多余边的数量
对每条多余边，输出原边和对应的替换边
 *
 *
 *时间复杂度：O(n×α(n))，其中α是阿克曼函数的反函数，近似为常数
 *
 *
 */
#include <cstdio>
#include <vector>
using namespace std;

long find(long x, vector<long>& v) {
    return (v[x] == x) ? x : (v[x] = find(v[x], v));
}

int main() {
    long n; scanf("%ld",&n);
    vector<long> f(n + 1, 0);
    for (long i = 1; i <= n; ++i) f[i] = i;

    vector<pair<long, long> > rem;
    for (long i = 1; i < n; ++i) {
        long x, y; scanf("%ld %ld",&x,&y);
        long r = find(x, f); long s = find(y, f);

        if (r == s) rem.push_back(make_pair(x, y));
        else f[s] = r;
    }

    vector<pair<long, long> > add;
    for (long i = 2; i <= n; ++i) {
        if (find(i, f) == find(1, f)) continue;
        add.push_back(make_pair(find(i, f), 1));
        f[find(i, f)] = find(1, f);
    }
    printf("%ld\n", rem.size());

    for (long i = 0; i < rem.size(); ++i) {
        printf("%ld %ld %ld %ld\n", rem[i].first, rem[i].second, add[i].first, add[i].second);
    }
    
    return 0;
}