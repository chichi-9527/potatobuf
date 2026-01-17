#include "IText.h"

namespace INVENT
{
    IText::~IText()
    {
        _data.clear();
    }

    IText::IText(const std::string& str)
    {
        _data.clear();
        _data.reserve(str.size());


        _from_utf8(str);

    }

    IText::IText(const char* c_str, size_t size)
    {
        _data.clear();
        if (size)
        {
            _data.reserve(size);
        }

        _from_utf8(size ? std::string(c_str, size) : std::string(c_str));

    }

    void IText::ToUtf8(std::string& result) const
    {
        result.clear();
        result.reserve(_data.size());

        for (uint32_t code_point : _data)
        {
            if (code_point <= 0x7F)
            {
                result.push_back(static_cast<char>(code_point));
            }
            else if (code_point <= 0x7FF)
            {
                result.push_back(static_cast<char>(0xC0 | ((code_point >> 6) & 0x1F)));
                result.push_back(static_cast<char>(0x80 | (code_point & 0x3F)));
            }
            else if (code_point <= 0xFFFF)
            {
                result.push_back(static_cast<char>(0xE0 | ((code_point >> 12) & 0x0F)));
                result.push_back(static_cast<char>(0x80 | ((code_point >> 6) & 0x3F)));
                result.push_back(static_cast<char>(0x80 | (code_point & 0x3F)));
            }
            else if (code_point <= 0x10FFFF)
            {
                result.push_back(static_cast<char>(0xF0 | ((code_point >> 18) & 0x07)));
                result.push_back(static_cast<char>(0x80 | ((code_point >> 12) & 0x3F)));
                result.push_back(static_cast<char>(0x80 | ((code_point >> 6) & 0x3F)));
                result.push_back(static_cast<char>(0x80 | (code_point & 0x3F)));
            }
        }
        
    }

    void IText::Append(const std::string& utf8_str)
    {
        Append(IText(utf8_str));
    }

    void IText::Append(const IText & other)
    {
        _data.insert(_data.end(), other._data.begin(), other._data.end());
    }

    void IText::_from_utf8(const std::string& str)
    {
        size_t i = 0;
        if (_data.size() > 0) _data.clear();

        auto str_size = str.size();
        while (i < str_size)
        {
            auto& code_point = _data.emplace_back();
            if ((str[i] & 0x80) == 0x00)
            {           // 1字节：0xxxxxxx
                code_point = str[i];
                i += 1;
            }
            else if ((str[i] & 0xE0) == 0xC0)
            {      // 2字节：110xxxxx
                if (i + 1 >= str_size) break;
                code_point = ((str[i] & 0x1F) << 6) |
                    (str[i + 1] & 0x3F);
                i += 2;
            }
            else if ((str[i] & 0xF0) == 0xE0)
            {      // 3字节：1110xxxx
                if (i + 2 >= str_size) break;
                code_point = ((str[i] & 0x0F) << 12) |
                    ((str[i + 1] & 0x3F) << 6) |
                    (str[i + 2] & 0x3F);
                i += 3;
            }
            else if ((str[i] & 0xF8) == 0xF0)
            {      // 4字节：11110xxx
                if (i + 3 >= str_size) break;
                code_point = ((str[i] & 0x07) << 18) |
                    ((str[i + 1] & 0x3F) << 12) |
                    ((str[i + 2] & 0x3F) << 6) |
                    (str[i + 3] & 0x3F);
                i += 4;
            }

        }// while

    }
    void IText::_from_wstring(const std::wstring& wstr)
    {
        if (_data.size() > 0) _data.clear();
#ifdef _WIN32
        size_t i = 0;
        const size_t len = wstr.length();

        while (i < len)
        {
            uint32_t high_surrogate = static_cast<uint32_t>(wstr[i]);

            // 检查是否是高代理项（0xD800-0xDBFF）
            if (high_surrogate >= 0xD800 && high_surrogate <= 0xDBFF && i + 1 < len)
            {
                uint32_t low_surrogate = static_cast<uint32_t>(wstr[i + 1]);

                // 检查是否是低代理项（0xDC00-0xDFFF）
                if (low_surrogate >= 0xDC00 && low_surrogate <= 0xDFFF)
                {
                    // 计算UTF-32码点
                    uint32_t code_point = 0x10000 +
                        ((high_surrogate - 0xD800) << 10) +
                        (low_surrogate - 0xDC00);
                    _data.push_back(code_point);
                    i += 2;  // 跳过代理对
                }
                else
                {
                    // 无效的代理对，只添加高代理
                    _data.push_back(high_surrogate);
                    ++i;
                }
            }
            else
            {
                // 基本多文种平面（BMP）字符
                _data.push_back(high_surrogate);
                ++i;
            }
        }
#else
        for (wchar_t wch : wstr)
        {
            _data.push_back(static_cast<uint32_t>(wch));
        }
#endif // _WIN32

    }
}
