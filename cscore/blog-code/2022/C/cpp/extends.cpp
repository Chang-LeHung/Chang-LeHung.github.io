
#include <iostream>

using namespace std;


class A{

  public:
    virtual void start() {
      cout << "a\n";
    }
};

class B:public A {

  public:
    virtual void start() {
      cout << "b\n";
    }
    template<typename T>
    void out(T s) {
      cout << s;
    }
};

int main() {

  B *b = new B;
  b->out("hello world\n");
  A* a = (A*) b;
  a->start();
  return 0;
}