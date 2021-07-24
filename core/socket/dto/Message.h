//
// Created by natri on 7/22/2021.
//

#ifndef MESSENGER_MESSAGE_H
#define MESSENGER_MESSAGE_H

#include <string>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;

struct Message {
    string username;
    string text;

    Message(string userName = "", string text = "") : text(move(text)), username(move(userName)) {}

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int /*version*/) {
        ar & text,
        ar & username;
    }
};

#endif //MESSENGER_MESSAGE_H
