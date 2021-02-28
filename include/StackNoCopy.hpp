//
// Created by lizer on 28.02.2021.
//
// Copyright 2021 elizavetamaikova

#ifndef TEMPLATE_STACKNOCOPY_HPP
#define TEMPLATE_STACKNOCOPY_HPP
#include "Stack.hpp"
#include <iostream>
#include <type_traits>


template <typename T>
class StackNoCopy {
 public:
  StackNoCopy()
  {
    _top = nullptr;
    if (!(std::is_move_constructible<T>::value ||
          std::is_move_assignable<T>::value))
      throw std::runtime_error("Error stack");
  }

  explicit StackNoCopy(const StackNoCopy& stack) = delete;

  StackNoCopy(StackNoCopy&& stack) = default;

  StackNoCopy& operator=(const StackNoCopy& stack) = delete;

  StackNoCopy& operator=(const StackNoCopy&& stack) noexcept
  {
    if (_top) _top = new Node<T>{std::move(stack), _top};
    else _top = new Node<T>{std::move(stack), nullptr};
  }


  ~StackNoCopy()
  {
    while (_top)
    {
      Node<T> *top = _top -> prev;
      delete _top;
      _top = top;
    }
  }

  template <typename... Arg>
  void push_emplace(Arg&&... value)
  {
    _top = new Node<T>{{std::forward<Arg>(value)...}, _top};
  }

  void push(T&& value)
  {
    _top = new Node<T>{std::move(value), _top};
  }

  T pop()
  {
    if (_top)
    {
      Node<T> *tmp = _top->prev;
      T data = std::move(_top->data);
      delete _top;
      _top = tmp;
      return data;
    }
    else
    {
      throw std::runtime_error("Stack empty");
    }
  }

  const T& head() const
  {
    if(!_top) throw std::runtime_error("Stack empty");
    return _top->data;
  }

 private:
  Node<T> *_top;
};

#endif  // TEMPLATE_STACKNOCOPY_HPP
