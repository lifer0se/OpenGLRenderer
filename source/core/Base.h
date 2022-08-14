#ifndef BASE_CLASS_H
#define BASE_CLASS_H

#define BIND_EVENT(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#endif
