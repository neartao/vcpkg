#include "vcpkg_Strings.h"

#include <cstdarg>
#include <algorithm>
#include <codecvt>
#include <iterator>

namespace vcpkg {namespace Strings {namespace details
{
    std::string format_internal(const char* fmtstr, ...)
    {
        va_list lst;
        va_start(lst, fmtstr);

        auto sz = _vscprintf(fmtstr, lst);
        std::string output(sz, '\0');
        _vsnprintf_s(&output[0], output.size() + 1, output.size() + 1, fmtstr, lst);
        va_end(lst);

        return output;
    }

    std::wstring wformat_internal(const wchar_t* fmtstr, ...)
    {
        va_list lst;
        va_start(lst, fmtstr);

        auto sz = _vscwprintf(fmtstr, lst);
        std::wstring output(sz, '\0');
        _vsnwprintf_s(&output[0], output.size() + 1, output.size() + 1, fmtstr, lst);
        va_end(lst);

        return output;
    }
}}}

namespace vcpkg {namespace Strings
{
    std::wstring utf8_to_utf16(const std::string& s)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> conversion;
        return conversion.from_bytes(s);
    }

    std::string utf16_to_utf8(const std::wstring& w)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>, wchar_t> conversion;
        return conversion.to_bytes(w);
    }

    std::string::const_iterator case_insensitive_ascii_find(const std::string& s, const std::string& pattern)
    {
        std::string pattern_as_lower_case;
        std::transform(pattern.begin(), pattern.end(), back_inserter(pattern_as_lower_case), tolower);
        return search(s.begin(), s.end(), pattern_as_lower_case.begin(), pattern_as_lower_case.end(), [](const char a, const char b)
                      {
                          return tolower(a) == b;
                      });
    }

    std::string ascii_to_lowercase(const std::string& input)
    {
        std::string output = input;
        std::transform(output.begin(), output.end(), output.begin(), ::tolower);
        return output;
    }

    std::string join(const std::vector<std::string>& v, const std::string& delimiter)
    {
        if (v.empty())
        {
            return std::string();
        }

        std::string output;
        size_t size = v.size();

        output.append(v.at(0));

        for (size_t i = 1; i < size; ++i)
        {
            output.append(delimiter);
            output.append(v.at(i));
        }

        return output;
    }
}}
