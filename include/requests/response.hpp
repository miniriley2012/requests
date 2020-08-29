//
// Created by Riley Quinn on 8/26/20.
//

#ifndef REQUESTS_REQUESTS_RESPONSE_HPP
#define REQUESTS_REQUESTS_RESPONSE_HPP


#include <unordered_map>
#include <vector>
#include <string>

namespace requests {
    struct Response {
        using header_type = std::unordered_map<std::string, std::vector<std::string>>;

        std::string version;
        unsigned int status;
        header_type headers;
        std::string body;
    };
}


#endif //REQUESTS_REQUESTS_RESPONSE_HPP
