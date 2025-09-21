//
// Created by Psy.C on 2025/9/21.
//

#include <cstdio>
#include <vector>
using namespace std;

const int N = 1000005;
int n;// 区间数量
int x[5005][2];// 存储区间的起始和结束点
int tmp[N];// 差分数组，用于计算覆盖次数
vector<int> ans;

int main() {
    scanf("%d",&n);

    for (int i = 0; i < n; ++i) {
        scanf("%d %d", &x[i][0], &x[i][1]);// 读取第i个区间的起点和终点
        tmp[x[i][0]]++;// 在起点处+1
        tmp[x[i][1]]--;// 在终点处-1（注意：这里终点是开区间）
    }

    int maxx = 0, a = -1, b = -1;// maxx记录当前覆盖次数，a和b记录重叠区域的起始和结束点
    for (int i = 0; i < N; ++i) {
        maxx += tmp[i];
        tmp[i] = maxx;// 保存当前点的覆盖次数（用于后续可能的查询）

        if (maxx > 1) {// 如果当前点被至少2个区间覆盖
            if (maxx >= 3) {// 如果被3个或以上区间覆盖
                printf("0\n");
                return 0;
            }
            if (a == -1) a = i;// 记录重叠区域的起始点
            b = i;// 更新重叠区域的结束点
        }
    }

    for (int i = 0; i < n; ++i) {// 查找包含重叠区域[a,b]的所有区间
        if (a == -1 || (x[i][0] <= a && b <= x[i][1] - 1))// 如果没有重叠区域(a=-1)或者当前区间包含整个重叠区域
            ans.push_back(i + 1);// 将区间编号（1基）添加到结果中
    }
    printf("%d\n", ans.size());// 输出符合条件的区间数量

    if (ans.size()) {
        printf("%d", ans[0]);
        for (int i = 1; i < ans.size(); ++i) printf(" %d", ans[i]);
        printf("\n");
    }

    return 0;
}