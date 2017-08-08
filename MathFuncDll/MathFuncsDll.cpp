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

  BSTR ConcatBSTRs(const BSTR& pOne, const BSTR& pTwo)
  {
    // Create a BSTR...
    // BSTR sample = SysAllocString(L"This is sample ");
    _bstr_t pWrapOne = pOne;
    _bstr_t pWrapTwo = pTwo;
    _bstr_t pConcat = pWrapOne + " " + pWrapTwo;
    return pConcat;
  }

  STDMETHODIMP Calculator::AppendInputToRandNumber(BSTR * input)
  {
    HRESULT hr = S_OK;

    // Make sure the input param has a value.
    ATLENSURE(NULL != *input);

    // Initialize random seed Generate number 
    // between 1 and 100 and convert to bstr.
    srand(time(NULL));
    int randNumber = rand() % 100 + 1;
    m_answer = randNumber;

    wstring sRandNumber = std::to_wstring(randNumber);
    BSTR bstrNumber = ::SysAllocStringLen(sRandNumber.c_str(), sRandNumber.length());

    CComBSTR preFix(*input);
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

  STDMETHODIMP Calculator::AppendStrings(BSTR input1, BSTR input2, BSTR * output)
  {
    HRESULT hr = S_OK;

    ::SysFreeString(*output);
    BSTR concatBstr = ConcatBSTRs(input1, input2);
    CComBSTR concat;
    concat.Attach(concatBstr);
    *output = concat.Detach();
    return hr;
  }
}