//
// Created by tamirsku@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT2_REQUESTS_H
#define BOOST_ECHO_CLIENT2_REQUESTS_H

#include <string>

using namespace std;
class Requests {
private:
    string genre;
    string bookName;
public:
    Requests(string _genre,string _bookName);
    ~Requests();


    const string &getGenre() const;

    const string &getBookName() const;
};


#endif //BOOST_ECHO_CLIENT2_REQUESTS_H
