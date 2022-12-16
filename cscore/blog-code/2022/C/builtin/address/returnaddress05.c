
#include <stdio.h>

void func_a()
{
  void* p        = __builtin_return_address(0);
  void* rbp      = __builtin_frame_address(0);
  void* last_rbp = __builtin_frame_address(1);
  asm volatile(
    "leaq 16(%1), %%rsp;" // 恢复 rsp 寄存器的值
    "movq %2, %%rbp;"     // 恢复 rbp 寄存器的值
    "jmp *%0;"            // 直接跳转
    ::"r"(p), "r"(rbp), "r"(last_rbp): // ① ② ③
  ); // ⓵⓶⓷⓸⓹⓺⓻⓼⓽⓾
  printf("finished in func_a\n");
}


int main()
{
  void* p = __builtin_return_address(0);
  printf("main return address = %p\n", p);
  func_a();
  printf("finished in main function \n");

  // 打印九九乘法表
  int i, j;
  for(i = 1; i < 10; ++i) 
  {
    for(j = 1; j <= i; ++j) {
      printf("%d x %d = %d\t", i, j, i * j);
    }
    printf("\n");
  }
  return 0;
}