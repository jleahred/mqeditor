
#ifndef  __config__
#define  __config__


// generated automatically
// coded last modification:        _CODED_LAST_MODIF


#include "yaml/yaml.h"
#include "support/nullable.hpp"
#include "support/fixed_number.h"
#include "support/date_time.h"
#include "support/list.hpp"
#include "support/alarm.h"
//#include "support/exec_max_frec.h"
#include "support/mtk_string.h"




namespace mqeditor { 




    //-------------------------------
    //      sub_color
    //-------------------------------    
    class sub_color     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit sub_color (    const int16_t&  _red,   const int16_t&  _green,   const int16_t&  _blue,   const int16_t&  _alfa );
        virtual ~sub_color (){}
        virtual std::string get_message_type_as_string       (void) const  { return "sub_color"; }
        static  std::string static_get_message_type_as_string(void)        { return "sub_color"; }
        
        // fields
        int16_t                                   red; 
    int16_t                                   green; 
    int16_t                                   blue; 
    int16_t                                   alfa; 


    
        
    };




    //-------------------------------
    //      sub_key_command
    //-------------------------------    
    class sub_key_command     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit sub_key_command (    const std::string&  _key,   const std::string&  _command );
        virtual ~sub_key_command (){}
        virtual std::string get_message_type_as_string       (void) const  { return "sub_key_command"; }
        static  std::string static_get_message_type_as_string(void)        { return "sub_key_command"; }
        
        // fields
        std::string                               key; 
    std::string                               command; 


    
        
    };




    //-------------------------------
    //      sub_auto_completion_text
    //-------------------------------    
    class sub_auto_completion_text     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit sub_auto_completion_text (    const int&  _automatic_after_letters,   const bool&  _only_words_with_prefix,   const std::string&  _re_split );
        virtual ~sub_auto_completion_text (){}
        virtual std::string get_message_type_as_string       (void) const  { return "sub_auto_completion_text"; }
        static  std::string static_get_message_type_as_string(void)        { return "sub_auto_completion_text"; }
        
        // fields
        int                                       automatic_after_letters; 
    bool                                      only_words_with_prefix; 
    std::string                               re_split; 


    
        
    };




    //-------------------------------
    //      sub_auto_completion
    //-------------------------------    
    class sub_auto_completion     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit sub_auto_completion (    const int&  _popup_max_width );
        virtual ~sub_auto_completion (){}
        virtual std::string get_message_type_as_string       (void) const  { return "sub_auto_completion"; }
        static  std::string static_get_message_type_as_string(void)        { return "sub_auto_completion"; }
        
        // fields
        int                                       popup_max_width; 


    
        
    };




    //-------------------------------
    //      sub_line_number
    //-------------------------------    
    class sub_line_number     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit sub_line_number (    const bool&  _visible,   const sub_color&  _font_color,   const sub_color&  _back_ground_color,   const int&  _font_relative_size );
        virtual ~sub_line_number (){}
        virtual std::string get_message_type_as_string       (void) const  { return "sub_line_number"; }
        static  std::string static_get_message_type_as_string(void)        { return "sub_line_number"; }
        
        // fields
        bool                                      visible; 
    sub_color                                 font_color; 
    sub_color                                 back_ground_color; 
    int                                       font_relative_size; 


    
        
    };




    //-------------------------------
    //      sub_highlight_current_block
    //-------------------------------    
    class sub_highlight_current_block     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit sub_highlight_current_block (    const bool&  _enabled,   const sub_color&  _back_ground_color,   const sub_color&  _font_color );
        virtual ~sub_highlight_current_block (){}
        virtual std::string get_message_type_as_string       (void) const  { return "sub_highlight_current_block"; }
        static  std::string static_get_message_type_as_string(void)        { return "sub_highlight_current_block"; }
        
        // fields
        bool                                      enabled; 
    sub_color                                 back_ground_color; 
    sub_color                                 font_color; 


    
        
    };




    //-------------------------------
    //      sub_identation
    //-------------------------------    
    class sub_identation     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit sub_identation (    const int&  _spaces,   const bool&  _delete_identation );
        virtual ~sub_identation (){}
        virtual std::string get_message_type_as_string       (void) const  { return "sub_identation"; }
        static  std::string static_get_message_type_as_string(void)        { return "sub_identation"; }
        
        // fields
        int                                       spaces; 
    bool                                      delete_identation; 


    
        
    };




    //-------------------------------
    //      sub_line_command_area
    //-------------------------------    
    class sub_line_command_area     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit sub_line_command_area (    const std::string&  _style_sheet );
        virtual ~sub_line_command_area (){}
        virtual std::string get_message_type_as_string       (void) const  { return "sub_line_command_area"; }
        static  std::string static_get_message_type_as_string(void)        { return "sub_line_command_area"; }
        
        // fields
        std::string                               style_sheet; 


    
        
    };




    //-------------------------------
    //      config
    //-------------------------------    
    class config     
    {
    public:
        //  inner classes
    
        
        // constructor
        explicit config (    const sub_auto_completion&  _auto_completion,   const sub_auto_completion_text&  _auto_completion_text,   const sub_line_number&  _line_number,   const sub_highlight_current_block&  _highlight_current_block,   const sub_identation&  _identation,   const sub_line_command_area&  _line_command_area,   const mtk::list<sub_key_command >&  _key_commands );
        virtual ~config (){}
        virtual std::string get_message_type_as_string       (void) const  { return "config"; }
        static  std::string static_get_message_type_as_string(void)        { return "config"; }
        
        // fields
        sub_auto_completion                       auto_completion; 
    sub_auto_completion_text                  auto_completion_text; 
    sub_line_number                           line_number; 
    sub_highlight_current_block               highlight_current_block; 
    sub_identation                            identation; 
    sub_line_command_area                     line_command_area; 
    mtk::list<sub_key_command >               key_commands; 


    
        
    };



    
    
    
//  fordward declarations-----------------------------------------------------------
    std::ostream& operator<< (std::ostream& o, const sub_color & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_color & c);
   void           operator >> (const YAML::Node& n,       sub_color & c);

bool operator== (const sub_color& a, const sub_color& b);
bool operator!= (const sub_color& a, const sub_color& b);

    std::ostream& operator<< (std::ostream& o, const sub_key_command & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_key_command & c);
   void           operator >> (const YAML::Node& n,       sub_key_command & c);

bool operator== (const sub_key_command& a, const sub_key_command& b);
bool operator!= (const sub_key_command& a, const sub_key_command& b);

    std::ostream& operator<< (std::ostream& o, const sub_auto_completion_text & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_auto_completion_text & c);
   void           operator >> (const YAML::Node& n,       sub_auto_completion_text & c);

bool operator== (const sub_auto_completion_text& a, const sub_auto_completion_text& b);
bool operator!= (const sub_auto_completion_text& a, const sub_auto_completion_text& b);

    std::ostream& operator<< (std::ostream& o, const sub_auto_completion & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_auto_completion & c);
   void           operator >> (const YAML::Node& n,       sub_auto_completion & c);

bool operator== (const sub_auto_completion& a, const sub_auto_completion& b);
bool operator!= (const sub_auto_completion& a, const sub_auto_completion& b);

    std::ostream& operator<< (std::ostream& o, const sub_line_number & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_line_number & c);
   void           operator >> (const YAML::Node& n,       sub_line_number & c);

bool operator== (const sub_line_number& a, const sub_line_number& b);
bool operator!= (const sub_line_number& a, const sub_line_number& b);

    std::ostream& operator<< (std::ostream& o, const sub_highlight_current_block & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_highlight_current_block & c);
   void           operator >> (const YAML::Node& n,       sub_highlight_current_block & c);

bool operator== (const sub_highlight_current_block& a, const sub_highlight_current_block& b);
bool operator!= (const sub_highlight_current_block& a, const sub_highlight_current_block& b);

    std::ostream& operator<< (std::ostream& o, const sub_identation & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_identation & c);
   void           operator >> (const YAML::Node& n,       sub_identation & c);

bool operator== (const sub_identation& a, const sub_identation& b);
bool operator!= (const sub_identation& a, const sub_identation& b);

    std::ostream& operator<< (std::ostream& o, const sub_line_command_area & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const sub_line_command_area & c);
   void           operator >> (const YAML::Node& n,       sub_line_command_area & c);

bool operator== (const sub_line_command_area& a, const sub_line_command_area& b);
bool operator!= (const sub_line_command_area& a, const sub_line_command_area& b);

    std::ostream& operator<< (std::ostream& o, const config & c);
   YAML::Emitter& operator << (YAML::Emitter&    o, const config & c);
   void           operator >> (const YAML::Node& n,       config & c);

bool operator== (const config& a, const config& b);
bool operator!= (const config& a, const config& b);


    sub_color  __internal_get_default(sub_color *);
    
    sub_key_command  __internal_get_default(sub_key_command *);
    
    sub_auto_completion_text  __internal_get_default(sub_auto_completion_text *);
    
    sub_auto_completion  __internal_get_default(sub_auto_completion *);
    
    sub_line_number  __internal_get_default(sub_line_number *);
    
    sub_highlight_current_block  __internal_get_default(sub_highlight_current_block *);
    
    sub_identation  __internal_get_default(sub_identation *);
    
    sub_line_command_area  __internal_get_default(sub_line_command_area *);
    
    config  __internal_get_default(config *);
    

}   //namespace mqeditor {






#endif
