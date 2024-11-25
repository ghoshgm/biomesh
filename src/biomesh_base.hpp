
#ifndef BIOMESH_BASE_HPP
#define BIOMESH_BASE_HPP

#include <biomesh_config.hpp>
#include <biomesh_stopwatch.hpp>

#include <cassert>
#include <cstdio>
#include <iostream>
#include <limits>
#include <string>

/* Utility macros. */
#define BIOMESH_SUCCESS 1
#define BIOMESH_ERROR 0

/* Tolerance for comparing two doubles. */
#define BIOMESH_DCOMP(a, b) (std::fabs (a - b) < 1e-8)

#ifdef BIOMESH_ENABLE_DEBUG
#define BIOMESH_ASSERT(c) assert (c == true)
#define BIOMESH_LDEBUG(format)                                                \
  do                                                                          \
    {                                                                         \
      std::cout << "[BIOMESH DEBUG] " << std::string (format) << std::endl;   \
    }                                                                         \
  while (0)
#else
#define BIOMESH_ASSERT(c) ((void)(0))
#define BIOMESH_LDEBUG(format) ((void)(0))
#endif

#define BIOMESH_LINFO(format)                                                 \
  do                                                                          \
    {                                                                         \
      std::cout << "[BIOMESH INFO] " << std::string (format) << std::endl;    \
    }                                                                         \
  while (0)
#endif