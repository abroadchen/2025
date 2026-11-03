//
// Created by Psy.C on 2026/11/3.
//

/**
真正学会的起点..
从 cur=2 开始，逐个确定 t[cur]。
每次只校验与前一个元素 t[cur-1] 的或、与是否匹配。只要当前数字 i 满足 i|t[cur-1]==a[cur-1] 且 i&t[cur-1]==b[cur-1]，就合法。
一旦填满 n 个元素（cur>n）即输出 YES 并 exit。
若某个 cur 所有 0..3 都无法满足，则回溯到上一层换值
枚举 t[1] 的所有可能值（0-3），然后 DFS 填后续。
若全部方案都失败，输出 NO（无解
*/
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)

using namespace std;

constexpr int N = 1e5+5;

int n, t[N], a[N], b[N];
void dfs(int cur) {
    if (cur > n) {//填满了整个数组
        cout << "YES\n";
        for (int i = 1; i <= n; i++) cout << t[i] << ' ';//输出解
        exit(0);//找到即终止整个程序
    }
    for (int i = 0; i <= 3; i++) {//枚举 t[cur] ∈ 0..3
        int x = i;
        //检查 t[cur] 与 t[cur-1] 的 或/与 恰好等于给定 a,b
        if ((x|t[cur-1])==a[cur-1] && (x&t[cur-1])==b[cur-1]) {
            t[cur] = i;//合法则填入
            dfs(cur+1);//继续填下一个
            t[cur] = 0;//回溯(还原)
        }
    }
}


int main() {
    fast;
    cin >> n;
    for (int i = 1; i < n; i++) cin >> a[i];
    for (int i = 1; i < n; i++) cin >> b[i];
    for (int i = 0; i <= 3; i++) { t[1] = i; dfs(2); }//枚举第一个元素后DFS
    cout << "NO\n";
    return 0;
}