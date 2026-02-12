//
// Created by Psy.C on 2026/2/12.
//
/**
dis[0]==dis[1]==dis[2]：最近的3个点（相邻顶点）距离相等
dis[3]==dis[4]==dis[5]：较远的3个点（面对角线顶点）距离相等
dis[3] == 2*dis[0]：面对角线距离是边长的√2倍（平方后是2倍）
dis[6] == 3*dis[0]：体对角线距离是边长的√3倍（平方后是3倍）
dis[0] != 0：没有重合点

递归深度为d，当d=8时完成所有点的处理
如果到达第8层，检查当前配置是否构成立方体
sort(a[d], a[d]+3)：对当前点的坐标排序
next_permutation：生成坐标的全排列
尝试每种坐标排列，直到找到立方体
 */
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int a[8][3];//存储8个点的坐标，每个点有3维坐标
ll dis[8];//存储距离数组（实际上只用7个）

ll get_dis(const int x, const int y) {
    ll ret = 0;
    for(int i = 0; i<3; i++) {
        ret += 1LL*(a[x][i]-a[y][i])*(a[x][i]-a[y][i]);
    }
    return ret;
}
void output() {
    puts("YES");
    for(const auto & i : a) {
        for(const int j : i) {
            cout<<j<<" ";
        }
        cout<<endl;
    }
}
int check() {
    for(int center = 0; center<8; center++) {//遍历每个点作为中心点
        int cnt = 0;
        for(int i = 0; i<8; i++) {//计算该点到其他7个点的距离
            if(i == center)
                continue;
            dis[cnt++] = get_dis(i, center);
        }
        sort(dis, dis+7);
        if(dis[0] == 0)
            return 0;
        if(dis[0]!=dis[1]||dis[1]!=dis[2])
            return 0;
        if(dis[3]!=dis[4]||dis[4]!=dis[5])
            return 0;
        if(dis[3]!= 2*dis[0])
            return 0;
        if(dis[6] != 3*dis[0])
            return 0;
    }
    return 1;
}
int dfs(const int d) {
    if(d == 8) {
        if(check()) {
            output();
            return 1;
        }
        return 0;
    }
    sort(a[d], a[d]+3);
    do {
        if(dfs(d+1))
            return 1;
    } while(next_permutation(a[d], a[d]+3));
    return 0;
}
int main()
{
    for(auto& i : a) {
        for(int& j : i) {
            cin>>j;
        }
    }
    if(!dfs(0)) {
        puts("NO");
    }
    return 0;
}