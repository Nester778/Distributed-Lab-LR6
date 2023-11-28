#include <iostream>
#include "Wrapper.h"

using namespace CryptoPP;
using namespace std;

struct ECPoint
{
	Integer X;
	Integer Y;
};

int main()
{
	// Встановлення параметрів кривої
	AutoSeededRandomPool rng;
	DL_GroupParameters_EC<ECP> params = ASN1::secp256r1();

	// Отримання базової точки G
	ECPoint G = BasePointGGet(params);

	// Обчислення H1 і H2
	ECPoint H1 = ScalarMult(G, params);
	ECPoint H2 = ScalarMult(H1, params);

	// Обчислення H3 і H4
	ECPoint H3 = ScalarMult(G, params);
	ECPoint H4 = ScalarMult(H3, params);

	// Перевірка рівності H2 і H4
	bool result = (H2.X == H4.X) && (H2.Y == H4.Y);

	cout << "H1.X =" << H1.X << endl << "H1.Y =" << H1.Y << endl << endl;
	cout << "H2.X =" << H2.X << endl << "H2.Y =" << H2.Y << endl << endl;
	cout << "H3.X =" << H3.X << endl << "H3.Y =" << H3.Y << endl << endl;
	cout << "H4.X =" << H4.X << endl << "H4.Y =" << H4.Y << endl << endl;

	// Вивід результату
	std::cout << "Result: " << (result ? "true" : "false") << std::endl;

	return 0;
}