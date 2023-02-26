#include "main.h"

main::main() : wxFrame(nullptr, wxID_ANY, "Realesrgan interface GUI")
{
    this->SetIcon(wxIcon("IDI_FILE"));
    // menu
    m_MenuBar = new wxMenuBar;
    m_ViewMenu = new wxMenu;

    m_ViewMenu->AppendCheckItem(main::OPTION_CHECK_VIEWMENU,"Option window");
    m_MenuBar->Append(m_ViewMenu,"View");

    m_MenuBar->Bind(wxEVT_COMMAND_MENU_SELECTED,&main::OnMenuSelected,this);
    // Frame init
    this->SetMinSize(wxSize(600, 500));
    FileDialog = new wxFileDialog(this);

    main_panel = new wxPanel(this, wxID_ANY);
    main_panel->SetBackgroundColour(wxColour(69, 150, 91));

    option_panel = new wxPanel(this, wxID_ANY);
    option_panel->SetMinSize(wxSize(250, 500));

    // Button
    upscale_btn = new wxButton(main_panel, main::UPSCALE_BUTTON, "Upscale", wxDefaultPosition, wxSize(80, 25));
    upscale_btn->SetToolTip("Upscales Image");
    upscale_btn->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &OnBtnPressed, this);

    input_btn = new wxButton(main_panel, main::INPUT_BUTTON, "Input", wxDefaultPosition, wxSize(75, 25));
    output_btn = new wxButton(main_panel, main::OUTPUT_BUTTON, "Output", wxDefaultPosition, wxSize(75, 25));
    input_btn->SetToolTip("Input image path");
    output_btn->SetToolTip("Output image path");

    realesrganExe_resetbtn = new wxButton(option_panel, main::REALESRGANEXE_TXTCTRL_RESET_BTN,"X");

    input_btn->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &main::OnBtnPressed, this);
    output_btn->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &main::OnBtnPressed, this);

    realesrganExe_resetbtn->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &main::OnBtnPressed,this);

    // textctrl
    input_txtctrl = new wxTextCtrl(main_panel, main::INPUT_TXTCTRL);
    output_txtctrl = new wxTextCtrl(main_panel, main::OUTPUT_TXTCTRL);
    command_txtctrl = new wxTextCtrl(main_panel, main::COMMAND_TXTCTRL, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY | wxTE_MULTILINE);
    realesrganExe_txtctrl = new wxTextCtrl(option_panel,main::REALESRGANEXE_TXTCTRL);
    
    input_txtctrl->DragAcceptFiles(true);

    input_txtctrl->SetValidator(NonEmptyValidator());
    output_txtctrl->SetValidator(NonEmptyValidator());

    realesrganExe_txtctrl->SetValue("<auto>");
    realesrganExe_txtctrl->Bind(wxEVT_LEFT_DOWN,&main::OnTextCtrlEnterWindow,this);
    realesrganExe_txtctrl->SetToolTip("Browse Realesrgan.exe file");

    // choice
    AImodel_choice = new wxChoice(option_panel, main::AIMODEL_CHOICE);
    AImodel_choice->Set(AImodelchoices);
    AImodel_choice->Select(0);
    AImodel_choice->SetToolTip("Choose the models to work with");
    AImodel_choice->Bind(wxEVT_COMMAND_CHOICE_SELECTED,&main::OnChoiceSelected,this);

    // slider
    scale_slider = new wxSlider(option_panel, main::SCALE_SLIDER, 4, 1, 4, wxDefaultPosition, wxDefaultSize, wxSL_AUTOTICKS | wxSL_VALUE_LABEL);
    scale_slider->SetToolTip("Scales the image by the multiple of (1,2,3,4) default is 4");

    // progress bar
    upscale_progressbar = new wxGauge(main_panel,wxID_ANY,100);

    // sizer
    main_horizontal_sizer = new wxBoxSizer(wxHORIZONTAL);

    // setting main panel sizer
    mainPanel_sizer = new wxBoxSizer(wxVERTICAL);

    // setting option panel sizer
    optionPanel_sizer = new wxBoxSizer(wxVERTICAL);

    // horizontal sizer for mainPanel
    wxBoxSizer *main_row_1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *main_row_2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *main_row_3 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *main_row_bottom = new wxBoxSizer(wxHORIZONTAL);

    main_row_1->Add(input_btn, 0, wxLEFT | wxTOP, 10);
    main_row_1->Add(input_txtctrl, 1, wxLEFT | wxTOP | wxRIGHT, 10);

    main_row_2->Add(output_btn, 0, wxLEFT | wxTOP, 10);
    main_row_2->Add(output_txtctrl, 1, wxLEFT | wxTOP | wxRIGHT, 10);

    main_row_3->Add(command_txtctrl, 1, wxEXPAND);

    main_row_bottom->Add(upscale_btn, 0);

    // add horizontal sizers to mainPanel sizer
    mainPanel_sizer->Add(main_row_1, 0, wxEXPAND);
    mainPanel_sizer->Add(main_row_2, 0, wxEXPAND);
    mainPanel_sizer->Add(main_row_3, 1, wxEXPAND | wxALL, 10);
    mainPanel_sizer->Add(upscale_progressbar,0,wxEXPAND | wxLEFT | wxRIGHT | wxBOTTOM,10);
    mainPanel_sizer->Add(main_row_bottom, 0, wxALIGN_RIGHT | wxRIGHT | wxBOTTOM, 10);

    // horizontal sizer for optionPanel
    wxBoxSizer *option_row_1 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *option_row_2 = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *option_row_3 = new wxBoxSizer(wxHORIZONTAL);

    // labels for the controls
    wxStaticText *AIchoice_label = new wxStaticText(option_panel, wxID_ANY, "Model");
    wxStaticText *Scaleslider_label = new wxStaticText(option_panel, wxID_ANY, "Scale");
    wxStaticText *RealesrganExe_label = new wxStaticText(option_panel,wxID_ANY,"Realesrgan");

    option_row_1->Add(AIchoice_label);
    option_row_1->AddSpacer(30);
    option_row_1->Add(AImodel_choice);

    option_row_2->Add(Scaleslider_label);
    option_row_2->AddSpacer(30);
    option_row_2->Add(scale_slider);

    option_row_3->Add(RealesrganExe_label);
    option_row_3->AddSpacer(30);
    option_row_3->Add(realesrganExe_txtctrl);
    option_row_3->AddSpacer(10);
    option_row_3->Add(realesrganExe_resetbtn);

    // add horizontal sizers to optionPanel sizer
    optionPanel_sizer->Add(option_row_1, 0, wxLEFT | wxRIGHT | wxTOP, 10);
    optionPanel_sizer->Add(option_row_2, 0, wxLEFT | wxRIGHT | wxTOP, 10);
    optionPanel_sizer->Add(option_row_3, 0, wxLEFT | wxRIGHT | wxTOP, 10);

    // Place panels in the mainframe horizontal sizer
    main_horizontal_sizer->Add(main_panel, 1, wxEXPAND);
    main_horizontal_sizer->Add(option_panel, 0, wxEXPAND);

    main_panel->SetSizer(mainPanel_sizer);
    option_panel->SetSizer(optionPanel_sizer);
    
    // Panel state
    m_ViewMenu->FindItem(OPTION_CHECK_VIEWMENU)->Check(true);
    option_panel->Show();

    this->SetSizer(main_horizontal_sizer);
    this->SetMenuBar(m_MenuBar);
    this->Layout();
}

main::~main()
{
}

void main::OnMenuSelected(wxCommandEvent &e)
{
    switch (e.GetId())
    {
    case wxID_EXIT:
        this->Destroy();
        break;
    case main::OPTION_CHECK_VIEWMENU:
    {

        if (m_ViewMenu->FindItem(OPTION_CHECK_VIEWMENU)->IsChecked())
            option_panel->Show();
        else option_panel->Hide();

        this->Layout();
        break;
    }
    }
    
}

void main::OnTextCtrlEnterWindow(wxMouseEvent &e)
{
    switch (e.GetId())
    {
    case main::REALESRGANEXE_TXTCTRL:
    {
        FileDialog->SetMessage(_("Realesrgan program location"));
        FileDialog->SetWildcard("Executable file (*.exe)|*.exe");
        FileDialog->SetWindowStyle(wxFD_OPEN | wxFD_FILE_MUST_EXIST);

        if (FileDialog->ShowModal() == wxID_CANCEL)
            return;
        
        // get the filepath for the realesrgan exe here
        realesrganExe_txtctrl->SetValue(FileDialog->GetPath());

        break;
    }
        
    
    default:
        break;
    }
}

void main::OnChoiceSelected(wxCommandEvent &e)
{
    switch(e.GetId())
    {
        case main::AIMODEL_CHOICE:
        {
            // if the selection is not realesr-animevideov3
            if (AImodel_choice->GetSelection() != 0)
            {
                scale_slider->SetValue(4); // 4x scale
                scale_slider->Disable();
            }    
            else scale_slider->Enable();

            break;
        }

    }
}

void main::OnBtnPressed(wxCommandEvent &e)
{
    switch (e.GetId())
    {
    case main::INPUT_BUTTON:
    {
        FileDialog->SetMessage(_("Open a image to upscale"));
        FileDialog->SetWildcard("JPEG image file (*.jpg or *.jpeg)|*.jpg;*.jpeg|PNG image file (*.png)|*.png|Web picture file (*.webp)|*.webp");
        FileDialog->SetWindowStyle(wxFD_OPEN | wxFD_FILE_MUST_EXIST);

        if (FileDialog->ShowModal() == wxID_CANCEL)
            return;

        // get the filepath for the realesrgan here
        input_txtctrl->SetValue(FileDialog->GetPath());
        break;
    }

    case main::OUTPUT_BUTTON:
    {
        FileDialog->SetMessage(_("Save image"));
        FileDialog->SetWildcard("JPEG image file (*.jpg or *.jpeg)|*.jpg;*.jpeg|PNG image file (*.png)|*.png|Web picture file (*.webp)|*.webp");
        FileDialog->SetWindowStyle(wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
        if (FileDialog->ShowModal() == wxID_CANCEL)
            return;

        // get the filepath
        output_txtctrl->SetValue(FileDialog->GetPath());
        break;
    }

    case main::REALESRGANEXE_TXTCTRL_RESET_BTN:
    {
        realesrganExe_txtctrl->SetValue("<auto>");
        break;
    }

    case main::UPSCALE_BUTTON:
    {
        if (input_txtctrl->Validate() && output_txtctrl->Validate())
        {
            upscale_btn->Disable();
            // Create the upscaler process
            std::string InputPath = input_txtctrl->GetValue().ToStdString(), OutputPath = output_txtctrl->GetValue().ToStdString(), Model = AImodelchoices[AImodel_choice->GetSelection()].ToStdString();
            int Scale = scale_slider->GetValue();

            SECURITY_ATTRIBUTES sa;
            sa.nLength = sizeof(SECURITY_ATTRIBUTES);
            sa.lpSecurityDescriptor = NULL;
            sa.bInheritHandle = TRUE;

            HANDLE hReadPipe, hWritePipe;
            CreatePipe(&hReadPipe, &hWritePipe, &sa, 0);

            STARTUPINFO si;
            ZeroMemory(&si, sizeof(STARTUPINFO));
            si.cb = sizeof(STARTUPINFO);
            si.hStdError = hWritePipe;
            si.hStdOutput = hWritePipe;
            si.dwFlags = STARTF_USESTDHANDLES;

            PROCESS_INFORMATION pi;
            ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
            std::string Command = std::string{};

            if (realesrganExe_txtctrl->GetValue() == "<auto>")
                Command = "realesrgan.exe -i \"" + InputPath + "\" -o \"" + OutputPath + "\" -n " + Model + " -s " + std::to_string(Scale);
            else 
                Command = "\"" + realesrganExe_txtctrl->GetValue() + "\" -i \"" + InputPath + "\" -o \"" + OutputPath + "\" -n " + Model + " -s " + std::to_string(Scale);

            command_txtctrl->AppendText("Executing task: " + Command + "\n\n");

            std::wstring wCommand(Command.begin(), Command.end());
            LPWSTR lpCommand = (LPWSTR)wCommand.c_str();
            if (!CreateProcess(NULL, lpCommand, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi))
            {
                CloseHandle(hWritePipe);
                CloseHandle(hReadPipe);

                command_txtctrl->AppendText("Error: Failed to create process\n");

                std::cout << "Error: Failed to create process";
                e.Skip();
                return;
            }

            CloseHandle(hWritePipe);

            DWORD dwRead;
            char buffer[4096];
            std::string Progress = "";
            bool ok = true;
            wxBusyCursor wait;
            while (ReadFile(hReadPipe, buffer, 4096, &dwRead, NULL) && dwRead > 0)
            {
                buffer[dwRead] = '\0';
                wxYield();
                Progress = buffer;
                size_t PercentPos = Progress.find("%");
                
                if (PercentPos != std::string::npos)
                {
                    upscale_progressbar->SetValue( std::stoi(Progress.substr(PercentPos - PercentPos, PercentPos)));
                    command_txtctrl->AppendText("Progress: " + Progress.substr(PercentPos - PercentPos, PercentPos) + "%\n");
                    std::cout << Progress.substr(PercentPos - PercentPos, PercentPos) + "%\n";
                }
                else{
                    command_txtctrl->AppendText(buffer);
                }

                if (Progress == "invalid outputpath extension type\r\n")
                    ok = false;
            }
            upscale_progressbar->Pulse();
            CloseHandle(hReadPipe);
            WaitForSingleObject(pi.hProcess, INFINITE);

            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
            
            if (ok)
                command_txtctrl->AppendText("Finished, file has been saved!\n");

            upscale_progressbar->SetValue(0);
            upscale_btn->Enable();
        }        
            break;
    }
    }
}


NonEmptyValidator::NonEmptyValidator()
{}


bool NonEmptyValidator::Validate(wxWindow* parent)
{
    wxTextCtrl *ctrl = (wxTextCtrl *) m_validatorWindow;
    wxString value = ctrl->GetValue();

    if (value.empty() || value.Trim().empty())
    {
        // Show a tooltip
        wxPoint pos = ctrl->ClientToScreen(wxPoint(0, 0));
        wxTipWindow *tip = new wxTipWindow(parent, "The input & output field cannot be empty or contain only whitespaces!");
        tip->SetBoundingRect(wxRect(pos.x, pos.y + ctrl->GetSize().GetHeight(), 1, 1));
        tip->Show();

        return false;
    }

    return true;   
}