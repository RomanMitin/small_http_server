#include <mutex>

#include "storage.hpp"

void storage::AppendKeyValueStorageComponent(userver::components::ComponentList& component_list) {
  component_list.Append<KeyValueStorage>();
}

void storage::KeyValueStorage::insert(const std::string& key,
                             const std::string& element) {
  std::unique_lock lock(mutex_);
  storage_[key] = element;
}

std::optional<std::string> storage::KeyValueStorage::get(const std::string& key) const {
  std::shared_lock lock(mutex_);

  auto it = storage_.find(key);
  if (it == storage_.end()) {
    return {};
  }

  return it->second;
}