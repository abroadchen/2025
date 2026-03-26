//
// Created by Psy.C on 2026/3/26.
//
///时间复杂度：O(n log n)，其中log n来自set的操作 空间复杂度：O(n)
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 3e5+5;
int n, a[N];///存储分割点的数组
set<int> s;
int main() {
    fast;
    cin >> n;
    int l = 0;//分割点数量
    for (int i = 1, x; i <= n; ++i) {
        cin >> x;
        if (s.contains(x)) {//x是否已在集合s中出现过 遇到了重复元素
            a[l++] = i;//记录分割点位置i，然后l自增
            s.clear();//清空集合，开始新的段
        } else s.insert(x);
    }
    if (l == 0) cout << "-1\n";//没有找到任何分割点
    else {
        a[l-1] = n;//将最后一个分割点设为n（序列末尾）
        cout << l << '\n';//分割成的段数
        cout << "1 " << a[0] << '\n';//第一段：从位置1到a[0]
        for (int i = 1; i < l; ++i)//+1是因为上一段的结尾是a[i-1]
            cout << a[i-1]+1 << ' ' << a[i] << '\n';
    }
    return 0;
}