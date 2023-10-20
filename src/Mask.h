/*
 * Mask.h
 *
 *  Created on: 17 sept. 2023
 *      Author: Yves
 */

#ifndef MASK_H_
#define MASK_H_
using namespace std;

#include <cstddef>
#include <cstdint>
#include <compare>
#include <iostream>
#include <array>
#include "Tools.h"

template< size_t s=Tools::sizeMax>
class Mask final {
	static const size_t lgWord=(sizeof(uint64_t)*8);
	static const size_t lgMask=(s+lgWord-1)/lgWord;

	array<uint64_t, lgMask> mask;
public:
	Mask():mask({0}){}
	Mask(size_t dec):mask({0}){
		setBit(dec);
	}
	void setBit(size_t dec)
	{
		size_t ind=dec/lgWord;
		size_t mod=dec%lgWord;
		mask[ind] |= 1ull <<mod;
	}
	bool isBit(size_t dec) const
	{
		size_t ind=dec/lgWord;
		size_t mod=dec%lgWord;
		return (mask[ind] &( 1ull<<mod)) != 0;
	}
	bool isBits( const Mask & m) const
	{
		for ( int i = 0 ; i < (int)mask.size() ; i++)
		{
			if ( (this->mask[i] & m.mask[i]) != 0)
				return true;
		}
		return false;
	}
	string to_string() const
	{
		stringstream ss;
		for ( int i=0 ; i < (int)s ; i++)
		{
			if ( isBit(i) )
				ss << i<<",";
		}
		return ss.str();
	}
	void reset()
	{
		mask={};
	}
	~Mask(){}
	Mask& operator=(const Mask &other){
		this->mask = other.mask;
		return *this;
	}
	bool operator<(const Mask &other) const{
		return this->mask < other.mask;
	}
};

#endif /* MASK_H_ */
