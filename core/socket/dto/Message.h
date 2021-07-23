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
    std::string text;

    Message(string text = "") : text(move(text)) {}

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int /*version*/) {
        ar & text;
    }
};

#endif //MESSENGER_MESSAGE_H
