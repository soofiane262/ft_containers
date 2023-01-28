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
	void log( void ) {
		if ( !root ) return;
		std::vector< output > vec;
		_log( vec, root, 0 );
		for ( int lvl = 0, i = -1; lvl <= output::lvls; lvl++, i = -1 ) {
			while ( ++i < vec.size() ) {
				if ( vec[ i ]._nd->_lvl != lvl ) continue;
				for ( int j = 0; j < output::lvls - vec[ i ]._nd->_lvl; j++ ) std::cout << ' ';
				std::cout << ' ' << vec[ i ]._nd->_n;
			}
			std::cout << '\n';
			i = -1;
			while ( ++i < vec.size() ) {
				if ( vec[ i ]._nd->_lvl != lvl ) continue;
				for ( int j = 0; j < output::lvls - vec[ i ]._nd->_lvl; j++ ) std::cout << ' ';
				if ( vec[ i ]._nd->left ) std::cout << "/ ";
				if ( vec[ i ]._nd->right ) std::cout << "\\  ";
			}
			std::cout << '\n';
		}
	};
};

int main( void ) {
	bst x;
	bst y;
	x.insert( 5 );
	x.insert( 3 );
	x.insert( 7 );
	x.insert( 2 );
	x.insert( 4 );
	x.insert( 6 );
	x.insert( 8 );
	for ( int i = 0; i < 8; i++ ) y.insert( i );
	x.log();
	y.log();
	return 0;
}
