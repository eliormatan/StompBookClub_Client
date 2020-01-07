//
// Created by tamirsku@wincs.cs.bgu.ac.il on 07/01/2020.
//
#include <stdlib.h>
#include <iostream>
#include "../include/connectionHandler.h"
#include <thread>
#include <mutex>
using namespace std;
int main (int argc, char *argv[]) {
    bool loggedIN = false;
    while(!loggedIN){
        string action,subAction;
        std::getline(std::cin, action);
        size_t space_pos = action.find(" "); //Find the first Space
        if (space_pos != std::string::npos) {
            subAction = action.substr(0, space_pos); //String before space
            action = action.substr(space_pos + 1); //String after space
        }
        if(subAction=="login"){
            loggedIN = true;
            int seperate=words[1].find(':');
            string host=words[1].substr(0,seperate);
            string port=words[1].substr(seperate+1,words[1].length()-1);
            string username=words[2];
            string password=words[3];
            stomp="CONNECT"+string("\n")+
                  "accept-version:1.2"+string("\n")+
                  "host:stomp.cs.bgu.ac.il"+string("\n")+
                  "login:"+username+string("\n")+
                  "passcode:"+password+string("\n")+"\0";

        }

    }
    ConnectionHandler connectionHandler(host, port);
    if (!connectionHandler.connect()) {
        std::cerr << "Cannot connect to " << host << ":" << port << std::endl;
        return 1;
    }
    mutex sharedMutex;
    KeyboardTask keyboardTask(sharedMutex,connectionHandler);
    ReadFromSocketTask readFromSocketTask(sharedMutex,connectionHandler);
    thread t1(&KeyboardTask::run(),&keyboardTask);    //todo
    thread t2(&ReadFromSocketTask::run(),&readFromSocketTask);    //todo
    t1.join();
    t2.join();
    return 0;
}
