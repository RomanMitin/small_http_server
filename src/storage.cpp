#include "storage.hpp"
#include <mutex>

void Storage::insert_element(const std::string& key,
                             const std::string& element) {
  std::unique_lock lk(mtx);
  _data[key] = element;
}

std::optional<std::string> Storage::get(const std::string& key) const {
  std::shared_lock lk(mtx);

  auto it = _data.find(key);
  if (it == _data.end()) {
    return {};
  }

  return it->second;
}