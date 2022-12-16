

#include <iostream>
#include <tuple>
#include <vector>

int main() {
  std::tuple<int, float, std::string> data(1, 2.2, "hello world\n");
  
  std::cout << std::get<0>(data) << "\t";
  std::cout << std::get<1>(data) << "\t";
  std::cout << std::get<2>(data) << "\t";
  std::vector<int>::iterator;
  return 0;
}
