//
// Created by Psy.C on 2025/11/2.
//
/*
*k: 玩家数量
n: 物品原始种类数
m: 合成配方数量
q: 查询操作数量
i: 循环变量
 *cin.ignore()清除输入缓冲区中的换行符
*创建一个包含k个元素的vector，每个元素是一个map<string,int>
表示k个玩家各自的物品库存（物品名->数量）
*创建一个map，用于存储合成配方
键为合成产物名称，值为所需原料列表（原料名和数量的pair组成的vector）
*定义正则表达式模式：匹配"物品名:原料列表"格式
smatch matches用于存储正则匹配结果
 *
 *提取匹配的第一组（物品名）和第二组（原料字符串）
 *使用stringstream按逗号分割原料字符串
 *如果原料字符串开头有空格，则去掉首空格
 *使用内部stringstream提取物品名和数量
 *将物品名和数量作为pair加入原料列表
 *
 */
#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <regex>
#include <algorithm>
#define rep(i,n) for(i=0;i<(n);++i)
using namespace std;

int k, n, m, q, i;


int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> k >> n >> m >> q; cin.ignore();
    vector<map<string, int>> c(k);
    rep(i, n) { string dummy; getline(cin, dummy); }
    map<string, vector<pair<string, int>>> h;
    rep(i, m) {
        string line; getline(cin, line);
        regex pattern("(\\w+):(.*)");
        smatch matches;
        if (regex_search(line, matches, pattern)) {
            string recipe_name = matches[1];
            string ingredients_str = matches[2];
            vector<pair<string, int>> ingredients;//创建临时vector存储当前配方的所有原料
            stringstream ss(ingredients_str);
            string ingredient;
            while (getline(ss, ingredient, ',')) {
                if (!ingredient.empty() && ingredient[0] == ' ') {
                    ingredient = ingredient.substr(1);
                }
                stringstream iss(ingredient);
                string item_name;
                int item_count;
                iss >> item_name >> item_count;
                ingredients.push_back({item_name, item_count});
            }
            h[recipe_name] = ingredients;//将配方名称和对应的原料列表存入配方map中
        }
    }
    rep(i, q) {//循环处理q次查询操作
        string player_num, item_name;
        cin >> player_num >> item_name;//读取玩家编号和物品名称
        int player_index = stoi(player_num) - 1;//将玩家编号字符串转换为整数，并减1得到数组索引（因为编号从1开始）
        c[player_index][item_name]++;//给对应玩家的对应物品数量加1
        for (auto& recipe : h) {//遍历所有配方，检查能否合成
            string recipe_name = recipe.first;//获取当前配方的名称和所需原料列表
            vector<pair<string, int>>& ingredients = recipe.second;
            bool can_craft = true;//假设可以合成
            for (auto& ingredient : ingredients) {//检查玩家是否拥有足够的每种原料
                string ingredient_name = ingredient.first;
                int required_amount = ingredient.second;
                if (c[player_index][ingredient_name] < required_amount) {
                    can_craft = false;
                    break;
                }
            }
            if (can_craft) {
                for (auto& ingredient : ingredients) {
                    string ingredient_name = ingredient.first;
                    int required_amount = ingredient.second;
                    c[player_index][ingredient_name] -= required_amount;//扣除所需的各种原料数量
                }
                c[player_index][recipe_name]++;//增加合成出的新物品数量
            }
        }
    }
    for (auto& player_inventory : c) {//遍历每个玩家的物品库存
        vector<string> keys_to_remove;
        for (auto& item : player_inventory) {
            if (item.second == 0) {//查找数量为0的物品，准备移除
                keys_to_remove.push_back(item.first);
            }
        }
        for (const string& key : keys_to_remove) {//实际移除数量为0的物品
            player_inventory.erase(key);
        }
        cout << player_inventory.size() << endl;//输出当前玩家拥有的物品种类数
        vector<pair<string, int>> sorted_items(player_inventory.begin(), player_inventory.end());
        sort(sorted_items.begin(), sorted_items.end());//将物品按名称排序
        for (auto& item : sorted_items) {//输出每种物品的名称和数量
            cout << item.first << " " << item.second << endl;
        }
    }
    return 0;
}