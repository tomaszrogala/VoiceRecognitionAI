//
// Created by Dawid Walenciak on 23/12/2020.
//

#include <Poco/JSON/Object.h>
#include "ResponseMessage.h"

namespace Rest {

ResponseMessage::ResponseMessage() : httpStatus(), userMessage() {}

ResponseMessage& ResponseMessage::status(Poco::Net::HTTPResponse::HTTPStatus status) {
    httpStatus = status;
    return *this;
}

ResponseMessage& ResponseMessage::message(const std::string& message) {
    userMessage = message;
    return *this;
}

std::string ResponseMessage::build() {
    std::stringstream output;
    Poco::JSON::Object jsonObject;
    jsonObject.set("code", httpStatus);
    jsonObject.set("reason", Poco::Net::HTTPResponse::getReasonForStatus(httpStatus));
    jsonObject.set("message", userMessage);
    jsonObject.stringify(output);
    return output.str();
}

}
