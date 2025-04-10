#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <mutex>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>

#define PORT 8080
#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024

std::vector<int> client_sockets(MAX_CLIENTS);
std::mutex mtx;

void broadcast_message(const std::string &message, int sender_socket) {
    std::lock_guard<std::mutex> lock(mtx);
    for (int client_socket : client_sockets) {
        if (client_socket != 0 && client_socket != sender_socket) {
            send(client_socket, message.c_str(), message.size(), 0);
        }
    }
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    while (true) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0) break;
        std::cout << "Received: " << buffer<<std::flush;
        broadcast_message(buffer, client_socket);
    }

    close(client_socket);
    std::lock_guard<std::mutex> lock(mtx);
    for (int &socket : client_sockets) {
        if (socket == client_socket) {
            socket = 0;
            break;
        }
    }
}

int main() {
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (sockaddr *)&server_addr, sizeof(server_addr));
    listen(server_socket, MAX_CLIENTS);
    std::cout << "Server listening on port " << PORT << "..." << std::endl;

    while (true) {
        int client_socket = accept(server_socket, nullptr, nullptr);
        std::lock_guard<std::mutex> lock(mtx);
        for (int &socket : client_sockets) {
            if (socket == 0) {
                socket = client_socket;
                std::thread(handle_client, client_socket).detach();
                break;
            }
        }
    }
    return 0;
}
