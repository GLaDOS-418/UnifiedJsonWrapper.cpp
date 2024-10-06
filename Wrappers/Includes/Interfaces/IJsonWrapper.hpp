#ifndef _INCLUDE_JSON_WRAPPER_SRC_IJSONWRAPPER_HPP_
#define _INCLUDE_JSON_WRAPPER_SRC_IJSONWRAPPER_HPP_

#include <memory>
#include <string>

namespace Wrappers
{
    /**
     * @interface IJsonWrapper
     * @brief Json wrapper contract for simple JSON types.
     * @note Doesn't contain support for arrays yet.
     */
    class IJsonWrapper
    {
    public:
        virtual ~IJsonWrapper() = default;

        // #region Setters

        /**
         * @brief Set an integer value in the JSON object.
         * @param key The key to set.
         * @param value The value to set.
         * @throw XJsonError if the operation fails.
         */
        virtual void SetInt(const std::string& key, int64_t value) = 0;

        /**
         * @brief Set a boolean value in the JSON object.
         * @param key The key to set.
         * @param value The value to set.
         * @throw XJsonError if the operation fails.
         */
        virtual void SetBool(const std::string& key, bool value) = 0;

        /**
         * @brief Set a string value in the JSON object.
         * @param key The key to set.
         * @param value The value to set.
         * @throw XJsonError if the operation fails.
         */
        virtual void SetString(const std::string& key, const std::string& value) = 0;

        /**
         * @brief Set an inner JSON object.
         * @param key The key to set.
         * @param jsonObjec The object to set.
         * @throw XJsonError if the operation fails.
         */
        virtual void SetObject(const std::string& key, std::unique_ptr<IJsonWrapper> jsonObject) = 0;

        /**
         * @brief Set a null value in the JSON object.
         * @param key The key to set.
         * @throw XJsonError if the operation fails.
         */
        virtual void SetNull(const std::string& key) = 0;

        // #endregion

        // #region Getters

        /**
         * @brief Get an integer value from the JSON object.
         * @param key The key to lookup.
         * @return The integer value associated with the key.
         * @throw XJsonError if the key doesn't exist or type conversion fails.
         */
        virtual int64_t GetInt(const std::string& key) = 0;

        /**
         * @brief Get an boolean value from the JSON object.
         * @param key The key to lookup.
         * @return The boolean value associated with the key.
         * @throw XJsonError if the key doesn't exist or type conversion fails.
         */
        virtual bool GetBool(const std::string& key) const = 0;

        /**
         * @brief Get an boolean value from the JSON object.
         * @param key The key to lookup.
         * @return The boolean value associated with the key.
         * @throw XJsonError if the key doesn't exist or type conversion fails.
         */
        virtual std::string GetString(const std::string& key) const = 0;

        /**
         * @brief Get an boolean value from the JSON object.
         * @param key The key to lookup.
         * @return The boolean value associated with the key.
         * @throw XJsonError if the key doesn't exist or type conversion fails.
         */
        virtual std::unique_ptr<IJsonWrapper> GetObject(const std::string& key) const = 0;

        /**
         * @brief Check if a value is null.
         * @param key The key to check.
         * @return @b true if the value is null, @b false otherwise.
         * @throw XJsonError if the key doesn't exist.
         */
        virtual bool IsNull(const std::string& key) const = 0;

        /**
         * @brief Checks if a key is present in the JSON object.
         * @param key The key to check.
         * @return @b true if the key is present, otherwise @b false.
         */
        virtual bool HasKey(const std::string& key) const = 0;

        // #endregion

        // #region Seraialization_Deserialization

        /**
         * @brief Parse a JSON string.
         * @param jsonString The string to parse.
         * @throw XJsonError if parsing fails.
         */
        virtual void Parse(const std::string& jsonString) = 0;

        /**
         * @brief Convert the JSON object to a string representation.
         * @return String representation of the JSON object.
         */
        virtual std::string ToString() const = 0;

        // #endregion

    protected:
        IJsonWrapper() = default;
    };

}  // namespace Wrappers

#endif  // _INCLUDE_JSON_WRAPPER_SRC_IJSONWRAPPER_HPP_
