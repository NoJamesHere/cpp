#include <arpa/inet.h>
#include <cstring>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  bool running = true;
  sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(12345);
  inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    printf("Connection Failed!!\n");
    return 1;
  }

  while (running) {
    char buffer[1024] = {0};
    ssize_t n = read(sock, buffer, sizeof(buffer) - 1);
    if (n <= 0)
      break;
    buffer[n] = '\0';
    printf("Server says: %s\n", buffer);
  }
  close(sock);
}
