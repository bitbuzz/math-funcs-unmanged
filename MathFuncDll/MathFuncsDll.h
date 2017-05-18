#ifndef MathFuncsDll
#define MathFuncsDll

#include <stdexcept>

using namespace std;

namespace MathFuncs
{
	// Generate GUIDs from VisualStudio Tools/Create Guid menu.

	// {41BE0735-7846-41BC-95F6-5BCC5A2068DC}
	static const GUID IID_ICalculator =
	{ 0x41be0735, 0x7846, 0x41bc, { 0x95, 0xf6, 0x5b, 0xcc, 0x5a, 0x20, 0x68, 0xdc } };

	// http://stackoverflow.com/questions/4741035/how-do-i-dllexport-a-c-class-for-use-in-a-c-sharp-application
	struct ICalculator : public IUnknown
	{
		// Add your own functions here they should be virtual and __stdcall
		STDMETHOD_(double, Add)(DOUBLE a, DOUBLE b) = 0;
		STDMETHOD_(double, Subtract)(DOUBLE a, DOUBLE b) = 0;
		STDMETHOD_(double, GetAnswer)() = 0;
		STDMETHOD(AppendString)(BSTR* input) = 0;
		STDMETHOD(Clear)() = 0;
	};

	// {62A9EFC7-7FFE-4C9B-B807-3BEC802AAC26}
	static const GUID IID_IScientificCalculator =
	{ 0x62a9efc7, 0x7ffe, 0x4c9b, { 0xb8, 0x7, 0x3b, 0xec, 0x80, 0x2a, 0xac, 0x26 } };

	interface IScientificCalculator : public ICalculator
	{		
		// Add your own functions here they should be virtual and __stdcall
		STDMETHOD_(double, AddOne)(DOUBLE a) = 0;
		STDMETHOD_(double, RaiseToPower)(DOUBLE a, DOUBLE b) = 0;
	};

	class Calculator : public IScientificCalculator {
		volatile long refcount_;

	private:
		double _answer;

	public:
		Calculator() : refcount_(1) {
		 _answer = 3; 
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

		STDMETHODIMP Clear() {
			_answer = 0;
			return SUCCEEDED(0);
		}

		STDMETHODIMP AppendString(BSTR* input);

		STDMETHODIMP_(DOUBLE) GetAnswer() {
			return _answer;
		}

		STDMETHODIMP_(DOUBLE) Add(DOUBLE a, DOUBLE b) {
			_answer = (DOUBLE)(a + b);
			return _answer;
		}

		STDMETHODIMP_(DOUBLE) Subtract(DOUBLE a, DOUBLE b) {
			_answer = (DOUBLE)(a - b);
			return _answer;
		}

		STDMETHODIMP_(DOUBLE) RaiseToPower(DOUBLE a, DOUBLE b) {
			_answer = std::pow(a, b);
			return _answer;
			}

		STDMETHODIMP_(DOUBLE) IScientificCalculator::AddOne(DOUBLE a){
			double d = 1;
			double result = a + 1;
			return result;
		}
	};

	extern "C" __declspec(dllexport) LPUNKNOWN WINAPI CreateInstance(){ return new Calculator(); }
	extern "C" { __declspec(dllexport) double Add(double a, double b); }
	extern "C" { __declspec(dllexport) double Subtract(double a, double b); }
	extern "C" { __declspec(dllexport) double Multiply(double a, double b); }
	extern "C" { __declspec(dllexport) double Divide(double a, double b); }
}

#endif

