#include "Implementations/NlohmannJsonWrapper.hpp"

#include <string>
#include <cstdint>
#include <memory>

#include "Exceptions/XJsonError.hpp"
#include "Interfaces/IJsonWrapper.hpp"

namespace Wrappers
{

    void NlohmannJsonWrapper::SetInt(const std::string& key, int64_t value)
    {
        try
        {
            _json[key] = value;
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError{std::string{"Failed to set Integer: "} + e.what()};
        }
    }

    void NlohmannJsonWrapper::SetUnsigned(const std::string& key, uint64_t value)
    {
        try
        {
            _json[key] = value;
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError{std::string{"Failed to set Unsigned Integer: "} + e.what()};
        }
    }

    void NlohmannJsonWrapper::SetDouble(const std::string& key, double value)
    {
        try
        {
            _json[key] = value;
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError{std::string{"Failed to set Double: "} + e.what()};
        }
    }

    void NlohmannJsonWrapper::SetBool(const std::string& key, bool value)
    {
        try
        {
            _json[key] = value;
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError{std::string{"Failed to set Boolean: "} + e.what()};
        }
    }

    void NlohmannJsonWrapper::SetString(const std::string& key, const std::string& value)
    {
        try
        {
            _json[key] = value;
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError{std::string{"Failed to set String: "} + e.what()};
        }
    }

    void NlohmannJsonWrapper::SetObject(const std::string& key, std::unique_ptr<IJsonWrapper> jsonObject)
    {
        try
        {
            const NlohmannJsonWrapper* nlohmannWrapper = dynamic_cast<NlohmannJsonWrapper*>(jsonObject.get());
            if (nullptr == nlohmannWrapper)
            {
                throw XJsonError{"Invalid JSON object to set."};
            }

            _json[key] = nlohmannWrapper->_json;
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError{std::string{"Failed to set Inner Object: "} + e.what()};
        }
    }

    void NlohmannJsonWrapper::SetNull(const std::string& key)
    {
        try
        {
            _json[key] = nullptr;
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError{std::string{"Failed to set null: "} + e.what()};
        }
    }

    int64_t NlohmannJsonWrapper::GetInt(const std::string& key) const
    {
        try
        {
            return _json.at(key).get<int64_t>();
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError("Failed to get Integer value.");
        }
    }

    uint64_t NlohmannJsonWrapper::GetUnsigned(const std::string& key) const
    {
        try
        {
            return _json.at(key).get<uint64_t>();
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError("Failed to get Unsigned Integer value.");
        }
    }

    double NlohmannJsonWrapper::GetDouble(const std::string& key) const
    {
        try
        {
            return _json.at(key).get<double>();
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError("Failed to get Double value.");
        }
    }

    bool NlohmannJsonWrapper::GetBool(const std::string& key) const
    {
        try
        {
            return _json.at(key).get<bool>();
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError("Failed to get Boolean value.");
        }
    }

    std::string NlohmannJsonWrapper::GetString(const std::string& key) const
    {
        try
        {
            return _json.at(key).get<std::string>();
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError("Failed to get String value.");
        }
    }

    std::unique_ptr<IJsonWrapper> NlohmannJsonWrapper::GetObject(const std::string& key) const
    {
        try
        {
            std::unique_ptr<NlohmannJsonWrapper> nlohmannWrapper = std::make_unique<NlohmannJsonWrapper>();

            if (nullptr == nlohmannWrapper)
            {
                throw XJsonError{"Could not allocate for JSON object."};
            }

            nlohmannWrapper->_json = _json.at(key).get<nlohmann::json>();

            return nlohmannWrapper;
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError("Failed to get Inner Object.");
        }
    }

    bool NlohmannJsonWrapper::IsNull(const std::string& key) const
    {
        try
        {
            return _json.at(key).is_null();
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError{"Failed to check nullability of the value."};
        }
    }

    bool NlohmannJsonWrapper::HasKey(const std::string& key) const
    {
        return _json.contains(key);
    }

    std::unique_ptr<IJsonWrapper> NlohmannJsonWrapper::GetEmptyObject() const
    {
        try
        {
            std::unique_ptr<NlohmannJsonWrapper> emptyObject = std::make_unique<NlohmannJsonWrapper>();
            if (nullptr == emptyObject)
            {
                throw XJsonError("Could not create an empty JSON object.");
            }

            emptyObject->_json = nlohmann::json::object();

            return emptyObject;
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError{"Failed to create an empty Json object."};
        }
    }

    void NlohmannJsonWrapper::Parse(const std::string& inputJson)
    {
        try
        {
            // 'nullptr' => no callback.
            // 'true' => throw exception on bad parse.
            _json = nlohmann::json::parse(inputJson, nullptr, true);
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError{"Failed to check nullability of the value."};
        }
    }

    std::string NlohmannJsonWrapper::ToString() const
    {
        try
        {
            return _json.dump();
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError{"Failed to convert JSON object to String. Verify if it's UTF-8 encoded."};
        }
    }

}  // namespace Wrappers
