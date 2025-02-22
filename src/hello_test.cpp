#include "hello.hpp"

#include <userver/utest/utest.hpp>

UTEST(SayHelloTo, Basic) {
  EXPECT_EQ(small_http_server::SayHelloTo("Developer"), "Hello, Developer!\n");
  EXPECT_EQ(small_http_server::SayHelloTo({}), "Hello, unknown user!\n");
}
