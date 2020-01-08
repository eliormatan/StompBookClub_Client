
#include "../include/ReadFromSocketTask.h"

ReadFromSocketTask::ReadFromSocketTask(mutex &mutex, ConnectionHandler &connectionHandler,StompMsgEncoderDecoder _encDec) : _mutex(mutex),
                                                                                             _connectionHandler(
                                                                                                     connectionHandler),
                                                                                             terminated(false),
                                                                                             encDec(_encDec){}

void ReadFromSocketTask::run() {  //todo
    while (!terminated) {
        std::string answer;
        if (!_connectionHandler.getLine(answer)) {
            std::cout << "Disconnected. Exiting...\n" << std::endl;
            break;
        }
        string decodedAns = encDec.decode(answer);
        if(decodedAns!=""){
            _connectionHandler.sendLine(decodedAns);
        }
//        std::cout << answer << std::endl;
//        if (answer == "bye") {
//            std::cout << "Exiting...\n" << std::endl;
//            break;
//        }
    }
}
