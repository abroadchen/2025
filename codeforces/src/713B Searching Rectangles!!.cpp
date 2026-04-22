//
// Created by Psy.C on 2026/4/21.
//
/**
? x1 y1 x2 y2，表示查询矩形区域左上角(x1,y1)到右下角(x2,y2)
cout.flush()：刷新输出缓冲区，确保查询立即发送
接收服务器返回的结果并返回给调用者

第一次二分查找 - 找最右边的点
在区间[x1, x2]内查找满足条件的最右侧x坐标
使用二分查找确定最大x值，使得矩形[mid, y1, x2, y2]内存在目标点
第二次二分查找 - 找最下方的点
在区间[y1, y2]内查找满足条件的最下方y坐标
确定最大y值，使得矩形[x1, mid, x2, y2]内存在目标点
第三次二分查找 - 找最左边的点
在区间[x1, x2]内查找满足条件的最左侧x坐标
使用二分查找确定最小x值，使得矩形[x1, y1, mid, y2]内存在目标点
第四次二分查找 - 找最上方的点
在区间[y1, y2]内查找满足条件的最上方y坐标
确定最小y值，使得矩形[x1, y1, x2, mid]内存在目标点

读入正方形网格的大小n
第一次二分查找 - 确定第一个矩形的边界
二分查找确定第一个矩形的最大x边界
找到最小的mid值，使得矩形[1,1,mid,n]包含至少一个点
如果存在第二个矩形（即在[l+1,1,n,n]区域内有点）
分别对两个矩形区域调用get函数获取边界点
否则说明两个点在同一列附近
按列分割，对两个子区域调用get函数
输出!表示答案开始
输出vector中的所有边界坐标，最后一个元素后换行，其余用空格分隔
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int out(int x1, int y1, int x2, int y2) {
    cout << '?' << ' ' << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
    cout.flush();
    int res;
    cin >> res;
    return res;
}

vector<int> v;
void get(int x1, int y1, int x2, int y2) {
    int l, r, ans;
    l = x1, r = x2, ans = -1;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (out(mid, y1, x2, y2))
            ans = mid, l = mid+1;
        else r = mid-1;
    }
    v.push_back(ans);
    l = y1, r = y2, ans = -1;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (out(x1, mid, x2, y2))
            ans = mid, l = mid+1;
        else r = mid-1;
    }
    v.push_back(ans);
    l = x1, r = x2, ans = -1;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (out(x1, y1, mid, y2))
            ans = mid, r = mid-1;
        else l = mid+1;
    }
    v.push_back(ans);
    l = y1, r = y2, ans = -1;
    while (l <= r) {
        int mid = (l+r)>>1;
        if (out(x1, y1, x2, mid))
            ans = mid, r = mid-1;
        else l = mid+1;
    }
    v.push_back(ans);
}

int n;
int main() {
    fast;
    cin >> n;
    int l = 1, r = n + 1;
    while (l < r) {
        int mid = (l+r)>>1;
        if (out(1, 1, mid, n)) r = mid;
        else l = mid+1;
    }
    if (l < n && out(l+1, 1, n, n) == 1) {
        get(1, 1, l, n);
        get(l+1, 1, n, n);
    } else {
        int l = 1, r = n;
        while (l < r) {
            int mid = (l+r)>>1;
            if (out(1, 1, n, mid)) r = mid;
            else l = mid+1;
        }
        get(1, 1, n, l);
        get(1, l+1, n, n);
    }
    cout << '!' << ' ';
    for (int i = 0; i < v.size(); ++i)
        cout << v[i] << " \n"[i==v.size()-1];
    return 0;
}