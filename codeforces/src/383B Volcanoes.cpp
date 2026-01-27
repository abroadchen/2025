//
// Created by Psy.C on 2026/1/27.
//

#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 100000
#define inf 2e9
using namespace std;

struct range { int l, r; } pre[N+10], cur[N+10];//前一状态的可行区间 当前状态的可行区间
struct node { int x, y; } b[N+1];//障碍物


int main() {
    fast;
    int n, m; cin >> n >> m;
    for (int i = 0; i < m; ++i) cin >> b[i].x >> b[i].y;
    sort(b, b+m, [](const node x, const node y) {
        return x.x < y.x || (x.x == y.x && x.y < y.y);
    });
    //前一状态区间数量 当前状态区间数量
    int cp = 1, cc = 0; pre[0].l = pre[0].r = 1;//第1行第1列为可达点 第一个区间为 [1,1]
    for (int i = 0; i < m;) {//遍历所有障碍物，按行处理
        //如果第一行没有障碍物，或者当前行与前一行不连续
        if ((i==0&&b[i].x!=1)||(i-1>=0&&b[i].x!=b[i-1].x+1)) {
            cp = 1; pre[0].r = n;//将前一状态扩展到整行（1到n）
        }
        int ed;//当前行障碍物的结束位置
        for (ed = i; b[ed].x == b[i].x && ed < m; ++ed) {}//找到当前行（b[i].x）的障碍物结束位置
        cc = 0;
        int L = 1;//当前可处理的起始位置 从第1列开始处理
        for (int j = i; j < ed; ++j) {//将 [L, b[j].y-1] 设为可达区间
            if (b[j].y - 1 >= L) {//障碍物左边还有空隙
                cur[cc].l = L;//新区间的左边界
                cur[cc++].r = b[j].y - 1;
            }
            L = b[j].y + 1;//更新下一个处理位置为障碍物右边
        }
        if (L <= n) {//处理最后一个障碍物之后的区域 创建区间 [L, n] 并加入当前状态
            cur[cc].l = L;
            cur[cc++].r = n;
        }
        //对每个当前区间进行可达性检查
        for (int j = 0; j < cc; ++j) {//对每个当前区间，二分查找从前一行可达的区间
            int lf = 0, rt = cp - 1, bd = -1;//二分查找范围     可达的左边界
            while (lf <= rt) {
                //前一状态的区间是否与当前区间重叠
                if (const int mid = (lf + rt) >> 1; pre[mid].r >= cur[j].l) {
                    bd = pre[mid].l;
                    rt = mid - 1;//向左查找更小的边界
                } else lf = mid + 1;//向右查找
            }
            //找不到可达边界或边界超出当前区间
            if (bd == -1 || bd > cur[j].r) cur[j].l = cur[j].r = inf;
            else cur[j].l = max(cur[j].l, bd);//原左边界, 可达边界
        }
        cp = 0;
        for (int j = 0; j < cc; ++j) {
            //将有效的当前区间复制到前一区间数组
            if (cur[j].l != inf && cur[j].r != inf) pre[cp++] = cur[j];
        }
        if (cp == 0) { cout << "-1\n"; return 0; }//没有有效区间
        i = ed;//移动到下一行的处理
    }
    //将状态更新为第n行为全行可达
    if (b[m-1].x != n) { cp = 1; pre[0].r = n; }//最后一个障碍物不在第n行
    if (pre[cp-1].r == n) cout << ((n-1)<<1) << '\n';//最后一个区间包含n（即可达终点）
    else cout << "-1\n";//无法到达
    return 0;
}