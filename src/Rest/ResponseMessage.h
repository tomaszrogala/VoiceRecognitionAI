//
// Created by Dawid Walenciak on 23/12/2020.
//

#ifndef VOICERECOGNITIONAI_RESPONSEMESSAGE_H
#define VOICERECOGNITIONAI_RESPONSEMESSAGE_H

#include <string>
#include <Poco/Net/HTTPResponse.h>

namespace Rest {

class ResponseMessage {
public:
    ResponseMessage();

    ResponseMessage& status(Poco::Net::HTTPResponse::HTTPStatus status);
    ResponseMessage& message(const std::string& message);

    std::string build();

private:
    Poco::Net::HTTPResponse::HTTPStatus httpStatus;
    std::string userMessage;

};

}

#endif //VOICERECOGNITIONAI_RESPONSEMESSAGE_H
