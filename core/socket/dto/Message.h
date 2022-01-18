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
    tm time;
    int tm_sec;
    int tm_min;
    int tm_hour;
    int tm_mday;
    int tm_mon;
    int tm_year;

    Message(string userName = "", string text = "", tm time = tm()) : text(move(text)),
                                                                      username(move(userName)),
                                                                      // TODO Provide struct instead of this shit
                                                                      tm_sec(move(time.tm_sec)),
                                                                      tm_min(move(time.tm_min)),
                                                                      tm_hour(move(time.tm_hour)),
                                                                      tm_mday(move(time.tm_mday)),
                                                                      tm_year(move(time.tm_year)) {}

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int /*version*/) {
        ar & text,
                ar & username,
                ar & tm_sec,
                ar & tm_min,
                ar & tm_hour,
                ar & tm_mday,
                ar & tm_mon,
                ar & tm_year;
    }
};

#endif //MESSENGER_MESSAGE_H
