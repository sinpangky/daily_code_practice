#include <stdio.h>
#include <stdlib.h>

#define MAXKEY 1000
int hash(const char* key) {
  int h = 0, g;
  while (*key) {
    h = (h << 4) + *key++;
    g = h & 0xf0000000;
    if (g) h ^= g >> 24;
    h &= ~g;
  }
  return h % MAXKEY;
}



int main() {
  const char* pStr[6] = {"xiongda", "lele", "hanmeimei", "wangdao", "fenghua","xiongda"};
  char* hashTable[MAXKEY] = {NULL};
  int i;
  for (i = 0; i < 6; i++) {
    if (hashTable[hash(pStr[i])]) {  // 冲突的话用简单的线性探测法解决
      int j;
      for (j  = 0; hashTable[hash(pStr[i])+j]; j++);
      printf("%10s hashValue=%d\n", pStr[i], hash(pStr[i])+j);
      hashTable[hash(pStr[i])+j] = (char*)pStr[i];
      
    } else {  // 不冲突就正常填入
      printf("%10s hashValue=%d\n", pStr[i], hash(pStr[i]));
      hashTable[hash(pStr[i])] = (char*)pStr[i];
    }
  }

  return 0;
}
