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

// This is a macro so this value can be changed at compile time.
#define TEST_URL "https://httpbin.org/status/200"

int main() {
    requests::InitRAII init;

    Request<Method::GET> req{TEST_URL};

    auto begin = std::chrono::high_resolution_clock::now();
    Response resp = req.perform();
    auto end = std::chrono::high_resolution_clock::now();

    fmt::print("Finished GET request to {} in {}ms\n", TEST_URL, duration_cast<milliseconds>(end - begin).count());
    fmt::print("Status: {}\nHeaders:\n{}\nBody:\n{}\n", resp.status, fmt::join(resp.headers, "\n"), resp.body);
}