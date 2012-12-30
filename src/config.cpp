
// generated automatically
// coded last modification:        $CODED_LAST_MODIF


#include "support/mtk_double.h"
#include "support/fixed_number.h"
#include "support/date_time.h"

#include "config.h"

namespace mqeditor { 







    inline std::string  __internal_get_default(std::string*)
    {
        return std::string();
    }

    inline mtk::Double __internal_get_default(mtk::Double*)
    {
        return mtk::Double(0.0);
    }
    inline mtk::FixedNumber __internal_get_default(mtk::FixedNumber*)
    {
        return mtk::FixedNumber(mtk::fnDouble(0), mtk::fnDec(0), mtk::fnInc(1));
    }
    inline mtk::fnExt  __internal_get_default(mtk::fnExt*)
    {
        return mtk::fnExt(mtk::fnDec(0), mtk::fnInc(1));
    }
    
    inline mtk::DateTime __internal_get_default(mtk::DateTime*)
    {
        return mtk::DateTime(mtk::dtYear(2000), mtk::dtMonth(1), mtk::dtDay(1));
    }
    inline mtk::dtTimeQuantity __internal_get_default(mtk::dtTimeQuantity*)
    {
        return mtk::dtTimeQuantity(mtk::dtHours(0), mtk::dtMinutes(0), mtk::dtSeconds(0), mtk::dtMilliseconds(0));
    }
    inline bool __internal_get_default(bool*)
    {
        return false;
    }
    inline int8_t __internal_get_default(int8_t*)
    {
        return 0;
    }
    inline int16_t  __internal_get_default(int16_t*)
    {
        return 0;
    }
    inline int32_t  __internal_get_default(int32_t*)
    {
        return 0;
    }

    template<typename T>
    mtk::list<T>  __internal_get_default(mtk::list<T>*)
    {
        return mtk::list<T>();
    }



    
template<typename T>
std::ostream& operator<< (std::ostream& o, const mtk::list<T>& list)
{
    typename mtk::list<T>::const_iterator it = list.begin();
    o << "[";
    while (it!= list.end())
    {
        o << *it << ", ";
        ++it;
    }
    o << "]";
    return o;
}



template<typename T>
bool operator== (const mtk::list<T>& l1, const mtk::list<T>& l2)
{
    if (l1.size() != l2.size())     return false;
    
    typename mtk::list<T>::const_iterator it1 = l1.begin();
    typename mtk::list<T>::const_iterator it2 = l2.begin();
    while (it1!= l1.end())
    {
        if (*it1 != *it2)       return false;
        ++it1;
        ++it2;
    }
    return true;
}



//========================================================================
//------------------------------------------------------------------------
//  I M P L E M E N T A T I O N
//  internal fordward declarations


sub_color::sub_color (   const int16_t&  _red,   const int16_t&  _green,   const int16_t&  _blue,   const int16_t&  _alfa)
    :     red(_red),   green(_green),   blue(_blue),   alfa(_alfa) 
       
    {  
    }



sub_key_command::sub_key_command (   const std::string&  _key,   const std::string&  _command)
    :     key(_key),   command(_command) 
       
    {  
    }



sub_auto_completion_text::sub_auto_completion_text (   const int&  _automatic_after_letters,   const bool&  _only_words_with_prefix,   const std::string&  _re_split)
    :     automatic_after_letters(_automatic_after_letters),   only_words_with_prefix(_only_words_with_prefix),   re_split(_re_split) 
       
    {  
    }



sub_auto_completion::sub_auto_completion (   const int&  _popup_max_width)
    :     popup_max_width(_popup_max_width) 
       
    {  
    }



sub_line_number::sub_line_number (   const bool&  _visible,   const sub_color&  _font_color,   const sub_color&  _back_ground_color,   const int&  _font_relative_size)
    :     visible(_visible),   font_color(_font_color),   back_ground_color(_back_ground_color),   font_relative_size(_font_relative_size) 
       
    {  
    }



sub_highlight_current_block::sub_highlight_current_block (   const bool&  _enabled,   const sub_color&  _back_ground_color,   const sub_color&  _font_color)
    :     enabled(_enabled),   back_ground_color(_back_ground_color),   font_color(_font_color) 
       
    {  
    }



sub_identation::sub_identation (   const int&  _spaces,   const bool&  _delete_identation)
    :     spaces(_spaces),   delete_identation(_delete_identation) 
       
    {  
    }



sub_line_command_area::sub_line_command_area (   const std::string&  _style_sheet)
    :     style_sheet(_style_sheet) 
       
    {  
    }



config::config (   const sub_auto_completion&  _auto_completion,   const sub_auto_completion_text&  _auto_completion_text,   const sub_line_number&  _line_number,   const sub_highlight_current_block&  _highlight_current_block,   const sub_identation&  _identation,   const sub_line_command_area&  _line_command_area,   const mtk::list<sub_key_command >&  _key_commands)
    :     auto_completion(_auto_completion),   auto_completion_text(_auto_completion_text),   line_number(_line_number),   highlight_current_block(_highlight_current_block),   identation(_identation),   line_command_area(_line_command_area),   key_commands(_key_commands) 
       
    {  
    }


std::ostream& operator<< (std::ostream& o, const sub_color & c)
{
    o << "{ "

        << "red:"<<   c.red << "  "        << "green:"<<   c.green << "  "        << "blue:"<<   c.blue << "  "        << "alfa:"<<   c.alfa << "  "
        << " }";
    return o;
}



YAML::Emitter& operator << (YAML::Emitter& o, const sub_color & c)
{
    o << YAML::BeginMap

        << YAML::Key << "red"  << YAML::Value <<   c.red        << YAML::Key << "green"  << YAML::Value <<   c.green        << YAML::Key << "blue"  << YAML::Value <<   c.blue        << YAML::Key << "alfa"  << YAML::Value <<   c.alfa
        << YAML::EndMap;
    return o;
}



void  operator >> (const YAML::Node& node, sub_color & c)
{


        node["red"]  >> c.red;
        node["green"]  >> c.green;
        node["blue"]  >> c.blue;
        node["alfa"]  >> c.alfa;


}


std::ostream& operator<< (std::ostream& o, const sub_key_command & c)
{
    o << "{ "

        << "key:"<<   c.key << "  "        << "command:"<<   c.command << "  "
        << " }";
    return o;
}



YAML::Emitter& operator << (YAML::Emitter& o, const sub_key_command & c)
{
    o << YAML::BeginMap

        << YAML::Key << "key"  << YAML::Value <<   c.key        << YAML::Key << "command"  << YAML::Value <<   c.command
        << YAML::EndMap;
    return o;
}



void  operator >> (const YAML::Node& node, sub_key_command & c)
{


        node["key"]  >> c.key;
        node["command"]  >> c.command;


}


std::ostream& operator<< (std::ostream& o, const sub_auto_completion_text & c)
{
    o << "{ "

        << "automatic_after_letters:"<< c.automatic_after_letters<<"  "        << "only_words_with_prefix:"<< c.only_words_with_prefix<<"  "        << "re_split:"<<   c.re_split << "  "
        << " }";
    return o;
}



YAML::Emitter& operator << (YAML::Emitter& o, const sub_auto_completion_text & c)
{
    o << YAML::BeginMap

        << YAML::Key << "automatic_after_letters"  << YAML::Value << c.automatic_after_letters        << YAML::Key << "only_words_with_prefix"  << YAML::Value << c.only_words_with_prefix        << YAML::Key << "re_split"  << YAML::Value <<   c.re_split
        << YAML::EndMap;
    return o;
}



void  operator >> (const YAML::Node& node, sub_auto_completion_text & c)
{


        node["automatic_after_letters"]  >> c.automatic_after_letters;
        node["only_words_with_prefix"]  >> c.only_words_with_prefix;
        node["re_split"]  >> c.re_split;


}


std::ostream& operator<< (std::ostream& o, const sub_auto_completion & c)
{
    o << "{ "

        << "popup_max_width:"<< c.popup_max_width<<"  "
        << " }";
    return o;
}



YAML::Emitter& operator << (YAML::Emitter& o, const sub_auto_completion & c)
{
    o << YAML::BeginMap

        << YAML::Key << "popup_max_width"  << YAML::Value << c.popup_max_width
        << YAML::EndMap;
    return o;
}



void  operator >> (const YAML::Node& node, sub_auto_completion & c)
{


        node["popup_max_width"]  >> c.popup_max_width;


}


std::ostream& operator<< (std::ostream& o, const sub_line_number & c)
{
    o << "{ "

        << "visible:"<< c.visible<<"  "        << "font_color:"<< c.font_color<<"  "        << "back_ground_color:"<< c.back_ground_color<<"  "        << "font_relative_size:"<< c.font_relative_size<<"  "
        << " }";
    return o;
}



YAML::Emitter& operator << (YAML::Emitter& o, const sub_line_number & c)
{
    o << YAML::BeginMap

        << YAML::Key << "visible"  << YAML::Value << c.visible        << YAML::Key << "font_color"  << YAML::Value << c.font_color        << YAML::Key << "back_ground_color"  << YAML::Value << c.back_ground_color        << YAML::Key << "font_relative_size"  << YAML::Value << c.font_relative_size
        << YAML::EndMap;
    return o;
}



void  operator >> (const YAML::Node& node, sub_line_number & c)
{


        node["visible"]  >> c.visible;
        node["font_color"]  >> c.font_color;
        node["back_ground_color"]  >> c.back_ground_color;
        node["font_relative_size"]  >> c.font_relative_size;


}


std::ostream& operator<< (std::ostream& o, const sub_highlight_current_block & c)
{
    o << "{ "

        << "enabled:"<< c.enabled<<"  "        << "back_ground_color:"<< c.back_ground_color<<"  "        << "font_color:"<< c.font_color<<"  "
        << " }";
    return o;
}



YAML::Emitter& operator << (YAML::Emitter& o, const sub_highlight_current_block & c)
{
    o << YAML::BeginMap

        << YAML::Key << "enabled"  << YAML::Value << c.enabled        << YAML::Key << "back_ground_color"  << YAML::Value << c.back_ground_color        << YAML::Key << "font_color"  << YAML::Value << c.font_color
        << YAML::EndMap;
    return o;
}



void  operator >> (const YAML::Node& node, sub_highlight_current_block & c)
{


        node["enabled"]  >> c.enabled;
        node["back_ground_color"]  >> c.back_ground_color;
        node["font_color"]  >> c.font_color;


}


std::ostream& operator<< (std::ostream& o, const sub_identation & c)
{
    o << "{ "

        << "spaces:"<< c.spaces<<"  "        << "delete_identation:"<< c.delete_identation<<"  "
        << " }";
    return o;
}



YAML::Emitter& operator << (YAML::Emitter& o, const sub_identation & c)
{
    o << YAML::BeginMap

        << YAML::Key << "spaces"  << YAML::Value << c.spaces        << YAML::Key << "delete_identation"  << YAML::Value << c.delete_identation
        << YAML::EndMap;
    return o;
}



void  operator >> (const YAML::Node& node, sub_identation & c)
{


        node["spaces"]  >> c.spaces;
        node["delete_identation"]  >> c.delete_identation;


}


std::ostream& operator<< (std::ostream& o, const sub_line_command_area & c)
{
    o << "{ "

        << "style_sheet:"<<   c.style_sheet << "  "
        << " }";
    return o;
}



YAML::Emitter& operator << (YAML::Emitter& o, const sub_line_command_area & c)
{
    o << YAML::BeginMap

        << YAML::Key << "style_sheet"  << YAML::Value <<   c.style_sheet
        << YAML::EndMap;
    return o;
}



void  operator >> (const YAML::Node& node, sub_line_command_area & c)
{


        node["style_sheet"]  >> c.style_sheet;


}


std::ostream& operator<< (std::ostream& o, const config & c)
{
    o << "{ "

        << "auto_completion:"<< c.auto_completion<<"  "        << "auto_completion_text:"<< c.auto_completion_text<<"  "        << "line_number:"<< c.line_number<<"  "        << "highlight_current_block:"<< c.highlight_current_block<<"  "        << "identation:"<< c.identation<<"  "        << "line_command_area:"<< c.line_command_area<<"  "        << "key_commands:"<< c.key_commands<<"  "
        << " }";
    return o;
}



YAML::Emitter& operator << (YAML::Emitter& o, const config & c)
{
    o << YAML::BeginMap

        << YAML::Key << "auto_completion"  << YAML::Value << c.auto_completion        << YAML::Key << "auto_completion_text"  << YAML::Value << c.auto_completion_text        << YAML::Key << "line_number"  << YAML::Value << c.line_number        << YAML::Key << "highlight_current_block"  << YAML::Value << c.highlight_current_block        << YAML::Key << "identation"  << YAML::Value << c.identation        << YAML::Key << "line_command_area"  << YAML::Value << c.line_command_area        << YAML::Key << "key_commands"  << YAML::Value << c.key_commands
        << YAML::EndMap;
    return o;
}



void  operator >> (const YAML::Node& node, config & c)
{


        node["auto_completion"]  >> c.auto_completion;
        node["auto_completion_text"]  >> c.auto_completion_text;
        node["line_number"]  >> c.line_number;
        node["highlight_current_block"]  >> c.highlight_current_block;
        node["identation"]  >> c.identation;
        node["line_command_area"]  >> c.line_command_area;
        node["key_commands"]  >> c.key_commands;


}


bool operator== (const sub_color& a, const sub_color& b)
{
    return (          a.red ==  b.red  &&          a.green ==  b.green  &&          a.blue ==  b.blue  &&          a.alfa ==  b.alfa  &&   true  );
}

bool operator!= (const sub_color& a, const sub_color& b)
{
    return !(a==b);
}



bool operator== (const sub_key_command& a, const sub_key_command& b)
{
    return (          a.key ==  b.key  &&          a.command ==  b.command  &&   true  );
}

bool operator!= (const sub_key_command& a, const sub_key_command& b)
{
    return !(a==b);
}



bool operator== (const sub_auto_completion_text& a, const sub_auto_completion_text& b)
{
    return (          a.automatic_after_letters ==  b.automatic_after_letters  &&          a.only_words_with_prefix ==  b.only_words_with_prefix  &&          a.re_split ==  b.re_split  &&   true  );
}

bool operator!= (const sub_auto_completion_text& a, const sub_auto_completion_text& b)
{
    return !(a==b);
}



bool operator== (const sub_auto_completion& a, const sub_auto_completion& b)
{
    return (          a.popup_max_width ==  b.popup_max_width  &&   true  );
}

bool operator!= (const sub_auto_completion& a, const sub_auto_completion& b)
{
    return !(a==b);
}



bool operator== (const sub_line_number& a, const sub_line_number& b)
{
    return (          a.visible ==  b.visible  &&          a.font_color ==  b.font_color  &&          a.back_ground_color ==  b.back_ground_color  &&          a.font_relative_size ==  b.font_relative_size  &&   true  );
}

bool operator!= (const sub_line_number& a, const sub_line_number& b)
{
    return !(a==b);
}



bool operator== (const sub_highlight_current_block& a, const sub_highlight_current_block& b)
{
    return (          a.enabled ==  b.enabled  &&          a.back_ground_color ==  b.back_ground_color  &&          a.font_color ==  b.font_color  &&   true  );
}

bool operator!= (const sub_highlight_current_block& a, const sub_highlight_current_block& b)
{
    return !(a==b);
}



bool operator== (const sub_identation& a, const sub_identation& b)
{
    return (          a.spaces ==  b.spaces  &&          a.delete_identation ==  b.delete_identation  &&   true  );
}

bool operator!= (const sub_identation& a, const sub_identation& b)
{
    return !(a==b);
}



bool operator== (const sub_line_command_area& a, const sub_line_command_area& b)
{
    return (          a.style_sheet ==  b.style_sheet  &&   true  );
}

bool operator!= (const sub_line_command_area& a, const sub_line_command_area& b)
{
    return !(a==b);
}



bool operator== (const config& a, const config& b)
{
    return (          a.auto_completion ==  b.auto_completion  &&          a.auto_completion_text ==  b.auto_completion_text  &&          a.line_number ==  b.line_number  &&          a.highlight_current_block ==  b.highlight_current_block  &&          a.identation ==  b.identation  &&          a.line_command_area ==  b.line_command_area  &&          a.key_commands ==  b.key_commands  &&   true  );
}

bool operator!= (const config& a, const config& b)
{
    return !(a==b);
}



    sub_color  __internal_get_default(sub_color*)
    {
        return sub_color(
//   field_type
   __internal_get_default ((int16_t*)0),
//   field_type
   __internal_get_default ((int16_t*)0),
//   field_type
   __internal_get_default ((int16_t*)0),
//   field_type
   __internal_get_default ((int16_t*)0)
            );
    }
    
    sub_key_command  __internal_get_default(sub_key_command*)
    {
        return sub_key_command(
//   field_type
   __internal_get_default ((std::string*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    sub_auto_completion_text  __internal_get_default(sub_auto_completion_text*)
    {
        return sub_auto_completion_text(
//   sub_msg_type
   __internal_get_default((int*)0),
//   sub_msg_type
   __internal_get_default((bool*)0),
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    sub_auto_completion  __internal_get_default(sub_auto_completion*)
    {
        return sub_auto_completion(
//   sub_msg_type
   __internal_get_default((int*)0)
            );
    }
    
    sub_line_number  __internal_get_default(sub_line_number*)
    {
        return sub_line_number(
//   sub_msg_type
   __internal_get_default((bool*)0),
//   sub_msg_type
   __internal_get_default((sub_color*)0),
//   sub_msg_type
   __internal_get_default((sub_color*)0),
//   sub_msg_type
   __internal_get_default((int*)0)
            );
    }
    
    sub_highlight_current_block  __internal_get_default(sub_highlight_current_block*)
    {
        return sub_highlight_current_block(
//   sub_msg_type
   __internal_get_default((bool*)0),
//   sub_msg_type
   __internal_get_default((sub_color*)0),
//   sub_msg_type
   __internal_get_default((sub_color*)0)
            );
    }
    
    sub_identation  __internal_get_default(sub_identation*)
    {
        return sub_identation(
//   sub_msg_type
   __internal_get_default((int*)0),
//   sub_msg_type
   __internal_get_default((bool*)0)
            );
    }
    
    sub_line_command_area  __internal_get_default(sub_line_command_area*)
    {
        return sub_line_command_area(
//   field_type
   __internal_get_default ((std::string*)0)
            );
    }
    
    config  __internal_get_default(config*)
    {
        return config(
//   sub_msg_type
   __internal_get_default((sub_auto_completion*)0),
//   sub_msg_type
   __internal_get_default((sub_auto_completion_text*)0),
//   sub_msg_type
   __internal_get_default((sub_line_number*)0),
//   sub_msg_type
   __internal_get_default((sub_highlight_current_block*)0),
//   sub_msg_type
   __internal_get_default((sub_identation*)0),
//   sub_msg_type
   __internal_get_default((sub_line_command_area*)0),
//   sub_msg_type
   __internal_get_default((mtk::list<sub_key_command >*)0)
            );
    }
    

}   //namespace mqeditor {


