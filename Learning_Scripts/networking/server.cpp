#include <cstring>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
  int port = 12345;
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == 0) {
    printf("Socket failed!\n");
    return 1;
  }
  sockaddr_in address;
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    printf("Bind failed!\n");
    return 1;
  }

  if (listen(server_fd, 3) < 0) {
    printf("Listen failed!\n");
    return 1;
  }
  printf("Server listening on port %d...\n", port);

  int addrlen = sizeof(address);
  int new_socket =
      accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
  if (new_socket < 0) {
    printf("Accept failed\n");
    return 1;
  }

  char message[1024];
  strcpy(message, "Hello from C++ server!!\n");
  send(new_socket, message, strlen(message), 0);
  while (true) {
    printf("Your message?: ");
    if (fgets(message, sizeof(message), stdin) == NULL)
      continue;

    size_t len = strlen(message);
    if (len > 0 && message[len - 1] == '\n')
      message[len - 1] = '\0';

    if (len == 0)
      continue;
    send(new_socket, message, strlen(message), 0);
  }

  close(new_socket);
  close(server_fd);

  return 0;
}
