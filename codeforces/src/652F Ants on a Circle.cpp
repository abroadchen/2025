//
// Created by Psy.C on 2026/4/7.
//
/**
n个人数，m为环形长度，t为时间
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 3e5+5;

int n, m, s[N], id[N], id2[N], ans[N];
ll t;
char op[N];
int main() {
    fast;
    cin >> n >> m >> t;
    for (int i = 0; i < n; ++i) {
        cin >> s[i] >> op[i]; s[i]--;//读入每个人的位置和方向，位置减1转换为0索引
        id[i] = id2[i] = i;//初始化id和id2数组为原始索引
    }
    sort(id, id + n, [](int a, int b) {
        int pa, pb;//计算两个人在时间t后的位置
        if (op[a] == 'L') pa = ((s[a]-t)%m+m)%m;//向左移动，计算新位置
        else pa = (s[a]+t)%m;//向右移动，计算新位置
        if (op[b] == 'L') pb = ((s[b]-t)%m+m)%m;
        else pb = (s[b]+t)%m;
        if (pa != pb) return pa < pb;//按照最终位置排序
        return op[a] == 'L';//位置相同，L优先于R
    });
    sort(id2, id2 + n, [](int a, int b) {
        if (s[a] != s[b]) return s[a] < s[b];//初始位置从小到大
        return op[a] == 'L';//相同位置时L优先
    });
    int pos = 0;//位置偏移量
    if (op[0] == 'L') {//第一个人(编号0)向左走
        ll x = s[0] - t;//在时间t后的新位置
        for (int i = 0; i < n; ++i) {
            if (op[i] == 'R') {//找到所有向右走的人
                ll y = s[i] + t;//这个人的时间t后的位置
                if (s[i] > s[0]) y -= m;//环形结构调整位置
                if (y < x) continue;//目标位置小于当前人位置
                pos = (pos+(y-x)/m+1)%n;//更新位置偏移量
            }
        }
        pos = (n-pos)%n;//反转偏移量
    } else {
        ll x = s[0] + t;
        for (int i = 0; i < n; ++i) {
            if (op[i] == 'L') {
                ll y = s[i] - t;
                if (s[i] < s[0]) y += m;
                if (y > x) continue;
                pos = (pos+(x-y)/m+1)%n;
            }
        }
    }
    int p = 0;
    //编号为0的人在排序后数组中的位置
    for (int i = 0; i < n; ++i) if (id2[i] == 0) p = i;
    p = (p + pos) % n;
    int q = 0;
    for (int i = 0; i < n; ++i) if (id[i] == 0) q = i;
    for (int i = 0; i < n; ++i) {
        int j = id[(q+i)%n], y;//最终位置排序后第i个位置的人
        if (op[j] == 'L') y = ((s[j]-t)%m+m)%m;//此人在时间t后的位置
        else y = (s[j]+t)%m;
        int z = id2[(p+i)%n];//按初始位置排序后对应位置的人的原编号
        ans[z] = y + 1;//将计算出的位置+1存储到答案数组中
    }
    for (int i = 0; i < n; ++i) cout << ans[i] << ' ';
    cout << '\n';
    return 0;
}