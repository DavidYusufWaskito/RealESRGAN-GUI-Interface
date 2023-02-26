#pragma once
#include "wx/wx.h"
#include "main.h"

class app : public wxApp
{
public:
    app();
    ~app();
public:
    main* apl = nullptr;
    virtual bool OnInit();
};