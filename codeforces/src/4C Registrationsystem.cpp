//
// Created by Psy.C on 2025/9/11.
//


#include <iostream>
#include <unordered_set>
#include <unordered_map>
using namespace std;

int main() {
    int n;
    cin>>n;

    unordered_set<string> registered;
    unordered_map<string, int> next_suffix;

    for (int i = 0; i < n; i++) {
        string name;
        cin>>name;

        if (registered.find(name) == registered.end()) {
            registered.insert(name);
            cout << "OK" << endl;
        } else {
            int suffix = next_suffix[name];
            if (suffix == 0) suffix = 1;

            string new_name;
            do {
                new_name = name + to_string(suffix);
                suffix++;
            } while (registered.find(new_name) != registered.end());

            next_suffix[name] = suffix;

            registered.insert(new_name);
            cout << new_name << endl;
        }
    }
    return 0;
}