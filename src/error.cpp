//
// Created by Riley Quinn on 8/29/20.
//

#include "requests/error.hpp"
#include <magic_enum.hpp>


std::string requests::error_code_str(requests::error_code ec) {
    return std::string{magic_enum::enum_name(ec)};
}
