//
// MATLAB Compiler: 6.0 (R2015a)
// Date: Fri Sep 11 12:56:01 2015
// Arguments: "-B" "macro_default" "-W" "cpplib:Detect_circles" "-T" "link:lib"
// "-d"
// "C:\Users\Dell\Desktop\Tree_project\Satellite-Image-Analyzer\Applications\Mat
// lab_lib\Detect_circles\for_testing" "-v"
// "C:\Users\Dell\Desktop\Tree_project\Satellite-Image-Analyzer\Applications\Mat
// lab_lib\Detect_circles.m" 
//

#include "stdafx.h"
#include <stdio.h>
#define EXPORTING_Detect_circles 1
#include "Detect_circles.h"

static HMCRINSTANCE _mcr_inst = NULL;


#if defined( _MSC_VER) || defined(__BORLANDC__) || defined(__WATCOMC__) || defined(__LCC__)
#ifdef __LCC__
#undef EXTERN_C
#endif
#include <windows.h>

static TCHAR path_to_dll[_MAX_PATH];

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, void *pv)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        if (GetModuleFileName(hInstance, path_to_dll, _MAX_PATH) == 0)
            return FALSE;
    }
    else if (dwReason == DLL_PROCESS_DETACH)
    {
    }
    return TRUE;
}
#endif
#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultPrintHandler(const char *s)
{
  return mclWrite(1 /* stdout */, s, sizeof(char)*strlen(s));
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

#ifdef __cplusplus
extern "C" {
#endif

static int mclDefaultErrorHandler(const char *s)
{
  int written = 0;
  size_t len = 0;
  len = strlen(s);
  written = mclWrite(2 /* stderr */, s, sizeof(char)*len);
  if (len > 0 && s[ len-1 ] != '\n')
    written += mclWrite(2 /* stderr */, "\n", sizeof(char));
  return written;
}

#ifdef __cplusplus
} /* End extern "C" block */
#endif

/* This symbol is defined in shared libraries. Define it here
 * (to nothing) in case this isn't a shared library. 
 */
#ifndef LIB_Detect_circles_C_API
#define LIB_Detect_circles_C_API /* No special import/export declaration */
#endif

LIB_Detect_circles_C_API 
bool MW_CALL_CONV Detect_circlesInitializeWithHandlers(
    mclOutputHandlerFcn error_handler,
    mclOutputHandlerFcn print_handler)
{
    int bResult = 0;
  if (_mcr_inst != NULL)
    return true;
  if (!mclmcrInitialize())
    return false;
  char *fname = "Detect_circles" ;
  
  if (!GetModuleFileName(GetModuleHandle(fname), path_to_dll, _MAX_PATH))
    return false;
    {
        mclCtfStream ctfStream = 
            mclGetEmbeddedCtfStream(path_to_dll);
        if (ctfStream) {
            bResult = mclInitializeComponentInstanceEmbedded(   &_mcr_inst,
                                                                error_handler, 
                                                                print_handler,
                                                                ctfStream);
            mclDestroyStream(ctfStream);
        } else {
            bResult = 0;
        }
    }  
    if (!bResult)
    return false;
  return true;
}

LIB_Detect_circles_C_API 
bool MW_CALL_CONV Detect_circlesInitialize(void)
{
  return Detect_circlesInitializeWithHandlers(mclDefaultErrorHandler, 
                                              mclDefaultPrintHandler);
}

LIB_Detect_circles_C_API 
void MW_CALL_CONV Detect_circlesTerminate(void)
{
  if (_mcr_inst != NULL)
    mclTerminateInstance(&_mcr_inst);
}

LIB_Detect_circles_C_API 
void MW_CALL_CONV Detect_circlesPrintStackTrace(void) 
{
  char** stackTrace;
  int stackDepth = mclGetStackTrace(&stackTrace);
  int i;
  for(i=0; i<stackDepth; i++)
  {
    mclWrite(2 /* stderr */, stackTrace[i], sizeof(char)*strlen(stackTrace[i]));
    mclWrite(2 /* stderr */, "\n", sizeof(char)*strlen("\n"));
  }
  mclFreeStackTrace(&stackTrace, stackDepth);
}


LIB_Detect_circles_C_API 
bool MW_CALL_CONV mlxDetect_circles(int nlhs, mxArray *plhs[], int nrhs, mxArray *prhs[])
{
  return mclFeval(_mcr_inst, "Detect_circles", nlhs, plhs, nrhs, prhs);
}

LIB_Detect_circles_CPP_API 
void MW_CALL_CONV Detect_circles(const mwArray& read_location)
{
  mclcppMlfFeval(_mcr_inst, "Detect_circles", 0, 0, 1, &read_location);
}

