//#pragma once

#ifndef MATH_FUNCS_DLL
#define MATH_FUNCS_DLL

#include <stdexcept>
#include <memory>
#include <iostream>
#include "MathFuncExtended.h"

using namespace std;

namespace MathFuncs
{
  // Generate GUIDs from VisualStudio Tools/Create Guid menu.

  // {41BE0735-7846-41BC-95F6-5BCC5A2068DC}
  static const GUID IID_ICalculator =
  { 0x41be0735, 0x7846, 0x41bc, { 0x95, 0xf6, 0x5b, 0xcc, 0x5a, 0x20, 0x68, 0xdc } };

  BSTR ConcatBSTRs(const BSTR& pOne, const BSTR& pTwo);

  // http://stackoverflow.com/questions/4741035/how-do-i-dllexport-a-c-class-for-use-in-a-c-sharp-application
  struct ICalculator : public IUnknown
  {
    // Add functions, they should be virtual and __stdcall
    STDMETHOD_(double, Add)(DOUBLE x, DOUBLE y) = 0;
    STDMETHOD_(double, Subtract)(DOUBLE x, DOUBLE y) = 0;
    STDMETHOD_(double, RaiseToPower)(DOUBLE x, DOUBLE y) = 0;
    STDMETHOD(AppendInputToRandNumber)(BSTR* input) = 0;
    STDMETHOD(AppendStrings)(BSTR input1, BSTR input2, BSTR* output) = 0;
  };

  // {62A9EFC7-7FFE-4C9B-B807-3BEC802AAC26}
  static const GUID IID_IScientificCalculator =
  { 0x62a9efc7, 0x7ffe, 0x4c9b, { 0xb8, 0x7, 0x3b, 0xec, 0x80, 0x2a, 0xac, 0x26 } };

  class IScientificCalculator : public ICalculator
  {
    // Add functions, they should be virtual and __stdcall
    STDMETHOD_(double, Sin)(DOUBLE x) = 0;
    STDMETHOD_(double, Cos)(DOUBLE x) = 0;
    STDMETHOD_(double, Tan)(DOUBLE x) = 0;
  };

  class Calculator : public IScientificCalculator {
    volatile long refcount_;

  public:
    Calculator() : refcount_(1) {
    }

    STDMETHODIMP QueryInterface(REFIID guid, void **pObj) {
      if (pObj == NULL) {
        return E_POINTER;
      }
      else if (guid == IID_IUnknown) {
        *pObj = this;
        AddRef();
        return S_OK;
      }
      else if (guid == IID_IScientificCalculator) {
        *pObj = this;
        AddRef();
        return S_OK;
      }
      else if (guid == IID_ICalculator) {
        *pObj = this;
        AddRef();
        return S_OK;
      }
      else {
        // always set [out] parameter
        *pObj = NULL;
        return E_NOINTERFACE;
      }
    }

    STDMETHODIMP_(ULONG) AddRef() {
      return InterlockedIncrement(&refcount_);
    }

    STDMETHODIMP_(ULONG) Release() {
      ULONG result = InterlockedDecrement(&refcount_);
      if (result == 0) delete this;
      return result;
    }

    STDMETHODIMP_(DOUBLE) RaiseToPower(DOUBLE x, DOUBLE y);

    STDMETHODIMP_(DOUBLE) Sin(DOUBLE x);

    STDMETHODIMP_(DOUBLE) Cos(DOUBLE x);

    STDMETHODIMP_(DOUBLE) Tan(DOUBLE x);

    STDMETHODIMP AppendInputToRandNumber(BSTR* input);

    STDMETHODIMP AppendStrings(BSTR input1, BSTR input2, BSTR* output);

    STDMETHODIMP_(DOUBLE) Add(DOUBLE x, DOUBLE y);

    STDMETHODIMP_(DOUBLE) Subtract(DOUBLE x, DOUBLE y);
  };

  extern "C" __declspec(dllexport) LPUNKNOWN WINAPI CreateInstance() { return new Calculator(); }
  extern "C" { __declspec(dllexport) double Add(double a, double b); }
  extern "C" { __declspec(dllexport) double Subtract(double a, double b); }
  extern "C" { __declspec(dllexport) double Multiply(double a, double b); }
  extern "C" { __declspec(dllexport) double Divide(double a, double b); }
}

#endif

