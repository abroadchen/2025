//
// Created by Psy.C on 2026/1/9.
//

#include <iostream>
#include <vector>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define rep(i,n) for (int i = 0; i < (n); ++i)
using namespace std;


int main() {
    fast;
    int n, m; cin >> n >> m;
    vector e(n, vector(n, false));//e[i][j]为true表示存在从i到j的边
    vector v(n, vector(n, vector<int>()));//存储每条边对应的路径信息
    for (int i = 0, x, y, k; i < m; ++i) {
        cin >> x >> y; x--, y--; e[x][y] = true;//读入边的起点x和终点y
        cin >> k; v[x][y].resize(k);//路径长度k
        //读入路径上的节点
        rep(j, k) { cin >> v[x][y][j]; v[x][y][j]--; }//读入第j个节点编号 转换为0基索引
    }
    vector<tuple<int,int,int,vector<int>>> f[2][2];//(起点, 终点, 长度, 路径) [左端是否存在][右端是否存在]
    rep(x,n) rep(y,n) if (e[x][y]) rep(i,v[x][y].size()+1) {// 遍历路径v[x][y]的所有可能分割点
        // 左半部分要么为空，要么以x结尾 右半部分要么为空，要么以y开头
        if ((!i || v[x][y][i-1]==x) && (i==v[x][y].size() || v[x][y][i]==y)) {
            vector<int> l, r; l.assign(v[x][y].rend()-i, v[x][y].rend());//从倒数第i个到末尾的元素复制给l（反向复制）
            if (!l.empty()) {//如果左半部分不为空
                bool ok = true;//有效性标志
                for (int j = 0; j+1<l.size() && l.size()<=2*n+1; ++j) {//循环直到只剩一个元素或长度超限
                    if (!e[l[j+1]][l[j]]) { ok = false; break; }// 检查相邻节点间是否有边
                    auto& f = v[l[j+1]][l[j]];// 获取这条边的路径
                    l.insert(l.end(), f.rbegin(), f.rend());//将路径反向插入l末尾
                }
                if (!ok || l.size() > 2*n+1) break;//无效或过长则跳出
            }
            r.assign(v[x][y].begin()+i, v[x][y].end());//从v[x][y]的第i个元素到末尾赋值给r
            if (!r.empty()) {
                bool ok = true;
                for (int j = 0; j+1<r.size() && r.size()<=2*n+1; ++j) {
                    if (!e[r[j]][r[j+1]]) { ok = false; break; }
                    auto& f = v[r[j]][r[j+1]];
                    r.insert(r.end(), f.begin(), f.end());
                }
                if (!ok || r.size() > 2*n+1) break;
            }
            vector<int> a;
            a.insert(a.end(), l.rbegin(), l.rend());//将l反向插入a末尾（因为l是反向构建的）
            a.insert(a.end(), r.begin(), r.end());
            //根据左右部分是否为空选择数组
            f[!l.empty()][!r.empty()].emplace_back(l.empty() ? x : l.back(),//起点是x或l的最后一个元素
                r.empty() ? y : r.back(), l.size() + r.size(), a);//终点是y或r的最后一个元素  总长度  完整路径
        }
    }
    //长度维度 节点维度 类型维度2 存储tuple<int,int,vector<int>>类型
    vector dp(2*n+2, vector(n, array<tuple<int,int,vector<int>>, 2>{}));
    rep(i,2*n+2) rep(j,n) dp[i][j].fill({-1,-1,{}});//将所有元素设为无效值
    rep(i,n) dp[0][i][0] = {};//长度为0时，所有节点的[0]状态为空
    //遍历所有长度i、类型u、类型v 对f[u][v]中的每个路径片段[x,y,l,t]
    rep(i,2*n+2) rep(u,2) rep(v,2) for (const auto& [x,y,l,t] : f[u][v]) {
        //如果总长度不超过限制且起始状态有效 更新目标状态：记录前驱节点、前驱类型、路径片段
        if (i+l <= 2*n+1 && get<0>(dp[i][x][!u]) != -1) dp[i+l][y][v] = {x,!u,t};
    }
    //寻找第一个有效的长度i的解
    for (int i = 1; i <= 2*n; ++i) rep(x,n) if (get<0>(dp[i][x][1]) != -1) {
        vector<int> ans;//存储结果路径
        int v = x, t = 1, len = i;//当前位置、类型、剩余长度
        while (len) {//还有长度需要处理时
            auto [u, q, a] = dp[len][v][t];//从DP表获取前驱信息
            ans.insert(ans.begin(), a.begin(), a.end());//将路径片段插入ans开头
            len -= a.size();//更新剩余长度、位置、类型
            v = u;
            t = q;
        }
        cout << ans.size() << '\n';//输出路径长度
        //输出路径中每个节点（转换回1基索引）
        rep(j,ans.size()) cout << ans[j]+1 << " \n"[j==ans.size()-1];
        return 0;
    }
    cout << 0 << '\n';
    return 0;
}