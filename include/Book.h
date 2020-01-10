//
// Created by tamirsku@wincs.cs.bgu.ac.il on 07/01/2020.
//

#ifndef BOOST_ECHO_CLIENT2_BOOK_H
#define BOOST_ECHO_CLIENT2_BOOK_H

#include <string>

using namespace std;

class Book {
private:
    string name;
    string borrowedFrom;
    bool isMineAtTheMoment;
public:
    Book(string _name,string _borrowedFrom);
    ~Book();
    string getBorrowedFrom();

    void setIsMineAtTheMoment(bool isMineAtTheMoment);

    const string &getName() const;

    bool getIsMineAtTheMoment() const;
};


#endif //BOOST_ECHO_CLIENT2_BOOK_H
