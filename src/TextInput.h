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

#ifndef _TEXTINPUT_H_
#define _TEXTINPUT_H_

#include <wx/wx.h>

#include "TextCtrl.h"

class TextInput: public wxDialog {
 public:
  TextInput(wxWindow* parent, int id, const wxString& title, bool setfont=true,
            const wxPoint& pos=wxDefaultPosition,
            const wxSize& size=wxDefaultSize,
            long style=wxDEFAULT_DIALOG_STYLE);
  bool isOk() { return ok; }
  wxString getValue();
  void setValue(wxString s);
 private:
  void set_properties();
  void do_layout();
  void onButton(wxCommandEvent& event);
 protected:
  TextCtrl* text_ctrl_1;
  wxButton* button_1;
  wxButton* button_2;
  bool ok;
  bool setFont;
  DECLARE_EVENT_TABLE()
};

#endif	//_TEXTINPUT_H_