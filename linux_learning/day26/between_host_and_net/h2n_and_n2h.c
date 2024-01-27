#include <func.h>

int main(int argc, char const *argv[]) {
  uint16_t hostshort = 0x1234;
  uint16_t netshort = htons(hostshort);
  hostshort = ntohs(netshort);
  uint32_t hostlong = 0x12345678;
  uint32_t netlong = htonl(hostlong);
  hostlong = ntohl(netlong);

  printf("Host ordered short: %x, Network ordered short: %x\n", hostshort,
         netshort);
  printf("Host ordered long: %x, Network ordered long: %x\n", hostlong,
         netlong);

  return 0;
}
