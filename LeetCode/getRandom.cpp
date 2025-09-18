#include <bits/stdc++.h>
using namespace std;

class RandomizedSet {
public:
    unordered_map<int, int> map = {};
    vector<int> vec = {};

    RandomizedSet() {}

    bool insert(int val) {
        if (map.find(val) != map.end())
            return false;
        vec.push_back(val);
        map[val] = vec.size() - 1;
        return true;
    }

    bool remove(int val) {
        if (map.find(val) == map.end())
            return false;
        int idx = map[val];
        vec[idx] = vec.back();
        vec.pop_back();
        map.erase(val);
        if (idx < vec.size())
            map[vec[idx]] = idx;
        return true;
    }

    int getRandom() {
        int i = rand() % vec.size();
        return vec[i];
    }
};

int main() {
    vector<int> test = {};
    auto r = RandomizedSet();
    cout << "output = [ null, ";
    cout << r.insert(1) << ", ";
    cout << r.remove(2) << ", ";
    cout << r.insert(2) << ", ";
    cout << r.getRandom() << ", ";
    cout << r.remove(1) << ", ";
    cout << r.insert(2) << ", ";
    cout << r.getRandom() << " ";
    cout << "]" << endl;

}
