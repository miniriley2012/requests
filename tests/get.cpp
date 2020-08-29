//
// Created by Riley Quinn on 8/29/20.
//

#include <requests/requests.hpp>
#include <requests/request.hpp>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <chrono>

using requests::Request;
using requests::Method;
using requests::Response;
using namespace std::chrono;

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        fmt::print("USAGE: {} <url>", argv[0]);
        return 0;
    }

    const char *url = argv[1];

    requests::InitRAII init;

    Request<Method::GET> req{url};

    auto begin = std::chrono::high_resolution_clock::now();
    Response resp = req.perform();
    auto end = std::chrono::high_resolution_clock::now();

    fmt::print("Finished GET request to {} in {}ms\n", url, duration_cast<milliseconds>(end - begin).count());
    fmt::print("Status: {}\nHeaders:\n{}\nBody:\n{}\n", resp.status, fmt::join(resp.headers, "\n"), resp.body);

    return 0;
}