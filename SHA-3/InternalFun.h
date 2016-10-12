#ifndef INTERNAL_FUN_H
#define INTERNAL_FUN_H

#include <string>
#include <bitset>

#define stateSize 1600
using std::string ;
using std::bitset ;

typedef bitset<stateSize> Binary ;

Binary internalFun(Binary stateVar) ;
Binary roundFun(Binary stateVar, bitset<64> singleRC) ;
void theta(bitset<64> a[][5]);
void rho(bitset<64> a[][5]);
void pi(bitset<64> a[][5]);
void xi(bitset<64> a[][5]);

#endif 