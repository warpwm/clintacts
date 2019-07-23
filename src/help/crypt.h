#pragma once
#include <string>
#include <type_traits>

template <typename dummy>
class cryptor_static_base
{
    protected:
        static const std::string m_base64_chars;
        static std::string m_key;
};

template <typename dummy>
const std::string cryptor_static_base<dummy>::m_base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

template <typename dummy>
std::string cryptor_static_base<dummy>::m_key = "default_key";

class cryptor : public cryptor_static_base<void>{
    public:
        cryptor() = delete;
        static std::string encrypt(const char* in, const std::string& key = m_key);
        template <typename buffer_type>
            static buffer_type encrypt(const buffer_type& in, const std::string& key = m_key);
        static std::string decrypt(const char* in, const std::string& key = m_key);
        template <typename buffer_type>
            static buffer_type decrypt(const buffer_type& in, const std::string& key = m_key);
        static const std::string& get_key();
        static void set_key(const std::string& key);
    private:
        static std::string do_xor(const char* data, const std::string& key);
        template <typename buffer_type>
            static buffer_type do_xor(const buffer_type& data, const std::string& key);
        template <typename buffer_type>
            static void xor_impl(buffer_type& data, const std::string& key);
        static std::string base64_encode(const char* in);
        template <typename buffer_type>
            static buffer_type base64_encode(const buffer_type& in);
        template <typename buffer_type>
            static buffer_type base64_encode_impl(const buffer_type& in);
        static std::string base64_decode(const char* encoded_data);
        template <typename buffer_type>
            static buffer_type base64_decode(const buffer_type& encoded_data);
        template <typename buffer_type, typename out_type>
            static void base64_decode_impl(buffer_type&& encoded_data, out_type& out);
        static bool is_base64(uint8_t c);
};

