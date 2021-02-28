//
// Created by lizer on 11.02.2021.
//
// Copyright 2021 elizavetamaikova

#ifndef TEMPLATE_STACK_HPP
#define TEMPLATE_STACK_HPP
#include <iostream>
#include <type_traits>

template <typename T>
struct Node
{
  T data;
  Node *prev;
};
template <typename T>
class Stack
{
 public:
  Stack()
  {
    _top = nullptr;
  }

  explicit Stack(const Stack&  stack) = delete;

  Stack(Stack&& stack) = default;

  Stack& operator=(Stack&& stack) = default;

  Stack& operator=(Stack& stack) = delete;

  ~Stack()
  {
    while (_top)
    {
      Node<T> *top = _top->prev;
      delete _top;
      _top = top;
    }
  };

  void push(T&& value)
  {
    _top = new Node<T> {std::move(value), _top};
  }

  void push(const T& value)
  {
    _top = new Node<T> {std::move(value), _top};
  }

  void pop()
  {
    if (_top)
    {
      Node<T> *tmp = _top->prev;
      delete _top;
      _top = tmp;
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

#endif  // TEMPLATE_STACK_HPP
