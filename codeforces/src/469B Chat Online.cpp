//
// Created by Psy.C on 2026/2/13.
//
/**
p：第一组区间的数量
q：第二组区间的数量
l, r：平移量的范围
vis[N<<1]：标记数组，记录第一组区间覆盖的位置
c[N], d[N]：存储第二组区间的左右端点

O((r-l+1) * q * max_length)，其中max_length是区间最大长度
在给定的数据范围下是可接受的
 */
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1010
using namespace std;

int p, q, l, r, vis[N<<1], c[N], d[N];

int main() {
    fast;
    cin >> p >> q >> l >> r;
    for (int i = 0, a, b; i < p; ++i) {//第一组p个区间
        cin >> a >> b;
        //将区间[a,b]内的所有点标记为1（表示被覆盖）
        for (int j = a; j <= b; ++j) vis[j] = 1;
    }
    //第二组q个区间，存储到c[i], d[i]
    for (int i = 0; i < q; ++i) cin >> c[i] >> d[i];
    int ans = 0;
    for (int k = l; k <= r; ++k) {//遍历所有可能的平移量k
        int flag = 0;//当前平移量下是否有重叠
        for (int i = 0; i < q && !flag; ++i) {//遍历第二组的所有区间
            //第i个区间平移k后变为[c[i]+k, d[i]+k] 检查平移后区间内的每个点
            for (int j = c[i]+k; j <= d[i]+k && !flag; ++j) {
                if (vis[j]) {//点j在第一组区间中被标记过
                    flag = 1;//发现重叠，设置标志并跳出
                    break;
                }
            }
        }
        if (flag) ans++;
    }
    cout << ans << '\n';
    return 0;
}