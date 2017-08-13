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
    double Add(double x, double y);

    [PreserveSig]
    double Subtract(double x, double y);

    [PreserveSig]
    void AppendInputToRandNumber([In, Out] ref string input);

    [PreserveSig]
    void AppendStrings([In] string input, [In] string input2, [In, Out] ref String output);
  }

  [ComImport]
  [Guid("62A9EFC7-7FFE-4C9B-B807-3BEC802AAC26")]
  [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
  public interface IScientificCalculator : ICalculator
  {
    [PreserveSig]
    double RaiseToPower(double x, double y);

    [PreserveSig]
    double Sin(double x);

    [PreserveSig]
    double Cos(double x);

    [PreserveSig]
    double Tan(double x);
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
