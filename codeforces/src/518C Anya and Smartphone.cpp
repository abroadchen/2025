//
// Created by Psy.C on 2026/2/28.
//
/**
n：数组长度
m：查询次数
k：分组大小
mp：映射表，存储值到位置的映射
创建数组a（从索引1开始）
读入数组元素并建立值到位置的映射
sum：累计操作次数
读入查询值q

如果q的位置能被k整除：
如果位置恰好是k，加1
否则加位置/k
否则加1 + 位置/k
这是在计算将元素移动到最前面需要的操作次数

如果q已经在位置1，跳过
否则：
j = mp[q]：q的当前位置
x = a[j-1]：q前面的元素
交换q和前面元素的位置
更新映射关系
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define int long long
using namespace std;

int n, m, k;
map<int, int> mp;
signed main() {
    fast;
    cin >> n >> m >> k;
    vector<int> a(n+1);
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        mp[a[i]] = i;
    }
    int sum = 0;
    for (int i = 0, q, j, x; i < m; ++i) {
        cin >> q;
        if (mp[q]%k == 0) {
            if (mp[q] == k) sum++;
            else sum += mp[q]/k;
        }
        else sum += 1 + mp[q]/k;
        if (mp[q] == 1) continue;
        j = mp[q]; x = a[j-1];
        mp[q] = j-1; mp[x] = j;
        swap(a[j-1], a[j]);
    }
    cout << sum;
    return 0;
}