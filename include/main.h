#pragma once
#include "wx/wx.h"
#include "wx/dir.h"
#include "wx/tipwin.h"
#include <wx/busyinfo.h>
#include <vector>

class main : public wxFrame
{
public: // IDs
    enum elementID
    {
        OPEN_FILE = 1000,
        OPEN_FOLDER,
        UPSCALE_BUTTON,
        INPUT_BUTTON,
        OUTPUT_BUTTON,
        INPUT_TXTCTRL,
        OUTPUT_TXTCTRL,
        COMMAND_TXTCTRL,
        AIMODEL_CHOICE,
        SCALE_SLIDER,
        REALESRGANEXE_TXTCTRL,
        REALESRGANEXE_TXTCTRL_RESET_BTN,

        OPTION_CHECK_VIEWMENU
    };

public:
    main();
    ~main();

public: // element
    // menu
    wxMenuBar* m_MenuBar;
    wxMenu* m_ViewMenu;

    // Panel
    wxPanel *main_panel;
    wxPanel *option_panel;
    // sizer
    wxBoxSizer *main_horizontal_sizer;
    wxBoxSizer *mainPanel_sizer;
    wxBoxSizer *optionPanel_sizer;

    // button
    wxButton *upscale_btn;
    wxButton *input_btn;
    wxButton *output_btn;
    wxButton *realesrganExe_resetbtn;

    // textctrl
    wxTextCtrl *input_txtctrl;
    wxTextCtrl *output_txtctrl;
    wxTextCtrl *command_txtctrl;
    wxTextCtrl *realesrganExe_txtctrl;

    // choices
    wxChoice* AImodel_choice;

    // combobox


    // slider
    wxSlider* scale_slider;

    // Filedialogs
    wxFileDialog* FileDialog;

    // Progressbar
    wxGauge* upscale_progressbar;
public: // variables
    std::vector<wxString> AImodelchoices = {
    "realesr-animevideov3",
    "realesrgan-x4plus",
    "realesrgan-x4plus-anime"
    };
public: // event handler
    void OnMenuSelected(wxCommandEvent &e);
    void OnTextCtrlEnterWindow(wxMouseEvent &e);
    void OnChoiceSelected(wxCommandEvent &e);
    void OnBtnPressed(wxCommandEvent &e);
};


// other classes

// Define a new validator class that inherits from the wxValidator class
class NonEmptyValidator : public wxValidator
{
public:
    // Constructor
    NonEmptyValidator();

    // Copy constructor
    NonEmptyValidator(const NonEmptyValidator& val) : wxValidator() {}

    // Override the Validate method to check if the value in the associated wxTextCtrl is not empty and does not contain only whitespaces
    virtual bool Validate(wxWindow *);


    // Override the Clone method to allow the validator to be copied
    virtual wxObject *Clone() const
    {
        return new NonEmptyValidator(*this);
    }
};

// image panel
class ImagePanel : public wxScrolledWindow
{
public:
    ImagePanel(wxWindow* parent,wxBitmap image,int id);
private:
    wxBitmap img;
    double m_scale;
    int m_offsetX;
    int m_offsetY;

private: // handler
    void onScroll(wxScrollEvent&);
    void onZoom(wxMouseEvent&);
    void onPaint(wxPaintEvent&);
};