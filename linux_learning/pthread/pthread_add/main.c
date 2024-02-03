#include <func.h>

typedef struct {
  int count;
  pthread_mutex_t mutex;
} Share_t, *pShare_t;

void* child_thread(void* share) {
  pShare_t p = (pShare_t)share;
  // 子线程加20000000
  for (int i = 0; i < 20000000; i++) {
    pthread_mutex_lock(&p->mutex);
    p->count++;
    pthread_mutex_unlock(&p->mutex);
  }
  pthread_exit(NULL);
}

int main(int argc, char const* argv[]) {
  // share变量初始化
  Share_t share;
  memset(&share, 0, sizeof(Share_t));
  // 锁初始化
  pthread_mutex_init(&share.mutex, NULL);
  // 创建子进程
  pthread_t child;
  int ret = pthread_create(&child, NULL, child_thread, &share);
  THREAD_ERR_CHECK(ret, "pthread_create");
  // 主线程加20000000
  for (int i = 0; i < 20000000; i++) {
    pthread_mutex_lock(&share.mutex);
    share.count++;
    pthread_mutex_unlock(&share.mutex);
  }
  // 等待子线程结束
  pthread_join(child, NULL);
  // 销毁锁
  pthread_mutex_destroy(&share.mutex);
  // 打印结果
  printf("count equals to %d\n", share.count);
  return 0;
}
