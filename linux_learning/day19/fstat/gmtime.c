#include <func.h>

int main(int argc, char const *argv[])
{
  time_t second =time(NULL);
  printf("%ld\n",second);
  struct tm *p = gmtime(&second);
  printf("%d %d %d %d:%d:%d",p->tm_year,p->tm_mon+1,p->tm_mday,p->tm_hour,p->tm_min,p->tm_sec);
   
  return 0;
}
