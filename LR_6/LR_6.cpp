#include <iostream>
#include <string>
#include <eccrypto.h>
#include <integer.h>
#include <osrng.h>
#include <hex.h>
#include <queue.h>

using namespace CryptoPP;
using namespace std;

// Тип точки ЕК
struct ECPoint
{
    Integer X;
    Integer Y;
};
string decToBin(long dec) {
    string res = "";
    while (dec > 0) {
        res = to_string(dec%2) + res;
        dec /= 2;
    }
    return res;
}

// Отримати базову точку G
ECPoint BasePointGGet(const DL_GroupParameters_EC<ECP>& params)
{
    const ECP::Point& G = params.GetSubgroupGenerator();
    ECPoint result;
    result.X = G.x;
    result.Y = G.y;
    return result;
}

// Створити точку ЕК
ECPoint ECPointGen(const Integer& x, const Integer& y)
{
    ECPoint result;
    result.X = x;
    result.Y = y;
    return result;
}

// Перевірка, чи належить точка кривій
bool IsOnCurveCheck(const ECPoint& a, const ECP& curve)
{
    ECP::Point point(a.X, a.Y);
    return curve.VerifyPoint(point);
}

// Додавання точок ЕК
ECPoint AddECPoints(const ECPoint& a, const ECPoint& b, const DL_GroupParameters_EC<ECP>& params)
{
    ECP::Point result(a.X + b.X, a.Y + b.Y);
    ECPoint resultPoint;
    resultPoint.X = result.x;
    resultPoint.Y = result.y;
    return resultPoint;
}

// Подвійна точка ЕК
ECPoint DoubleECPoints(const ECPoint& a, const DL_GroupParameters_EC<ECP>& params)
{
    ECP::Point result(a.X + a.X, a.Y + a.Y);
    ECPoint resultPoint;
    resultPoint.X = result.x;
    resultPoint.Y = result.y;
    return resultPoint;
}

// Множення точки на скаляр
ECPoint ScalarMult(const Integer& k, const ECPoint& a, const DL_GroupParameters_EC<ECP>& params)
{
    ECPoint result;
    result.X = a.X;
    result.Y = a.Y;
    for (int i = 0; i < k; i++)
    {
        result.X *= a.X;
        result.Y *= a.Y;
    }
    
    return result;
}

// Серіалізація точки
string ECPointToString(const ECPoint& point)
{
    string result;
    long X = point.X.ConvertToLong();
    long Y = point.Y.ConvertToLong();

    result += decToBin(X);
    result += ",";
    result += decToBin(Y);
    return result;
}

// Десеріалізація точки
ECPoint StringToECPoint(const string& s)
{
    ECPoint result;
    size_t pos = s.find(",");
    string binX = s.substr(0, pos).c_str();
    string binY = s.substr(pos + 1).c_str();
    result.X = Integer(s.substr(0, pos).c_str());
    result.Y = Integer(s.substr(pos + 1).c_str());
    return result;
}

// Вивід точки
void PrintECPoint(const ECPoint& point)
{
    std::cout << "X: " << point.X << std::endl;
    std::cout << "Y: " << point.Y << std::endl;
}

int main()
{
    // Встановлення параметрів кривої
    AutoSeededRandomPool rng;
    DL_GroupParameters_EC<ECP> params = ECP::ASN1::secp256r1();

    // Отримання базової точки G
    ECPoint G = BasePointGGet(params);

    // Випадкові числа
    Integer k(rng, 256);
    Integer d(rng, 256);

    // Обчислення H1 і H2
    ECPoint H1 = ScalarMult(d, G, params);
    ECPoint H2 = ScalarMult(k, H1, params);

    // Обчислення H3 і H4
    ECPoint H3 = ScalarMult(k, G, params);
    ECPoint H4 = ScalarMult(d, H3, params);

    // Перевірка рівності H2 і H4
    bool result = (H2.X == H4.X) && (H2.Y == H4.Y);

    // Вивід результату
    std::cout << "Result: " << (result ? "true" : "false") << std::endl;

    return 0;
}