//
// Created by Psy.C on 2026/4/25.
//
/**
id: 客户编号
a, b: 可接受的尺码范围（左端点，右端点）
重载 < 运算符，按 a 升序排序
n: 客户数量, num[i]: 第i种尺码的数量, ans[i]: 第i个客户分配的尺码
尺码名称数组

时间复杂度
O(n log n): 主要是排序的时间复杂度
其他操作都是线性的
空间复杂度
O(n): 主要是存储范围需求客户的数组
 */
#include <bits/stdc++.h>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
constexpr int N = 1e5+7;

struct node {
    int id, a, b;
    bool operator<(const node &o) const {
        return a < o.a;
    }
};
vector<node> v;///有范围需求的客户
int n, num[10], ans[N];
string s, str[] = {
    "S","M","L","XL","XXL","XXXL"
};
bool get() {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> s;
        if (s.find(',') != string::npos) {//检查是否包含逗号（范围需求）
            auto a = s.substr(0, s.find(',')),//分割字符串获取第一个尺码
            b = s.substr(s.find(',')+1);//分割字符串获取第二个尺码
            for (int j = 0; j < 6; ++j) {
                if (str[j] == a) {//找到第一个尺码对应索引
                    v.push_back({i, j, j+1});//存储范围 [j, j+1]
                    break;
                }
            }
        } else {//单一尺码需求
            for (int j = 0; j < 6; ++j) {
                if (s == str[j]) {
                    if (num[j] == 0) return false;//库存不足
                    num[j]--;//分配一件
                    ans[i] = j;//记录分配结果
                }
            }
        }
    }
    sort(v.begin(), v.end());
    for (auto &[id, a, b] : v) {//遍历范围需求客户
        if (num[a]) {//优先满足较小尺码
            num[a]--;
            ans[id] = a;
        } else if (num[b]) {//尝试较大尺码
            num[b]--;
            ans[id] = b;
        } else return false;//两种尺码都缺货
    }
    return true;
}

int main() {
    fast;
    for (int i = 0; i < 6; ++i) cin >> num[i];//读取各尺码库存
    if (get()) {// 处理分配
        cout << "YES\n";
        for (int i = 1; i <= n; ++i)
            cout << str[ans[i]].c_str() << '\n';//输出分配结果
    } else cout << "NO\n";
    return 0;
}