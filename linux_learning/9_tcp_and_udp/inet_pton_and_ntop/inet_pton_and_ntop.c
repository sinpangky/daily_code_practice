#include <func.h>

int main(int argc, char const *argv[]) {
  char dot_addr[20] = "234.123.5.12";
  printf("Dot-decimal is:        %s\n",dot_addr);
  struct in_addr  in_addr;
  int ret = inet_pton(AF_INET,dot_addr,&in_addr);
  ERROR_CHECK(ret,0,"inet_pton");
  printf("Network byte order is: %x\n",in_addr.s_addr);
  inet_ntop(AF_INET,&in_addr,dot_addr,20);
  printf("New dot-decimal is:    %s\n",dot_addr);

  return 0;
}
