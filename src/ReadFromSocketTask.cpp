
#include "../include/ReadFromSocketTask.h"

ReadFromSocketTask::ReadFromSocketTask(mutex &mutex, ConnectionHandler &connectionHandler) : _mutex(mutex),
                                                                                             _connectionHandler(
                                                                                                     connectionHandler),
                                                                                             terminated(false) {}

void ReadFromSocketTask::run() {  //todo
    while (!terminated) {
        std::string answer;
        if (!_connectionHandler.getLine(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        int len = answer.length();
        answer.resize(len - 1);
        std::cout << answer << std::endl;
        if (answer == "bye") {
            std::cout << "Exiting...\n" << std::endl;
            break;
        }
    }
}
