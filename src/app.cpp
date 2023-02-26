#include "app.h"
wxIMPLEMENT_APP(app);

app::app()
{

}

app::~app()
{

}

bool app::OnInit()
{
    apl = new main();
    apl->Show();
    return true;
}