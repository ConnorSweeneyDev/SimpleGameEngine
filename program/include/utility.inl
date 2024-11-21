#pragma once

#include <iostream>
#include <type_traits>

#include "item.hpp"
#include "player.hpp"
#include "utility.hpp"

namespace cse::object
{
  template <typename Type, typename Callable> void call_for_all(Callable callable, Call_action action)
  {
    if constexpr (std::is_same<Type, void>::value)
    {
      for (auto &player : players) callable(player);
      for (auto &item : items) callable(item);
      switch (action)
      {
        case Call_action::REMOVE:
          players.clear();
          items.clear();
          break;

        default: break;
      }
    }
    else if constexpr (std::is_same<Type, Player>::value)
    {
      for (auto &player : players) callable(player);
      switch (action)
      {
        case Call_action::REMOVE: players.clear(); break;
        default: break;
      }
    }
    else if constexpr (std::is_same<Type, Item>::value)
    {
      for (auto &item : items) callable(item);
      switch (action)
      {
        case Call_action::REMOVE: items.clear(); break;
        default: break;
      }
    }
    else
      std::cout << "Invalid Type!" << std::endl;
  }
}
