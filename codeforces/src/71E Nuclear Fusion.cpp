//
// Created by Psy.C on 2025/11/3.
//
/*
*n: 第一组元素数量
m: 第二组元素数量
s1[N]: 存储第一组元素（反应物）
s2[N]: 存储第二组元素（生成物）
pos[N]: 记录每个第一组元素对应的生成物索引
flag: 标记是否找到解
 *声明映射，用于存储元素符号到原子序数的映射
*定义元素数组e，存储前100号元素的化学符号（索引对应原子序数）
声明字符串变量s用于临时存储输入
 *声明向量数组，用于存储每个生成物对应的反应物
 *
*定义深度优先搜索函数
l: 当前考虑的反应物索引
sum: 当前组合的原子序数和
r: 当前考虑的生成物索引
 *递归终止条件：如果所有生成物都已处理完，标记找到解并返回
*如果当前生成物的原子序数等于当前组合和，说明找到了一种匹配
递归处理下一个生成物，重置sum为0
*pre用于去重，避免重复考虑相同原子序数的元素
遍历剩余的反应物，剪枝条件：
还有未处理的反应物
还未找到解
当前反应物加上已选反应物的和不超过目标生成物的原子序数
*如果第i个反应物未被使用且与前一个不同：
记录当前反应物原子序数用于去重
将第i个反应物分配给第r个生成物
递归搜索下一个反应物
如果未找到解，回溯取消分配
 *
 *
 *按格式输出化学反应方程式
 *
 */
#include <vector>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

const int N = 20;
int n, m, s1[N], s2[N], pos[N];
bool flag;
map<string, int> mp;
string e[110] = {
    "", "H", "He", "Li", "Be", "B",
    "C", "N", "O", "F", "Ne", "Na",
    "Mg", "Al","Si","P","S","Cl",
    "Ar","K","Ca","Sc","Ti","V",
    "Cr","Mn","Fe","Co","Ni","Cu",
    "Zn","Ga","Ge","As","Se","Br",
    "Kr","Rb","Sr","Y","Zr","Nb",
    "Mo","Tc","Ru","Rh","Pd","Ag",
    "Cd","In","Sn","Sb","Te","I",
    "Xe","Cs","Ba","La","Ce","Pr",
    "Nd","Pm","Sm","Eu","Gd","Tb",
    "Dy","Ho","Er","Tm","Yb","Lu",
    "Hf","Ta","W","Re","Os","Ir",
    "Pt","Au","Hg","Tl","Pb","Bi",
    "Po","At","Rn","Fr","Ra","Ac",
    "Th","Pa","U","Np","Pu","Am",
    "Cm","Bk","Cf","Es","Fm"
}, s;
vector<int> ans[N];

void dfs(int l, int sum, int r) {
    if (r == m + 1) { flag = 1; return; }
    if (s2[r] == sum) { dfs(1, 0, r + 1); return; }
    int pre(-1);
    for (int i = l; i <= n && !flag && s1[i] + sum <= s2[r]; ++i) {
        if (pos[i] == -1 && s1[i] != pre) {
            pre = s1[i];
            pos[i] = r;
            dfs(l + 1, s1[i] + sum, r);
            if (!flag) pos[i] = -1;
        }
    }
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for (int i = 1; i <= 100; ++i) mp[e[i]] = i;
    for (int i = 1; i <= n; ++i) cin >> s, s1[i] = mp[s];
    for (int i = 1; i <= m; ++i) cin >> s, s2[i] = mp[s];
    sort(s1 + 1, s1 + n + 1);
    sort(s2 + 1, s2 + m + 1);
    for (int i = 1; i <= n; ++i) pos[i] = -1;
    dfs(1, 0, 1);
    if (flag) {
        cout << "YES\n";
        for (int i = 1; i <= n; ++i) ans[pos[i]].push_back(s1[i]);
        for (int i = 1; i <= m; ++i) {
            cout << e[ans[i][0]];
            for (int j = 1; j <= (int)ans[i].size() - 1; ++j) {
                cout << "+" << e[ans[i][j]];
            }
            cout << "->" << e[s2[i]] << endl;
        }
    } else {
        cout << "NO\n";
    }
    return 0;
}