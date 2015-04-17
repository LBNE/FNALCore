// ======================================================================
//
// test "system_error" header
//
// ======================================================================


#include "cpp0x/system_error"
#include "cpp0x/type_traits"
#include <cstdlib>
#include <string>


void
  ensure( int which, bool claim )
{ if( not claim )
    std::exit(which);
}


#if 0 && ! defined CPP0X_HAS_SYSTEM_ERROR_HDR

  namespace my_code {
    enum my_code_t { E1 = 101, E2, E3 };
  }


  class my_category_impl
    : public std::error_category
  {
  public:
    virtual  const char*
      name( ) const
    {
      return "my_category";
    }

    virtual  std::string
      message( int ev ) const
    {
      switch( ev ) {
        case my_code::E1: return "E1";
        case my_code::E2: return "E2";
        case my_code::E3: return "E3";
        default         : return "Unknown";
      };
    }

  };  // my_category_impl


  std::error_category const &
    my_category( )
  {
    static  my_category_impl  my_category;
    return my_category;
  }


  std::error_code
    make_error_code( my_code::my_code_t e )
  {
    return std::error_code( static_cast<int>(e)
                          , my_category()
                          );
  }


  std::error_condition
    make_error_condition( my_code::my_code_t e )
  {
    return std::error_condition( static_cast<int>(e)
                               , my_category()
                               );
  }


  namespace boost { namespace system {  // TODO: how to move this to std?

    template<>
      struct is_error_code_enum<my_code::my_code_t>
        : public std::true_type
    { };

  } }

#endif  // CPP0X_HAS_SYSTEM_ERROR_HDR


int
  main( )
{

  return 0;

}  // main()
