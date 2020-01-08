//
// Created by tamirsku@wincs.cs.bgu.ac.il on 07/01/2020.
//

#include "../include/SplitThings.h"
 void SplitThings::splitWords(string line,vector<string>& words) {
    string word;
    for(unsigned int i=0;i<line.size();i++){
        if(line[i] == ' '){
            words.push_back(word);
            word = "";
        }
        else{
            word += line[i];
        }
    }
    words.push_back(word);
}

 void SplitThings::split_string(const string& str,vector<string> & strings) { //TODO CHECK STRINGS
    string::size_type pos = 0;
    string::size_type prev = 0;
    while ((pos = str.find('\n', prev)) != string::npos) {
        strings.push_back(str.substr(prev, pos - prev));
        prev = pos + 1;
    }
    // To get the last substring (or only, if delimiter is not found)
    strings.push_back(str.substr(prev));
}