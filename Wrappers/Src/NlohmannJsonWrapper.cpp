#include "Implementations/NlohmannJsonWrapper.hpp"
#include "Exceptions/XJsonError.hpp"

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
            throw XJsonError{std::string{"Failed to set null: "} + e.what()};
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
            throw XJsonError{std::string{"Failed to set null: "} + e.what()};
        }
    }

    void NlohmannJsonWrapper::SetString(const std::string& key, std::string value)
    {
        try
        {
            _json[key] = value;
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError{std::string{"Failed to set null: "} + e.what()};
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
            throw XJsonError{std::string{"Failed to set null: "} + e.what()};
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

    int64_t NlohmannJsonWrapper::GetInt(const std::string& key)
    {
        try
        {
            return _json.at(key).get<int64_t>();
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError("Failed to get integer value.");
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
            throw XJsonError("Failed to get integer value.");
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
            throw XJsonError("Failed to get integer value.");
        }
    }

    std::unique_ptr<IJsonWrapper> NlohmannJsonWrapper::GetObject(const std::string& key) const
    {
        try
        {
            std::unique_ptr<NlohmannJsonWrapper> nlohmannWrapper = std::make_unique<NlohmannJsonWrapper>();

            if (nullptr == nlohmannWrapper)
            {
                throw XJsonError{"Could not create JSON object."};
            }

            nlohmannWrapper->_json = _json.at(key).get<nlohmann::json>();

            return nlohmannWrapper;
        }
        catch (const nlohmann::json::exception& e)
        {
            throw XJsonError("Failed to get integer value.");
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

    void NlohmannJsonWrapper::Parse(const std::string& inputJson)
    {
        try
        {
            // nullptr -> no callback. true -> throw exception on bad parse.
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
            throw XJsonError{"Failed to check nullability of the value."};
        }
    }

}  // namespace Wrappers
