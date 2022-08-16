#ifndef PCH_H
#define PCH_H

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cerrno>

#include "Logger.h"

#define BIND_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#endif
