#include <gtest/gtest.h>

#include <chrono>
#include <limits>

#include <formats/bson.hpp>

namespace fb = formats::bson;
using TimePoint = std::chrono::system_clock::time_point;

TEST(BsonExtraction, Missing) {
  auto test_elem = [](const fb::Value& elem) {
    EXPECT_TRUE(elem.IsMissing());
    EXPECT_FALSE(elem.IsArray());
    EXPECT_FALSE(elem.IsDocument());
    EXPECT_FALSE(elem.IsNull());
    EXPECT_FALSE(elem.IsBool());
    EXPECT_FALSE(elem.IsInt32());
    EXPECT_FALSE(elem.IsInt64());
    EXPECT_FALSE(elem.IsDouble());
    EXPECT_FALSE(elem.IsString());
    EXPECT_FALSE(elem.IsDateTime());
    EXPECT_FALSE(elem.IsOid());
    EXPECT_FALSE(elem.IsBinary());
    EXPECT_FALSE(elem.IsDecimal128());
    EXPECT_FALSE(elem.IsMinKey());
    EXPECT_FALSE(elem.IsMaxKey());
    EXPECT_FALSE(elem.IsObject());

    EXPECT_THROW(elem.As<bool>(), fb::MemberMissingException);
    EXPECT_THROW(elem.As<int32_t>(), fb::MemberMissingException);
    EXPECT_THROW(elem.As<int64_t>(), fb::MemberMissingException);
    EXPECT_THROW(elem.As<size_t>(), fb::MemberMissingException);
    EXPECT_THROW(elem.As<double>(), fb::MemberMissingException);
    EXPECT_THROW(elem.As<std::string>(), fb::MemberMissingException);
    EXPECT_THROW(elem.As<TimePoint>(), fb::MemberMissingException);
    EXPECT_THROW(elem.As<fb::Oid>(), fb::MemberMissingException);
    EXPECT_THROW(elem.As<fb::Binary>(), fb::MemberMissingException);
    EXPECT_THROW(elem.As<fb::Decimal128>(), fb::MemberMissingException);
    EXPECT_THROW(elem.As<fb::Document>(), fb::MemberMissingException);
  };

  const auto doc = fb::MakeDoc("a", fb::MakeArray(), "b", fb::MakeDoc());
  EXPECT_THROW(doc["a"][0], fb::OutOfBoundsException);
  EXPECT_THROW(doc["a"]["b"], fb::TypeMismatchException);
  EXPECT_THROW(doc["b"][0], fb::TypeMismatchException);
  test_elem(doc["b"]["c"]);
  test_elem(doc["d"]);
}

TEST(BsonExtraction, Null) {
  auto test_elem = [](const fb::Value& elem) {
    EXPECT_FALSE(elem.IsMissing());
    EXPECT_FALSE(elem.IsArray());
    EXPECT_FALSE(elem.IsDocument());
    EXPECT_TRUE(elem.IsNull());
    EXPECT_FALSE(elem.IsBool());
    EXPECT_FALSE(elem.IsInt32());
    EXPECT_FALSE(elem.IsInt64());
    EXPECT_FALSE(elem.IsDouble());
    EXPECT_FALSE(elem.IsString());
    EXPECT_FALSE(elem.IsDateTime());
    EXPECT_FALSE(elem.IsOid());
    EXPECT_FALSE(elem.IsBinary());
    EXPECT_FALSE(elem.IsDecimal128());
    EXPECT_FALSE(elem.IsMinKey());
    EXPECT_FALSE(elem.IsMaxKey());
    EXPECT_FALSE(elem.IsObject());

    EXPECT_THROW(elem.As<bool>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<int32_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<int64_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<size_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<double>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<std::string>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<TimePoint>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Oid>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Binary>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Decimal128>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Document>(), fb::TypeMismatchException);
  };

  const auto doc = fb::MakeDoc("a", fb::MakeArray(nullptr), "e", nullptr);
  test_elem(doc["a"][0]);
  test_elem(doc["e"]);
}

TEST(BsonExtraction, Bool) {
  auto test_elem = [](const fb::Value& elem, bool value) {
    EXPECT_FALSE(elem.IsMissing());
    EXPECT_FALSE(elem.IsArray());
    EXPECT_FALSE(elem.IsDocument());
    EXPECT_FALSE(elem.IsNull());
    EXPECT_TRUE(elem.IsBool());
    EXPECT_FALSE(elem.IsInt32());
    EXPECT_FALSE(elem.IsInt64());
    EXPECT_FALSE(elem.IsDouble());
    EXPECT_FALSE(elem.IsString());
    EXPECT_FALSE(elem.IsDateTime());
    EXPECT_FALSE(elem.IsOid());
    EXPECT_FALSE(elem.IsBinary());
    EXPECT_FALSE(elem.IsDecimal128());
    EXPECT_FALSE(elem.IsMinKey());
    EXPECT_FALSE(elem.IsMaxKey());
    EXPECT_FALSE(elem.IsObject());

    EXPECT_EQ(value, elem.As<bool>());
    EXPECT_THROW(elem.As<int32_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<int64_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<size_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<double>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<std::string>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<TimePoint>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Oid>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Binary>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Decimal128>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Document>(), fb::TypeMismatchException);
  };

  const auto doc =
      fb::MakeDoc("a", fb::MakeArray(false, true), "ef", false, "et", true);
  test_elem(doc["a"][0], false);
  test_elem(doc["a"][1], true);
  test_elem(doc["ef"], false);
  test_elem(doc["et"], true);
}

TEST(BsonExtraction, Double) {
  auto test_elem = [](const fb::Value& elem, double value) {
    EXPECT_FALSE(elem.IsMissing());
    EXPECT_FALSE(elem.IsArray());
    EXPECT_FALSE(elem.IsDocument());
    EXPECT_FALSE(elem.IsNull());
    EXPECT_FALSE(elem.IsBool());
    EXPECT_FALSE(elem.IsInt32());
    EXPECT_FALSE(elem.IsInt64());
    EXPECT_TRUE(elem.IsDouble());
    EXPECT_FALSE(elem.IsString());
    EXPECT_FALSE(elem.IsDateTime());
    EXPECT_FALSE(elem.IsOid());
    EXPECT_FALSE(elem.IsBinary());
    EXPECT_FALSE(elem.IsDecimal128());
    EXPECT_FALSE(elem.IsMinKey());
    EXPECT_FALSE(elem.IsMaxKey());
    EXPECT_FALSE(elem.IsObject());

    EXPECT_THROW(elem.As<bool>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<int32_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<int64_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<size_t>(), fb::TypeMismatchException);
    EXPECT_DOUBLE_EQ(value, elem.As<double>());
    EXPECT_THROW(elem.As<std::string>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<TimePoint>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Oid>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Binary>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Decimal128>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Document>(), fb::TypeMismatchException);
  };

  const auto doc = fb::MakeDoc("a", fb::MakeArray(0.0, 0.123, -0.123), "ez",
                               0.0, "ep", 3.21, "en", -3.21);
  test_elem(doc["a"][0], 0.0);
  test_elem(doc["a"][1], 0.123);
  test_elem(doc["a"][2], -0.123);
  test_elem(doc["ez"], 0.0);
  test_elem(doc["ep"], 3.21);
  test_elem(doc["en"], -3.21);
}

TEST(BsonExtraction, Int32) {
  auto test_elem = [](const fb::Value& elem, int32_t value) {
    EXPECT_FALSE(elem.IsMissing());
    EXPECT_FALSE(elem.IsArray());
    EXPECT_FALSE(elem.IsDocument());
    EXPECT_FALSE(elem.IsNull());
    EXPECT_FALSE(elem.IsBool());
    EXPECT_TRUE(elem.IsInt32());
    EXPECT_TRUE(elem.IsInt64());
    EXPECT_TRUE(elem.IsDouble());
    EXPECT_FALSE(elem.IsString());
    EXPECT_FALSE(elem.IsDateTime());
    EXPECT_FALSE(elem.IsOid());
    EXPECT_FALSE(elem.IsBinary());
    EXPECT_FALSE(elem.IsDecimal128());
    EXPECT_FALSE(elem.IsMinKey());
    EXPECT_FALSE(elem.IsMaxKey());
    EXPECT_FALSE(elem.IsObject());

    EXPECT_THROW(elem.As<bool>(), fb::TypeMismatchException);
    EXPECT_EQ(value, elem.As<int32_t>());
    EXPECT_EQ(value, elem.As<int64_t>());
    if (value >= 0) {
      EXPECT_EQ(value, elem.As<size_t>());
    } else {
      EXPECT_ANY_THROW(elem.As<size_t>());
    }
    EXPECT_DOUBLE_EQ(value, elem.As<double>());
    EXPECT_THROW(elem.As<std::string>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<TimePoint>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Oid>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Binary>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Decimal128>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Document>(), fb::TypeMismatchException);
  };

  const auto doc =
      fb::MakeDoc("a", fb::MakeArray(int32_t{0}, int32_t{123}, int32_t{-123}),
                  "ez", int32_t{0}, "ep", int32_t{321}, "en", int32_t{-321});
  test_elem(doc["a"][0], 0);
  test_elem(doc["a"][1], 123);
  test_elem(doc["a"][2], -123);
  test_elem(doc["ez"], 0);
  test_elem(doc["ep"], 321);
  test_elem(doc["en"], -321);
}

TEST(BsonExtraction, Int64) {
  auto test_elem = [](const fb::Value& elem, int64_t value) {
    EXPECT_FALSE(elem.IsMissing());
    EXPECT_FALSE(elem.IsArray());
    EXPECT_FALSE(elem.IsDocument());
    EXPECT_FALSE(elem.IsNull());
    EXPECT_FALSE(elem.IsBool());
    EXPECT_FALSE(elem.IsInt32());
    EXPECT_TRUE(elem.IsInt64());
    EXPECT_TRUE(elem.IsDouble());
    EXPECT_FALSE(elem.IsString());
    EXPECT_FALSE(elem.IsDateTime());
    EXPECT_FALSE(elem.IsOid());
    EXPECT_FALSE(elem.IsBinary());
    EXPECT_FALSE(elem.IsDecimal128());
    EXPECT_FALSE(elem.IsMinKey());
    EXPECT_FALSE(elem.IsMaxKey());
    EXPECT_FALSE(elem.IsObject());

    EXPECT_THROW(elem.As<bool>(), fb::TypeMismatchException);
    if (value < std::numeric_limits<int32_t>::min() ||
        value > std::numeric_limits<int32_t>::max()) {
      EXPECT_ANY_THROW(elem.As<int32_t>());
    } else {
      EXPECT_EQ(value, elem.As<int32_t>());
    }
    EXPECT_EQ(value, elem.As<int64_t>());
    if (value >= 0) {
      EXPECT_EQ(value, elem.As<size_t>());
    } else {
      EXPECT_ANY_THROW(elem.As<size_t>());
    }
    EXPECT_DOUBLE_EQ(value, elem.As<double>());
    EXPECT_THROW(elem.As<std::string>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<TimePoint>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Oid>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Binary>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Decimal128>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Document>(), fb::TypeMismatchException);
  };

  const auto doc =
      fb::MakeDoc("a", fb::MakeArray(int64_t{0}, int64_t{123}, int64_t{-123}),
                  "ez", int64_t{0}, "ep", int64_t{321}, "en", int64_t{-321},
                  "large", int64_t{1} << 42, "small", -(int64_t{1} << 42));
  test_elem(doc["a"][0], 0);
  test_elem(doc["a"][1], 123);
  test_elem(doc["a"][2], -123);
  test_elem(doc["ez"], 0);
  test_elem(doc["ep"], 321);
  test_elem(doc["en"], -321);
  test_elem(doc["large"], 1L << 42);
  test_elem(doc["small"], -(1L << 42));
}

TEST(BsonExtraction, Utf8) {
  auto test_elem = [](const fb::Value& elem, const std::string& value) {
    EXPECT_FALSE(elem.IsMissing());
    EXPECT_FALSE(elem.IsArray());
    EXPECT_FALSE(elem.IsDocument());
    EXPECT_FALSE(elem.IsNull());
    EXPECT_FALSE(elem.IsBool());
    EXPECT_FALSE(elem.IsInt32());
    EXPECT_FALSE(elem.IsInt64());
    EXPECT_FALSE(elem.IsDouble());
    EXPECT_TRUE(elem.IsString());
    EXPECT_FALSE(elem.IsDateTime());
    EXPECT_FALSE(elem.IsOid());
    EXPECT_FALSE(elem.IsBinary());
    EXPECT_FALSE(elem.IsDecimal128());
    EXPECT_FALSE(elem.IsMinKey());
    EXPECT_FALSE(elem.IsMaxKey());
    EXPECT_FALSE(elem.IsObject());

    EXPECT_THROW(elem.As<bool>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<int32_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<int64_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<size_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<double>(), fb::TypeMismatchException);
    EXPECT_EQ(value, elem.As<std::string>());
    EXPECT_THROW(elem.As<TimePoint>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Oid>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Binary>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Decimal128>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Document>(), fb::TypeMismatchException);
  };

  const auto doc =
      fb::MakeDoc("a", fb::MakeArray("", "test"), "ee", "", "e", "string");
  test_elem(doc["a"][0], {});
  test_elem(doc["a"][1], "test");
  test_elem(doc["ee"], {});
  test_elem(doc["e"], "string");
}

TEST(BsonExtraction, Binary) {
  auto test_elem = [](const fb::Value& elem, const std::string& value) {
    EXPECT_FALSE(elem.IsMissing());
    EXPECT_FALSE(elem.IsArray());
    EXPECT_FALSE(elem.IsDocument());
    EXPECT_FALSE(elem.IsNull());
    EXPECT_FALSE(elem.IsBool());
    EXPECT_FALSE(elem.IsInt32());
    EXPECT_FALSE(elem.IsInt64());
    EXPECT_FALSE(elem.IsDouble());
    EXPECT_FALSE(elem.IsString());
    EXPECT_FALSE(elem.IsDateTime());
    EXPECT_FALSE(elem.IsOid());
    EXPECT_TRUE(elem.IsBinary());
    EXPECT_FALSE(elem.IsDecimal128());
    EXPECT_FALSE(elem.IsMinKey());
    EXPECT_FALSE(elem.IsMaxKey());
    EXPECT_FALSE(elem.IsObject());

    EXPECT_THROW(elem.As<bool>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<int32_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<int64_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<size_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<double>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<std::string>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<TimePoint>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Oid>(), fb::TypeMismatchException);
    EXPECT_EQ(fb::Binary(value), elem.As<fb::Binary>());
    EXPECT_THROW(elem.As<fb::Decimal128>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Document>(), fb::TypeMismatchException);
  };

  const auto doc =
      fb::MakeDoc("a", fb::MakeArray(fb::Binary(""), fb::Binary("test")), "ee",
                  fb::Binary(""), "e", fb::Binary("\377\377"));
  test_elem(doc["a"][0], {});
  test_elem(doc["a"][1], "test");
  test_elem(doc["ee"], {});
  test_elem(doc["e"], "\377\377");
}

TEST(BsonExtraction, DateTime) {
  auto test_elem = [](const fb::Value& elem,
                      const std::chrono::system_clock::time_point& value) {
    EXPECT_FALSE(elem.IsMissing());
    EXPECT_FALSE(elem.IsArray());
    EXPECT_FALSE(elem.IsDocument());
    EXPECT_FALSE(elem.IsNull());
    EXPECT_FALSE(elem.IsBool());
    EXPECT_FALSE(elem.IsInt32());
    EXPECT_FALSE(elem.IsInt64());
    EXPECT_FALSE(elem.IsDouble());
    EXPECT_FALSE(elem.IsString());
    EXPECT_TRUE(elem.IsDateTime());
    EXPECT_FALSE(elem.IsOid());
    EXPECT_FALSE(elem.IsBinary());
    EXPECT_FALSE(elem.IsDecimal128());
    EXPECT_FALSE(elem.IsMinKey());
    EXPECT_FALSE(elem.IsMaxKey());
    EXPECT_FALSE(elem.IsObject());

    EXPECT_THROW(elem.As<bool>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<int32_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<int64_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<size_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<double>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<std::string>(), fb::TypeMismatchException);
    EXPECT_EQ(value, elem.As<TimePoint>());
    EXPECT_THROW(elem.As<fb::Oid>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Binary>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Decimal128>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Document>(), fb::TypeMismatchException);
  };

  const auto time1 = std::chrono::system_clock::from_time_t(1535749200);
  const auto time2 = std::chrono::system_clock::from_time_t(1538341200);

  const auto doc = fb::MakeDoc("a", fb::MakeArray(time1), "e", time2);
  test_elem(doc["a"][0], time1);
  test_elem(doc["e"], time2);
}

TEST(BsonExtraction, Oid) {
  auto test_elem = [](const fb::Value& elem, const std::string& oid_string) {
    EXPECT_FALSE(elem.IsMissing());
    EXPECT_FALSE(elem.IsArray());
    EXPECT_FALSE(elem.IsDocument());
    EXPECT_FALSE(elem.IsNull());
    EXPECT_FALSE(elem.IsBool());
    EXPECT_FALSE(elem.IsInt32());
    EXPECT_FALSE(elem.IsInt64());
    EXPECT_FALSE(elem.IsDouble());
    EXPECT_FALSE(elem.IsString());
    EXPECT_FALSE(elem.IsDateTime());
    EXPECT_TRUE(elem.IsOid());
    EXPECT_FALSE(elem.IsBinary());
    EXPECT_FALSE(elem.IsDecimal128());
    EXPECT_FALSE(elem.IsMinKey());
    EXPECT_FALSE(elem.IsMaxKey());
    EXPECT_FALSE(elem.IsObject());

    EXPECT_THROW(elem.As<bool>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<int32_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<int64_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<size_t>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<double>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<std::string>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<TimePoint>(), fb::TypeMismatchException);
    EXPECT_EQ(fb::Oid(oid_string), elem.As<fb::Oid>());
    EXPECT_THROW(elem.As<fb::Binary>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Decimal128>(), fb::TypeMismatchException);
    EXPECT_THROW(elem.As<fb::Document>(), fb::TypeMismatchException);
  };

  const auto doc =
      fb::MakeDoc("a", fb::MakeArray(fb::Oid("5b89ac509ecb0a21a6000001")), "e",
                  fb::Oid("5bb139509ecb0a21a6000002"));
  test_elem(doc["a"][0], "5b89ac509ecb0a21a6000001");
  test_elem(doc["e"], "5bb139509ecb0a21a6000002");
}
