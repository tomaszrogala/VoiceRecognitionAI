//
// Created by Dawid Walenciak on 13/10/2020.
//

#include "RestUtils.h"

#include <Poco/UUIDGenerator.h>

namespace Rest {

std::string RestUtils::generateRequestId() {
    return Poco::UUIDGenerator().createOne().toString();
}

}
