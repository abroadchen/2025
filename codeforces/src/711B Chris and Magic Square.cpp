//
// Created by Psy.C on 2026/4/20.
//
/**
输入n×n矩阵的所有元素
同时记录值为0的元素位置（x,y），这个位置是要填充的空位
sum数组存储所有行、列和对角线的和
check(st, ed)函数检查从st到ed-1的sum数组元素是否都相等

读入矩阵大小n
获取零元素位置(x,y)
如果n=1，特殊处理，输出一个很大的数
计算每行的和存入sum数组
计算每列的和存入sum数组
len用来跟踪sum数组的长度
计算主对角线（左上到右下）的和
计算反对角线（右上到左下）的和
对sum数组排序，但这是为了后面比较方便
根据零元素的位置决定有多少条线的和应该相等：
如果零在中心位置（奇数阶矩阵的中心），会影响4条线（行列对角线）
如果零在对角线上，会影响3条线
否则影响2条线
检查前ed个和是否相等（这些是包含零元素的线）
检查其余的和是否相等（这些是不包含零元素的线）
如果所有线的和都能相等，输出最大值与最小值的差
如果差值为0，输出-1（说明矩阵已经是一个幻方）
否则输出-1（无法构成幻方）
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define ll long long
using namespace std;
constexpr int N = 507;

ll a[N][N];
void get(int& x, int& y, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
            if (a[i][j] == 0) x = i, y = j;
        }
}

ll sum[(N<<1)+7];
bool check(int st, int ed) {
    for (int i = st; i < ed; ++i)
        if (sum[i] != sum[i-1])
            return false;
    return true;
}

int n;
int main() {
    fast;
    cin >> n;
    int x = -1, y = -1; get(x, y, n);
    if (n == 1) {
        cout << (ll)1e18-1 << '\n';
        return 0;
    }
    int len = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            sum[len] += a[i][j], sum[len+1] += a[j][i];
        len += 2;
    }
    for (int i = 0; i < n; ++i) sum[len] += a[i][i], sum[len+1] += a[i][n-i-1];
    len += 2;
    sort(sum, sum + len);
    int ed = -1;
    if (n%2 != 0 && x == y && x == n/2) ed = 4;
    else if (x == y || x == n - 1 - y) ed = 3;
    else ed = 2;
    int flag = 0;
    if (check(1, ed) && check(ed + 1, len)) flag = 1;
    if (flag == 1) cout << (sum[len-1]-sum[0] == 0 ? -1 : sum[len-1]-sum[0]) << '\n';
    else cout << -1 << '\n';
    return 0;
}