//
// Created by Psy.C on 2025/9/11.
//


#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    string command;
    set<string> people;
    long long totalTraffic = 0;

    while (getline(cin, command)) {
        if (command.empty()) continue;
        if (command[0] == '+') {
            string name = command.substr(1);
            people.insert(name);
        }
        else if (command[0] == '-') {
            string name = command.substr(1);
            people.erase(name);
        }
        else {
            size_t colonPos = command.find(':');
            if (colonPos != string::npos) {
                string sender = command.substr(0, colonPos);
                string message = command.substr(colonPos + 1);

                int messageLength = message.length();
                int chatSize = people.size();
                totalTraffic += (long long) messageLength * chatSize;
            }
        }
    }

    cout << totalTraffic << endl;

    return 0;
}