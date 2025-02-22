#pragma once

#include <fmt/format.h>
#include "storage.hpp"

enum class request_type { insert, get };

class RequestHandler {
  Storage storage;

 public:
  std::string handle_request(request_type type, const std::string& key,
                             const std::string& value = {}) {
    if (key.empty()) {
      return "Key is not set!\n";
    }

    switch (type) {
      case request_type::insert:
        if (value.empty()) {
          return "Value is not set!\n";
        }
        storage.insert_element(key, value);
        return "New value successfully inserted\n";
        break;
      case request_type::get:
        auto res = storage.get(key);
        if (res.has_value()) {
          return "Value = " + res.value() + "\n";
        } else {
          return "No data for key = " + key + "\n";
        }
    }
  }
};