#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

void printRightAligned(char* message) {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    int i = strlen(message)-1;
    message[i] = 0;
    int padding = w.ws_col - i; // 计算右对齐所需的空格数量
    if (padding < 0) padding = 0;

    printf("\033[A\033[2K"); // 先上移光标一行，然后清除该行
    printf("%*s%s\n", padding, "", message); // 输出右对齐的消息
}


int main() {
    // 模拟接收到的客户端消息
    const char* clientMessage = "Hello from the client!";
    printFromClient(clientMessage);

    // 模拟发送的消息
    char buffer[1000] ={0};
    read(STDIN_FILENO,buffer,sizeof(buffer));
    printRightAligned(buffer);

    return 0;
}
