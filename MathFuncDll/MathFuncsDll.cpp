// MathFuncDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MathFuncsDll.h"

namespace MathFuncs
{
  BSTR ConcatBSTRs(const BSTR& pOne, const BSTR& pTwo)
  {
    // Create a BSTR...
    // BSTR sample = SysAllocString(L"This is sample ");
    _bstr_t pWrapOne = pOne;
    _bstr_t pWrapTwo = pTwo;
    _bstr_t pConcat = pWrapOne + " " + pWrapTwo;
    return pConcat;
  }

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
    if (b == 0) {
      throw invalid_argument("b cannot be zero!");
      return -1;
    }
    return a / b;
  }

  // Calculator
  //
  HRESULT Calculator::AppendInputToRandNumber(BSTR * input)
  {
    HRESULT hr = S_OK;

    // Make sure the input param has a value.
    ATLENSURE(NULL != *input);

    // Initialize random seed Generate number 
    // between 1 and 100 and convert to bstr.
    srand(time(NULL));
    int randNumber = rand() % 100 + 1;

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

  HRESULT Calculator::AppendStrings(BSTR input1, BSTR input2, BSTR * output)
  {
    HRESULT hr = S_OK;

    ::SysFreeString(*output);
    BSTR concatBstr = ConcatBSTRs(input1, input2);
    CComBSTR concat;
    concat.Attach(concatBstr);
    *output = concat.Detach();
    return hr;
  }

  DOUBLE Calculator::Add(DOUBLE x, DOUBLE y) {
    return (DOUBLE)(x + y);
  }

  DOUBLE Calculator::Subtract(DOUBLE x, DOUBLE y) {
    return (DOUBLE)(x - y);
  }

  // IScientificCalculator
  //
  DOUBLE Calculator::RaiseToPower(DOUBLE x, DOUBLE y) {
    auto answer = std::pow(x, y);
    return answer;
  }

  DOUBLE Calculator::Sin(DOUBLE x) {
    //std::unique_ptr<MathFuncATL::MathFuncExtended> mathExt(new MathFuncATL::MathFuncExtended());
    //DOUBLE sin = mathExt->GetSin(x);
    auto answer = x + 1;
    return answer;
  }

  DOUBLE Calculator::Cos(DOUBLE x) {
    return std::cos(x);
  }

  DOUBLE Calculator::Tan(DOUBLE x) {
    return std::tan(x);
  }
}