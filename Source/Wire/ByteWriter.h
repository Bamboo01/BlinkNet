#ifndef BLINKNET_BYTESTREAM_H
#define BLINKNET_BYTESTREAM_H

#include <cstdint>
#include <vector>
#include <bits/ios_base.h>

namespace BlinkNet
{
    // Helper class that appends big endian fields to a byte vector by reference
    class ByteWriter
    {
    private:
        std::vector<uint8_t>& out;

    public:
        explicit ByteWriter(std::vector<uint8_t>& source) : out(source) {};

        void U8(uint8_t v)
        {
            out.push_back(v);
        }

        void U16(uint16_t v)
        {
            out.push_back(v >> 8);
            out.push_back(v);
        }

        void U32(uint32_t v)
        {
            out.push_back(v >> 24);
            out.push_back(v >> 16);
            out.push_back(v >> 8);
            out.push_back(v);
        }

        void Bytes(std::vector<uint8_t> bytes)
        {
            out.insert(out.end(), bytes.begin(), bytes.end());
        }
    };

    // Reads big endian
    class ByteReader
    {
    private:

        // The input byte
        std::vector<uint8_t> bytes;

        // Whether or not we encounter any error during streaming
        bool error = false;

        // Cursor that moves every time we read via any of the byte reading functions
        size_t pos = 0;

        // n is num bytes
        bool CanStream(size_t n)
        {
            // Is the current cursor position valid?
            if (error || n + pos > bytes.size())
                error = true;

            return error;
        }

    public:
        explicit ByteReader(std::vector<uint8_t>& input) : bytes(input) {};

        uint8_t U8()
        {
            if (CanStream(1))
                return 0;

            return bytes[pos++];
        }

        uint16_t U16()
        {
            if (CanStream(2))
                return 0;

            const uint16_t ret = static_cast<uint16_t>((bytes[pos] << 8) | bytes[pos + 1]);
            pos += 2;

            return ret;
        }

        uint32_t U32()
        {
            if (CanStream(4))
                return 0;

            const uint32_t ret = static_cast<uint32_t>(
                (bytes[pos] << 24)      |
                (bytes[pos + 1] << 16)  |
                (bytes[pos + 2] << 8)   |
                (bytes[pos + 3]));

            pos += 4;

            return ret;
        }

        std::vector<uint8_t> Remainder()
        {
            if (error)
                return std::vector<uint8_t>();

            size_t rem = pos;
            pos = bytes.size();

            return std::vector<uint8_t>(bytes.begin() + rem, bytes.end());
        }

        bool Error() const
        {
            return error;
        }
    };
}


#endif //BLINKNET_BYTESTREAM_H
