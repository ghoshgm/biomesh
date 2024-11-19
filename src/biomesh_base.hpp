
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
#define BIOMESH_DCOMP(a, b) std::fabs (a - b) < 1e-8

#ifdef BIOMESH_ENABLE_DEBUG
#define BIOMESH_ASSERT(c) assert (c == true)
#define BIOMESH_LDEBUG(mpirank, format, ...)                                  \
  do                                                                          \
    {                                                                         \
      std::string message                                                     \
          = "[BIOMESH %d DEBUG] " + std::string (format) + "\n";              \
      printf (message.c_str (), mpirank, ##__VA_ARGS__);                      \
    }                                                                         \
  while (0)
#else
#define BIOMESH_ASSERT(c) ((void)(0))
#define BIOMESH_LDEBUG(mpirank, format, ...) ((void)(0))
#endif

#define BIOMESH_LINFO(mpirank, format, ...)                                   \
  do                                                                          \
    {                                                                         \
      std::string message                                                     \
          = "[BIOMESH %d INFO] " + std::string (format) + "\n";               \
      printf (message.c_str (), mpirank, ##__VA_ARGS__);                      \
    }                                                                         \
  while (0)

#define BIOMESH_TRACE(mpirank, format, ...)                                   \
  do                                                                          \
    {                                                                         \
      std::string message                                                     \
          = "[BIOMESH %d TRACE] " + std::string ("FILE:" __FILE__) + " "      \
            + std::string ("LINE:") + std::to_string (__LINE__) + " "         \
            + std::string ("FUNCTION:") + std::string (__PRETTY_FUNCTION__)   \
            + " " + std::string (format) + "\n";                              \
      printf (message.c_str (), mpirank, ##__VA_ARGS__);                      \
    }                                                                         \
  while (0)

#endif