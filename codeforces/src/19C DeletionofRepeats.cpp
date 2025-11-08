//
// Created by Psy.C on 2025/9/18.
//
/*
*arr[LIM]：经过压缩处理后的数组
org[LIM]：保存原始数组值
idx[LIM]：记录每个元素在其值组中的索引位置
len[LIM][12]：长度矩阵，用于记录连续匹配序列的长度
mapid：将原始值映射到压缩后的ID
inds[LIM]：对于每个压缩ID，存储该值出现的所有索引位置
 *
 *
*mapid.count(arr[i])：

这是在检查mapid这个map容器中是否已经存在键值为arr[i]的元素
count()函数会返回键值在map中出现的次数（对于map来说，结果要么是0要么是1）
如果arr[i]这个值之前已经处理过，返回1；如果没处理过，返回0
if (...)：

如果count()返回1，说明arr[i]这个值之前已经在map中出现过
如果count()返回0，说明arr[i]这个值是第一次遇到
id = mapid[arr[i]]：

如果条件成立（即该值之前出现过），就把之前分配给这个值的ID重新赋给变量id
mapid[arr[i]]是获取arr[i]这个键对应的值（即之前分配的ID）

 *
 *
*对于同一值的之前出现位置：
如果下一个元素也匹配，则延长匹配序列长度
len[k][idx[i]]表示从位置k开始的匹配序列长度
 *
 *
*查找可以移除的子序列：
对于每个位置i，检查该值后面出现的位置k
如果它们之间的距离(dist)小于等于匹配长度
将(起始位置, 距离)对添加到移除列表中
按起始位置对移除列表进行排序
 *
 *
*从左到右贪婪处理移除操作：
encut跟踪已经移除的最右位置
跳过与已移除段重叠的移除操作
更新encut为当前移除段的结束位置
 *
 *
 *
 */
#include <ios>
#include <cstdio>
#include <iostream>
#include <map>
#include <ostream>
#include <vector>
#define rep(i,n) for(int i=0;i<n;++i)
#define repd(i,a,b,d) for(int i=a; i>=b; i-=d)
#define repa(i,a,b,d) for(int i=a; i<=b; i+=d)
#define LIM 100002
#define sz(a) ((int)a.size())
using namespace std;

int arr[LIM], org[LIM], idx[LIM], len[LIM][12];
map<int, int> mapid;
vector<int> inds[LIM];

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    int n; scanf("%d",&n);
    rep (i, n) {
        scanf("%d",&arr[i]);
        org[i] = arr[i];
        int id = sz(mapid);
        if (mapid.count(arr[i])) id = mapid[arr[i]];
        else mapid[arr[i]] = id;
        arr[i] = id;
        idx[i] = sz(inds[id]);
        inds[id].push_back(i);
    }

    repd (i, n - 2, 0, 1) {
        repd (j, idx[i] - 1, 0, 1) {
            int k = inds[arr[i]][j];
            if (arr[i + 1] == arr[k + 1])
                len[k][idx[i]] = len[k + 1][idx[i + 1]] + 1;
        }
    }

    vector<pair<int,int>> rem;
    rep (i, n) {
        repa (j, idx[i] + 1, sz(inds[arr[i]]) - 1, 1) {
            int k = inds[arr[i]][j];
            int dist = k - i - 1;
            if (dist <= len[i][idx[k]])
                rem.push_back(make_pair(i, dist));
        }
    }
    sort(rem.begin(), rem.end());

    int encut = -1;
    rep (i, sz(rem)) {
        if (encut >= rem[i].first) continue;
        encut = rem[i].first + rem[i].second;
    }

    cout << n - encut - 1 << endl;
    repa (i, encut + 1, n - 1, 1) cout << org[i] << " ";
    
    return 0;
}