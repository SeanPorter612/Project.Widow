#pragma once
#ifndef __WI_Lexer__
#define __WI_Lexer__

//void example01()
//{
//	std::string expression = "(sin(x/pi)cos(2y) + 1)==(sin(x / pi) * cos(2 * y) + 1)";
//
//	generator generator;
//
//	if (!generator.process(expression))
//	{
//		std::cout << "Example01 - Failed to lex: " << expression << std::endl;
//		return;
//	}
//
//	std::cout << "***** Example01 *****" << std::endl;
//	helper::dump(generator);
//	std::cout << "*********************" << std::endl;
//
//}
//
//void example02()
//{
//	std::string expression = "(sin(x/pi)123.456cos(2y) + 1)==(sin(x / pi) * 123.456 * cos(2 * y) + 1)";
//
//	generator generator;
//
//	if (!generator.process(expression))
//	{
//		std::cout << "Example02 - Failed to lex: " << expression << std::endl;
//		return;
//	}
//
//	helper::commutative_inserter ci;
//	ci.process(generator);
//
//	std::cout << "***** Example02 *****" << std::endl;
//	helper::dump(generator);
//	std::cout << "*********************" << std::endl;
//}
//
//void example03()
//{
//	std::string expression = "((1.1 > = 2.2) ! = (3.3 < = 4.4)) < > [x_x : = y_y]";
//
//	generator generator;
//
//	if (!generator.process(expression))
//	{
//		std::cout << "Example03 - Failed to lex: " << expression << std::endl;
//		return;
//	}
//
//	helper::operator_joiner oj;
//	oj.process(generator);
//
//	std::cout << "***** Example03 *****" << std::endl;
//	helper::dump(generator);
//	std::cout << "*********************" << std::endl;
//}
//
//void example04()
//{
//	std::string expression = "{a+(b-[c*(e/{f+g}-h)*i]%[j+(k-{l*m}/n)+o]-p)*q}";
//
//	generator generator;
//
//	if (!generator.process(expression))
//	{
//		std::cout << "Example04 - Failed to lex: " << expression << std::endl;
//		return;
//	}
//
//	helper::bracket_checker bc;
//	bc.process(generator);
//
//	if (!bc.result())
//	{
//		std::cout << "Example04 - Failed Bracket Checker!" << std::endl;
//		return;
//	}
//
//	std::cout << "***** Example04 *****" << std::endl;
//	helper::dump(generator);
//	std::cout << "*********************" << std::endl;
//}
//
//void example05()
//{
//	std::string expression = "(sin(x/pi) * cos(2y) + 1)";
//
//	generator generator;
//
//	if (!generator.process(expression))
//	{
//		std::cout << "Example05 - Failed to lex: " << expression << std::endl;
//		return;
//	}
//
//	helper::symbol_replacer sr;
//
//	sr.add_replace("sin","Deg2RadSine");
//	sr.add_replace("cos","Deg2RadCosine");
//
//	std::size_t change_count = sr.process(generator);
//
//	std::cout << "Example05 - Number of changes: " << change_count << std::endl;
//
//	std::cout << "***** Example05 *****" << std::endl;
//	helper::dump(generator);
//	std::cout << "*********************" << std::endl;
//}

WI_Inline bool is_whitespace(const char c)
{
    return (' '  == c) || ('\n' == c) ||
        ('\r' == c) || ('\t' == c) ||
        ('\b' == c) || ('\v' == c) ||
        ('\f' == c) ;
}

      WI_Inline bool is_operator_char(const char c)
      {
         return ('+' == c) || ('-' == c) ||
                ('*' == c) || ('/' == c) ||
                ('^' == c) || ('<' == c) ||
                ('>' == c) || ('=' == c) ||
                (',' == c) || ('!' == c) ||
                ('(' == c) || (')' == c) ||
                ('[' == c) || (']' == c) ||
                ('{' == c) || ('}' == c) ||
                ('%' == c) || (':' == c) ||
                ('?' == c) || ('&' == c) ||
                ('|' == c) || (';' == c);
      }

      WI_Inline bool is_letter(const char c)
      {
         return (('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z'));
      }

      WI_Inline bool is_digit(const char c)
      {
         return ('0' <= c) && (c <= '9');
      }

      WI_Inline bool is_letter_or_digit(const char c)
      {
         return is_letter(c) || is_digit(c);
      }

      WI_Inline bool is_left_bracket(const char c)
      {
         return ('(' == c) || ('[' == c) || ('{' == c);
      }

      WI_Inline bool is_right_bracket(const char c)
      {
         return (')' == c) || (']' == c) || ('}' == c);
      }

      WI_Inline bool is_bracket(const char c)
      {
         return is_left_bracket(c) || is_right_bracket(c);
      }

      WI_Inline bool is_sign(const char c)
      {
         return ('+' == c) || ('-' == c);
      }

      WI_Inline bool is_invalid(const char c)
      {
         return !is_whitespace(c)    &&
                !is_operator_char(c) &&
                !is_letter(c)        &&
                !is_digit(c)         &&
                ('.' != c)           &&
                ('_' != c)           &&
                ('$' != c)           &&
                ('~' != c)           &&
                ('\'' != c);
      }

      WI_Inline bool imatch(const char c1, const char c2)
      {
         return tolower(c1) == tolower(c2);
      }

      WI_Inline bool imatch(const string& s1, const string& s2)
      {
         if (s1.size() == s2.size())
         {
            for (size_t i = 0; i < s1.size(); ++i)
            {
               if (tolower(s1[i]) != tolower(s2[i]))
               {
                  return false;
               }
            }
            return true;
         }
         return false;
      }

      struct ilesscompare
      {
         WI_Inline bool operator()(const string& s1, const string& s2) const
         {
            const size_t length = min(s1.size(),s2.size());
            for (size_t i = 0; i < length;  ++i)
            {
               if (tolower(s1[i]) > tolower(s2[i]))
                  return false;
               else if (tolower(s1[i]) < tolower(s2[i]))
                  return true;
            }
            return s1.size() < s2.size();
         }
      };

      WI_Inline void cleanup_escapes(string& s)
      {
         string::iterator itr1 = s.begin();
         string::iterator itr2 = s.begin();
         string::iterator end =    s.end();
         size_t removal_count = 0;
         while (end != itr1)
         {
            bool bypass = false;
            if ('\\' == (*itr1))
            {
               bypass = true;
               ++removal_count;
               if (end == ++itr1)
                  break;
               else if ('\\' != (*itr1))
               {
                  switch (*itr1)
                  {
                     case 'n' : (*itr1) = '\n'; break;
                     case 'r' : (*itr1) = '\r'; break;
                     case 't' : (*itr1) = '\t'; break;
                  }
                  continue;
               }
               else
                  bypass = false;
            }

            if (!bypass)
            {
               if (itr1 != itr2)
               {
                  (*itr2) = (*itr1);
               }
               ++itr1;
               ++itr2;
            }
         }
         s.resize(s.size() - removal_count);
      }

   struct token
   {

      enum token_type
      {
         e_none        =   0, e_error       =   1, e_err_symbol  =   2,
         e_err_number  =   3, e_err_string  =   4, e_err_sfunc   =   5,
         e_eof         =   6, e_number      =   7, e_symbol      =   8,
         e_string      =   9, e_assign      =  10, e_shr         =  11,
         e_shl         =  12, e_lte         =  13, e_ne          =  14,
         e_gte         =  15, e_lt          = '<', e_gt          = '>',
         e_eq          = '=', e_rbracket    = ')', e_lbracket    = '(',
         e_rsqrbracket = ']', e_lsqrbracket = '[', e_rcrlbracket = '}',
         e_lcrlbracket = '{', e_comma       = ',', e_add         = '+',
         e_sub         = '-', e_div         = '/', e_mul         = '*',
         e_mod         = '%', e_pow         = '^', e_colon       = ':'
      };

      token()
      : type(e_none),
        value(""),
        position( 0 )
      {}

      void clear()
      {
         type     = e_none;
         value    = "";
         position = 0;
      }

      template <typename Iterator>
      WI_Inline token& set_operator(const token_type tt, const Iterator begin, const Iterator end, const Iterator base_begin = Iterator(0))
      {
         type = tt;
         value.assign(begin,end);
         if (base_begin)
            position = distance(base_begin,begin);
         return *this;
      }

      template <typename Iterator>
      WI_Inline token& set_symbol(const Iterator begin, const Iterator end, const Iterator base_begin = Iterator(0))
      {
         type = e_symbol;
         value.assign(begin,end);
         if (base_begin)
            position = distance(base_begin,begin);
         return *this;
      }

      template <typename Iterator>
      WI_Inline token& set_numeric(const Iterator begin, const Iterator end, const Iterator base_begin = Iterator(0))
      {
         type = e_number;
         value.assign(begin,end);
         if (base_begin)
            position = distance(base_begin,begin);
         return *this;
      }

      template <typename Iterator>
      WI_Inline token& set_string(const Iterator begin, const Iterator end, const Iterator base_begin = Iterator(0))
      {
         type = e_string;
         value.assign(begin,end);
         if (base_begin)
            position = distance(base_begin,begin);
         return *this;
      }

      WI_Inline token& set_string(const string& s, const size_t p)
      {
         type     = e_string;
         value    = s;
         position = p;
         return *this;
      }

      template <typename Iterator>
      WI_Inline token& set_error(const token_type et, const Iterator begin, const Iterator end, const Iterator base_begin = Iterator(0))
      {
         if (
              (e_error      == et) ||
              (e_err_symbol == et) ||
              (e_err_number == et) ||
              (e_err_string == et)
            )
         {
            type = e_error;
         }
         else
            type = e_error;
         value.assign(begin,end);
         if (base_begin)
            position = distance(base_begin,begin);
         return *this;
      }

      static WI_Inline string to_str(token_type t)
      {
         switch (t)
         {
            case e_none        : return "NONE";
            case e_error       : return "ERROR";
            case e_err_symbol  : return "ERROR_SYMBOL";
            case e_err_number  : return "ERROR_NUMBER";
            case e_err_string  : return "ERROR_STRING";
            case e_eof         : return "EOF";
            case e_number      : return "NUMBER";
            case e_symbol      : return "SYMBOL";
            case e_string      : return "STRING";
            case e_assign      : return ":=";
            case e_shr         : return ">>";
            case e_shl         : return "<<";
            case e_lte         : return "<=";
            case e_ne          : return "!=";
            case e_gte         : return ">=";
            case e_lt          : return "<";
            case e_gt          : return ">";
            case e_eq          : return "=";
            case e_rbracket    : return ")";
            case e_lbracket    : return "(";
            case e_rsqrbracket : return "]";
            case e_lsqrbracket : return "[";
            case e_rcrlbracket : return "}";
            case e_lcrlbracket : return "{";
            case e_comma       : return ",";
            case e_add         : return "+";
            case e_sub         : return "-";
            case e_div         : return "/";
            case e_mul         : return "*";
            case e_mod         : return "%";
            case e_pow         : return "^";
            case e_colon       : return ":";
            default            : return "UNKNOWN";
         }
      }

      WI_Inline bool is_error() const
      {
         return (
                  (e_error      == type) ||
                  (e_err_symbol == type) ||
                  (e_err_number == type) ||
                  (e_err_string == type)
                );
      }

      token_type type;
      string value;
      size_t position;
   };

   class generator
   {
   public:

      typedef token token_t;
      typedef deque<token_t> token_list_t;
      typedef deque<token_t>::iterator token_list_itr_t;

      generator()
      : base_itr_(0),
        s_itr_(0),
        s_end_(0)
      {
         clear();
      }

      WI_Inline void clear()
      {
         base_itr_ = 0;
         s_itr_    = 0;
         s_end_    = 0;
         token_list_.clear();
         token_itr_ = token_list_.end();
         store_token_itr_ = token_list_.end();
      }

      WI_Inline bool process(const string& str)
      {
         base_itr_ = str.data();
         s_itr_    = str.data();
         s_end_    = str.data() + str.size();
         eof_token_.set_operator(token_t::e_eof,s_end_,s_end_,base_itr_);
         token_list_.clear();
         while (!is_end(s_itr_))
         {
            scan_token();
            if (token_list_.empty())
               return true;
            else if (token_list_.back().is_error())
            {
               return false;
            }
         }
         return true;
      }

      WI_Inline bool empty() const
      {
         return token_list_.empty();
      }

      WI_Inline size_t size() const
      {
         return token_list_.size();
      }

      WI_Inline void begin()
      {
         token_itr_ = token_list_.begin();
         store_token_itr_ = token_list_.begin();
      }

      WI_Inline void store()
      {
         store_token_itr_ = token_itr_;
      }

      WI_Inline void restore()
      {
         token_itr_ = store_token_itr_;
      }

      WI_Inline token_t& next_token()
      {
         if (token_list_.end() != token_itr_)
         {
            return *token_itr_++;
         }
         else
            return eof_token_;
      }

      WI_Inline token_t& peek_next_token()
      {
         if (token_list_.end() != token_itr_)
         {
            return *token_itr_;
         }
         else
            return eof_token_;
      }

      WI_Inline token_t& operator[](const size_t& index)
      {
         if (index < token_list_.size())
            return token_list_[index];
         else
            return eof_token_;
      }

      WI_Inline token_t operator[](const size_t& index) const
      {
         if (index < token_list_.size())
            return token_list_[index];
         else
            return eof_token_;
      }

      WI_Inline bool finished() const
      {
         return (token_list_.end() == token_itr_);
      }

   private:

      WI_Inline bool is_end(const char* itr)
      {
         return (s_end_ == itr);
      }

      WI_Inline void skip_whitespace()
      {
         while (!is_end(s_itr_) && is_whitespace(*s_itr_))
         {
            ++s_itr_;
         }
      }

      WI_Inline void skip_comments()
      {
         //The following comment styles are supported:
         // 1. // .... \n
         // 2. #  .... \n
         // 3. /* .... */
         struct test
         {
            static WI_Inline bool comment_start(const char c0, const char c1, int& mode, int& incr)
            {
               mode = 0;
                    if ('#' == c0)    { mode = 1; incr = 1; }
               else if ('/' == c0)
               {
                       if ('/' == c1) { mode = 1; incr = 2; }
                  else if ('*' == c1) { mode = 2; incr = 2; }
               }
               return (mode != 0);
            }

            static WI_Inline bool comment_end(const char c0, const char c1, const int mode)
            {
               return ((1 == mode) && ('\n' == c0)) ||
                      ((2 == mode) && ( '*' == c0) && ('/' == c1));
            }
         };

         int mode = 0;
         int increment = 0;
         if (is_end(s_itr_) || is_end((s_itr_ + 1)))
            return;
         else if (!test::comment_start(*s_itr_,*(s_itr_ + 1),mode,increment))
            return;
         s_itr_ += increment;
         while (!is_end(s_itr_) && !test::comment_end(*s_itr_,*(s_itr_ + 1),mode))
         {
            ++s_itr_;
         }
         if (!is_end(s_itr_))
         {
            s_itr_ += mode;
            skip_whitespace();
            skip_comments();
         }
      }

      WI_Inline void scan_token()
      {
         skip_whitespace();
         skip_comments();
         if (is_end(s_itr_))
         {
            return;
         }
         else if (is_operator_char(*s_itr_))
         {
            scan_operator();
            return;
         }
         else if (is_letter(*s_itr_))
         {
            scan_symbol();
            return;
         }
         else if (is_digit((*s_itr_)) || ('.' == (*s_itr_)))
         {
            scan_number();
            return;
         }
         else if ('\'' == (*s_itr_))
         {
            scan_string();
            return;
         }
         else
         {
            token_t t;
            t.set_error(token::e_error,s_itr_,s_itr_ + 2,base_itr_);
            token_list_.push_back(t);
            ++s_itr_;
         }
      }

      WI_Inline void scan_operator()
      {
         token_t t;

         if (!is_end(s_itr_ + 1))
         {
            token_t::token_type ttype = token_t::e_none;
            char c0 = s_itr_[0];
            char c1 = s_itr_[1];
                 if ((c0 == '<') && (c1 == '=')) ttype = token_t::e_lte;
            else if ((c0 == '>') && (c1 == '=')) ttype = token_t::e_gte;
            else if ((c0 == '<') && (c1 == '>')) ttype = token_t::e_ne;
            else if ((c0 == '!') && (c1 == '=')) ttype = token_t::e_ne;
            else if ((c0 == '=') && (c1 == '=')) ttype = token_t::e_eq;
            else if ((c0 == ':') && (c1 == '=')) ttype = token_t::e_assign;
            else if ((c0 == '<') && (c1 == '<')) ttype = token_t::e_shl;
            else if ((c0 == '>') && (c1 == '>')) ttype = token_t::e_shr;

            if (token_t::e_none != ttype)
            {
               t.set_operator(ttype,s_itr_,s_itr_ + 2,base_itr_);
               token_list_.push_back(t);
               s_itr_ += 2;
               return;
            }
         }
         if ('<' == *s_itr_)
            t.set_operator(token_t::e_lt ,s_itr_,s_itr_ + 1,base_itr_);
         else if ('>' == *s_itr_)
            t.set_operator(token_t::e_gt ,s_itr_,s_itr_ + 1,base_itr_);
         else if (';' == *s_itr_)
            t.set_operator(token_t::e_eof,s_itr_,s_itr_ + 1,base_itr_);
         else if ('&' == *s_itr_)
            t.set_symbol(s_itr_,s_itr_ + 1,base_itr_);
         else if ('|' == *s_itr_)
            t.set_symbol(s_itr_,s_itr_ + 1,base_itr_);
         else
            t.set_operator(token_t::token_type(*s_itr_),s_itr_,s_itr_ + 1,base_itr_);
         token_list_.push_back(t);
         ++s_itr_;
      }

      WI_Inline void scan_symbol()
      {
         const char* begin = s_itr_;
         while (
                (!is_end(s_itr_)) &&
                (is_letter_or_digit(*s_itr_) || ((*s_itr_) == '_'))
               )
         {
            ++s_itr_;
         }
         token_t t;
         t.set_symbol(begin,s_itr_,base_itr_);
         token_list_.push_back(t);
      }

      WI_Inline void scan_number()
      {
         /*
            Attempt to match a valid numeric value in one of the following formats:
            1. 123456
            2. 123.456
            3. 123.456e3
            4. 123.456E3
            5. 123.456e+3
            6. 123.456E+3
            7. 123.456e-3
            8. 123.456E-3
         */
         const char* begin      = s_itr_;
         bool dot_found         = false;
         bool e_found           = false;
         bool post_e_sign_found = false;
         token_t t;

         while (!is_end(s_itr_))
         {
            if ('.' == (*s_itr_))
            {
               if (dot_found)
               {
                  t.set_error(token::e_err_number,begin,s_itr_,base_itr_);
                  token_list_.push_back(t);
                  return;
               }
               dot_found = true;
               ++s_itr_;
               continue;
            }
            else if (imatch('e',(*s_itr_)))
            {
               const char& c = *(s_itr_ + 1);

               if (is_end(s_itr_ + 1))
               {
                  t.set_error(token::e_err_number,begin,s_itr_,base_itr_);
                  token_list_.push_back(t);
                  return;
               }
               else if (
                        ('+' != c) &&
                        ('-' != c) &&
                        !is_digit(c)
                       )
               {
                  t.set_error(token::e_err_number,begin,s_itr_,base_itr_);
                  token_list_.push_back(t);
                  return;
               }

               e_found = true;
               ++s_itr_;
               continue;
            }
            else if (e_found && is_sign(*s_itr_))
            {
               if (post_e_sign_found)
               {
                  t.set_error(token::e_err_number,begin,s_itr_,base_itr_);
                  token_list_.push_back(t);
                  return;
               }

               post_e_sign_found = true;
               ++s_itr_;
               continue;
            }
            else if (('.' != (*s_itr_)) && !is_digit(*s_itr_))
               break;
            else
               ++s_itr_;
         }

         t.set_numeric(begin,s_itr_,base_itr_);
         token_list_.push_back(t);
         return;
      }

      WI_Inline void scan_string()
      {
         const char* begin = s_itr_ + 1;
         token_t t;
         if (distance(s_itr_,s_end_) < 2)
         {
            t.set_error(token::e_err_string,s_itr_,s_end_,base_itr_);
            token_list_.push_back(t);
            return;
         }
         ++s_itr_;

         bool escaped_found = false;
         bool escaped = false;

         while (!is_end(s_itr_))
         {
            if ('\\' == *s_itr_)
            {
               escaped_found = true;
               escaped = true;
               ++s_itr_;
               continue;
            }
            else if (!escaped)
            {
               if ('\'' == *s_itr_)
                  break;
            }
            else if (escaped)
               escaped = false;
            ++s_itr_;
         }

         if (is_end(s_itr_))
         {
            t.set_error(token::e_err_string,begin,s_itr_,base_itr_);
            token_list_.push_back(t);
            return;
         }

         if (!escaped_found)
            t.set_string(begin,s_itr_,base_itr_);
         else
         {
            string parsed_string(begin,s_itr_);
            cleanup_escapes(parsed_string);
            t.set_string(parsed_string, distance(base_itr_,begin));
         }

         token_list_.push_back(t);
         ++s_itr_;
         return;
      }

   private:

      token_list_t token_list_;
      token_list_itr_t token_itr_;
      token_list_itr_t store_token_itr_;
      token_t eof_token_;
      const char* base_itr_;
      const char* s_itr_;
      const char* s_end_;

      friend class token_scanner;
      friend class token_modifier;
      friend class token_inserter;
      friend class token_joiner;
   };

   class helper_interface
   {
   public:

      virtual void init()                     {              }
      virtual void reset()                    {              }
      virtual bool result()                   { return true; }
      virtual size_t process(generator&) { return 0;    }
      virtual ~helper_interface()             {              }
   };

   class token_scanner : public helper_interface
   {
   public:

      virtual ~token_scanner()
      {}

      explicit token_scanner(const size_t& stride)
      : stride_(stride)
      {
         if (stride > 4)
         {
            throw invalid_argument("token_scanner() - Invalid stride value");
         }
      }

      WI_Inline size_t process(generator& g)
      {
         if (!g.token_list_.empty())
         {
            for (size_t i = 0; i < (g.token_list_.size() - stride_ + 1); ++i)
            {
               token t;
               switch (stride_)
               {
                  case 1 :
                           {
                              const token& t0 = g.token_list_[i];
                              if (!operator()(t0)) return i;
                           }
                           break;

                  case 2 :
                           {
                              const token& t0 = g.token_list_[i    ];
                              const token& t1 = g.token_list_[i + 1];
                              if (!operator()(t0,t1)) return i;
                           }
                           break;

                  case 3 :
                           {
                              const token& t0 = g.token_list_[i    ];
                              const token& t1 = g.token_list_[i + 1];
                              const token& t2 = g.token_list_[i + 2];
                              if (!operator()(t0,t1,t2)) return i;
                           }
                           break;

                  case 4 :
                           {
                              const token& t0 = g.token_list_[i    ];
                              const token& t1 = g.token_list_[i + 1];
                              const token& t2 = g.token_list_[i + 2];
                              const token& t3 = g.token_list_[i + 3];
                              if (!operator()(t0,t1,t2,t3)) return i;
                           }
                           break;
               }
            }
         }
         return (g.token_list_.size() - stride_ + 1);
      }

      virtual bool operator()(const token&)
      {
         return false;
      }

      virtual bool operator()(const token&, const token&)
      {
         return false;
      }

      virtual bool operator()(const token&, const token&, const token&)
      {
         return false;
      }

      virtual bool operator()(const token&, const token&, const token&, const token&)
      {
         return false;
      }

   private:

      size_t stride_;
   };

   class token_modifier : public helper_interface
   {
   public:

      WI_Inline size_t process(generator& g)
      {
         size_t changes = 0;
         for (size_t i = 0; i < g.token_list_.size(); ++i)
         {
            if (modify(g.token_list_[i])) changes++;
         }
         return changes;
      }

      virtual bool modify(token& t) = 0;
   };

   class token_inserter : public helper_interface
   {
   public:

      explicit token_inserter(const size_t& stride)
      : stride_(stride)
      {
         if (stride > 5)
         {
            throw invalid_argument("token_inserter() - Invalid stride value");
         }
      }

      WI_Inline size_t process(generator& g)
      {
         if (g.token_list_.empty())
            return 0;
         size_t changes = 0;
         for (size_t i = 0; i < (g.token_list_.size() - stride_ + 1); ++i)
         {
            token t;
            int insert_index = -1;
            switch (stride_)
            {
               case 1 : insert_index = insert(g.token_list_[i],t);
                        break;

               case 2 : insert_index = insert(g.token_list_[i],g.token_list_[i + 1],t);
                        break;

               case 3 : insert_index = insert(g.token_list_[i],g.token_list_[i + 1],g.token_list_[i + 2],t);
                        break;

               case 4 : insert_index = insert(g.token_list_[i],g.token_list_[i + 1],g.token_list_[i + 2],g.token_list_[i + 3],t);
                        break;

               case 5 : insert_index = insert(g.token_list_[i],g.token_list_[i + 1],g.token_list_[i + 2],g.token_list_[i + 3],g.token_list_[i + 4],t);
                        break;
            }

            if ((insert_index >= 0) && (insert_index <= (static_cast<int>(stride_) + 1)))
            {
               g.token_list_.insert(g.token_list_.begin() + (i + insert_index),t);
               changes++;
            }
         }

         return changes;
      }

      virtual WI_Inline int insert(const token&, token& )
      {
         return -1;
      }

      virtual WI_Inline int insert(const token&, const token&, token&)
      {
         return -1;
      }

      virtual WI_Inline int insert(const token&, const token&, const token&, token&)
      {
         return -1;
      }

      virtual WI_Inline int insert(const token&, const token&, const token&, const token&, token&)
      {
         return -1;
      }

      virtual WI_Inline int insert(const token&, const token&, const token&, const token&, const token&, token&)
      {
         return -1;
      }

   private:

      size_t stride_;
   };

   class token_joiner : public helper_interface
   {
   public:

      WI_Inline size_t process(generator& g)
      {
         if (g.token_list_.empty())
            return 0;
         size_t changes = 0;
         for (size_t i = 0; i < g.token_list_.size() - 1; ++i)
         {
            token t;
            if (join(g.token_list_[i],g.token_list_[i + 1],t))
            {
               g.token_list_[i] = t;
               g.token_list_.erase(g.token_list_.begin() + (i + 1));
               ++changes;
            }
         }
         return changes;
      }

      virtual bool join(const token&, const token&, token&) = 0;
   };

   namespace helper
   {

      WI_Inline void dump(generator& generator)
      {
         for (size_t i = 0; i < generator.size(); ++i)
         {
            token t = generator[i];
            printf("Token[%02d] @ %03d  %6s  -->  '%s'\n",
                   static_cast<unsigned int>(i),
                   static_cast<unsigned int>(t.position),
                   t.to_str(t.type).c_str(),
                   t.value.c_str());
         }
      }

      class commutative_inserter : public token_inserter
      {
      public:

         commutative_inserter()
         : token_inserter(2)
         {}

         WI_Inline void ignore_symbol(const string& symbol)
         {
            ignore_set_.insert(symbol);
         }

         WI_Inline int insert(const token& t0, const token& t1, token& new_token)
         {
            new_token.type     = token::e_mul;
            new_token.value    = "*";
            new_token.position = t1.position;
            bool match         = false;

            if (t0.type == token::e_symbol)
            {
               if (ignore_set_.end() != ignore_set_.find(t0.value))
               {
                  return -1;
               }
               else if (!t0.value.empty() && ('$' == t0.value[0]))
               {
                  return -1;
               }
            }

            if (t1.type == token::e_symbol)
            {
               if (ignore_set_.end() != ignore_set_.find(t1.value))
               {
                  return -1;
               }
            }
                 if ((t0.type == token::e_number     ) && (t1.type == token::e_symbol     )) match = true;
            else if ((t0.type == token::e_number     ) && (t1.type == token::e_lbracket   )) match = true;
            else if ((t0.type == token::e_number     ) && (t1.type == token::e_lcrlbracket)) match = true;
            else if ((t0.type == token::e_number     ) && (t1.type == token::e_lsqrbracket)) match = true;
            else if ((t0.type == token::e_symbol     ) && (t1.type == token::e_number     )) match = true;
            else if ((t0.type == token::e_rbracket   ) && (t1.type == token::e_number     )) match = true;
            else if ((t0.type == token::e_rcrlbracket) && (t1.type == token::e_number     )) match = true;
            else if ((t0.type == token::e_rsqrbracket) && (t1.type == token::e_number     )) match = true;
            else if ((t0.type == token::e_rbracket   ) && (t1.type == token::e_symbol     )) match = true;
            else if ((t0.type == token::e_rcrlbracket) && (t1.type == token::e_symbol     )) match = true;
            else if ((t0.type == token::e_rsqrbracket) && (t1.type == token::e_symbol     )) match = true;
            return (match) ? 1 : -1;
         }

      private:

         set<string,ilesscompare> ignore_set_;
      };

      class operator_joiner : public token_joiner
      {
      public:

         WI_Inline bool join(const token& t0, const token& t1, token& t)
         {
            //': =' --> ':='
            if ((t0.type == token::e_colon) && (t1.type == token::e_eq))
            {
               t.type = token::e_assign;
               t.value = ":=";
               t.position = t0.position;
               return true;
            }
            //'> =' --> '>='
            else if ((t0.type == token::e_gt) && (t1.type == token::e_eq))
            {
               t.type = token::e_gte;
               t.value = ">=";
               t.position = t0.position;
               return true;
            }
            //'< =' --> '<='
            else if ((t0.type == token::e_lt) && (t1.type == token::e_eq))
            {
               t.type = token::e_lte;
               t.value = "<=";
               t.position = t0.position;
               return true;
            }
            //'= =' --> '=='
            else if ((t0.type == token::e_eq) && (t1.type == token::e_eq))
            {
               t.type = token::e_eq;
               t.value = "==";
               t.position = t0.position;
               return true;
            }
            //'! =' --> '!='
            else if ((static_cast<char>(t0.type) == '!') && (t1.type == token::e_eq))
            {
               t.type = token::e_ne;
               t.value = "!=";
               t.position = t0.position;
               return true;
            }
            //'< >' --> '<>'
            else if ((t0.type == token::e_lt) && (t1.type == token::e_gt))
            {
               t.type = token::e_ne;
               t.value = "<>";
               t.position = t0.position;
               return true;
            }
            else
               return false;
         }
      };

      class bracket_checker : public token_scanner
      {
      public:

         bracket_checker()
         : token_scanner(1),
           state_(true)
         {}

         bool result()
         {
            return state_ && stack_.empty();
         }

         token error_token()
         {
            return error_token_;
         }

         void reset()
         {
            //why? because msvc doesn't support swap properly.
            stack_ = stack<char>();
            state_ = true;
            error_token_.clear();
         }

         bool operator()(const token& t)
         {
            if (!t.value.empty()                         &&
                (token::e_string != t.type)     &&
                (token::e_symbol != t.type)     &&
                is_bracket(t.value[0])
               )
            {
               char c = t.value[0];
                    if (t.type == token::e_lbracket)    stack_.push(')');
               else if (t.type == token::e_lcrlbracket) stack_.push('}');
               else if (t.type == token::e_lsqrbracket) stack_.push(']');
               else if (is_right_bracket(c))
               {
                  if (stack_.empty())
                  {
                     state_ = false;
                     error_token_ = t;
                     return false;
                  }
                  else if (c != stack_.top())
                  {
                     state_ = false;
                     error_token_ = t;
                     return false;
                  }
                  else
                     stack_.pop();
               }
            }
            return true;
         }

      private:

         bool state_;
         stack<char> stack_;
         token error_token_;
      };

      class symbol_replacer : public token_modifier
      {
      private:

         typedef map<string,pair<string,token::token_type>,ilesscompare> replace_map_t;

      public:

         bool remove(const string& target_symbol)
         {
            replace_map_t::iterator itr = replace_map_.find(target_symbol);
            if (replace_map_.end() == itr)
               return false;
            replace_map_.erase(itr);
            return true;
         }

         bool add_replace(const string& target_symbol,
                          const string& replace_symbol,
                          const token::token_type token_type = token::e_symbol)
         {
            replace_map_t::iterator itr = replace_map_.find(target_symbol);
            if (replace_map_.end() != itr)
            {
               return false;
            }
            replace_map_[target_symbol] = make_pair(replace_symbol,token_type);
            return true;
         }

         void clear()
         {
            replace_map_.clear();
         }

      private:

         bool modify(token& t)
         {
            if (token::e_symbol == t.type)
            {
               if (replace_map_.empty())
                  return false;
               replace_map_t::iterator itr = replace_map_.find(t.value);
               if (replace_map_.end() != itr)
               {
                  t.value = itr->second.first;
                  t.type  = itr->second.second;
                  return true;
               }
            }
            return false;
         }

         replace_map_t replace_map_;
      };

      class sequence_validator : public token_scanner
      {
      private:

         typedef pair<token::token_type,token::token_type> token_pair_t;
         typedef set<token_pair_t> set_t;

      public:

         sequence_validator()
         : token_scanner(2)
         {
            add_invalid(token::e_number,token::e_number);
            add_invalid(token::e_string,token::e_string);
            add_invalid(token::e_number,token::e_string);
            add_invalid(token::e_string,token::e_number);
            add_invalid(token::e_string,token::e_colon);
            add_invalid(token::e_colon,token::e_string);
            add_invalid_set1(token::e_assign);
            add_invalid_set1(token::e_shr);
            add_invalid_set1(token::e_shl);
            add_invalid_set1(token::e_lte);
            add_invalid_set1(token::e_ne);
            add_invalid_set1(token::e_gte);
            add_invalid_set1(token::e_lt);
            add_invalid_set1(token::e_gt);
            add_invalid_set1(token::e_eq);
            add_invalid_set1(token::e_comma);
            add_invalid_set1(token::e_add);
            add_invalid_set1(token::e_sub);
            add_invalid_set1(token::e_div);
            add_invalid_set1(token::e_mul);
            add_invalid_set1(token::e_mod);
            add_invalid_set1(token::e_pow);
            add_invalid_set1(token::e_colon);
         }

         bool result()
         {
            return error_list_.empty();
         }

         bool operator()(const token& t0, const token& t1)
         {
            set_t::value_type p = make_pair(t0.type,t1.type);
            if (invalid_bracket_check(t0.type,t1.type))
            {
               error_list_.push_back(make_pair(t0,t1));
            }
            else if (invalid_comb_.find(p) != invalid_comb_.end())
               error_list_.push_back(make_pair(t0,t1));
            return true;
         }

         size_t error_count()
         {
            return error_list_.size();
         }

         pair<token,token> error(const size_t index)
         {
            if (index < error_list_.size())
            {
               return error_list_[index];
            }
            else
            {
               static const token error_token;
               return make_pair(error_token,error_token);
            }
         }

         void clear_errors()
         {
            error_list_.clear();
         }

      private:

         void add_invalid(token::token_type base, token::token_type t)
         {
            invalid_comb_.insert(make_pair(base,t));
         }

         void add_invalid_set1(token::token_type t)
         {
            add_invalid(t,token::e_assign);
            add_invalid(t,token::e_shr);
            add_invalid(t,token::e_shl);
            add_invalid(t,token::e_lte);
            add_invalid(t,token::e_ne);
            add_invalid(t,token::e_gte);
            add_invalid(t,token::e_lt);
            add_invalid(t,token::e_gt);
            add_invalid(t,token::e_eq);
            add_invalid(t,token::e_comma);
            add_invalid(t,token::e_div);
            add_invalid(t,token::e_mul);
            add_invalid(t,token::e_mod);
            add_invalid(t,token::e_pow);
            add_invalid(t,token::e_colon);
         }

         bool invalid_bracket_check(token::token_type base, token::token_type t)
         {
            if (is_right_bracket(static_cast<char>(base)))
            {
               switch (t)
               {
                  case token::e_string : return true;
                  case token::e_assign : return true;
                  default                       : return false;
               }
            }
            else if (is_left_bracket(static_cast<char>(base)))
            {
               if (is_right_bracket(static_cast<char>(t)))
                  return false;
               else if (is_left_bracket(static_cast<char>(t)))
                  return false;
               else
               {
                  switch (t)
                  {
                     case token::e_number : return false;
                     case token::e_symbol : return false;
                     case token::e_string : return false;
                     case token::e_add    : return false;
                     case token::e_sub    : return false;
                     case token::e_colon  : return false;
                     default                       : return true;
                  }
               }
            }
            else if (is_right_bracket(static_cast<char>(t)))
            {
               switch (base)
               {
                  case token::e_number : return false;
                  case token::e_symbol : return false;
                  case token::e_string : return false;
                  case token::e_eof    : return false;
                  case token::e_colon  : return false;
                  default                       : return true;
               }
            }
            else if (is_left_bracket(static_cast<char>(t)))
            {
               switch (base)
               {
                  case token::e_rbracket    : return true;
                  case token::e_rsqrbracket : return true;
                  case token::e_rcrlbracket : return true;
                  default                            : return false;
               }
            }
            return false;
         }

         set_t invalid_comb_;
         deque<pair<token,token> > error_list_;

      };

      struct helper_assembly
      {
         WI_Inline bool register_scanner(token_scanner* scanner)
         {
            if (token_scanner_list.end() != find(token_scanner_list.begin(),
                                                      token_scanner_list.end(),
                                                      scanner))
            {
               return false;
            }
            token_scanner_list.push_back(scanner);
            return true;
         }

         WI_Inline bool register_modifier(token_modifier* modifier)
         {
            if (token_modifier_list.end() != find(token_modifier_list.begin(),
                                                       token_modifier_list.end(),
                                                       modifier))
            {
               return false;
            }
            token_modifier_list.push_back(modifier);
            return true;
         }

         WI_Inline bool register_joiner(token_joiner* joiner)
         {
            if (token_joiner_list.end() != find(token_joiner_list.begin(),
                                                     token_joiner_list.end(),
                                                     joiner))
            {
               return false;
            }
            token_joiner_list.push_back(joiner);
            return true;
         }

         WI_Inline bool register_inserter(token_inserter* inserter)
         {
            if (token_inserter_list.end() != find(token_inserter_list.begin(),
                                                       token_inserter_list.end(),
                                                       inserter))
            {
               return false;
            }
            token_inserter_list.push_back(inserter);
            return true;
         }

         WI_Inline bool run_modifiers(generator& g)
         {
            error_token_modifier = reinterpret_cast<token_modifier*>(0);
            bool result = true;
            for (size_t i = 0; i < token_modifier_list.size(); ++i)
            {
               token_modifier& modifier = (*token_modifier_list[i]);
               modifier.reset();
               modifier.process(g);
               if (!modifier.result())
               {
                  error_token_modifier = token_modifier_list[i];
                  return false;
               }
            }
            return result;
         }

         WI_Inline bool run_joiners(generator& g)
         {
            error_token_joiner = reinterpret_cast<token_joiner*>(0);
            bool result = true;
            for (size_t i = 0; i < token_joiner_list.size(); ++i)
            {
               token_joiner& joiner = (*token_joiner_list[i]);
               joiner.reset();
               joiner.process(g);
               if (!joiner.result())
               {
                  error_token_joiner = token_joiner_list[i];
                  return false;
               }
            }
            return result;
         }

         WI_Inline bool run_inserters(generator& g)
         {
            error_token_inserter = reinterpret_cast<token_inserter*>(0);
            bool result = true;
            for (size_t i = 0; i < token_inserter_list.size(); ++i)
            {
               token_inserter& inserter = (*token_inserter_list[i]);
               inserter.reset();
               inserter.process(g);
               if (!inserter.result())
               {
                  error_token_inserter = token_inserter_list[i];
                  return false;
               }
            }
            return result;
         }

         WI_Inline bool run_scanners(generator& g)
         {
            error_token_scanner = reinterpret_cast<token_scanner*>(0);
            bool result = true;
            for (size_t i = 0; i < token_scanner_list.size(); ++i)
            {
               token_scanner& scanner = (*token_scanner_list[i]);
               scanner.reset();
               scanner.process(g);
               if (!scanner.result())
               {
                  error_token_scanner = token_scanner_list[i];
                  return false;
               }
            }
            return result;
         }

         deque<token_scanner*>  token_scanner_list;
         deque<token_modifier*> token_modifier_list;
         deque<token_joiner*>   token_joiner_list;
         deque<token_inserter*> token_inserter_list;

         token_scanner*  error_token_scanner;
         token_modifier* error_token_modifier;
         token_joiner*   error_token_joiner;
         token_inserter* error_token_inserter;
      };
}

/*
WI_Inline bool WI_IsCharWhiteSpace ( const char c )
{
    return (' '  == c) || ('\n' == c) ||
           ('\r' == c) || ('\t' == c) ||
		   ('\b' == c) || ('\v' == c) ||
		   ('\f' == c);
}

WI_Inline bool WI_IsCharOperator ( const char c )
{
    return ( '+' == c )	||	( '-' == c ) ||
           ( '*' == c )	||	( '/' == c ) ||
		   ( '^' == c )	||	( '<' == c ) ||
		   ( '>' == c )	||	( '=' == c ) ||
		   ( ',' == c )	||	( '!' == c ) ||
		   ( '(' == c )	||	( ')' == c ) ||
		   ( '[' == c )	||	( ']' == c ) ||
		   ( '{' == c )	||	( '}' == c ) ||
		   ( '%' == c )	||	( ':' == c ) ||
		   ( '?' == c )	||	( '&' == c ) ||
		   ( '|' == c )	||	( ';' == c );
}


WI_Inline bool WI_IsCharLetter ( const char c )
{
    return ( ( 'a' <= c )		&& 
			 ( c <= 'z' ) )		||
			 ( ( 'A' <= c )		&&
			 ( c <= 'Z' ) );
}

WI_Inline bool WI_IsCharDigit(const char c)
{
    return ('0' <= c) && (c <= '9');
}

WI_Inline bool WI_IsCharLetterOrDigit ( const char c )
{
    return WI_IsCharLetter ( c ) || 
		   WI_IsCharDigit  ( c );
}

WI_Inline bool WI_IsCharCloseBracket ( const char c )
{
    return ( '(' == c ) || 
		   ( '[' == c ) || 
		   ( '{' == c );
}

WI_Inline bool WI_IsCharOpenBracket ( const char c )
{
    return ( ')' == c ) ||
		   ( ']' == c ) || 
		   ( '}' == c );
}

WI_Inline bool WI_IsCharBracket ( const char c )
{
    return WI_IsCharOpenBracket  ( c ) || 
		   WI_IsCharCloseBracket ( c );
}

WI_Inline bool WI_IsCharSign ( const char c )
{
    return ( '+' == c ) || 
		   ( '-' == c );
}

WI_Inline bool WI_IsCharInValid ( const char c )
{
    return !WI_IsCharWhiteSpace	( c )   &&
           !WI_IsCharOperator	( c )	&&
		   !WI_IsCharLetter		( c )	&&
		   !WI_IsCharDigit		( c )	&&
		   ( '.' != c )					&&
		   ( '_' != c )					&&
		   ( '$' != c )					&&
		   ( '~' != c )					&&
		   ( '\'' != c );
}

WI_Inline bool WI_CharCompairNoCase ( const char c1, const char c2 )
{
    return tolower(c1) == tolower(c2);
}

WI_Inline bool WI_CharMatchNoCase ( WI_String s1, WI_String s2 )
{
	s1.LowerCase();
	s2.LowerCase();

	if ( s1.GetStringLength() == s2.GetStringLength() )
    {
		for ( WI_UInt i = 0; i < s1.GetStringLength ( ); ++i)
		{
			if ( ( s1.GetAsChar()[ i ] ) != ( s2.GetAsChar()[ i ] ) )
			{
				return false;
			}
		}

		return true;
    }

    return false;
}
*/

struct tWiLessCompare
{
    WI_Inline bool operator ( ) ( WI_String s1, WI_String s2) const;
};

WI_Inline void WI_CleanupCharEscapes ( WI_String& szS );

#pragma message ( "		Widow Lyte's String Lexer class complete..." )
#endif