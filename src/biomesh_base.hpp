
#ifndef BIOMESH_BASE_HPP
#define BIOMESH_BASE_HPP

#include <biomesh_config.hpp>
#include <cassert>

/* Utility macros. */
#ifdef BIOMESH_ENABLE_DEBUG
#define BIOMESH_ASSERT(c) assert(c == 1) 
#else
#define BIOMESH_ASSERT(c) ((void) (0))
#endif

#endif