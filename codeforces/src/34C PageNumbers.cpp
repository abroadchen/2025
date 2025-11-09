//
// Created by Psy.C on 2025/9/21.
//时间复杂度：O(N + n)，其中N是数字范围，n是输入数字个数 空间复杂度：O(N)

#include <iosfwd>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const long N = 1111;

vector<int> parseStr(string s) {
    int x(0);// 当前正在解析的数字
    vector<int> nums;// 存储解析出的数字
    for (long i = 0; i < s.size(); ++i) {// 遍历字符串中的每个字符
        if (s[i] == ',') {
            nums.push_back(x);// 将当前数字加入结果
            x = 0;// 重置当前数字
        } else {
            x = x * 10 + (s[i] - '0');
        }
    }
    nums.push_back(x);// 添加最后一个数字
    return nums;
}

int main() {

    ios::sync_with_stdio(false);
    cin.tie(nullptr); cout.tie(nullptr);

    string s; cin >> s;
    vector<int> nums = parseStr(s);// 解析字符串为数字向量
    vector<bool> a(N, 0);// 建立布尔数组标记哪些数字出现过
    for (long i = 0; i < nums.size(); ++i) a[nums[i]] = true;
    // 当前区间的起始位置
    long from(-1), ok(1);// 输出分隔符控制标志
    for (long i = 0; i < N; ++i) {
        if (!a[i]) {// 如果当前数字不存在
            if (from >= 0) {// 如果之前有连续区间
                long to = i - 1;// 当前区间的结束位置
                if (!ok) cout << ",";// 添加分隔符
                ok = false;
                if (from < to) cout << from << "-" << to;// 输出区间格式
                else cout << from;// 输出单个数字
            }
            from = -1;// 重置区间起始位置
        } else if (a[i] && from < 0) {// 如果当前数字存在且不在区间中
            from = i;// 开始新区间
        }
    }

    cout << endl;// 输出换行

    return 0;
}