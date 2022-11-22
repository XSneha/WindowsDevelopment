#pragma once

class IMyMath : public IDispatch {
public :
	//pure virtual
	virtual HRESULT __stdcall SumSumOfTwoIntegers(int , int , int *) = 0;

	//pure virtual
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

//new : {B487D653-A5B5-484D-9E1D-F09EC487560B}
//old : {94248ECA-86B3-4A90-9DAB-E969BE8B62A8}
//const CLSID CLSID_MyMath = { 0x94248eca, 0x86b3, 0x4a90, 0x9d, 0xab, 0xe9, 0x69, 0xbe, 0x8b, 0x62, 0xa8 }; //{<cls-id->}; // {stringised}
const CLSID CLSID_MyMath = { 0xb487d653, 0xa5b5, 0x484d, 0x9e, 0x1d, 0xf0, 0x9e, 0xc4, 0x87, 0x56, 0xb }; //{<cls-id->}; // {stringised}

//new : {626F95E1-44B2-4FC5-8F8F-D1DC7613EA18}
//old : {6641FCB9-5D50-429E-9967-AAD944C0F5BD}
//const IID IID_IMyMath = { 0x6641fcb9, 0x5d50, 0x429e, 0x99, 0x67, 0xaa, 0xd9, 0x44, 0xc0, 0xf5, 0xbd };//{<guid-form>};
const IID IID_IMyMath = { 0x626f95e1, 0x44b2, 0x4fc5, 0x8f, 0x8f, 0xd1, 0xdc, 0x76, 0x13, 0xea, 0x18 };//{<guid-form>};