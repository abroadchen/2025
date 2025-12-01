//
// Created by Psy.C on 2025/12/1.
//时间复杂度：O(n²) - 双重循环遍历点对
//空间复杂度：O(N²) - 二维标记数组

#include <iostream>
#include <algorithm>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 3005
using namespace std;

struct node { int a, b; } pt[N];
int a[N<<1][N<<1] = {};//标记点的存在
inline int cmp(const node u, const node v) {//按x坐标优先，y坐标次要的顺序排序
    if (u.a != v.a) return u.a < v.a;
    return u.b < v.b;
}

int main() {
    fast;
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> pt[i].a >> pt[i].b;
        a[pt[i].a+N][pt[i].b+N] = 1;//加上N是为了处理负坐标，避免数组下标为负
    }
    sort(pt, pt+n, cmp);
    int cnt = 0;
    for (int i = 0; i < n - 1; ++i)
        for (int j = i + 2; j < n; ++j) {//（跳过相邻点）
            if ((pt[i].a+pt[j].a)%2||(pt[i].b+pt[j].b)%2) continue;//检查中点坐标是否为整数
            cnt += a[(pt[i].a+pt[j].a)/2+N][(pt[i].b+pt[j].b)/2+N];//检查该中点是否有对应的点存在
        }
    cout << cnt << '\n';
    return 0;
}