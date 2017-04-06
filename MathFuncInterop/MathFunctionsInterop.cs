using System;
using System.Runtime.InteropServices;

namespace MathFuncInterop
{
	[ComImport]
	[Guid("41BE0735-7846-41BC-95F6-5BCC5A2068DC")]
	[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
	public interface ICalculator
	{
		[PreserveSig]
		double Add(double a, double b);

		[PreserveSig]
		double Subtract(double a, double b);

		[PreserveSig]
		double RaiseToPower(double a, double b);

		[PreserveSig]
		double GetAnswer();

		//[return: MarshalAs(UnmanagedType.BStr)]
		//string GetString([MarshalAs(UnmanagedType.BStr)] string s);
		void GetString([MarshalAs(UnmanagedType.BStr)]ref string input);

		void Clear();

		void ThrowError();
	}

	[ComImport]
	[Guid("62A9EFC7-7FFE-4C9B-B807-3BEC802AAC26")]
	[InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
	public interface IScientificCalculator : ICalculator
	{
		[PreserveSig]
		double AddOne(double a);
	}

	public class CalculatorFactory
	{
		[DllImport("MathFuncDLL.dll")]
		static extern ICalculator CreateInstance();

		public ICalculator CreateCalculator()
		{
			return CreateInstance();
		}
	}

	internal static class UnsafeNativeMethods
	{
		const string _dllLocation = "MathFuncDll.dll";

		[DllImport(_dllLocation, CallingConvention = CallingConvention.Cdecl)]
		public static extern double Subtract(double a, double b);

		[DllImport(_dllLocation, CallingConvention = CallingConvention.Cdecl)]
		public static extern double Add(double a, double b);

		[DllImport(_dllLocation, CallingConvention = CallingConvention.Cdecl)]
		public static extern double Multiply(double a, double b);

		[DllImport(_dllLocation, CallingConvention = CallingConvention.Cdecl)]
		public static extern double Divide(double a, double b);
	}

	public static class MathFunctionsInterop
	{
		public static double SubtractNumbers(double a, double b)
		{
			return UnsafeNativeMethods.Subtract(a, b);
		}

		public static double AddNumbers(double a, double b)
		{
			return UnsafeNativeMethods.Add(a, b);
		}

		public static double MultiplyNumbers(double a, double b)
		{
			return UnsafeNativeMethods.Multiply(a, b);
		}

		public static double DivideNumbers(double a, double b)
		{
			return UnsafeNativeMethods.Divide(a, b);
		}
	}
}
