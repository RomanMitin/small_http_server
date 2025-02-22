#include "http_handlers.hpp"

#include <fmt/format.h>

#include <userver/components/component_context.hpp>
#include <userver/server/handlers/http_handler_base.hpp>

#include "request_handler.hpp"

namespace small_http_server {

namespace {

using namespace userver::v2_8_rc::server::http;

class HttpHandlerGet final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-get";

  HttpHandlerGet(const userver::components::ComponentConfig& config,
                 const userver::components::ComponentContext& component_context)
      : HttpHandlerBase(config, component_context),
        _handler(component_context.FindComponent<RequestHandler>()) {}

  using HttpHandlerBase::HttpHandlerBase;

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const override {
    assert(request.GetMethod() == HttpMethod::kGet);

    return _handler.handle_request(request_type::get, request.GetArg("key"));
  }

  RequestHandler& _handler;
};

class HttpHandlerPost final
    : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-post";

  HttpHandlerPost(
      const userver::components::ComponentConfig& config,
      const userver::components::ComponentContext& component_context)
      : HttpHandlerBase(config, component_context),
        _handler(component_context.FindComponent<RequestHandler>()) {}

  using HttpHandlerBase::HttpHandlerBase;

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const override {
    assert(request.GetMethod() == HttpMethod::kPost);

    return _handler.handle_request(request_type::insert, request.GetArg("key"),
                                   request.GetArg("value"));
  }

  RequestHandler& _handler;
};

}  // namespace

void AppendHttpHandler(userver::components::ComponentList& component_list) {
  component_list.Append<HttpHandlerGet>();
  component_list.Append<HttpHandlerPost>();
}

}  // namespace small_http_server
