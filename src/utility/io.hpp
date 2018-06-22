#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace sk::utility
{
    /**
     * Unlike std::basic_streambuf, has a decent interface and doesn't deal
     * with locales and buffering.
     */
    class Reader
    {
    public:
        virtual ~Reader();

        virtual std::size_t read(char* buffer, std::size_t bufferSize) = 0;
    };

    class FileReader : public Reader
    {
    public:
        explicit FileReader(char const* path);
        ~FileReader();

        std::size_t read(char* buffer, std::size_t bufferSize) override;

    private:
        int fd;
    };

    void readFull(Reader& r, char* buffer, std::size_t bufferSize);

    template<std::size_t N>
    std::array<char, N> readArray(Reader& r);

    std::uint16_t readUint16LE(Reader& r);
    std::uint32_t readUint32LE(Reader& r);
    std::uint64_t readUint64LE(Reader& r);

    template<std::size_t N>
    std::array<char, N> readArray(Reader& r)
    {
        std::array<char, N> buffer;
        readFull(r, buffer.data(), buffer.size());
        return buffer;
    }

    /**
     * Unlike std::basic_streambuf, has a decent interface and doesn't deal
     * with locales and buffering.
     */
    class Writer
    {
    public:
        virtual ~Writer();

        virtual std::size_t write(
            char const* buffer,
            std::size_t bufferSize
        ) = 0;
    };

    void writeFull(Writer& w, char const* buffer, std::size_t bufferSize);
    void writeString(Writer& w, char const* string);
}
