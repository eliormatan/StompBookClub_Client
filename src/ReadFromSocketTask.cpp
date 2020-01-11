
#include "../include/ReadFromSocketTask.h"

ReadFromSocketTask::ReadFromSocketTask(ConnectionHandler &connectionHandler,
                                       StompMsgEncoderDecoder _encDec) :
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
                _connectionHandler.sendLine(decodedAns);
            }
            else terminated=true;
        }
    }
}
