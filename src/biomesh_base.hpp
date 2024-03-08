
#ifndef BIOMESH_BASE_HPP
#define BIOMESH_BASE_HPP

#include <biomesh_config.hpp>
#include <cassert>
#include <cstdio>
#include <string>

/* Utility macros. */
#ifdef BIOMESH_ENABLE_DEBUG
#define BIOMESH_ASSERT(c) assert (c == 1)
#define BIOMESH_LDEBUG(mpirank, format, ...)                                  \
  do                                                                          \
    {                                                                         \
      std::string message = "[biomesh %d] " + std::string (format);           \
      printf (message.c_str (), mpirank, ##__VA_ARGS__);                      \
    }                                                                         \
  while (0)
#else
#define BIOMESH_ASSERT(c) ((void)(0))
#define BIOMESH_LDEBUG(mpirank, fmt, ...) ((void)(0))
#endif

#endif