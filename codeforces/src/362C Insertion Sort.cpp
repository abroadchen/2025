//
// Created by Psy.C on 2026/1/19.
//
/*
* 前缀和构建：O(n²)
x值计算：O(n²)
插入排序模拟：O(n²)（最坏情况）
总体：O(n²)
 */
#include <iostream>
#include <map>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 5000
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;



int main() {
    fast;
    int n, a[N], b[N][N]; cin >> n;
    rep(i,n) cin >> a[i];
    rep(i,n) rep(j,n) b[i][j] = -1;
    rep(i,n) {
        b[i][0] = 0;
        rep(j,i) {//处理i左侧的元素（j < i）
            if (a[i] < a[j]) b[i][j+1] = b[i][j] + 1;
            else b[i][j+1] = b[i][j];
        }
        for (int j = i + 1; j < n; ++j) {//处理i右侧的元素（j > i）
            if (a[i] < a[j]) b[i][j] = b[i][j-1] + 1;
            else b[i][j] = b[i][j-1];
        }
    }
    int ans = 0; map<int, int> mp;
    rep(i,n) for (int j = i + 1; j < n; ++j) {//遍历所有(i,j)对，其中i < j
        int x = 2 * (b[i][j] - b[i][i] + b[j][i] - b[j][j]) -//加权计数
            (a[i] < a[j] ? 1 : 0) + (a[i] > a[j] ? 1 : 0);//根据大小关系调整
        mp[x]++;//每种x值的出现次数
        ans = min(ans, x);//最小的x值
    }
    int cnt = 0;
    for (int i = 1; i < n; ++i) {
        int j = i;
        while (j > 0 && a[j] < a[j-1]) {
            swap(a[j], a[j-1]);//相邻元素交换次数
            cnt++;
            j = j - 1;
        }
    }
    //交换次数+最小值 最小值出现的次数
    cout << cnt + ans << ' ' << mp[ans] << '\n';
    return 0;
}