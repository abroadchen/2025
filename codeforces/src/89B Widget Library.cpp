//
// Created by Psy.C on 2025/11/8.
//
/*
*l[N], r[N]: 存储每个元素的最小和最大尺寸
f[N]: 存储元素类型（1=VBox, 2=HBox）
v1[N], v2[N]: 存储边距/间距参数
mp: 字符串到索引的映射
len: 当前元素数量
a[N]: 存储元素名称
e[N]: 存储每个容器的子元素
 *
*如果已经计算过(l[x] != -1)，直接返回
初始化最小尺寸为0
*遍历所有子元素：
递归计算子元素尺寸
根据容器类型计算尺寸：
VBox (f[x] == 1): 宽度取子元素最大值，高度累加子元素高度
HBox (f[x] == 2): 宽度累加子元素宽度，高度取子元素最大值
*处理边距和间距：
m: 子元素数量
如果有子元素：
VBox: 高度增加(m-1)个间距
HBox: 宽度增加(m-1)个间距
宽度和高度都增加2倍边距（左右/上下边距）
 *
 *解析名称和尺寸，存储到相应数组中
*处理容器定义：
VBox: 垂直布局容器
HBox: 水平布局容器
 *
*处理属性设置和父子关系：
格式如："A.spacing=10" 或 "A.add(B)"
设置边距/间距或添加子元素
 *
 */
#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#include <cstring>
#define sz(x) ((int)(x).size())
using namespace std;

typedef long long ll;
const int N = 105;
ll l[N], r[N], f[N], v1[N], v2[N];
map<string, int> mp;
int len;
string a[N];
vector<int> e[N];

void dfs(int x) {
    if (l[x] != -1) return;
    l[x] = 0;
    for (int v : e[x]) {
        dfs(v);
        if (f[x] == 1) l[x] = max(l[x], l[v]), r[x] += r[v];
        else r[x] = max(r[x], r[v]), l[x] += l[v];
    }
    int m = sz(e[x]);
    if (m) {
        if (f[x] == 1) r[x] += (m - 1) * v2[x];
        else l[x] += (m - 1) * v2[x];
        l[x] += 2 * v1[x], r[x] += 2 * v1[x];
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    memset(l, -1, sizeof(l));
    int q; cin >> q;
    while (q--) {
        string s; cin >> s;
        if (s == "Widget") {
            cin >> s; string b = ""; int n = sz(s);
            for (int i = 0; i < n; ++i) {
                if (s[i] == '(') {
                    mp[b] = ++len; l[len] = 0; a[len] = b;
                    int p = i + 1;
                    while (s[p] != ',') {
                        l[len] = l[len] * 10 + s[p] - '0';
                        p++;
                    }
                    p++;
                    while (s[p] != ')') {
                        r[len] = r[len] * 10 + s[p] - '0';
                        p++;
                    }
                    break;
                }
                b += s[i];
            }
        } else if (s == "VBox") {
            cin >> s;
            mp[s] = ++len; a[len] = s; f[len] = 1;
        } else if (s == "HBox") {
            cin >> s;
            mp[s] = ++len; a[len] = s; f[len] = 2;
        } else {
            int n = sz(s); string b = "", c = "";
            for (int i = 0; i < n; ++i) {
                if (s[i] == '.') {
                    if (s[i + 1] == 's') {
                        int x = 0;
                        for (int j = i + 1; j < n - 1; ++j) {
                            if (s[j] >= '0' && s[j] <= '9')
                                x = x * 10 + s[j] - '0';
                        }
                        if (s[i + 5] == 'b') v1[mp[b]] = x;
                        else v2[mp[b]] = x;
                    } else {
                        for (int j = i + 6; j < n - 1; ++j) c += s[j];
                        e[mp[b]].push_back(mp[c]);//将元素 c 添加为元素 b 的子元素
                    }
                    break;
                }
                b += s[i];
            }
        }
    }
    sort(a + 1, a + len + 1);
    for (int i = 1; i <= len; ++i) {
        dfs(mp[a[i]]);
        cout << a[i] << " " << l[mp[a[i]]] << " " << r[mp[a[i]]] << '\n';
    }
    return 0;
}