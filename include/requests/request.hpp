//
// Created by Riley Quinn on 8/26/20.
//

#ifndef REQUESTS_REQUESTS_REQUEST_HPP
#define REQUESTS_REQUESTS_REQUEST_HPP


#include "error.hpp"
#include "response.hpp"
#include "method.hpp"
#include <string_view>
#include <experimental/propagate_const>

namespace requests {
    class CURLHandle;

    template<Method>
    class Request;

    template<>
    class Request<Method::GET> {
    public:
        explicit Request(std::string_view url);

        ~Request();

        Response perform();
    private:
        Response response;
        std::experimental::propagate_const<std::unique_ptr<CURLHandle>> handle;
    };
}


#endif //REQUESTS_REQUESTS_REQUEST_HPP
