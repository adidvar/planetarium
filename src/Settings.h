#pragma once

#define SHARED
#if ( defined(_WIN32) || defined(_WIN64)) && defined(SHARED)
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#else
#define EXPORT
#define IMPORT
#endif