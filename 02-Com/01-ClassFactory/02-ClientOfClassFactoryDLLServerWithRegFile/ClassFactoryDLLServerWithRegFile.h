#pragma once

class ISum : public IUnknown
{
public : 
	virtual HRESULT __stdcall SumOfTwoIntegers(int,int,int*)=0;
};

class ISubstract : public IUnknown
{
public :
	virtual HRESULT __stdcall SubstractionOfTwoIntegers(int, int, int*) = 0;
};

// {EA3D3E04-2F1B-4E54-8E8A-871BE06D067B}
const CLSID CLSID_SumSubstract = { 0xea3d3e04, 0x2f1b, 0x4e54, 0x8e, 0x8a, 0x87, 0x1b, 0xe0, 0x6d, 0x6, 0x7b };

// {94248ECA-86B3-4A90-9DAB-E969BE8B62A8}
const IID IID_ISum = { 0x94248eca, 0x86b3, 0x4a90, 0x9d, 0xab, 0xe9, 0x69, 0xbe, 0x8b, 0x62, 0xa8};

// {6641FCB9-5D50-429E-9967-AAD944C0F5BD}
const IID IID_ISubstract = { 0x6641fcb9, 0x5d50, 0x429e, 0x99, 0x67, 0xaa, 0xd9, 0x44, 0xc0, 0xf5, 0xbd };
