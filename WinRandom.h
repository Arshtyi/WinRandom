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

    WinRandom(const WinRandom &) = delete;
    WinRandom &operator=(const WinRandom &) = delete;

    int GetRandomInt();

    int GetRandomInt(int min, int max);

    double GetRandomDouble();

    double GetRandomDouble(double min, double max);

    std::vector<BYTE> GetRandomBytes(size_t count);

    void FillRandomBytes(BYTE *buffer, size_t bufferSize);

private:
    BCRYPT_ALG_HANDLE hAlgorithm;
    bool isInitialized;
};

#endif // WIN_RANDOM_H