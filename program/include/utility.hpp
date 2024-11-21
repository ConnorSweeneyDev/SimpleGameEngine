#pragma once

namespace cse::object
{
  enum struct Call_action
  {
    NONE,
    REMOVE
  };
  template <typename Type = void, typename Callable>
  void call_for_all(Callable callable, const Call_action action = Call_action::NONE);
}

#include "utility.inl"
