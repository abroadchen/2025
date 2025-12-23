
#include <set>
#include <queue>
#include <vector>
#include <iostream>
using namespace std;

int main() {
    set<long long> generated;
    queue<long long> q;
    vector<long long> sequence;

    // 起始值
    q.push(1);
    generated.insert(1);
    sequence.push_back(1);

    while (!q.empty() && sequence.size() < 1000) {
        long long x = q.front();
        q.pop();

        // 生成子节点的规则需要更仔细分析原始序列
        long long c1 = 3 * x;
        long long c2 = 3 * x + 1;

        if (generated.find(c1) == generated.end()) {
            generated.insert(c1);
            q.push(c1);
            sequence.push_back(c1);
        }

        if (generated.find(c2) == generated.end()) {
            generated.insert(c2);
            q.push(c2);
            sequence.push_back(c2);
        }
    }

    sequence.push_back(0);
    sequence.push_back(1000000001);
    sort(sequence.begin(), sequence.end());

    // 输出结果
    cout << "int a[1005] = {" << endl;
    for (int i = 0; i < min(1000, (int)sequence.size()); i++) {
        if (i % 18 == 0) cout << "    ";
        cout << sequence[i];
        if (i != min(1000, (int)sequence.size()) - 1) cout << ",";
        if (i % 18 == 17) cout << endl;
    }
    if (sequence.size() % 18 != 0) cout << endl;
    cout << "};" << endl;

    return 0;
}