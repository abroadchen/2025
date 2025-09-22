//
// Created by Psy.C on 2025/9/22.
//


#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
const int N = 1000;

pair<int, int> a[N];// 存储长度和原始索引的配对数组

bool cmp(const pair<int, int>& a, const pair<int, int>& b) { return a.first < b.first; }

int main() {
    int n;
    vector<string> ans;
    scanf("%d",&n);
    ans.resize(n);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i].first);
        a[i].second = i;
    }
    sort(a, a+n, cmp);

    string s = "0";// 初始化第一个码字为"0"
    int j = 0;// 当前处理的数组索引
    bool flag = false;// 溢出标志

    for (int i = 1; i <= 1000; ++i) {
        while (i == a[j].first) {// 处理所有长度为i的码字需求
            ans[a[j].second] = s;// 将当前码字分配给对应位置
            bool carry = true;
            for (int k = (int)s.size() - 1; k >= 0; --k) {// 从最低位开始
                if (carry && s[k] == '0') {// 0 + 1 = 1，无进位
                    s[k] = '1';
                    carry = false;
                } else if (carry && s[k] == '1') {// 1 + 1 = 0，有进位
                    s[k] = '0';
                    carry = true;
                } else {
                    break;
                }
            }
            if (carry) {// 如果最高位仍有进位
                flag = true;
                break;
            }
            j += 1;// 处理下一个码字需求
        }
        if (flag) break;
        s += "0";// 扩展码字长度，添加一个'0'
    }

    if (flag && j != n - 1) printf("NO\n");// 如果溢出且未处理完所有需求
    else {
        printf("YES\n");
        for (int i = 0; i < n; ++i)
            printf("%s\n",ans[i].c_str());
    }

    return 0;
}