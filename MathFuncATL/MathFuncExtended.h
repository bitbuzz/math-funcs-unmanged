
//////////////////////////////////////////////////////////////////
// Instructions for linking this .dll to other external .dll's. //
//////////////////////////////////////////////////////////////////
//
// Linking isn't done directly against a DLL, links are done against the LIB produced by the DLL.
// A LIB provides symbols and other necessary data to either include a library in your code(static linking) 
// or refer to the DLL(dynamic linking).
//
// Make sure to have the.lib, .dll, and.h.
//
// To link against a.lib:
// Project->Properties->Configuration Properties->Linker->Input->Additional Dependencies > e.g.MathFuncATL.lib
//
// Specify the path to the.lib:
// Project->Properties->Configuration Properties->Linker->General->Additional Library Directories > e.g.$(SolutionDir)MathFuncATL
//
// Specify the location of the.h:
// Project->Properties->Configuration Properties->General->Additional Include Directories->e.g.$(SolutionDir)MathFuncATL
//
// Use build events to copy the.dll to the Debug / Release directories :
// Build Events->Post - Build Events ->
// Command Line : XCOPY "$(SolutionDir)MathFuncATL\*.DLL" "$(TargetDir)" / D / K / Y
// Description : Copy DLLs to Target Directory
//
// Not in this sln / project, but in the referecing project, you may have to set 
// Project->Properties->Configuration Properties->Linker->Register Output equal to No, if the project doesn't compile.
//
// Usage:
// std::unique_ptr<MathFuncATL::MathFuncExtended> mathExt(new MathFuncATL::MathFuncExtended());
// m_answer = mathExt->SomeFunction();

//#pragma once

#ifndef MATH_FUNC_EXTENDED
#define MATH_FUNC_EXTENDED

#include <windows.h>
#include <objbase.h>

using namespace std;

namespace MathFuncATL
{
  class __declspec(dllexport) MathFuncExtended
  {
  private:
    const DOUBLE PI = 3.14159265359;
    DOUBLE DegreesToRadians(DOUBLE x);
    DOUBLE RadiansToDegrees(DOUBLE x);
  public:
    MathFuncExtended();
    ~MathFuncExtended();
    DOUBLE GetSin(DOUBLE x);
    DOUBLE GetCos(DOUBLE x);
    DOUBLE GetTan(DOUBLE x);
  };
}

#endif
