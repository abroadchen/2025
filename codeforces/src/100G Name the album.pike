//
// Created by Psy.C on 2025/11/12.
//

/*
从标准输入读取所有内容
使用- ({""})去除空字符串（处理末尾可能的空行）

按空格分割每行数据得到p数组
p[0]是姓名，p[1]是年份
将姓名和年份的对应关系存入映射mp

m表示要查询的人员数量
cy获取该姓名对应的年份，如果找不到则默认为1899
如果当前年份小于已找到的最小年份：
更新最小年份res
更新答案ans
如果当前年份等于最小年份且姓名字典序更大：
更新答案ans（字典序大的优先）

data[0]: 存储人员总数 n
data[1] 到 data[n]: 存储n个人员的信息（姓名和年份）
data[n+1]: 存储查询人数 m
data[n+2] 到 data[n+1+m]: 存储m个要查询的姓名

*/

int main() {
    array(string) data = (Stdio.stdin.read() / "\n") - ({""});
    int n = (int)data[0];
    mapping(string:int) mp = ([]);
    for (int i = 1; i <= n; ++i) {
        array(string) p = data[i] / " ";
        string name = p[0];
        int year = (int)p[1];
        mp[name] = year;
    }

    int m = (int)data[n + 1];
    string ans = "";
    int res = 2012;

    for (int i = n + 2; i < n + 2 + m; ++i) {
        string cur = data[i];
        int cy = mp[cur] || 1899;
        if (cy < res) {
            res = cy;
            ans = cur;
        } else if (cy == res && cur > ans) {
            ans = cur;
        }
    }

    write(ans + "\n");
    return 0;
}
