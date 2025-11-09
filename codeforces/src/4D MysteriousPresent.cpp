//
// Created by Psy.C on 2025/9/11.
//


#include <iostream>
#include <vector>
using namespace std;

struct Envelope {
    int width, height, index;
};


int main() {
    int n, w, h;
    cin >> n >> w >> h;

    vector<Envelope> envelopes;

    for (int i = 1; i <= n; i++) {
        int width, height;
        cin >> width >> height;
        if (width > w && height > h) {
            envelopes.push_back({width, height, i});
        }
    }

    if (envelopes.empty()) {
        cout << 0 << endl;
        return 0;
    }

    sort(envelopes.begin(), envelopes.end(), [](const Envelope& a, const Envelope& b) {
        if (a.width != b.width) return a.width < b.width;
        return a.height < b.height;
    });

    int size = envelopes.size();
    vector<int> dp(size, 1);
    vector<int> parent(size, -1);

    for (int i = 1; i < size; i++) {
        for (int j = 0; j < i; j++) {
            if (envelopes[j].width < envelopes[i].width &&
                envelopes[j].height < envelopes[i].height) {
                if (dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    parent[i] = j;
                }
            }
        }
    }

    int maxLength = 0;
    int maxIndex = -1;
    for (int i = 0; i < size; i++) {
        if (dp[i] > maxLength) {
            maxLength = dp[i];
            maxIndex = i;
        }
    }

    cout << maxLength << endl;

    if (maxLength > 0) {
        vector<int> chain;
        int current = maxIndex;
        while (current != -1) {
            chain.push_back(envelopes[current].index);
            current = parent[current];
        }
        reverse(chain.begin(), chain.end());
        for (int i = 0; i < chain.size(); i++) {
            cout << chain[i];
            if (i < chain.size() - 1) cout << " ";
        }
        cout << endl;
    }

    return 0;
}