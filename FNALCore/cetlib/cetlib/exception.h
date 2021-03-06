#ifndef CETLIB_EXCEPTION_H
#define CETLIB_EXCEPTION_H

// ======================================================================
//
//  exception: An exception type with category capability
//
// ----------------------------------------------------------------------
//
// Each exception is identified by a category string.  This string is a
// short word or phrase (no whitespace) describing the problem that was
// encountered.  These category identifiers can be concatenated when
// exceptions are caught and rethrown; the entire list can be accessed
// using the history() call.  Example:
//
//   try {
//     func();
//   }
//   catch (cet::exception & e)
//   {
//     throw cet::exception("DataCorrupt","encountered while unpacking",e);
//   }
//
// Information can be appended to the exception via operator <<.  Example:
//
//   if( (rc=func()) < 0 ) {
//     throw cet::exception("DataCorrupt")
//       << "I died with rc = " << rc
//       << std::endl;
//   }
//
// ----------------------------------------------------------------------
//
// Derived types are expected to adjust the category, either
//   1) by passing a string literal to the base class constructor, or
//   2) by ensuring the developer gives a category name.
// Example:
//
//  class infinite_loop
//    : public cet::exception
//  {
//    infinite_loop( std::string const & mesg )
//      : exception( "infinite_loop", mesg )
//    { }
//  };
//
// ----------------------------------------------------------------------
//
// The output from what() has a simple format that makes it easy to
// locate the reason for and context of the error and separate it from
// the user-supplied free-format text.  The output from what() contains
// all the category and context information in a nested hierarchical format.
//
// ======================================================================

#include "cpp0x/type_traits"
#include <exception>
#include <iosfwd>
#include <list>
#include <sstream>
#include <string>

namespace cet {
  class exception;

  std::ostream &
    operator << ( std::ostream & os, exception const & e );
}

// ======================================================================

namespace cet {
  namespace detail {

    template< class D
            , bool = std::is_base_of<cet::exception,D>::value
            >
      struct enable_if_an_exception
    { typedef  D const &  type; };

    template< class D >
      struct enable_if_an_exception<D,false>
    { };

  }  // detail
}  // cet

// ======================================================================

namespace cet {

  class exception
    : public std::exception
  {
  public:
    typedef  std::string          Category;
    typedef  std::list<Category>  CategoryList;

    // --- c'tors, d'tor:

    explicit
      exception( Category const & category );

    exception( Category    const & category
             , std::string const & message );
    exception( Category    const & category
             , std::string const & message
             , exception   const & another );

    exception( exception const & other );

    virtual
      ~exception( ) noexcept;

    // --- inspectors:

    virtual  char const *  what( ) const throw();
    virtual  std::string   explain_self( ) const;
    std::string            category( ) const;
    CategoryList const &   history( ) const;
    std::string            root_cause( ) const;

    // --- mutators:

    void  append( exception const & another ) const;

    void  append( std::string const & more_information   ) const;
    void  append( char        const   more_information[] ) const;

    void  append( std::ostream & f(std::ostream &) ) const;
    void  append( std::ios_base& f(std::ios_base&) ) const;

    template< class T >
      void
      append( T const & more_information ) const
    { ost_ << more_information; }

  private:
    mutable  std::ostringstream   ost_;
    CategoryList                  category_;
    mutable std::string           what_;

    virtual  std::exception *  clone() const;
    virtual  void  rethrow();

  };  // exception

  template< class E >
    typename detail::enable_if_an_exception<E>::type
    operator << ( E const & e, std::string const & t )
  { e.append(t); return e; }

  template< class E >
    typename detail::enable_if_an_exception<E>::type
    operator << ( E const & e, char const t[] )
  { e.append(t); return e; }

  template< class E >
    typename detail::enable_if_an_exception<E>::type
    operator << ( E const & e, std::ostream& f(std::ostream&) )
  { e.append(f); return e; }

  template< class E >
    typename detail::enable_if_an_exception<E>::type
    operator << ( E const & e, std::ios_base& f(std::ios_base&) )
  { e.append(f); return e; }

  template< class E, class T >
    typename detail::enable_if_an_exception<E>::type
    operator << ( E const & e, T const & t )
  { e.append(t); return e; }

}  // namespace cet

// ======================================================================

#endif
