#ifndef _INCLUDE_JSON_WRAPPER_SRC_IJSONWRAPPER_HPP_
#define _INCLUDE_JSON_WRAPPER_SRC_IJSONWRAPPER_HPP_

#include <memory>
#include <string>

namespace Wrappers
{
    /**
     * @interface IJsonWrapper
     * @brief Json wrapper contract for simple JSON types.
     * @note Doesn't contain support for arrays.
     */
    class IJsonWrapper
    {
    public:
        virtual ~IJsonWrapper() = default;

        virtual void SetInt(const std::string& key, int64_t value) = 0;

        virtual void SetBool(const std::string& key, bool value) = 0;

        virtual void SetString(const std::string& key, std::string value) = 0;

        virtual void SetObject(const std::string& key, std::unique_ptr<IJsonWrapper> jsonObject) = 0;

        virtual void SetNull(const std::string& key) = 0;

        virtual int64_t GetInt(const std::string& key) = 0;

        virtual bool GetBool(const std::string& key) const = 0;

        virtual std::string GetString(const std::string& key) const = 0;

        virtual std::unique_ptr<IJsonWrapper> GetObject(const std::string& key) const = 0;

        virtual bool IsNull(const std::string& key) const = 0;

        virtual bool HasKey(const std::string& key) const = 0;

        virtual void Parse(const std::string& inputJson) = 0;

        virtual std::string ToString() const = 0;

    protected:
        IJsonWrapper() = default;
    };

}  // namespace Wrappers

#endif  // _INCLUDE_JSON_WRAPPER_SRC_IJSONWRAPPER_HPP_
