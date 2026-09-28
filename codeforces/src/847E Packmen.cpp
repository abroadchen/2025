//
// Created by Psy.C on 2026/9/28.
//
/**
x[] 存所有 * 的位置（下标），p[] 存所有 P 的位置。
get(l, r, pos)：返回位于 pos 的人，若要覆盖区间 [l, r] 内所有点，所需的最短时间：
人先走到左端 l 或右端 r 中较近的一端（min(abs(pos-l), abs(pos-r))），再走完全区间宽度 abs(r-l)。
即"先去近端、再横穿整个区间"的经典覆盖用时
pre = -1：当前"已覆盖到的星星位置"在前一个人的处理中推进到的下界（-1 表示还没覆盖任何）。
pos = -1：当前人覆盖到的最右星星下标，也是全局已覆盖到的星星下标。
我们把人 p[0], p[1], ... 依次当作"覆盖工具"，前一个人覆盖到的星星，后一个人继续往后覆盖，保证不重叠向前推进
让当前这个人 p[i] 尽可能多地往后覆盖星星：从 x[pre+1]（前一个人覆盖完后的下一个未覆盖星星）到 x[pos+1]（尝试扩展到的下一颗星星）。
只要 get(x[pre+1], x[pos+1], p[i]) <= t（即在 t 时间内能覆盖 [前一个未覆盖星星 … 这颗新星星] 这段区间），就把 pos 右移一个（覆盖更多一颗）。
循环停止条件是：覆盖到全部星星（pos == sn-1）或下一颗扩展会让用时超 t
当前人覆盖完，更新 pre = pos，即"已覆盖到的最右星星下界"，交给下一个人继续从 pre+1 往后

读长度 n 和字符串 s，下标从 0 开始。
扫一遍：把 P 的下标存进 p[]，把 * 的下标存进 x[]
答案（最小时间 t）落在 [0, 2n]（覆盖最坏情况约需 2n）。
二分：check(mid) 成立（mid 内能覆盖全部星星）则收紧上界 r=mid，否则增大下界 l=mid+1。
二分结束，l 即最小可行时间，输出

 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

constexpr int N = 1e5+5;

int get(int l, int r, int pos) { return min(abs(pos-l), abs(pos-r)) + abs(r-l); }

int pn, sn, x[N], p[N];
bool check(int t) {
    int pre = -1, pos = -1;
    for (int i = 0; i < pn; ++i) {
        while (pos < sn-1 && get(x[pre+1], x[pos+1], p[i]) <= t) ++pos;
        pre = pos;
    }
    return pos == sn-1;//若最后一个人已覆盖到最后一颗星星，说明 t 内可行
}

int n;
char s[N];
int main() {
    fast;
    cin >> n >> s; pn = 0, sn = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'P') p[pn++] = i;
        if (s[i] == '*') x[sn++] = i;
    }
    int l = 0, r = 2*n;
    while (l < r) {
        int mid = (l+r)>>1;
        if (check(mid)) r = mid; else l = mid+1;
    }
    cout << l << '\n';
    return 0;
}