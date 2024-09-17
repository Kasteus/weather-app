#pragma once

#include <memory>

class QString;

class Interface
{
public:
    enum wheaterStation
    {
        api_met_no = 0
    };

    static std::shared_ptr<Interface> create(wheaterStation type);

public:
    virtual QString wheaterIcon() const = 0;
    virtual QString temperature() const = 0;
    virtual QString wind() const = 0;

public:
    virtual double latitude() const = 0;
    virtual double longitude() const = 0;
    virtual double timezone() const = 0;
};
