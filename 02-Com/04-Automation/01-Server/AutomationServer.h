#pragma once

class IMyMath : public IDispatch {
public :
	//pure virtual
	virtual HRESULT __stdcall SumOfTwoIntegers(int , int , int *) = 0;

	//pure virtual
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

const CLSID CLSID_MyMath = {<cls-id->}; // {stringised}

const IID IID_MyMath = {<guid-form>};
