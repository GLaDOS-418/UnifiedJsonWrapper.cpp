#include <gtest/gtest.h>

#include "Exceptions/XJsonError.hpp"
#include "Implementations/NlohmannJsonWrapper.hpp"

template<typename TJsonWrapperImpl>
class TestIJsonWrapper : public ::testing::Test
{
public:
    TJsonWrapperImpl _jsonWrapper;
    std::unique_ptr<TJsonWrapperImpl> _innerObject{std::make_unique<TJsonWrapperImpl>()};
};

using TestTypes = ::testing::Types<Wrappers::NlohmannJsonWrapper>;

// NOTE: trailing comma required to avoid unnecessary compiler warning
// Ref: https://github.com/google/googletest/issues/2271#issuecomment-665742471
TYPED_TEST_SUITE(TestIJsonWrapper, TestTypes, );

TYPED_TEST(TestIJsonWrapper, DefaultJson)
{
    Wrappers::IJsonWrapper& jsonWrapper = this->_jsonWrapper;
    const std::string expectedJson = R"(null)";

    EXPECT_EQ(jsonWrapper.ToString(), expectedJson);
}

TYPED_TEST(TestIJsonWrapper, EmptyJson)
{
    Wrappers::IJsonWrapper& jsonWrapper = this->_jsonWrapper;
    const std::string expectedJson = R"(null)";

    EXPECT_EQ(jsonWrapper.ToString(), expectedJson);
}

TYPED_TEST(TestIJsonWrapper, IntegerValue)
{
    Wrappers::IJsonWrapper& jsonWrapper = this->_jsonWrapper;
    const std::string key = "Integer";
    constexpr int value = 10;

    jsonWrapper.SetInt(key, value);

    const std::string expectedJson = R"({"Integer":10})";

    EXPECT_EQ(jsonWrapper.ToString(), expectedJson);
    EXPECT_EQ(jsonWrapper.GetInt(key), value);
    EXPECT_TRUE(jsonWrapper.HasKey(key));
}

TYPED_TEST(TestIJsonWrapper, BooleanValue)
{
    Wrappers::IJsonWrapper& jsonWrapper = this->_jsonWrapper;
    const std::string trueKey = "TrueKey";
    const std::string falseKey = "FalseKey";

    jsonWrapper.SetBool(falseKey, false);
    jsonWrapper.SetBool(trueKey, true);

    const std::string expectedJson = R"({"FalseKey":false,"TrueKey":true})";

    EXPECT_EQ(jsonWrapper.ToString(), expectedJson);
    EXPECT_TRUE(jsonWrapper.HasKey(trueKey));
    EXPECT_EQ(jsonWrapper.GetBool(trueKey), true);
    EXPECT_EQ(jsonWrapper.GetBool(falseKey), false);
    EXPECT_TRUE(jsonWrapper.HasKey(falseKey));
}

TYPED_TEST(TestIJsonWrapper, NullValue)
{
    Wrappers::IJsonWrapper& jsonWrapper = this->_jsonWrapper;
    const std::string key = "Null";

    jsonWrapper.SetNull(key);

    const std::string expectedJson = R"({"Null":null})";

    EXPECT_EQ(jsonWrapper.ToString(), expectedJson);
    EXPECT_TRUE(jsonWrapper.IsNull(key));
    EXPECT_TRUE(jsonWrapper.HasKey(key));
}

TYPED_TEST(TestIJsonWrapper, StringValue)
{
    Wrappers::IJsonWrapper& jsonWrapper = this->_jsonWrapper;
    const std::string key = "String";
    const std::string value = "string_value";

    jsonWrapper.SetString(key, value);

    const std::string expectedJson = R"({"String":"string_value"})";

    EXPECT_EQ(jsonWrapper.ToString(), expectedJson);
    EXPECT_EQ(jsonWrapper.GetString(key), value);
    EXPECT_TRUE(jsonWrapper.HasKey(key));
}

// TODO(glados): implement double api.
TYPED_TEST(TestIJsonWrapper, DISABLED_DoubleValue)
{
    // Wrappers::IJsonWrapper& jsonWrapper = this->_jsonWrapper;

    // const std::string key = "Double";
    // constexpr double value = 3.14;
    //
    // const std::string expectedJson = R"({"Double":3.14})";

    // EXPECT_EQ(jsonWrapper.ToString(), expectedJson);
    // EXPECT_DOUBLE_EQ(jsonWrapper.GetDouble(key), value);
    // EXPECT_TRUE(jsonWrapper.HasKey(key));
}

TYPED_TEST(TestIJsonWrapper, InnerObject)
{
    Wrappers::IJsonWrapper& jsonWrapper = this->_jsonWrapper;

    const std::string innerKey = "InnerKey";
    const std::string innerValue = "InnerValue";
    this->_innerObject->SetString(innerKey, innerValue);

    const std::string key = "InnerObject";
    jsonWrapper.SetObject(key, std::move(this->_innerObject));

    const std::string expectedJson = R"({"InnerObject":{"InnerKey":"InnerValue"}})";

    EXPECT_EQ(jsonWrapper.ToString(), expectedJson);

    std::unique_ptr<const Wrappers::IJsonWrapper> innerObject = jsonWrapper.GetObject(key);
    EXPECT_TRUE(nullptr != innerObject);
    EXPECT_TRUE(jsonWrapper.HasKey(key));

    const std::string expectedInnerJson = R"({"InnerKey":"InnerValue"})";
    EXPECT_EQ(innerObject->ToString(), expectedInnerJson);
    EXPECT_EQ(innerObject->GetString(innerKey), innerValue);
    EXPECT_TRUE(innerObject->HasKey(innerKey));
}

TYPED_TEST(TestIJsonWrapper, IntegerKeyAbsent)
{
    Wrappers::IJsonWrapper& jsonWrapper = this->_jsonWrapper;
    const std::string key = "IntegerKey";

    EXPECT_THROW(jsonWrapper.GetInt(key), Wrappers::XJsonError);
    EXPECT_TRUE(false == jsonWrapper.HasKey(key));
}

TYPED_TEST(TestIJsonWrapper, BooleanKeyAbsent)
{
    Wrappers::IJsonWrapper& jsonWrapper = this->_jsonWrapper;
    const std::string key = "BooleanKey";

    EXPECT_THROW(jsonWrapper.GetBool(key), Wrappers::XJsonError);
    EXPECT_TRUE(false == jsonWrapper.HasKey(key));
}

// TODO(glados): implement double api
TYPED_TEST(TestIJsonWrapper, DISABLED_DoubleKeyAbsent)
{
    // Wrappers::IJsonWrapper& jsonWrapper = this->_jsonWrapper;
    // const std::string key = "DoubleKey";
    //
    // EXPECT_THROW(jsonWrapper.GetDouble(key), Wrappers::XJsonError);
    // EXPECT_TRUE(false == jsonWrapper.HasKey(key));
}

TYPED_TEST(TestIJsonWrapper, StringKeyAbsent)
{
    Wrappers::IJsonWrapper& jsonWrapper = this->_jsonWrapper;
    const std::string key = "StringKey";

    EXPECT_THROW(jsonWrapper.GetString(key), Wrappers::XJsonError);
    EXPECT_TRUE(false == jsonWrapper.HasKey(key));
}

TYPED_TEST(TestIJsonWrapper, InnerObjectKeyAbsent)
{
    Wrappers::IJsonWrapper& jsonWrapper = this->_jsonWrapper;
    const std::string key = "InnerObjectKey";

    EXPECT_THROW(jsonWrapper.GetObject(key), Wrappers::XJsonError);
    EXPECT_TRUE(false == jsonWrapper.HasKey(key));
}

TYPED_TEST(TestIJsonWrapper, ParseWellFormedJson)
{
    const std::string inputJson = R"(
        {
          "pi": 3.141,
          "happy": true,
          "name": "json",
          "nothing": null,
          "answer": {
            "everything": 42
          },
          "list": [1, 0, 2],
          "object": {
            "currency": "USD",
            "value": 42.99
          }
        })";

    //NOTE: 1) the keys get ordered.
    //NOTE: 2) even the list (which is not supported yet, gets serialized).
    const std::string expectedJson = R"({"answer":{"everything":42},"happy":true,)"
                                     R"("list":[1,0,2],"name":"json","nothing":null,)"
                                     R"("object":{"currency":"USD","value":42.99},)"
                                     R"("pi":3.141})";

    Wrappers::IJsonWrapper& jsonWrapper = this->_jsonWrapper;
    jsonWrapper.Parse(inputJson);

    EXPECT_EQ(jsonWrapper.ToString(), expectedJson);
}
