#include "gtest/gtest.h"
#include <gtest/gtest.h>

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

TYPED_TEST(TestIJsonWrapper, IntegerValue)
{
    Wrappers::IJsonWrapper& jsonWrapper = this->_jsonWrapper;
    const std::string key = "Integer";
    constexpr int value = 10;

    jsonWrapper.SetInt(key, value);

    std::string expectedJson = R"({"Integer":10})";

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

    std::string expectedJson = R"({"FalseKey":false,"TrueKey":true})";

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

    std::string expectedJson = R"({"Null":null})";

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

    std::string expectedJson = R"({"String":"string_value"})";

    EXPECT_EQ(jsonWrapper.ToString(), expectedJson);
    EXPECT_EQ(jsonWrapper.GetString(key), value);
    EXPECT_TRUE(jsonWrapper.HasKey(key));
}

// NOTE: implement double api.
TYPED_TEST(TestIJsonWrapper, DISABLED_DoubleValue)
{
    // Wrappers::IJsonWrapper& jsonWrapper = this->_jsonWrapper;

    // const std::string key = "Double";
    // constexpr double value = 3.14;
    //
    // std::string expectedJson = R"({"Double":3.14})";

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

    std::string expectedJson = R"({"InnerObject":{"InnerKey":"InnerValue"}})";

    EXPECT_EQ(jsonWrapper.ToString(), expectedJson);

    std::unique_ptr<Wrappers::IJsonWrapper> innerObject = jsonWrapper.GetObject(key);
    EXPECT_TRUE(nullptr != innerObject);
    EXPECT_TRUE(jsonWrapper.HasKey(key));

    const std::string expectedInnerJson = R"({"InnerKey":"InnerValue"})";
    EXPECT_EQ(innerObject->ToString(), expectedInnerJson);
    EXPECT_EQ(innerObject->GetString(innerKey), innerValue);
    EXPECT_TRUE(jsonWrapper.HasKey(innerKey));
}
