//
// Created by Psy.C on 2026/2/5.
//
/**
* cnt: 记录不是1的元素个数
top: 栈顶指针
s[N]: 栈数组，存储剩余空间
a[N]: 输入数组
 */
#include <algorithm>
#include <iostream>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 25
using namespace std;

int cnt, top, s[N], a[N];
void dfs(const int x) {
    if (x > cnt) { cout << "YES"; exit(0); }//处理完所有非1元素后
    for (int i = 1; i <= top; ++i) {//遍历栈中每个位置，检查能否放置a[x]
        if (s[i] >= a[x] && (s[i] > a[x] || s[i] != a[i] - 1)) {
            s[i] -= a[x];//在第i个位置放a[x]，减少相应空间
            s[++top] = a[x] - 1;//新开辟一个位置，容量为a[x]-1
            dfs(x + 1);//递归处理下一个元素
            s[i] += a[x];//回溯：恢复第i个位置的空间
            top--;//回溯：弹出栈顶
        }
    }
}


int main() {
    fast;
    int n; cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        if (a[i] == 2) { cout << "NO"; return 0; }//有2
        cnt += a[i] != 1;
    }
    sort(a + 1, a + n + 1, greater<int>{});
    //最大值必须等于n 不是1的元素不能太多
    if (a[1] != n || cnt*2 >= n) { cout << "NO"; return 0; }
    //初始化栈，第一个元素容量为a[1]-1
    s[++top] = a[1] - 1; dfs(2);
    cout << "NO";
    return 0;
}