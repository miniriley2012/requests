//
// Created by Riley Quinn on 8/29/20.
//

#ifndef REQUESTS_REQUESTS_REQUESTS_HPP
#define REQUESTS_REQUESTS_REQUESTS_HPP

namespace requests {
    void global_init();

    void cleanup();

    struct InitRAII {
        InitRAII() { global_init(); }

        ~InitRAII() { cleanup(); }
    };
}

#endif //REQUESTS_REQUESTS_REQUESTS_HPP
