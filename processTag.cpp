// processTag.cpp - implementation for tag processing

#include <iostream>
#include "processTag.h"

int tag(int n)
{
   if (n <= 2) 
      return 1;
   else 
      return tag(n-1) + tag(n-2);
}
