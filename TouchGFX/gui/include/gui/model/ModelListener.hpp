#ifndef MODELLISTENER_HPP
#define MODELLISTENER_HPP

#include <gui/model/Model.hpp>
#include <cstdint>

class ModelListener
{
public:
    ModelListener() : model(0) {}
    
    virtual ~ModelListener() {}

    void bind(Model* m)
    {
        model = m;
    }

    virtual void requestPlotUpdate(volatile uint16_t* ptr, int len) {};
    virtual void requestFFTUpdate (volatile uint16_t* ptr, int len) {};
protected:
    Model* model;
};

#endif // MODELLISTENER_HPP
