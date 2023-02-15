#include "../vector/vector.hpp"

#include <cstddef>
#include <map>
#include <set>

enum dealloc_result { DEALLOC_BAD_POINTER, DEALLOC_BAD_SIZE, DEALLOC_SUCCESS };

class memory_tracker {
  public:
	static std::size_t	  allocation_count();
	static bool			  allocation_empty();
	static std::size_t	  block_size( void* ptr );
	static void			  add_allocation( void* ptr, std::size_t size );
	static dealloc_result remove_allocation( void* ptr, std::size_t size );
	static std::size_t	  constructs_count();
	static bool			  constructs_empty();
	static bool			  add_constructor_call( void* ptr );
	static bool			  add_destructor_call( void* ptr );

  private:
	static std::map< void*, std::size_t > allocations;
	static std::set< void* >			  constructs;
};

#include <cstddef>
#include <map>

std::size_t memory_tracker::allocation_count() { return allocations.size(); }

bool memory_tracker::allocation_empty() { return allocations.empty(); }

std::size_t memory_tracker::block_size( void* ptr ) {
	std::map< void*, std::size_t >::iterator it = allocations.find( ptr );

	return it != allocations.end() ? it->second : 0;
}

void memory_tracker::add_allocation( void* ptr, std::size_t size ) {
	allocations.insert( std::make_pair( ptr, size ) );
}

dealloc_result memory_tracker::remove_allocation( void* ptr, std::size_t size ) {
	std::map< void*, std::size_t >::iterator it = allocations.find( ptr );

	if ( it == allocations.end() ) { return DEALLOC_BAD_POINTER; }
	if ( it->second != size ) { return DEALLOC_BAD_SIZE; }

	allocations.erase( it );
	return DEALLOC_SUCCESS;
}

std::size_t memory_tracker::constructs_count() { return constructs.size(); }

bool memory_tracker::constructs_empty() { return constructs.empty(); }

bool memory_tracker::add_constructor_call( void* ptr ) {
	std::set< void* >::iterator it = constructs.find( ptr );

	if ( it != constructs.end() ) { return false; }

	constructs.insert( ptr );
	return true;
}

bool memory_tracker::add_destructor_call( void* ptr ) {
	std::set< void* >::iterator it = constructs.find( ptr );

	if ( it == constructs.end() ) { return false; }

	constructs.erase( ptr );
	return true;
}

std::map< void*, std::size_t > memory_tracker::allocations = std::map< void*, std::size_t >();
std::set< void* >			   memory_tracker::constructs  = std::set< void* >();

#include <iostream>
#include <memory>

template < typename T > class track_allocator {
  public:
	// clang-format off
    typedef T              value_type;
    typedef T*             pointer;
    typedef const T*       const_pointer;
    typedef T&             reference;
    typedef const T&       const_reference;
    typedef std::size_t    size_type;
    typedef std::ptrdiff_t difference_type;

	// clang-format on

	template < typename U > struct rebind {
		typedef track_allocator< U > other;
	};

  public:
	track_allocator() {}

	track_allocator( const track_allocator& ) {}

	template < typename U > track_allocator( const track_allocator< U >& ) {}

	~track_allocator() {}

  public:
	bool operator==( const track_allocator& ) { return true; }

	bool operator!=( const track_allocator& ) { return false; }

  public:
	pointer address( reference x ) const { return &x; }

	const_pointer address( const_reference x ) const { return &x; }

	T* allocate( std::size_t n, const void* hint = 0 ) {
		T* block = std::allocator< T >().allocate( n, hint );
		tracker.add_allocation( (void*)block, n );
		return block;
	}

	void deallocate( T* p, std::size_t n ) {
		if ( p == NULL ) { std::cout << "Called deallocate on null" << std::endl; }

		dealloc_result result = tracker.remove_allocation( (void*)p, n );

		switch ( result ) {
			case DEALLOC_BAD_POINTER:
				std::cout << "Called deallocate on non-allocated address: " << p << std::endl;
				break;
			case DEALLOC_BAD_SIZE:
				std::cout << "Called deallocate with wrong block size: " << n << " (expected "
						  << tracker.block_size( p ) << ")" << std::endl;
				break;
			default:;
		}
		std::allocator< T >().deallocate( p, n );
	}

	size_type max_size() const { return std::allocator< T >().max_size(); }

	void construct( pointer p, const_reference val ) {
		if ( p == NULL ) { std::cout << "Called construct on null" << std::endl; }

		const bool result = tracker.add_constructor_call( (void*)p );

		if ( !result ) {
			std::cout << "Called construct on initialized memory: " << p << std::endl;
		}

		std::allocator< T >().construct( p, val );
	}

	void destroy( pointer p ) {
		if ( p == NULL ) { std::cout << "Called destroy on null" << std::endl; }

		const bool result = tracker.add_destructor_call( (void*)p );

		if ( !result ) {
			std::cout << "Called destroy on uninitialized memory: " << p << std::endl;
		}

		std::allocator< T >().destroy( p );
	}

  private:
	memory_tracker tracker;
};
#include <cstdlib>
#include <limits>
#include <sstream>
#include <string>

#define SEED 64

#define PRINT_FILE_LINE() \
	{ std::cout << " (file: " << __FILE__ << ", line: " << __LINE__ << ")" << std::endl; }

#define PRINT_LINE( msg, value )              \
	{                                         \
		std::cout << msg << " " << ( value ); \
		PRINT_FILE_LINE();                    \
	}

#define PRINT_MSG( msg )   \
	{                      \
		std::cout << msg;  \
		PRINT_FILE_LINE(); \
	}

template < typename Iter > void print_range( Iter first, Iter last ) {
	for ( Iter it = first; it != last; ++it ) { std::cout << *it << " "; }
	std::cout << std::endl;
}

#define PRINT_SIZE( c ) \
	{ PRINT_LINE( "Size:", c.size() ); }

#define CATCH_UNHANDLED_EX()                \
	catch ( ... ) {                         \
		std::cout << "unhandled exception"; \
		PRINT_FILE_LINE();                  \
	}

template < typename ForwardIt, typename T >
void iota( ForwardIt first, ForwardIt last, T value = T() ) {
	while ( first != last ) {
		*first++ = value;
		++value;
	}
}

#ifndef NAMESPACE
	#define NAMESPACE ft
#endif

#ifdef SINGLE_BINARY
	#define MAIN( test_func )
#else
	#define MAIN( test_func )          \
		int main() {                   \
			srand( SEED );             \
			test_func();               \
			leak_checker::check_all(); \
		}
#endif

struct true_type {
	static const bool value = true;
	typedef true_type type;
};

struct false_type {
	static const bool  value = false;
	typedef false_type type;
};

template < typename T, typename U > struct is_same : public false_type {};

template < typename T > struct is_same< T, T > : public true_type {};

struct big_struct {
	long data[ 2000 ];
};

#include <list>
#include <vector>

#define PRINT_VEC( vec )                       \
	{                                          \
		std::cout << "\nVector content:\n";    \
		print_range( vec.begin(), vec.end() ); \
		std::cout << std::endl;                \
	}

#define PRINT_ALL( vec )   \
	{                      \
		PRINT_SIZE( vec ); \
		PRINT_VEC( vec );  \
	}

#define CHECK_CAPACITY( vec )                             \
	{                                                     \
		if ( !( vec.capacity() >= vec.size() ) ) {        \
			PRINT_MSG( "Capacity is smaller than size" ); \
		} else {                                          \
			PRINT_MSG( "Capacity Ok" );                   \
		}                                                 \
	}

#define CHECK_AND_PRINT_ALL( vec ) \
	{                              \
		CHECK_CAPACITY( vec );     \
		PRINT_ALL( vec );          \
	}

template < typename T > void init_array( T* arr, std::size_t size ) {
	iota( arr, arr + size, (T)rand() );
}

#define SETUP_ARRAY( type, name, size ) \
	type name[ size ];                  \
	init_array( name, size );

#define SETUP_ARRAYS()                                                          \
	SETUP_ARRAY( long, s_long, 32 );                                            \
	SETUP_ARRAY( long, b_long, 64 );                                            \
	SETUP_ARRAY( int, s_int, 32 );                                              \
	SETUP_ARRAY( int, b_int, 64 );                                              \
	SETUP_ARRAY( double, s_double, 32 );                                        \
	SETUP_ARRAY( double, b_double, 64 );                                        \
	char s_char[ 32 ];                                                          \
	iota( s_char, s_char + 32, '@' );                                           \
	char b_char[ 64 ];                                                          \
	iota( b_char, b_char + 64, '$' );                                           \
	std::size_t s_size = 32;                                                    \
	std::size_t b_size = 64;                                                    \
	(void)s_size;                                                               \
	(void)b_size;                                                               \
	std::string s_string[ 32 ] = {                                              \
		"QExoqp0nICr0sXsHqty2", "naax9QcpJhvaL7DezsNQ", "25ZTtB6wbptfbxM8AvHB", \
		"tShYNtc0MkdjqLrOatgz", "7Z3kf1Qec0NnsLSEpbOt", "WhkSNrKJC966fvjZ2Or1", \
		"8vlxlFRRgW7yYj4GO7dt", "5sq1aoT8zP0HaHj3nFOK", "61Dv31GYZhkgjKCErpng", \
		"l0IIcWWHhOcPzoxEamQM", "bE1RYclskwXlhCm46YFs", "kXeoi5qz94JYPqSDTs79", \
		"TFsQP1dz8VVos9KzUpY0", "b3wYQR7An193gjgYuRj3", "xSmyNsnSJ47jLqrvbpyr", \
		"guAIP2Wq43Gf8VhHsyu5", "yT6c2loPebHovnq9BQog", "3qvU1xcVm2g1DKFDlqh4", \
		"L0q8RR9P41VD4sVjdnWl", "YdjESsIZM4b1oGQPjpBe", "l1ZVQbWKw7brHUSimJgq", \
		"xdn0cf4vqRzpfXWtl10G", "lYnZvpqaV0s8DowMZwzV", "8P1cyKrwJNLoJyvLjYqO", \
		"4MhOXNbAX23CEijO5cRT", "tHe3miAwCOVQbuoLaEP2", "l6uNLsc8fiLl3eWoG6j6", \
		"477xt6l0lph9ALQdr4HX", "D9UJNe4s8YF02LhrwOdl", "dLCisBNOdE8yugntu6cj", \
		"YvY4aQFHgAuagn4dFLO1", "eGR6Dtv7LW75qlV5Fkik" };                       \
	std::string b_string[ 64 ] = {                                              \
		"uvg6KqtcgduR31n3ajsv", "wbiAcjgojb9JOagZwyMn", "ATZKCzaPOqgkhPjwuGlf", \
		"MOhaJs56yjOw8f6nLPRA", "0gyB2Tr42v6awMw2nK7J", "e6GsiLFUuoDpVFEhJKZ1", \
		"z0jXAhiV9keBsaLOY0Xf", "P68p2ZAosHJdmoZh1C7N", "Pu3EuZVeY0TCO3ojdK0t", \
		"z7jCHMooHCS73M8GygKB", "uT4KoK83JrZxZjkul7ty", "g8gfrZoY5XwfzRusvHvv", \
		"7PGmkM0OSRnYREt9mFIP", "q1od7mBIpPEsCtpF9kdw", "XQo0LWId5TdZnLnpUNOb", \
		"U0m1R0kFFhAFyS6hmHHw", "K0lPKfxJxIOnE8QB90xn", "cZ5xyQifMJhrKxqBK9A7", \
		"cFBiwjfYw7Js6qEGy5Kt", "1tW0KWfXxeFO69tByqcE", "3Fvq9NxBrhPXHe0IlIVx", \
		"MSRDjdFRvHAhFGhiMtDe", "zGm2joMh71jQkYzg5L4V", "Mq4RRaeLvSAO0z2ibp8Q", \
		"WnLFYnQKP8TNJkqVVbUg", "E98UphbbVSzrW5Mzurmg", "F8HRxeEcaTZDkFPkioij", \
		"jmUVl4Q8X5BwVNzXN219", "n7Xp4w4FwzGKit7AI4SO", "4MxXYr6rKOcXLt9UkVd2", \
		"4RVTDsADtRyboaai9d29", "XaSqsrrtdhAfFoJIc5KK", "9Z9jdVCrTT09bg348ceb", \
		"I6uqLG9dO5mfNdSMwOYm", "UwMTzJPlbnhgwbHpDi6w", "DebjMP9afncYE6GhhO00", \
		"YGPuscYDiGfAjY1UWST0", "K6gbvgGjVZgEFUDlkdSk", "8xCBPI0w6TpC0RA62c2W", \
		"fYMxkNwmKg3moP8KvD9v", "QpPdhwhEYjIugg3OPcPH", "qQBXjSn43I3EMP54SyxZ", \
		"7qvdKwoW1CQEZTWPvuSC", "rCT212rdYO0zTGHXesKg", "dBHvlHsBwcR9MkkenYYG", \
		"NQiSlergqR8fVbOeivLj", "xYVqsV147UIe7jVBVwXo", "tcxayO4DdEJ885TbqUMy", \
		"9TGSMTD8U8ksRpHqq0cL", "TIJ16jCv9BSUiWvhbF9T", "BM9GL2ig1hePkA6lM6Ck", \
		"TfJTYB9JQMU6CGcYg20Q", "Fg6e5YT2FQbpTZNTDqdo", "LI5q6ml40MeE9H1dPb93", \
		"OaxJUSm3nYN9Y8Ela7sS", "BgBeODAwXz7xJo50Rwqd", "xdkgKj1dEoJ6zuVhkvvo", \
		"olIewtUEvXJgs1lB9bCn", "dTsPDS0x2uXtcgOIJHb8", "DYvJ2phLppGNZKboTBrd", \
		"DjNFMtt9PxkzqvWBHI6j", "1Z3YkeTFlPniKnzFhzgu", "76XqQg6hqMf5IXxKPOEs", \
		"gzaapTWW7i9EZjjzLeK6" };                                               \
	(void)s_string;                                                             \
	(void)b_string;

typedef NAMESPACE::vector< std::string > strvector;
typedef NAMESPACE::vector< int >		 intvector;
typedef NAMESPACE::vector< long >		 longvector;
typedef NAMESPACE::vector< double >		 doublevector;
typedef NAMESPACE::vector< char >		 charvector;

template < typename T > T times2( const T& x ) { return x * 2; }

template < typename T > void print( const T& x ) { std::cout << x << '\n'; }

int main() {
	SETUP_ARRAYS();

	{
		strvector v;

		v.insert( v.begin(), v.begin(), v.begin() );

		CHECK_AND_PRINT_ALL( v );

		v.insert( v.begin(), v.begin(), v.end() );

		CHECK_AND_PRINT_ALL( v );

		v.insert( v.end(), v.begin(), v.end() );

		CHECK_AND_PRINT_ALL( v );

		v.insert( v.begin(), s_string, s_string + s_size );

		CHECK_AND_PRINT_ALL( v );

		v.insert( v.begin(), b_string, b_string + 10 );

		CHECK_AND_PRINT_ALL( v );
		std::cout << "here\n";
		v.insert( v.begin() + 20, b_string, b_string + b_size );

		CHECK_AND_PRINT_ALL( v );

		v.insert( v.end(), b_string + 10, b_string + 15 );

		CHECK_AND_PRINT_ALL( v );
	}

	{
		std::list< int > li( s_int, s_int + s_size );

		intvector v( 5, 1 );

		v.insert( v.begin() + 3, li.begin(), li.end() );

		CHECK_AND_PRINT_ALL( v );
	}

	{
		// This test checks if vector works with iterators tagged as std::input_iterator_tag
		std::istringstream				 str( "1 2 3 4 5 6 7 8 9 0 A B C D E F" );
		std::istreambuf_iterator< char > it( str ), end;

		charvector v( 2, 'U' );

		v.insert( v.end(), it, end );

		CHECK_AND_PRINT_ALL( v );
	}
}
