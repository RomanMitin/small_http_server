#pragma once

#include <fmt/format.h>
#include "storage.hpp"

#include <userver/components/component_base.hpp>
#include <userver/components/component_list.hpp>

enum class request_type { insert, get };

inline std::string _handle_request_with_storage(request_type type,
                                                Storage& storage,
                                                const std::string& key,
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

class RequestHandler final : public userver::components::ComponentBase {
  Storage storage;

 public:
  static constexpr std::string_view kName = "request-handler";

  using ComponentBase::ComponentBase;

  std::string handle_request(request_type type, const std::string& key,
                             const std::string& value = {}) {
    return _handle_request_with_storage(type, storage, key, value);
  }
};

inline void AppendRequestHandler(
    userver::components::ComponentList& component_list) {
  component_list.Append<RequestHandler>();
}