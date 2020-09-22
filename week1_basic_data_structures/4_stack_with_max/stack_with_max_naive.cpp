#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <algorithm>

using std::cin;
using std::string;
using std::vector;
using std::cout;
using std::max_element;
using std::endl;

class StackWithMax {
    vector<int> stack;

  public:

    void Push(int value) {
        stack.push_back(value);
    }

    void Pop() {
        assert(stack.size());
        stack.pop_back();
    }

    int Max() const {
        assert(stack.size());
        return *max_element(stack.begin(), stack.end());
    }
};

int main() {
    int num_queries = 0;
    cin >> num_queries;

    vector<int> f_stack;

    string query;
    string value;

    StackWithMax stack;
    int count=0;

    for (int i = 0; i < num_queries; ++i) {
        cin >> query;
        if (query == "push") {
            cin >> value;
            stack.Push(std::stoi(value));
        }
        else if (query == "pop") {
            stack.Pop();
        }
        else if (query == "max") {
           f_stack.push_back(stack.Max());
        }
        else {
            assert(0);
        }
    }

    for (int i = 0; i < f_stack.size(); ++i) {
        cout<<f_stack[i]<<endl;
    }


    return 0;
    
}