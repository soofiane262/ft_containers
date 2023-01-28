#include <ios>
#include <iostream>
#include <sstream>
#include <vector>

struct node {
	int	 _n;
	char _s;
	int	 _lvl;
	node( void ) {
		left  = NULL;
		right = NULL;
	};
	node( const int n, const int s ) { _insert( n, s ); };
	~node( void ) {
		if ( left ) delete left;
		if ( right ) delete right;
	};
	void _insert( const int n, const int s ) {
		_n	  = n;
		_s	  = s;
		left  = NULL;
		right = NULL;
	};
	void insert( const int n ) {
		node *x = NULL;
		if ( n == _n ) return;
		else if ( n < _n ) {
			if ( !left ) left = new node( n, 'l' );
			else
				left->insert( n );
		} else {
			if ( !right ) right = new node( n, 'r' );
			else
				right->insert( n );
		}
	};
	bool find( const int n ) {
		if ( n == _n ) return true;
		else if ( n < _n ) {
			if ( !left ) return false;
			else
				return left->find( n );
		} else {
			if ( !right ) return false;
			else
				return right->find( n );
		}
	};
	struct node *left, *right;
};

struct output {
	node	  *_nd;
	static int lvls;
	output( node *nd ) {
		_nd = nd;
		if ( _nd->_lvl > lvls ) lvls = _nd->_lvl;
	};
};

int output::lvls = 0;

class bst {
  private:
	void _log( std::vector< output > &vec, node *x, const int lvl ) {
		if ( !x ) return;
		_log( vec, x->left, lvl + 1 );
		x->_lvl = lvl;
		vec.push_back( output( x ) );
		_log( vec, x->right, lvl + 1 );
	};
	void _log2( std::vector< output > &vec ) {
		for ( int lvl = 0, i = -1, lsl = -1; lvl <= output::lvls; lvl++, i = -1, lsl = -1 ) {
			while ( ++i < vec.size() ) {
				if ( vec[ i ]._nd->_lvl != lvl ) continue;
				for ( int j = 0; j < i - lsl; j++ ) std::cout << ' ';
				std::cout << vec[ i ]._nd->_n;
				lsl = i;
			}
			std::cout << '\n';
			i	= -1;
			lsl = -1;
			while ( ++i < vec.size() ) {
				if ( vec[ i ]._nd->_lvl != lvl ) continue;
				for ( int j = 0; j < i - lsl; j++ ) std::cout << ' ';
				if ( vec[ i ]._nd->left ) std::cout << '/';
				if ( vec[ i ]._nd->right ) std::cout << '\\';
				lsl = i;
			}
			std::cout << '\n';
		}
	};
	node *root;

  public:
	bst( void ) { root = NULL; };
	bst( const int n ) { root = new node( n, 0 ); };
	~bst( void ) { delete root; };
	void insert( const int n ) {
		if ( !root ) root = new node( n, 'b' );
		else
			root->insert( n );
	};
	bool find( const int n ) {
		if ( !root ) return false;
		else
			return root->find( n );
	};
	void log( void ) {
		if ( !root ) return;
		std::vector< output > vec;
		_log( vec, root, 0 );
		_log2( vec );
	};
};

int main( void ) {
	bst x;
	bst y;
	std::cout << std::boolalpha;
	x.insert( 5 );
	x.insert( 3 );
	x.insert( 7 );
	x.insert( 2 );
	x.insert( 4 );
	x.insert( 6 );
	x.insert( 8 );
	x.log();
	/*
	for ( int i = 0; i < 15; i++ ) std::cout << "x.find( " << i << " ) : " << x.find( i ) << '\n';
	for ( int i = 0; i < 8; i++ ) y.insert( i );
	y.log();
	for ( int i = 0; i < 15; i++ ) std::cout << "y.find( " << i << " ) : " << y.find( i ) << '\n';
	*/
	return 0;
}
