
#if !defined(_LAYER_H)
#define _LAYER_H

#include "Node.h"

class Layer : public Node
{
  private:
    /* data */
  public:
    Layer();
    ~Layer();
    CREATE_FUN(Layer);
    virtual bool init();
};




#endif // _LAYER_H
