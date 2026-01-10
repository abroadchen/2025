//
// Created by Psy.C on 2026/1/10.
//
/**
 *
*for (int i = 1; i <= n; ++i)：遍历行（从1到n）
for (int j = 1; j <= m; ++j)：遍历列（从1到m）
if (a[i][j] >= val)：如果当前位置的值大于等于目标值
for (int k = j + 1; k <= m; ++k)：遍历该行后续列
if (a[i][k] >= val)：如果另一个位置的值也大于等于目标值
 *
*查和标记
if (flag[j][k]) return true：如果这对列已经存在过，返回 true
flag[j][k] = true：标记这对列已出现
 *
*向上取整：(left + right + 1) / 2，用于搜索右边界
向下取整：(left + right) / 2，用于搜索左边界
 *
* 找到最大的 x，使得 f(x) <= target
while (l < r) {
    int mid = (l + r + 1) / 2;  // 向上取整
    if (f(mid) <= target) {
        l = mid;        // mid 可能满足条件，保留
    } else {
        r = mid - 1;    // mid 肯定不满足，排除
    }
}
*找到最小的 x，使得 f(x) >= target
while (l < r) {
    int mid = (l + r) / 2;      // 向下取整
    if (f(mid) >= target) {
        r = mid;        // mid 可能满足条件，保留
    } else {
        l = mid + 1;    // mid 肯定不满足，排除
    }
}
 *
 *
*查找第一个满足条件的位置（下界）
cpp
// 查找第一个 >= target 的位置
int lower_bound(vector<int>& arr, int target) {
    int left = 0, right = arr.size();  // 注意右边界
    while (left < right) {             // 注意是 < 不是 <=
        int mid = left + (right - left) / 2;
        if (arr[mid] >= target) {
            right = mid;    // mid 可能是答案，保留mid
        } else {
            left = mid + 1; // mid 肯定不是答案，排除mid
        }
    }
    return left;
}
 *
*查找最后一个满足条件的位置（上界）
cpp
// 查找最后一个 < target 的位置
int upper_bound_like(vector<int>& arr, int target) {
    int left = 0, right = arr.size();
    while (left < right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] < target) {
            left = mid + 1; // mid 可能是答案，但要继续向右找
        } else {
            right = mid;    // mid 肯定不是答案，排除mid
        }
    }
    return left - 1; // 最后一个 < target 的位置
}
 *
*查找特定值（精确匹配）
cpp
// 查找目标值
int binary_search(vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;
    while (left <= right) {  // 注意是 <=
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) left = mid + 1;   // 排除mid，搜索右半部分
        else right = mid - 1;                         // 排除mid，搜索左半部分
    }
    return -1;
}
 *
 *
 *
 */
#include <iostream>
#include <cstring>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define N 1010
#define inf 1e9
using namespace std;

int n, m, a[N][N];
bool flag[N][N];
bool ok(const int val) {
    memset(flag, 0, sizeof(flag));
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) {
        if (a[i][j] >= val) for (int k = j + 1; k <= m; ++k) {
            if (a[i][k] >= val) {
                if (flag[j][k]) return true;
                flag[j][k] = true;
            }
        }
    }
    return false;
}

int main() {
    fast;
    cin >> n >> m;
    for (int i = 1; i <= n; ++i) for (int j = 1; j <= m; ++j) cin >> a[i][j];
    int l = 0, r = inf;
    while (l < r) {
        if (const int mid = (l + r + 1) >> 1; ok(mid)) l = mid; else r = mid - 1;
    }
    cout << l << '\n';
    return 0;
}