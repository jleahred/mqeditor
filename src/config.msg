BEGIN_INIT

#INCLUDES = ['#include "support/mtk_string.h"' ]
NAMESPACES = ['mqeditor']
QPID=False

END_INIT



sub_color  [< >]
{
    red     (red)       :    int16
    green   (green)     :    int16
    blue    (blue)      :    int16
    alfa    (alfa)      :    int16
}


//---------------------------------------------------------------------
//        sub_key_command
//---------------------------------------------------------------------
sub_key_command [< >]
{
    key         (key)       :  string
    command     (command)   :  string
}

//---------------------------------------------------------------------
//        sub_auto_completion_text
//---------------------------------------------------------------------
sub_auto_completion_text [< >]
{
    automatic_after_letters     (aal)   :   int     // 0 means not automatic  3
    only_words_with_prefix      (owp)   :   bool    // false
    re_split                    (respl) :   string  //   [^a-zA-Z0-9_]
}

//---------------------------------------------------------------------
//        sub_auto_completion
//---------------------------------------------------------------------
sub_auto_completion [< >]
{
    popup_max_width             (pumw)  :   int     // 300
}

//---------------------------------------------------------------------
//        sub_line_number
//---------------------------------------------------------------------
sub_line_number [< >]
{
    visible             (v)     :       bool        //   true
    font_color          (fc)    :       sub_color
    back_ground_color   (bc)    :       sub_color
    font_relative_size  (frs)   :       int         // size increase in pixels (from font size on editor)
}


//---------------------------------------------------------------------
//        sub_highlight_current_block
//---------------------------------------------------------------------
sub_highlight_current_block [< >]
{
    enabled             (e)     :   bool            //  true
    back_ground_color   (bc)    :   sub_color       
    font_color          (fc)    :   sub_color
}


//---------------------------------------------------------------------
//        sub_identation
//---------------------------------------------------------------------
sub_identation [< >]
{
    spaces              (s)     :   int             // 4
    delete_identation   (di)    :   bool            // true
}


//---------------------------------------------------------------------
//        sub_line_command_area
//---------------------------------------------------------------------
sub_line_command_area [< >]
{
    //font                (f)     :   sub_font
    style_sheet         (ss)    :   string
}





//---------------------------------------------------------------------

//

//        config

//

//---------------------------------------------------------------------


config  [< >]
{
    auto_completion             (ac)        :       sub_auto_completion
    auto_completion_text        (act)       :       sub_auto_completion_text

    line_number                 (sln)       :       sub_line_number
    highlight_current_block     (hlb)       :       sub_highlight_current_block
    identation                  (ident)     :       sub_identation
    line_command_area           (lca)       :       sub_line_command_area

    [key_commands]              (kc)        :       sub_key_command
}