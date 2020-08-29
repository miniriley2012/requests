//
// Created by Riley Quinn on 8/29/20.
//

#include "requests/requests.hpp"
#include <system_error>
#include "curl/curl.h"

namespace requests {
    static bool cleanup_done = true;

    void global_init() {
        if (CURLcode err = curl_global_init(CURL_GLOBAL_NOTHING)) {
            throw std::runtime_error{curl_easy_strerror(err)};
        }
        cleanup_done = false;
    }

    void cleanup() {
        if (!cleanup_done) curl_global_cleanup();
    }
}