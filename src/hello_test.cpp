#include "request_handler.hpp"

#include <userver/utest/utest.hpp>

UTEST(SayHelloTo, Basic) {
  RequestHandler handler;
  EXPECT_EQ(handler.handle_request(request_type::get, "key1"),
            "No data for key = key1\n");
  EXPECT_EQ(handler.handle_request(request_type::get, "key1", "Some val"),
            "No data for key = key1\n");
  EXPECT_EQ(handler.handle_request(request_type::get, ""), "Key is not set!\n");
  EXPECT_EQ(handler.handle_request(request_type::get, "", "Some val"),
            "Key is not set!\n");

  EXPECT_EQ(handler.handle_request(request_type::insert, "key1"),
            "Value is not set!\n");
  EXPECT_EQ(handler.handle_request(request_type::insert, "key1", "value1"),
            "New value successfully inserted\n");
  EXPECT_EQ(handler.handle_request(request_type::insert, "key1", "value2"),
            "New value successfully inserted\n");

  EXPECT_EQ(handler.handle_request(request_type::get, "key1"),
            "Value = value2\n");
  EXPECT_EQ(handler.handle_request(request_type::get, "key1"),
            "Value = value2\n");

  EXPECT_EQ(handler.handle_request(request_type::insert, "key2"),
            "Value is not set!\n");
  EXPECT_EQ(handler.handle_request(request_type::insert, "key2", "value3"),
            "New value successfully inserted\n");

  EXPECT_EQ(handler.handle_request(request_type::get, "key1"),
            "Value = value2\n");
  EXPECT_EQ(handler.handle_request(request_type::get, "key2"),
            "Value = value3\n");
}
