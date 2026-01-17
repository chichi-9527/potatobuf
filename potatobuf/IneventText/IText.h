#ifndef _ITEXT_
#define _ITEXT_

#include <stdint.h>
#include <string>
#include <vector>

namespace INVENT
{
	// only from utf-8 string or wstring(define INVENT_ITEXT_USE_WSTRING)
	// only can output utf-8 string and no out wstring
	// this class essentially was about converting to UTF-32.
	// so you can use function operator[] get code point
	class IText
	{
	public:
		~IText();

		IText() = default;
		IText(const IText& other) noexcept { _data = other._data; }
		IText(IText&& other) noexcept { _data = std::move(other._data); }
		IText& operator=(IText&& other) noexcept { _data = std::move(other._data); }

		explicit IText(const std::string& utf8_str);
		explicit IText(const char* utf8_c_str, size_t size = 0);

#ifdef INVENT_ITEXT_USE_WSTRING
		explicit IText(const std::wstring& wstr);
		explicit IText(const wchar_t* c_wstr, size_t size = 0);
#endif // INVENT_ITEXT_USE_WSTRING

		void ToUtf8(std::string& result) const;

		// only utf-8 string
		void Append(const std::string& utf8_str);
		void Append(const IText& other);

		// only utf-8 string
		IText& operator+=(const std::string& utf8_str)
		{
			Append(utf8_str);
			return *this;
		}

		IText& operator+=(const IText& other)
		{
			Append(other);
			return *this;
		}

		// if pos >= size will error
		uint32_t operator[](size_t pos) const
		{
			return _data[pos];
		}

		// if pos >= size will return max uint32
		uint32_t at(size_t pos) const
		{
			if (pos >= _data.size()) return (uint32_t)-1;
			return _data[pos];
		}

		auto begin() { return _data.begin(); }
		auto end() { return _data.end(); }
		auto begin() const { return _data.begin(); }
		auto end() const { return _data.end(); }

		size_t size(){return _data.size(); }

	private:
		void _from_utf8(const std::string& str);
		void _from_wstring(const std::wstring& wstr);

	private:
		std::vector<uint32_t> _data;
	};

#ifdef INVENT_ITEXT_USE_WSTRING
	IText::IText(const std::wstring& wstr)
	{
		_data.clear();
		_data.reserve(wstr.size());

		_from_wstring(wstr);
	}

	IText::IText(const wchar_t* c_wstr, size_t size)
	{
		_data.clear();
		if (size)
		{
			_data.reserve(size);
		}

		_from_wstring(size ? std::wstring(c_wstr, size) : std::wstring(c_wstr));
	}
#endif // INVENT_ITEXT_USE_WSTRING


}



#endif // !_ITEXT_