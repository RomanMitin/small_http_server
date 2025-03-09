#include "request_handler.hpp"

#include <userver/utest/utest.hpp>

UTEST(SayHelloTo, Basic) {
  Storage storage;
  EXPECT_EQ(_handle_request_with_storage(request_type::get, storage, "key1"),
            "No data for key = key1\n");
  EXPECT_EQ(_handle_request_with_storage(request_type::get, storage, "key1",
                                         "Some val"),
            "No data for key = key1\n");
  EXPECT_EQ(_handle_request_with_storage(request_type::get, storage, ""),
            "Key is not set!\n");
  EXPECT_EQ(
      _handle_request_with_storage(request_type::get, storage, "", "Some val"),
      "Key is not set!\n");

  EXPECT_EQ(_handle_request_with_storage(request_type::insert, storage, "key1"),
            "Value is not set!\n");
  EXPECT_EQ(_handle_request_with_storage(request_type::insert, storage, "key1",
                                         "value1"),
            "New value successfully inserted\n");
  EXPECT_EQ(_handle_request_with_storage(request_type::insert, storage, "key1",
                                         "value2"),
            "New value successfully inserted\n");

  EXPECT_EQ(_handle_request_with_storage(request_type::get, storage, "key1"),
            "Value = value2\n");
  EXPECT_EQ(_handle_request_with_storage(request_type::get, storage, "key1"),
            "Value = value2\n");

  EXPECT_EQ(_handle_request_with_storage(request_type::insert, storage, "key2"),
            "Value is not set!\n");
  EXPECT_EQ(_handle_request_with_storage(request_type::insert, storage, "key2",
                                         "value3"),
            "New value successfully inserted\n");

  EXPECT_EQ(_handle_request_with_storage(request_type::get, storage, "key1"),
            "Value = value2\n");
  EXPECT_EQ(_handle_request_with_storage(request_type::get, storage, "key2"),
            "Value = value3\n");
}
