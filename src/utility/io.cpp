#include "src/utility/io.hpp"

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cassert>
#include <cstdint>
#include <cstring>

namespace sk::utility
{
    Reader::~Reader() = default;

    FileReader::FileReader(char const* path)
    {
        fd = ::open(path, O_RDONLY);
        if (fd == -1)
        {
            // TODO: Throw a more descriptive exception.
            throw "";
        }
    }

    FileReader::~FileReader()
    {
        ::close(fd);
    }

    std::size_t FileReader::read(char* buffer, std::size_t bufferSize)
    {
        ::ssize_t nread = ::read(fd, buffer, bufferSize);
        if (nread == -1)
        {
            // TODO: Throw a more descriptive exception.
            throw "";
        }
        return nread;
    }

    void readFull(Reader& r, char* buffer, std::size_t bufferSize)
    {
        while (bufferSize != 0)
        {
            std::size_t nread = r.read(buffer, bufferSize);
            if (nread == 0)
            {
                // FIXME: Throw a more descriptive exception, and document that
                //        such an exception is thrown.
                throw "";
            }
            buffer += nread;
            bufferSize -= nread;
        }
    }

    std::uint16_t readUint16LE(Reader& r)
    {
        auto buffer = readArray<2>(r);
        return (static_cast<std::uint16_t>(buffer[0]) <<  0) |
               (static_cast<std::uint16_t>(buffer[1]) <<  8) ;
    }

    std::uint32_t readUint32LE(Reader& r)
    {
        auto buffer = readArray<4>(r);
        return (static_cast<std::uint32_t>(buffer[0]) <<  0) |
               (static_cast<std::uint32_t>(buffer[1]) <<  8) |
               (static_cast<std::uint32_t>(buffer[2]) << 16) |
               (static_cast<std::uint32_t>(buffer[3]) << 24) ;
    }

    std::uint64_t readUint64LE(Reader& r)
    {
        auto buffer = readArray<8>(r);
        return (static_cast<std::uint64_t>(buffer[0]) <<  0) |
               (static_cast<std::uint64_t>(buffer[1]) <<  8) |
               (static_cast<std::uint64_t>(buffer[2]) << 16) |
               (static_cast<std::uint64_t>(buffer[3]) << 24) |
               (static_cast<std::uint64_t>(buffer[4]) << 32) |
               (static_cast<std::uint64_t>(buffer[5]) << 40) |
               (static_cast<std::uint64_t>(buffer[6]) << 48) |
               (static_cast<std::uint64_t>(buffer[7]) << 56) ;
    }

    Writer::~Writer() = default;

    void writeFull(Writer& w, char const* buffer, std::size_t bufferSize)
    {
        while (bufferSize != 0)
        {
            std::size_t nwritten = w.write(buffer, bufferSize);
            assert(nwritten != 0);
            buffer += nwritten;
            bufferSize -= nwritten;
        }
    }

    void writeString(Writer& w, char const* string)
    {
        writeFull(w, string, std::strlen(string));
    }
}
