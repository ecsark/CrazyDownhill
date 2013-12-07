#ifndef SIGLETON_HPP_
# define SIGLETON_HPP_

template<typename T>
class Singleton
{

public:

  static T& Instance()
  {
    static T i;
    return i;
  }

};

#endif
