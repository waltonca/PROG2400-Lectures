#include <iostream>
#include <memory>

struct Data {
  int _num {0};
  float _val {0.0};
};
std::ostream &operator<<(std::ostream &output, const Data &data) {
    output << "num: " << data._num << ", val: " << data._val;
    return output;
}

class Stack {
  struct Node {
    Data _data;
    std::unique_ptr<Node> _next {nullptr};
  };
  std::unique_ptr<Node> _top {nullptr};
public:
  void push(Data data) {
      auto node = std::make_unique<Node>(data);
      node->_next = std::move(_top);
      _top = std::move(node);
  }

  friend std::ostream &operator<<(std::ostream &output, const Stack &stack);
};

std::ostream &operator<<(std::ostream &output, const Stack &stack) {
    auto node = stack._top.get();
    while (node != nullptr) {
        output << node->_data << std::endl;
        node = node->_next.get();
    }
    return output;
}

int main() {

    Stack stack;

    // test 1 - add a node to the stack
    std::cout << "Test 1 - add a node" << std::endl;
    std::cout << "-------------------" << std::endl;

    stack.push({1, 6.67});

    std::cout << stack << std::endl;

    // test 2 - add more nodes to the stack
    std::cout << "Test 2 - add more nodes" << std::endl;
    std::cout << "-----------------------" << std::endl;

    stack.push({2, 1.1});
    stack.push({3, 2.2});
    stack.push({4, 3.3});
    stack.push({5, 4.4});

    std::cout << stack << std::endl;

    return 0;
}