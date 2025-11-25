//
// Created by Psy.C on 2025/11/23.
//

#include <vector>
#include <iostream>
#define rep(i,n) for(int i=0;i<n;++i)
using namespace std;


bool ckt(const string &s) {
    if (s[0]==s[1] && s[0]==s[3] && s[0]==s[4] &&
        s[0]==s[6] && s[0]==s[7]) return true;
    return false;
}

bool ckp(const string &s) {
    if (s[0]>s[1] && s[1]>s[3] && s[3]>s[4] &&
        s[4]>s[6] && s[6]>s[7]) return true;
    return false;
}

int main() {
    ostream::sync_with_stdio(false);
    int t; cin>>t;
    vector<pair<int,string>> ta, pho, pi;
    int mt(-1), mph(-1), mpi(-1);
    while(t--) {
        int n, ph(0), tx(0), pz(0);
        string name, phone;
        cin >> n >> name;
        rep(i,n) {
            cin >> phone;
            if (ckt(phone)) tx++;
            else if (ckp(phone)) pz++;
            else ph++;
        }
        if (tx >= mt) { mt = tx; ta.emplace_back(tx, name); }
        if (pz >= mpi) { mpi = pz; pi.emplace_back(pz, name); }
        if (ph >= mph) { mph = ph; pho.emplace_back(ph, phone); }
    }

    vector<string> ans1, ans2, ans3;
    for (const auto& i : ta) {
        if (i.first == mt) ans1.emplace_back(i.second);
    }
    for (const auto& i : pi) {
        if (i.first == mpi) ans2.emplace_back(i.second);
    }
    for (const auto& i : pho) {
        if (i.first == mph) ans3.emplace_back(i.second);
    }

    cout << "If you want to call a taxi, you should call: ";
    rep(i,ans1.size()) {
        if (i == ans1.size() - 1) cout << ans1[i] << '.' << '\n';
        else cout <<  ans1[i] << ", ";
    }
    cout << "If you want to order a pizza, you should call: ";
    rep(i,ans2.size()) {
        if (i == ans2.size() - 1) cout << ans2[i] << '.' << '\n';
        else cout <<  ans2[i] << ", ";
    }
    cout << "If you want to go to a cafe with a wonderful girl, you should call: ";
    rep(i,ans3.size()) {
        if (i == ans3.size() - 1) cout << ans3[i] << '.' << '\n';
        else cout <<  ans3[i] << ", ";
    }
    return 0;
}