//
// Created by Psy.C on 2025/10/16.
//
/*
 *声明字符串数组p，用于存储输入的网格数据
 *声明pii类型的向量v，用于存储满足条件的(a,b)对
 *
*自定义比较函数，用于排序：
首先比较两个pair的乘积（first*second）
如果乘积相等，则比较first值
用于按面积和字典序排序
 *
 *从标准输入读取网格的行数n和列数m
 *读取n行字符串，存储到数组p中，构成一个n×m的网格
 *遍历a从1到n，如果n不能被a整除则跳过，确保a是n的因子
 *遍历b从1到m，如果m不能被b整除则跳过，确保b是m的因子
 *创建字符串集合up，用于存储不同的子网格表示
 *以步长a遍历x坐标，以步长b遍历y坐标，将网格分割成a×b的子网格
 *提取a×b子网格的一种表示（原始形式），存储到字符串s中并加入向量r
 *提取a×b子网格的另一种表示（水平和垂直翻转），存储到s2并加入r
*如果a等于b（正方形），则额外考虑旋转的情况：
s3: 顺时针旋转90度的表示
s4: 逆时针旋转90度的表示
*在所有可能的表示中找到字典序最小的表示minn
将minn插入集合up中
*计算总共应该有多少个子网格：(n/a) * (m/b)
如果集合up的大小等于子网格总数，说明所有子网格都不相同，将(a,b)加入向量v
输出满足条件的(a,b)对的数量
输出排序后第一个元素，即面积最小且字典序最小的(a,b)对
 */
#include <vector>
#include <ios>
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
const int N = 22;
int n, m, cnt(0), a, b;
string p[N];
vector<pii> v;


bool cmp(pii x, pii y) {
    if (x.first * x.second == y.first * y.second)
        return x.first < y.first;
    return x.first * x.second < y.first * y.second;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(nullptr);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> p[i];
    for (a = 1; a <= n; ++a) {
        if (n % a != 0) continue;
        for (b = 1; b <= m; ++b) {
            if (m % b != 0) continue;
            set<string> up;
            for (int x = 0; x < n; x += a) {
                for (int y = 0; y < m; y += b) {
                    vector<string> r; string s("");
                    for (int i = 0; i < a; ++i) {
                        for (int j = 0; j < b; ++j)
                            s += p[x + i][y + j];
                    }
                    r.push_back(s);
                    string s2("");
                    for (int i = a - 1; i >= 0; --i) {
                        for (int j = b - 1; j >= 0; --j)
                            s2 += p[x + i][y + j];
                    }
                    r.push_back(s2);
                    if (a == b) {
                        string s3("");
                        for (int j = 0; j < b; ++j) {
                            for (int i = a - 1; i >= 0; --i)
                                s3 += p[x + i][y + j];
                        }
                        r.push_back(s3);
                        string s4("");
                        for (int j = b - 1; j >= 0; --j) {
                            for (int i = 0; i < a; ++i)
                                s4 += p[x + i][y + j];
                        }
                        r.push_back(s4);
                    }
                    string minn = *min_element(r.begin(), r.end());
                    up.insert(minn);
                }
            }
            int t = (n / a) * (m / b);
            if (up.size() == t) v.push_back({a, b});
        }
    }
    cout << v.size() << '\n';
    sort(v.begin(), v.end(), cmp);
    cout << v[0].first << " " << v[0].second;
    return 0;
}