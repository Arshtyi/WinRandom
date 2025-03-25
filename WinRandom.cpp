#include "WinRandom.h"
#include <stdexcept>
#include <string>
#include <cstdint>

WinRandom::WinRandom() : isInitialized(false), hAlgorithm(NULL)
{
    // 初始化加密随机数生成器
    NTSTATUS status = BCryptOpenAlgorithmProvider(
        &hAlgorithm,
        BCRYPT_RNG_ALGORITHM,
        NULL,
        0);

    if (!BCRYPT_SUCCESS(status))
    {
        throw std::runtime_error("无法初始化随机数生成器，错误码: " + std::to_string(status));
    }

    isInitialized = true;
}

WinRandom::~WinRandom()
{
    if (hAlgorithm)
    {
        BCryptCloseAlgorithmProvider(hAlgorithm, 0);
        hAlgorithm = NULL;
    }
}

int WinRandom::GetRandomInt()
{
    int value;
    FillRandomBytes(reinterpret_cast<BYTE *>(&value), sizeof(value));
    return value;
}

int WinRandom::GetRandomInt(int min, int max)
{
    if (min > max)
    {
        throw std::invalid_argument("最小值不能大于最大值");
    }

    // 计算范围并确保不溢出
    uint64_t range = static_cast<uint64_t>(max) - min + 1;

    // 使用拒绝采样确保均匀分布
    uint32_t raw;
    uint32_t limit = (UINT32_MAX - (UINT32_MAX % static_cast<uint32_t>(range)));

    do
    {
        FillRandomBytes(reinterpret_cast<BYTE *>(&raw), sizeof(raw));
    } while (raw >= limit);

    return min + (raw % static_cast<uint32_t>(range));
}

double WinRandom::GetRandomDouble()
{
    uint64_t value;
    FillRandomBytes(reinterpret_cast<BYTE *>(&value), sizeof(value));

    // 生成 [0, 1) 范围的双精度浮点数
    // 取高52位作为小数部分
    constexpr uint64_t mask = (1ULL << 52) - 1;
    constexpr double norm = 1.0 / (1ULL << 52);

    return (value & mask) * norm;
}

double WinRandom::GetRandomDouble(double min, double max)
{
    if (min > max)
    {
        throw std::invalid_argument("最小值不能大于最大值");
    }

    return min + GetRandomDouble() * (max - min);
}

std::vector<BYTE> WinRandom::GetRandomBytes(size_t count)
{
    std::vector<BYTE> buffer(count);
    FillRandomBytes(buffer.data(), count);
    return buffer;
}

void WinRandom::FillRandomBytes(BYTE *buffer, size_t bufferSize)
{
    if (!isInitialized)
    {
        throw std::runtime_error("随机数生成器未初始化");
    }

    NTSTATUS status = BCryptGenRandom(
        hAlgorithm,
        buffer,
        static_cast<ULONG>(bufferSize),
        0);

    if (!BCRYPT_SUCCESS(status))
    {
        throw std::runtime_error("生成随机数失败，错误码: " + std::to_string(status));
    }
}