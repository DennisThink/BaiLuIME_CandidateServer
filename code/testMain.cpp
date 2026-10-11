#include "CCandidateServer.hpp"
#include "CandidateGeneratorManager.hpp"
#include <iostream>
#include <windows.h>
int testServer(int argc,char* argv[]) {
	CCandidateServer server;
	server.start();
	int x = 0;
	while(true) {
		server.run();
		std::cout << "Input 1 for continue and 0 for stop" << std::endl;
		std::cin >> x;
		if(x == 0) {
			server.stop();
			break;
		}
	}
	return 0;
}

int testCandidateGeneratorManager(int argc,char* argv[]) {
	CCandidateGeneratorManager* manager = CCandidateGeneratorManager::GetInstance();
	std::string userInput;
	int maxCount = 10;
	while(true) {
		std::cout << "Input user input for candidate generation (or 'exit' to quit):" << std::endl;
		std::cin >> userInput;
		if(userInput == "exit") {
			break;
		}
		auto candidates = manager->GenerateCandidates(userInput, maxCount);
		std::cout << "Generated candidates:" << std::endl;
		for(const auto& candidate : candidates) {
			std::cout << candidate << std::endl;
		}
	}
	return 0;
}

int main(int argc,char* argv[]) {
#ifdef _WIN32
	::SetConsoleOutputCP(CP_UTF8);   // 输出用 UTF-8
	::SetConsoleCP(CP_UTF8);         // 输入用 UTF-8
#endif
	if(argc > 1 && std::string(argv[1]) == "server") {
		return testServer(argc, argv);
	} else if(argc > 1 && std::string(argv[1]) == "generator") {
		return testCandidateGeneratorManager(argc, argv);
	} else {
		std::cout << "Usage: " << argv[0] << " [server|generator]" << std::endl;
		return 1;
	}
}