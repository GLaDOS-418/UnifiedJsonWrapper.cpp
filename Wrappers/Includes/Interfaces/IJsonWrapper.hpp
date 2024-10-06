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
     * @note Default object state is 'null' instead of empty object("{}").
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
         * @throw XJsonError If the operation fails.
         */
        virtual void SetInt(const std::string& key, int64_t value) = 0;

        /**
         * @brief Set an unsigned integer value in the JSON object.
         * @param key The key to set.
         * @param value The value to set.
         * @throw XJsonError If the operation fails.
         */
        virtual void SetUnsigned(const std::string& key, uint64_t value) = 0;

        /**
         * @brief Set a double value in the JSON object.
         * @param key The key to set.
         * @param value The value to set.
         * @throw XJsonError If the operation fails.
         */
        virtual void SetDouble(const std::string& key, double value) = 0;

        /**
         * @brief Set a boolean value in the JSON object.
         * @param key The key to set.
         * @param value The value to set.
         * @throw XJsonError If the operation fails.
         */
        virtual void SetBool(const std::string& key, bool value) = 0;

        /**
         * @brief Set a string value in the JSON object.
         * @param key The key to set.
         * @param value The value to set.
         * @throw XJsonError If the operation fails.
         */
        virtual void SetString(const std::string& key, const std::string& value) = 0;

        /**
         * @brief Set an inner JSON object.
         * @param key The key to set.
         * @param jsonObjec The object to set.
         * @throw XJsonError If the operation fails.
         */
        virtual void SetObject(const std::string& key, std::unique_ptr<IJsonWrapper> jsonObject) = 0;

        /**
         * @brief Set a null value in the JSON object.
         * @param key The key to set.
         * @throw XJsonError If the operation fails.
         */
        virtual void SetNull(const std::string& key) = 0;

        // #endregion

        // #region Getters

        /**
         * @brief Get an integer value from the JSON object.
         * @param key The key to lookup.
         * @return The integer value associated with the key.
         * @throw XJsonError If the key doesn't exist or type conversion fails.
         */
        virtual int64_t GetInt(const std::string& key) const = 0;

        /**
         * @brief Get an unsigned integer value from the JSON object.
         * @param key The key to lookup.
         * @return The unsigned integer value associated with the key.
         * @throw XJsonError If the key doesn't exist or type conversion fails.
         */
        virtual uint64_t GetUnsigned(const std::string& key) const = 0;

        /**
         * @brief Get a double value from the JSON object.
         * @param key The key to lookup.
         * @return The double value associated with the key.
         * @throw XJsonError If the key doesn't exist or type conversion fails.
         */
        virtual double GetDouble(const std::string& key) const = 0;

        /**
         * @brief Get an boolean value from the JSON object.
         * @param key The key to lookup.
         * @return The boolean value associated with the key.
         * @throw XJsonError If the key doesn't exist or type conversion fails.
         */
        virtual bool GetBool(const std::string& key) const = 0;

        /**
         * @brief Get a string value from the JSON object.
         * @param key The key to lookup.
         * @return The string value associated with the key.
         * @throw XJsonError If the key doesn't exist or type conversion fails.
         */
        virtual std::string GetString(const std::string& key) const = 0;

        /**
         * @brief Get an inner object copy from the JSON object.
         * @param key The key to lookup.
         * @return The inner object copy associated with the key.
         * @throw XJsonError If the key doesn't exist or type conversion fails.
         */
        virtual std::unique_ptr<IJsonWrapper> GetObject(const std::string& key) const = 0;

        /**
         * @brief Check if a value is null.
         * @param key The key to check.
         * @return @b true if the value is null, @b false otherwise.
         * @throw XJsonError If the key doesn't exist.
         */
        virtual bool IsNull(const std::string& key) const = 0;

        /**
         * @brief Checks if a key is present in the JSON object.
         * @param key The key to check.
         * @return @b true if the key is present, otherwise @b false.
         */
        virtual bool HasKey(const std::string& key) const = 0;

        /**
         * @brief Create an empty JSON object.
         * @return Empty JSON object.
         * @throws XJsonError If empty JSON object could not be created.
         */
        virtual std::unique_ptr<IJsonWrapper> GetEmptyObject() const = 0;

        // #endregion

        // #region Seraialization_Deserialization

        /**
         * @brief Parse a JSON string.
         * @param jsonString The string to parse.
         * @throw XJsonError If parsing fails.
         */
        virtual void Parse(const std::string& jsonString) = 0;

        /**
         * @brief Convert the JSON object to a string representation.
         * @return String representation of the JSON object.
         * @throw XJsonError If conversion of Json object to string fails.
         * @note Conversion might fail due to bad structure, non utf-8 compliant string values etc.
         */
        virtual std::string ToString() const = 0;

        // #endregion

    protected:
        IJsonWrapper() = default;
    };

}  // namespace Wrappers

#endif  // _INCLUDE_JSON_WRAPPER_SRC_IJSONWRAPPER_HPP_
