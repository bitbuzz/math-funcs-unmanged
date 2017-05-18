// MathFuncDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MathFuncsDll.h"

namespace MathFuncs
{
	double Add(double a, double b)
	{
		return a + b;
	}
	double Subtract(double a, double b)
	{
		return a - b;
	}
	double Multiply(double a, double b)
	{
		return a * b;
	}
	double Divide(double a, double b)
	{
		if (b == 0)
			throw invalid_argument("b cannot be zero!");
		return a / b;
	}

	STDMETHODIMP Calculator::AppendString(BSTR * input)
	{
		HRESULT hr = S_OK;

		// Make sure the input param has a value.
		//ATLENSURE(NULL != *input);

		// Initialize random seed Generate number 
		// between 1 and 100 and convert to bstr.
		srand(time(NULL));
		int randNumber = rand() % 100 + 1;
		
		wstring sRandNumber = std::to_wstring(randNumber);
		BSTR bstrNumber = ::SysAllocStringLen(sRandNumber.c_str(), sRandNumber.length());

		CComBSTR preFix;
		CComBSTR postFix(L"brick in the wall, id.");

		preFix.Attach(*input);
		hr = preFix.Append(postFix);
		hr = preFix.AppendBSTR(bstrNumber);
		
		::SysFreeString(*input);
		::SysFreeString(bstrNumber);

		if (SUCCEEDED(hr))
		{
			*input = preFix.Detach();
		}
		else
		{
			return E_FAIL;
		}
		
		return hr;
	}
}