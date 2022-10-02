// git-lfs-lib.h : Include file for standard system include files,
// or project specific include files.

#pragma once



#if defined (_WIN32)
	#if defined(GIT_LFS_LIB_EXTPORTS)
		#define  GIT_LFS_LIB_DLL_EXPORT __declspec(dllexport)
	#else
		#define  GIT_LFS_LIB_DLL_EXPORT __declspec(dllimport)
	#endif /* MyLibrary_EXPORTS */
#else /* defined (_WIN32) */
	#define MYLIB_EXPORT
#endif





// TODO: Reference additional headers your program requires here.
