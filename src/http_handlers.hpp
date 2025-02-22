#pragma once

#include <string>
#include <string_view>

#include <userver/components/component_list.hpp>

namespace small_http_server {

void AppendHttpHandler(userver::components::ComponentList& component_list);

}  // namespace small_http_server
