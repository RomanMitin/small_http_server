#pragma once

#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>

#include <userver/engine/shared_mutex.hpp>
#include <userver/components/component_base.hpp>
#include <userver/components/component_list.hpp>

namespace storage {

class KeyValueStorage final : public userver::components::ComponentBase {
 public:

  static constexpr std::string_view kName = "key-value-storage";

  KeyValueStorage(const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : userver::components::ComponentBase(config, context) {

    }

  void insert(const std::string& key, const std::string& element);
  std::optional<std::string> get(const std::string& key) const;

 private:

  mutable userver::engine::SharedMutex mutex_;
  std::unordered_map<std::string, std::string> storage_;
};

void AppendKeyValueStorageComponent(userver::components::ComponentList& component_list);

} // namespace storage


template <>
inline constexpr auto userver::components::kConfigFileMode<storage::KeyValueStorage> = ConfigFileMode::kNotRequired;