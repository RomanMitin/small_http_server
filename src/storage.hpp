#pragma once
#include <optional>
#include <shared_mutex>
#include <string>
#include <string_view>
#include <unordered_map>

class Storage {
  mutable std::shared_mutex mtx;
  std::unordered_map<std::string, std::string> _data;

 public:
  void insert_element(const std::string& key, const std::string& element);
  std::optional<std::string> get(const std::string& key) const;
};
