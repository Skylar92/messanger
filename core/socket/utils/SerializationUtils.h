//
// Created by natri on 7/23/2021.
//

#ifndef MESSENGER_SERIALIZATIONUTILS_H
#define MESSENGER_SERIALIZATIONUTILS_H

#include <sstream>
#include <iostream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>


template<typename T, typename = std::enable_if<std::is_base_of<boost::serialization::access, T>::value>>
static basic_string<char> serializeObject(T t) {
    std::ostringstream oss;
    boost::archive::text_oarchive oa(oss);
    oa << t;
    return oss.str();
}

template<typename T, typename = std::enable_if<std::is_base_of<boost::serialization::access, T>::value>>
static T deserializeObject(const basic_string<char> &serializedObj) {
    T cloned;
    std::istringstream iss(serializedObj);
    {
        boost::archive::text_iarchive ia(iss);
        ia >> cloned;
    }
    return cloned;
}

#endif //MESSENGER_SERIALIZATIONUTILS_H
