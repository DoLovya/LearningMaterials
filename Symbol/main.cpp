#include <algorithm> // std::min
#include <limits>

typedef unsigned int uint;

template <int Count, size_t StringSize> struct StringData
{
    uint offsetsAndSizes[Count] = {};
    char stringdata0[StringSize] = {};
    constexpr StringData() = default;
};

template <uint... Nx> constexpr size_t stringDataSizeHelper(std::integer_sequence<uint, Nx...>)
{
    // same as:
    //   return (0 + ... + Nx);
    // but not using the fold expression to avoid exceeding compiler limits
    size_t total = 0;
    uint sizes[] = { Nx... };
    for (uint n : sizes)
        total += n;
    return total;
}

template <uint... Nx> constexpr auto stringData(const char (&...strings)[Nx])
{
    constexpr size_t StringSize = stringDataSizeHelper<Nx...>({});
    constexpr size_t Count = 2 * sizeof...(Nx);

    StringData<Count, StringSize> result;
    const char *inputs[] = { strings... };
    uint sizes[] = { Nx... };

    uint offset = 0;
    char *output = result.stringdata0;
    for (size_t i = 0; i < sizeof...(Nx); ++i) {
        // copy the input string, including the terminating null
        uint len = sizes[i];
        for (uint j = 0; j < len; ++j)
            output[offset + j] = inputs[i][j];
        result.offsetsAndSizes[2 * i] = offset + sizeof(result.offsetsAndSizes);
        result.offsetsAndSizes[2 * i + 1] = len - 1;
        offset += len;
    }

    return result;
}

int main()
{
  auto result = stringData<3ul, 3ul>("123", "123");
  return 0;
}