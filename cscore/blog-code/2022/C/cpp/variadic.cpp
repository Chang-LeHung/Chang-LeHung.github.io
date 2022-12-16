

#include <iostream>
#include <bitset>

template<typename T>
void print(const T& arg){
  std::cout << arg;
}

template <typename T, typename... Types>
void print(const T& firstArg, const Types&... args) {
  std::cout << firstArg << "\t";
  print(args...);
}

int main() {

  print(1, 2, 3, 4, "hello world", std::bitset<16>(377));
  NULL;
  return 0;
}