//
// Created by Riley Quinn on 8/26/20.
//

#include "requests/request.hpp"

#include <curl/curl.h>

namespace requests {
    class CURLHandle {
    public:
        CURLHandle() {
            handle = curl_easy_init();
            if (!handle) {
                throw requests::requests_error{requests::error_code::INITIALIZATION_ERROR};
            }
        }

        ~CURLHandle() {
            curl_easy_cleanup(handle);
        }

        CURL *operator*() {
            return handle;
        }

        operator CURL *() {
            return handle;
        }

    private:
        CURL *handle;
    };

    size_t process_header(char *ptr, size_t size, size_t nitems, Response *resp) {
        std::string_view s{ptr, nitems};
        auto it = s.begin();
        auto next = [&it, &s](char c = ' ') -> const char * {
            return it = std::find(it, s.end(), c);
        };

        auto trim = [](std::string_view s) {
            return s.substr(s.find_first_not_of(' '), s.find_last_not_of(" \r\n"));
        };

        if (s == "\r\n") {
            return size * nitems;
        }

        if (s.starts_with("HTTP/")) {
            resp->headers.clear();
            resp->version = {std::string{it, next()}};
            resp->status = int(std::strtol(it, nullptr, 10));
            return size * nitems;
        }

        auto sep = s.find_first_of(':') + 1;
        std::string_view name = trim(s.substr(0, sep));
        std::string_view value = trim(s.substr(sep));
        resp->headers[std::string{name}].emplace_back(value);

        return size * nitems;
    }

    size_t process_body(char *buffer, size_t size, size_t nitems, std::string *str) {
        str->reserve(str->size() + size * nitems);
        str->append(buffer);
        str->resize(str->size() + size * nitems);
        str->erase(str->find_first_of('\0'));
        return size * nitems;
    }

    Request<Method::GET>::Request(std::string_view url) {
        handle = std::make_unique<CURLHandle>();
        curl_easy_setopt(*handle, CURLOPT_URL, url);
        curl_easy_setopt(*handle, CURLOPT_HEADERFUNCTION, process_header);
        curl_easy_setopt(*handle, CURLOPT_HEADERDATA, &response);
        curl_easy_setopt(*handle, CURLOPT_WRITEFUNCTION, process_body);
        curl_easy_setopt(*handle, CURLOPT_WRITEDATA, &response.body);
    }

    Request<Method::GET>::~Request() = default;

    Response Request<Method::GET>::perform() {
        curl_easy_perform(*handle);
        return response;
    }
}
