//
// Created by Riley Quinn on 8/29/20.
//

#ifndef REQUESTS_REQUESTS_ERROR_HPP
#define REQUESTS_REQUESTS_ERROR_HPP

#include <string>
#include <system_error>

namespace requests {
     enum class [[maybe_unused]] error_code {
        OK = 0,
        INITIALIZATION_ERROR,
    };

    std::string error_code_str(error_code ec);

    class error_category : std::error_category {
        [[nodiscard]] const char *name() const noexcept override {
            return "requests error";
        }

        [[nodiscard]] std::error_condition default_error_condition(int ev) const noexcept override {
            return {ev, *this};
        }

        [[nodiscard]] bool equivalent(int code, const std::error_condition &condition) const noexcept override {
            return code == condition.value();
        }

        [[nodiscard]] bool equivalent(const std::error_code &code, int condition) const noexcept override {
            return code.value() == condition;
        }

        [[nodiscard]] std::string message(int ev) const override {
            return error_code_str(error_code{ev});
        }
    };

    struct requests_error : std::runtime_error {
        explicit requests_error(error_code ec) : std::runtime_error{error_code_str(ec)} {}
    };
}

template<>
struct ::std::is_error_code_enum<requests::error_code> : std::true_type {
};

#endif //REQUESTS_REQUESTS_ERROR_HPP
