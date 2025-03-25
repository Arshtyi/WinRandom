#ifndef WIN_RANDOM_H
#define WIN_RANDOM_H

#include <windows.h>
#include <bcrypt.h>
#include <vector>
#include <stdexcept>

// #pragma comment(lib, "bcrypt.lib")

class WinRandom
{
public:
    WinRandom();

    ~WinRandom();
    // 禁用拷贝构造函数和赋值运算符
    WinRandom(const WinRandom &) = delete;
    WinRandom &operator=(const WinRandom &) = delete;
    // 生成单个随机整数
    int GetRandomInt();
    // 生成范围在[min, max]的随机整数
    int GetRandomInt(int min, int max);
    // 生成范围在[0, 1)的随机浮点数
    double GetRandomDouble();
    // 生成范围在[min, max)的随机浮点数
    double GetRandomDouble(double min, double max);
    // 生成随机字节
    std::vector<BYTE> GetRandomBytes(size_t count);
    // 填充随机数到数组
    void FillRandomBytes(BYTE *buffer, size_t bufferSize);

private:
    BCRYPT_ALG_HANDLE hAlgorithm;
    bool isInitialized;
};

#endif // WIN_RANDOM_H