//
// Created by Psy.C on 2025/11/3.
//
/*
*n: 数组长度
a[N]: 存储输入数据的数组
v: 存储可能周期长度的向量
 *
 *检查函数，判断是否存在周期为x的模式
*遍历一个周期内的每个起始位置
st表示当前检查的位置
ok标记当前周期是否有效
*从位置i开始，每隔x个位置检查一次元素
如果遇到0则标记为无效并跳出循环
否则继续检查下一个周期位置
*如果存在任何一个起始位置能够构成全非零的周期序列，返回true
否则返回false
 *
 *
*查找所有满足条件的可能周期：
i必须是n的因数（n%i==0）
周期数必须至少为3（n/i>=3）
将满足条件的周期长度加入向量v
 *
*遍历所有可能的周期长度
调用check函数验证该周期是否可行
如果找到可行的周期，输出"YES"并结束程序
 *
 */
#include <iostream>
#include <vector>
using namespace std;

const int N = 1e5+10;
int n, a[N];
vector<int> v;

bool check(int x) {
    for (int i = 0; i < x; ++i) {
        int st = i;
        bool ok = true;
        while (st < n) {
            if (a[st] == 0) {
                ok = false;
                break;
            }
            st += x;
        }
        if (ok) return true;
    }
    return false;
}


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) {
        if (n % i == 0 && n / i >= 3) v.push_back(i);
    }
    for (int i = 0; i < v.size(); ++i) {
        if (check(v[i])) {
            cout << "YES" << endl;
            return 0;
        }
    }
    cout << "NO" << endl;
    return 0;
}