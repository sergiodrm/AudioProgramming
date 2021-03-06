#pragma once

struct SInputCode
{
  enum EKey : int
  {
    InvalidKey = -1,
    W, A, S, D, Up, Down, Right, Left, Space, Escape
  };

  enum EAction : int
  {
    InvalidAction = -1,
    Press, Release, Maintain
  };

  static int GetKeyCode(EKey _key);
  static EKey GetKeyCode(int _key);
  static int GetActionCode(EAction _action);
  static EAction GetActionCode(int _action);
};