#include <iostream>
#include <thread>
#include <string>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

#define PORT 8080
#define BUFFER_SIZE 1024

void receive_messages(int socket_fd) {
    char buffer[BUFFER_SIZE];
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(socket_fd, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) break;
        std::cout << buffer;
    }
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        std::cerr << "Socket creation failed!" << std::endl;
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost

    if (connect(sock, (sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        std::cerr << "Connection to server failed!" << std::endl;
        return 1;
    }

    std::cout << "Connected to server." << std::endl;

    // Start a thread to receive messages from the server
    std::thread recv_thread(receive_messages, sock);

    std::string input;
    while (true) {
        std::getline(std::cin, input);
        if (input == "/exit") break;
        send(sock, input.c_str(), input.size(), 0);
    }

    close(sock);
    recv_thread.join();  // Wait for the receive thread to finish
    return 0;
}
