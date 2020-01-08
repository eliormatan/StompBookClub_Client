//
// Created by tamirsku@wincs.cs.bgu.ac.il on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT2_SPLITTHINGS_H
#define BOOST_ECHO_CLIENT2_SPLITTHINGS_H

#include <string>
#include <vector>
using namespace std;


class SplitThings {
public:
    static void split_string(const string& str,vector<string> & strings);
    static void splitWords(string line,vector<string> & words);
};


#endif //BOOST_ECHO_CLIENT2_SPLITTHINGS_H
