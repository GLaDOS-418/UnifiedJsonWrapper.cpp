#ifndef _INCLUDE_JSON_WRAPPER_INCLUDES_NLOHMANNJSONWRAPPER_HPP_
#define _INCLUDE_JSON_WRAPPER_INCLUDES_NLOHMANNJSONWRAPPER_HPP_

#include <nlohmann/json.hpp>

#include "Interfaces/IJsonWrapper.hpp"

namespace Wrappers
{
    /**
     * @class NlohmannJsonWrapper
     * @brief Implementation of `Wrappers::IJsonWrapper` interface.
     */
    class NlohmannJsonWrapper : public IJsonWrapper
    {
    public:
        NlohmannJsonWrapper() = default;

        ~NlohmannJsonWrapper() override = default;

        void SetInt(const std::string& key, int64_t value) override;

        void SetUnsigned(const std::string& key, uint64_t value) override;

        void SetDouble(const std::string& key, double value) override;

        void SetBool(const std::string& key, bool value) override;

        void SetString(const std::string& key, const std::string& value) override;

        void SetObject(const std::string& key, std::unique_ptr<IJsonWrapper> jsonObject) override;

        void SetNull(const std::string& key) override;

        int64_t GetInt(const std::string& key) const override;

        uint64_t GetUnsigned(const std::string& key) const override;

        double GetDouble(const std::string& key) const override;

        bool GetBool(const std::string& key) const override;

        std::string GetString(const std::string& key) const override;

        std::unique_ptr<IJsonWrapper> GetObject(const std::string& key) const override;

        bool IsNull(const std::string& key) const override;

        bool HasKey(const std::string& key) const override;

        std::unique_ptr<IJsonWrapper> GetEmptyObject() const override;

        void Parse(const std::string& inputJson) override;

        std::string ToString() const override;

    private:
        nlohmann::json _json;
    };

}  // namespace Wrappers

#endif  // _INCLUDE_JSON_WRAPPER_INCLUDES_NLOHMANNJSONWRAPPER_HPP_
