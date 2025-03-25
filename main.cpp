#include <iostream>
#include <iomanip>
#include <vector>
#include "WinRandom.h"

void PrintRandomIntegers(WinRandom &rng, int count, int min, int max)
{
    std::cout << "生成 " << count << " 个范围在 [" << min << ", " << max << "] 的随机整数:" << std::endl;

    for (int i = 0; i < count; ++i)
    {
        std::cout << rng.GetRandomInt(min, max) << " ";
        if ((i + 1) % 10 == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;
}

void PrintRandomDoubles(WinRandom &rng, int count, double min, double max)
{
    std::cout << "生成 " << count << " 个范围在 [" << min << ", " << max << ") 的随机浮点数:" << std::endl;

    std::cout << std::fixed << std::setprecision(6);
    for (int i = 0; i < count; ++i)
    {
        std::cout << rng.GetRandomDouble(min, max) << " ";
        if ((i + 1) % 5 == 0)
            std::cout << std::endl;
    }
    std::cout << std::endl;
}

void PrintRandomBytes(WinRandom &rng, int count)
{
    std::cout << "生成 " << count << " 个随机字节:" << std::endl;

    std::vector<BYTE> bytes = rng.GetRandomBytes(count);

    std::cout << std::hex << std::setfill('0');
    for (size_t i = 0; i < bytes.size(); ++i)
    {
        std::cout << std::setw(2) << static_cast<int>(bytes[i]) << " ";
        if ((i + 1) % 16 == 0)
            std::cout << std::endl;
    }
    std::cout << std::dec << std::endl;
}

int main()
{
    try
    {
        std::cout << "Windows 加密随机数生成器Demo" << std::endl;
        std::cout << std::string(60, '=') << std::endl;

        WinRandom rng;
        std::cout << "按Enter键继续..." << std::endl;
        std::cin.get();
        // 演示生成随机整数
        PrintRandomIntegers(rng, 20, 1, 100);

        // 演示生成随机浮点数
        PrintRandomDoubles(rng, 10, 0.0, 1.0);

        // 演示生成较大范围的随机浮点数
        PrintRandomDoubles(rng, 10, -100.0, 100.0);

        // 演示生成随机字节
        PrintRandomBytes(rng, 64);

        std::cout << "随机数生成完成!" << std::endl;
        std::cout << "按Enter键继续..." << std::endl;
        std::cin.get();
    }
    catch (const std::exception &e)
    {
        std::cerr << "错误: " << e.what() << std::endl;
        std::cout << "按Enter键继续..." << std::endl;
        std::cin.get();
        return 1;
    }

    return 0;
}