/*
 *  Copyright (C) 2004-2005 Andrej Vodopivec <andrejv@users.sourceforge.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 * 
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */



#include "LimitWiz.h"


LimitWiz::LimitWiz(wxWindow* parent, int id, const wxString& title,
                   const wxPoint& pos, const wxSize& size, long style):
  wxDialog(parent, id, title, pos, size, wxDEFAULT_DIALOG_STYLE)
{
  label_1 = new wxStaticText(this, -1, _("Limit"));
  label_2 = new wxStaticText(this, -1, _("Limit of:"));
  text_ctrl_1 = new BTextCtrl(this, -1, wxT(""), wxDefaultPosition,
                              wxSize(180,-1));
  label_3 = new wxStaticText(this, -1, _("when variable:"));
  text_ctrl_2 = new BTextCtrl(this, -1, wxT("x"));
  label_4 = new wxStaticText(this, -1, _("goes to:"));
  text_ctrl_3 = new BTextCtrl(this, -1, wxT("0"));
  button_1 = new wxButton(this, special, _("Special"));
  label_5 = new wxStaticText(this, -1, _("from:"));
  const wxString combo_box_1_choices[] = {
    _("both sides"),
    _("left"),
    _("right")
  };
  combo_box_1 = new wxComboBox(this, -1, wxT(""), wxDefaultPosition,
                               wxSize(130, -1), 3,
                               combo_box_1_choices, wxCB_DROPDOWN);
  static_line_1 = new wxStaticLine(this, -1);
  button_2 = new wxButton(this, wxOK, _("OK"));
  button_3 = new wxButton(this, wxCANCEL, _("Cancel"));
  button_2->SetDefault();

  set_properties();
  do_layout();
  ok = false;
}


void LimitWiz::set_properties()
{
  SetTitle(_("Limit"));
  label_1->SetFont(wxFont(20, wxROMAN, wxITALIC, wxNORMAL, 0, wxT("")));
  combo_box_1->SetSelection(0);
}


void LimitWiz::do_layout()
{
  wxFlexGridSizer* grid_sizer_1 = new wxFlexGridSizer(3, 1, 3, 3);
  wxBoxSizer* sizer_2 = new wxBoxSizer(wxHORIZONTAL);
  wxFlexGridSizer* grid_sizer_2 = new wxFlexGridSizer(4, 2, 3, 3);
  wxFlexGridSizer* sizer_1 = new wxFlexGridSizer(1, 2, 0, 0);
  grid_sizer_1->Add(label_1, 0, wxALIGN_CENTER_HORIZONTAL|wxALL, 3);
  grid_sizer_2->Add(label_2, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 3);
  grid_sizer_2->Add(text_ctrl_1, 0, wxALL, 3);
  grid_sizer_2->Add(label_3, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 3);
  grid_sizer_2->Add(text_ctrl_2, 0, wxALL, 3);
  grid_sizer_2->Add(label_4, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 3);
  sizer_1->Add(text_ctrl_3, 0, wxALL|wxEXPAND, 3);
  sizer_1->Add(button_1, 0, wxALL, 3);
  sizer_1->AddGrowableCol(0);
  grid_sizer_2->Add(sizer_1, 1, 0, 0);
  grid_sizer_2->Add(label_5, 0, wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL|wxALL, 2);
  grid_sizer_2->Add(combo_box_1, 0, wxALL, 2);
  grid_sizer_1->Add(grid_sizer_2, 1, wxEXPAND, 0);
  grid_sizer_1->Add(static_line_1, 0, wxEXPAND, 0);
  sizer_2->Add(button_2, 0, wxALL, 2);
  sizer_2->Add(button_3, 0, wxALL, 2);
  grid_sizer_1->Add(sizer_2, 1, wxALIGN_RIGHT, 0);
  SetAutoLayout(true);
  SetSizer(grid_sizer_1);
  grid_sizer_1->Fit(this);
  grid_sizer_1->SetSizeHints(this);
  Layout();
}

wxString LimitWiz::getValue()
{
  wxString s = wxT("limit(");
  s += text_ctrl_1->GetValue();
  s += wxT(", ");
  s += text_ctrl_2->GetValue();
  s += wxT(", ");
  s += text_ctrl_3->GetValue();
  wxString f = combo_box_1->GetValue();
  if (f == wxT("left"))
    s += wxT(", MINUS");
  else if (f == wxT("right"))
    s += wxT(", PLUS");
  s += wxT(");");
  
  return s;
}

void LimitWiz::onButton(wxCommandEvent& event)
{
  switch (event.GetId()) {
  case special:
    {
      wxString choices[] = {wxT("Pi"), wxT("E"), wxT("Infinity"),
                            wxT("- Infinity")};
      wxString choice = wxGetSingleChoice(_("Select a constant"),
                                          _("Constant"), 4, choices, this);
      if (choice.Length()) {
        if (choice == wxT("Pi"))
          text_ctrl_3->SetValue(wxT("%pi"));
        else if (choice == wxT("E"))
          text_ctrl_3->SetValue(wxT("%e"));
        else if (choice == wxT("Infinity"))
          text_ctrl_3->SetValue(wxT("inf"));
        else if (choice == wxT("- Infinity"))
          text_ctrl_3->SetValue(wxT("minf"));
      }
    }
    break;
  case wxOK:
    ok = true;
  case wxCANCEL:
    Close();
    break;
  }
}

BEGIN_EVENT_TABLE(LimitWiz, wxDialog)
  EVT_BUTTON(special, LimitWiz::onButton)
  EVT_BUTTON(wxOK, LimitWiz::onButton)
  EVT_BUTTON(wxCANCEL, LimitWiz::onButton)
END_EVENT_TABLE()