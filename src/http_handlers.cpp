#include <fmt/format.h>

#include <userver/components/component_context.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/utils/async.hpp>
#include <userver/http/status_code.hpp>

#include "storage.hpp"
#include "http_handlers.hpp"

namespace small_http_server {

using namespace userver::v2_8_rc::server::http;

class HttpHandlerGet final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-get";

  HttpHandlerGet(const userver::components::ComponentConfig& config,
                 const userver::components::ComponentContext& component_context)
      : HttpHandlerBase(config, component_context),
      storage_(component_context.FindComponent<storage::KeyValueStorage>()) {}

  using HttpHandlerBase::HttpHandlerBase;

  std::string HandleRequest(
      userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const override {

      auto& key = request.GetArg("key");
      auto& response = request.GetHttpResponse();

      if (key.empty()) {
        response.SetStatus(userver::server::http::HttpStatus::kBadRequest);
        return fmt::format("Key must be provided\n");
      }

      auto res = storage_.get(key);
      if (!res.has_value()) {
        response.SetStatus(userver::server::http::HttpStatus::kNotFound);
        return fmt::format("Key {} not found\n", key);
      }

      return fmt::format("Value for key {}: {}\n", key, res.value());
  }

  storage::KeyValueStorage& storage_;
};

class HttpHandlerPost final
    : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-post";

  HttpHandlerPost(
      const userver::components::ComponentConfig& config,
      const userver::components::ComponentContext& component_context)
      : HttpHandlerBase(config, component_context),
        storage_(component_context.FindComponent<storage::KeyValueStorage>()) {}

  using HttpHandlerBase::HttpHandlerBase;

  std::string HandleRequest(
      userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const override {
      
      auto& key = request.GetArg("key");
      auto& value = request.GetArg("value");

      auto& response = request.GetHttpResponse();

      if (key.empty()) {
        response.SetStatus(userver::server::http::HttpStatus::kBadRequest);
        return fmt::format("Key must be provided\n");
      }

      if (value.empty()) {
        response.SetStatus(userver::server::http::HttpStatus::kBadRequest);
        return fmt::format("Value must be provided\n");
      }

      storage_.insert(key, value);
      return fmt::format("Stored Key: {} with Value: {}\n", key, value);
  }

  storage::KeyValueStorage& storage_;
};

void AppendHttpHandler(userver::components::ComponentList& component_list) {
  component_list.Append<HttpHandlerGet>()
                .Append<HttpHandlerPost>();
}

}  // namespace small_http_server
