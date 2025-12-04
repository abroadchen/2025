//
// Created by Psy.C on 2025/12/3.
//
/*
*n: 存储输入的行数
tp: 存储throw语句所在的行号
s: 存储当前处理的字符串行
ts: 存储throw语句中的异常类型
st: 整数栈，用于跟踪try语句的行号
 */
#include <iostream>
#include <algorithm>
#include <stack>
#define fast ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;

int n, tp;
string s, ts;
stack<int> st;

int get() {//识别当前行的语句类型
    for (int i = 0; i < static_cast<int>(s.length()); ++i) {//遍历字符串s的每个字符位置
        if (s.substr(i,3) == "try") return 1;
        if (s.substr(i,5) == "catch") return 2;
        if (s.substr(i,5) == "throw") return 3;
    }
    return -1;
}
string search(const bool tag=false) {//提取括号中的内容，tag参数决定查找模式
    string res;
    const int l = static_cast<int>(s.find('(')),//查找左括号'('的位置l
    r = static_cast<int>(s.find(tag ? ')' : ','));//根据tag的值查找右位置：如果tag为true查找')'，否则查找','
    if (l + 1 && r + 1) {//检查是否找到了左右括号（find返回-1表示未找到，+1后变为0即false）
        for (int i = l + 1; i < r; ++i) if (s[i] != ' ') {
            res += s[i];//遍历括号间的内容，跳过空格，将非空格字符添加到结果中
        }
    }
    return res;
}

void out() {//输出引号内的内容
    const int l = static_cast<int>(s.find('\"')),
    r = static_cast<int>(s.rfind('\"'));//查找第一个双引号和最后一个双引号的位置
    if (l + 1 && r + 1) {//检查是否找到了两个双引号
        for (int i = l + 1; i < r; ++i) cout << s[i];
        cout << '\n';//输出双引号之间的所有字符，然后换行
    }
}

int main() {
    fast;
    cin >> n; getline(cin, s);//使用getline读取第一行剩余内容（消耗换行符）
    for (int i = 1; i <= n; ++i) {//循环处理每一行，从第1行到第n行
        getline(cin, s);//读取当前行内容到字符串s
        const int t = get();//获取当前行的语句类型
        if (t == 1) st.push(i);
        else if (t == 2) {
            const int x = st.top(); st.pop();//取出最近的try语句行号x，并从栈中弹出
            if (tp > x && search() == ts) { out(); return 0; }//throw语句在当前try-catch块之后(tp>x)且异常类型匹配(search()==ts)
        } else if (t == 3) {
            ts = search(true);//提取异常类型保存到ts
            tp = i;//记录throw语句的行号到tp
        }
    }
    cout << "Unhandled Exception" << '\n';
    return 0;
}