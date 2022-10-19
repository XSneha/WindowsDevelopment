#pragma once

class IMyMath : public IDispatch {
public:
	//pure virtual
	virtual HRESULT __stdcall SumSumOfTwoIntegers(int, int, int*) = 0;

	//pure virtual
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

// {94248ECA-86B3-4A90-9DAB-E969BE8B62A8}
const CLSID CLSID_MyMath = { 0x94248eca, 0x86b3, 0x4a90, 0x9d, 0xab, 0xe9, 0x69, 0xbe, 0x8b, 0x62, 0xa8 }; //{<cls-id->}; // {stringised}

// {6641FCB9-5D50-429E-9967-AAD944C0F5BD}
const IID IID_IMyMath = { 0x6641fcb9, 0x5d50, 0x429e, 0x99, 0x67, 0xaa, 0xd9, 0x44, 0xc0, 0xf5, 0xbd };//{<guid-form>};