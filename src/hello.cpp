#include "hello.hpp"

#include <fmt/format.h>

#include <userver/server/handlers/http_handler_base.hpp>

#include "request_handler.hpp"

namespace small_http_server {

namespace {

using namespace userver::v2_8_rc::server::http;

class HttpHandler final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-hello";

  using HttpHandlerBase::HttpHandlerBase;

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const override {
    switch (request.GetMethod()) {
      case HttpMethod::kGet:
        return _handler->handle_request(request_type::get,
                                        request.GetArg("key"));
      case HttpMethod::kPost:
        return _handler->handle_request(request_type::insert,
                                        request.GetArg("key"),
                                        request.GetArg("value"));
    }
    return "Unsupported HTTP method\n";
  }

  std::shared_ptr<RequestHandler> _handler = std::make_shared<RequestHandler>();
};

}  // namespace

void AppendHttpHandler(userver::components::ComponentList& component_list) {
  component_list.Append<HttpHandler>();
}

}  // namespace small_http_server
