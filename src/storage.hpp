#pragma once
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <userver/engine/shared_mutex.hpp>

class Storage {
  mutable userver::engine::SharedMutex mtx;
  std::unordered_map<std::string, std::string> _data;

 public:
  void insert_element(const std::string& key, const std::string& element);
  std::optional<std::string> get(const std::string& key) const;
};
