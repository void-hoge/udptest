#include <iostream>
#include <string>
#include <vector>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
	const int port = 4000;
	const std::string addr = "0.0.0.0";
	struct sockaddr_in clientaddr;
	unsigned int addrlen = sizeof(clientaddr);
	auto sockid = socket(AF_INET, SOCK_DGRAM, 0);
	if (sockid < 0) {
		std::cerr << "Failed to create a socket." << std::endl;
		return 1;
	}
	clientaddr.sin_family = AF_INET;
	if (inet_pton(AF_INET, addr.c_str(), &(clientaddr.sin_addr)) != 1) {
		std::cerr << "Invalid address." << std::endl;
		return 1;
	}
	clientaddr.sin_port = htons(port);
	if (bind(sockid, (struct sockaddr*)&clientaddr, sizeof(clientaddr)) != 0) {
		std::cerr << "Invalid address." << std::endl;
		return 1;
	}
	std::vector<char> buff(1000, 0);
	while (true) {
		auto len = recvfrom(sockid, buff.data(), 1000, 0,
							(struct sockaddr*)&clientaddr, &addrlen);
		if (len < 0) {
			std::cerr << "Failed to receive the data." << std::endl;
			return 1;
		}
		std::cout << "received: \"" << std::string(buff.data()) << "\""<< std::endl;
	}
	return 0;
}
