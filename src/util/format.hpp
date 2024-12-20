#pragma once

#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "common.hpp"
#include "stringbuffer.hpp"

TODO("Format options");
template <typename T>
struct FormatWriter;

template <typename T>
concept FormatWritable = requires(T value, StringBuffer& sb) {
    { FormatWriter<T>::write(value, sb) };
};

namespace {

struct Token {
    enum class Kind {
        None = 0,
        Literal,
        LeftBrace,
        RightBrace,
        Formatter,
    };

    Token() = delete;
    Token(Kind kind, Index location) : kind(kind), location(location) {}

    Kind kind;
    Index location;
};

std::vector<Token> parseFormatString(const char* format_string,
                                     const Size length) {
    std::vector<Token> tokens;
    Token::Kind current = Token::Kind::None;

    for (Index i = 0; i < length; ++i) {
        if (format_string[i] == '{') {
            if (current == Token::Kind::LeftBrace) {
                tokens.emplace_back(current, i - 1);
                current = Token::Kind::None;
            } else {
                current = Token::Kind::LeftBrace;
            }
        } else if (format_string[i] == '}') {
            if (current == Token::Kind::LeftBrace) {
                tokens.emplace_back(Token::Kind::Formatter, i - 1);
                current = Token::Kind::None;
            } else if (current == Token::Kind::RightBrace) {
                tokens.emplace_back(Token::Kind::RightBrace, i - 1);
                current = Token::Kind::None;
            } else {
                current = Token::Kind::RightBrace;
            }
        } else {
            if (current == Token::Kind::LeftBrace ||
                current == Token::Kind::RightBrace) {
                StringBuffer sb;
                sb.appendFormat("unexpected brace at index {}", i);
                throw std::runtime_error(sb.str());
            }

            if (current == Token::Kind::None) {
                tokens.emplace_back(Token::Kind::Literal, i);
                current = Token::Kind::Literal;
            }
        }
    }
    return tokens;
}

}

class Formatter {
public:
    Formatter(const char* format_string, const Size length)
        : m_formatString(format_string), m_formatStringLength(length) {}

    template <typename... Targs>
    void format(StringBuffer& sb, Targs... args) {
        std::vector<Token> tokens =
            parseFormatString(m_formatString, m_formatStringLength);

        u32 num_args = sizeof...(args);
        u32 num_formatters = 0;
        for (auto token : tokens) {
            if (token.kind == Token::Kind::Formatter)
                ++num_formatters;
        }
        if (num_args != num_formatters) {
            StringBuffer sb;
            sb.appendFormat(
                "unexpected number of formatter args (num_args={}, "
                "num_formatters={})",
                num_args, num_formatters);
            throw std::runtime_error(sb.str());
        }

        Index i = 0;
        (
            [&] {
                i = writeLiterals(sb, tokens, i);
                FormatWriter<decltype(args)>::write(args, sb);
                ++i;
            }(),
            ...);
        writeLiterals(sb, tokens, i);
    }

private:
    const char* m_formatString;
    Size m_formatStringLength;

    Index writeLiterals(StringBuffer& sb, const std::vector<Token>& tokens,
                        const Index start) {
        Index i = start, n = tokens.size();
        while (i < n && tokens[i].kind != Token::Kind::Formatter) {
            Token token = tokens[i];
            Index left = token.location;
            Index right =
                i < n - 1 ? tokens[i + 1].location : m_formatStringLength;
            switch (token.kind) {
            case Token::Kind::Literal:
                for (Index j = left; j < right; ++j) {
                    sb.putSafe(m_formatString[j]);
                }
                break;
            case Token::Kind::LeftBrace:
                sb.putSafe('{');
                break;
            case Token::Kind::RightBrace:
                sb.putSafe('}');
                break;
            default:
                unreachable;
                break;
            }
            ++i;
        }
        return i;
    }
};

template <typename... Targs>
std::string format(const char* format_string, Targs... args) {
    Formatter formatter(format_string, std::strlen(format_string));
    StringBuffer sb;

    try {
        formatter.format(sb, args...);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        return std::string();
    }

    return std::string(sb.str());
}

template <typename... Targs>
void format(StringBuffer& sb, const char* format_string, Targs... args) {
    Formatter formatter(format_string, std::strlen(format_string));
    try {
        formatter.format(sb, args...);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << '\n';
        return;
    }
}

template <typename... Targs>
void println(const char* format_string, Targs... args) {
    StringBuffer sb;
    format(sb, format_string, args...);
    std::cout << sb.str() << '\n';
}

template <typename... Targs>
void print(const char* format_string, Targs... args) {
    StringBuffer sb;
    format(sb, format_string, args...);
    std::cout << sb.str();
}

template <typename... Targs>
void eprintln(const char* format_string, Targs... args) {
    StringBuffer sb;
    format(sb, format_string, args...);
    std::cerr << sb.str() << std::endl;
}

template <typename... Targs>
void eprint(const char* format_string, Targs... args) {
    StringBuffer sb;
    format(sb, format_string, args...);
    std::cerr << sb.str() << std::flush;
}

template <>
struct FormatWriter<char> {
    static void write(char value, StringBuffer& sb) { sb.putSafe(value); }
};

template <>
struct FormatWriter<const char*> {
    static void write(const char* value, StringBuffer& sb) {
        const char* ptr = value;
        TODO("optimize put call");
        while (*ptr != '\0') sb.putSafe(*ptr++);
    }
};

template <>
struct FormatWriter<std::string> {
    static void write(const std::string& value, StringBuffer& sb) {
        sb.append(value.c_str(), value.size());
    }
};

template <>
struct FormatWriter<bool> {
    static void write(bool value, StringBuffer& sb) {
        if (value)
            sb.append("true", 4);
        else
            sb.append("false", 5);
    }
};

template <UnsignedIntegral U>
struct FormatWriter<U> {
    static void write(U value, StringBuffer& sb) {
        if (value == 0) {
            sb.putSafe('0');
            return;
        }

        char int_buffer[20];
        char* ptr = int_buffer;
        while (value > 0) {
            char digit(value % 10);
            value /= 10;
            *ptr++ = digit + '0';
        }

        TODO("optimize put call");
        while (ptr != int_buffer) {
            sb.putSafe(*(--ptr));
        }
    }
};

template <SignedIntegral S>
struct FormatWriter<S> {
    static void write(S value, StringBuffer& sb) {
        if (value == 0) {
            sb.putSafe('0');
            return;
        }

        char int_buffer[19];
        char* ptr = int_buffer;

        S sign = 1;
        if (value < 0) {
            sb.putSafe('-');
            sign = -1;
        }

        while (value != 0) {
            char digit((value % 10) * sign);
            value /= 10;
            *ptr++ = digit + '0';
        }

        TODO("optimize put call");
        while (ptr != int_buffer) {
            sb.putSafe(*(--ptr));
        }
    }
};

template <std::floating_point F>
struct FormatWriter<F> {
    static void write(F value, StringBuffer& sb) {
        TODO("RTW for float printing");
        sb.append(std::to_string(value).c_str());
    }
};

template <typename T>
    requires FormatWritable<T>
struct FormatWriter<std::vector<T>> {
    static void write(const std::vector<T>& vec, StringBuffer& sb) {
        sb.putSafe('[');
        for (auto iter = vec.begin(); iter != vec.end(); ++iter) {
            FormatWriter<T>::write(*iter, sb);
            if (iter != vec.end())
                sb.putSafe(',');
        }
        sb.putSafe(']');
    }
};

template <typename K, typename V>
    requires FormatWritable<K> && FormatWritable<V>
struct FormatWriter<std::map<K, V>> {
    static void write(const std::map<K, V>& hashmap, StringBuffer& sb) {
        sb.putSafe('{');
        for (auto iter = hashmap.begin(); iter != hashmap.end(); ++iter) {
            sb.putSafe('{');
            FormatWriter<K>::write(iter->first, sb);
            sb.putSafe(',');
            FormatWriter<V>::write(iter->second, sb);
            sb.putSafe('}');
            if (distance(iter, hashmap.end()) > 1)
                sb.append(", ", 2);
        }
        sb.putSafe('}');
    }
};
