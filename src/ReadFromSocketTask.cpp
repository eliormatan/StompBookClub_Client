
#include "../include/ReadFromSocketTask.h"

ReadFromSocketTask::ReadFromSocketTask(mutex &mutex, ConnectionHandler &connectionHandler,
                                       StompMsgEncoderDecoder _encDec) : _mutex(mutex),
                                                                         _connectionHandler(
                                                                                 connectionHandler),
                                                                         terminated(false),
                                                                         encDec(_encDec) {}

void ReadFromSocketTask::run() {  //todo
    while (!terminated) {
        std::string answer;
        if (!_connectionHandler.getLine(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        string decodedAns = encDec.decode(answer);
        if (decodedAns != "") {
            if (decodedAns != "letMeOut!") {
                lock_guard<mutex> lock(mutex);
                _connectionHandler.sendLine(decodedAns);
                lock_guard<mutex> unlock(mutex);
            }
            else terminated=true;
        }
    }
}
