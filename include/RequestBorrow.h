//
// Created by tamirsku@wincs.cs.bgu.ac.il on 08/01/2020.
//

#ifndef BOOST_ECHO_CLIENT2_REQUESTBORROW_H
#define BOOST_ECHO_CLIENT2_REQUESTBORROW_H

#include <string>

using namespace std;
class RequestBorrow {
private:
    string genre;
    string bookName;
    bool handled;
public:
    RequestBorrow(string _genre, string _bookName);
    ~RequestBorrow();


    const string &getGenre() const;

    const string &getBookName() const;

    bool isHandled() const;

    void setHandled(bool handled);
};


#endif //BOOST_ECHO_CLIENT2_REQUESTBORROW_H
