//
// Created by Psy.C on 2025/9/22.
//

#include <algorithm>
#include <cstdio>
using namespace std;
const int N = 1010;
// n:节点数, x:初始资源, y:每轮恢复量, t[]:时间数组, id[]:节点ID数组, vis[]:访问标记数组
int n, x, y, t[N], id[N], vis[N];

struct Node {
    int id, p, d;// id:节点编号, p:价格, d:防御值
} a[N];

bool cmp(Node a, Node b) { return a.d > b.d; }

int main() {

    scanf("%d%d%d",&n,&x,&y);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d",&a[i].p,&a[i].d);
        a[i].id = i;// 设置节点编号
    }
    sort(a + 1,a + 1 + n, cmp);
    // now:当前资源, d:总防御值, be:上一轮防御值, cnt:已购买节点数
    int now(x), d(0), be(0), cnt(0);
    for (int i = 0; ; ++i) {
        now -= d;// 消耗资源，减去总防御值
        now += y;// 恢复资源，加上每轮恢复量
        now = min(now, x);// 资源不能超过初始值
        if (now <= 0) {
            printf("YES\n%d %d\n", i, cnt);
            for (int j = 0; j < cnt; ++j)
                printf("%d %d\n", t[j], id[j]);// 输出购买记录
            return 0;
        }
        for (int j = 1; j <= n; ++j) {
            if (vis[j] || a[j].p * x < now * 100) continue;// 如果已购买或价格不够，跳过
            vis[j] = 1;// 标记为已购买
            d += a[j].d;// 增加总防御值
            t[cnt] = i;// 记录购买时间
            id[cnt++] = a[j].id;// 记录购买节点ID
            break;
        }
        if (be == d && d <= y) break;// 如果防御值未增加且小于等于恢复量，无法继续
        be = d;// 更新上一轮防御值
    }
    printf("NO\n");
    return 0;
}