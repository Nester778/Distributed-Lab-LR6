#pragma once
#include <iostream>
#include <cryptlib.h>
#include <string>
#include <eccrypto.h>
#include <integer.h>
#include <osrng.h>
#include <bitset>
#include <oids.h>

using namespace std;
using namespace CryptoPP;

struct ECPoint;
string decToBin(long dec);
ECPoint BasePointGGet(const DL_GroupParameters_EC<ECP>& params);
ECPoint ECPointGen(const Integer& x, const Integer& y);
bool IsOnCurveCheck(const ECPoint& a, const ECP& curve);
ECPoint AddECPoints(const ECPoint& a, const ECPoint& b, const DL_GroupParameters_EC<ECP>& params);
ECPoint DoubleECPoints(const ECPoint& a, const DL_GroupParameters_EC<ECP>& params);
ECPoint ScalarMult(const ECPoint& a, const DL_GroupParameters_EC<ECP>& params);
string ECPointToString(const ECPoint& point);
ECPoint StringToECPoint(const string& s);
void PrintECPoint(const ECPoint& point);