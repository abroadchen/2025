//
// Created by Psy.C on 2025/12/20.
//

#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define minn(a,b) (((a)<(b))?(a):(b))
#define N 100001
using namespace std;


int main() {
    fast;
    int m, mn = 0x7fffffff;
    cin>>m;
    for (int i = 1, t; i <= m; ++i) {//循环读入m个数，找出其中的最小值存入mn
        cin>>t;
        mn = minn(mn,t);
    }
    int n, a[N]; cin>>n;
    for (int i = 1; i <= n; ++i) cin>>a[i];//循环读入n个数存入数组a
    sort(a+1,a+n+1);
    int x = n, cnt = 0, ans = 0;
    while (x > 0) {//从最大元素开始选择，每选择mn个连续元素后，跳过接下来的2个元素
        ans += a[x];//将当前最大的元素a[x]加入结果ans
        ++cnt;
        --x;//指针x向前移动一位
        if (cnt == mn) { cnt = 0; x -= 2; }//当计数器等于之前找到的最小值mn时重置计数器为0 跳过接下来的2个元素（x -= 2）
    }
    cout << ans << '\n';
    return 0;
}