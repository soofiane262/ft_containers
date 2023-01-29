#include <cstdlib>
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
	node( const int n, const int s, const int lvl ) { _insert( n, s, lvl ); };
	~node( void ) {};
	void _insert( const int n, const int s, const int lvl ) {
		_n	  = n;
		_s	  = s;
		_lvl  = lvl;
		left  = NULL;
		right = NULL;
	};
	void insert( const int n ) {
		if ( n == _n ) return;
		else if ( n < _n ) {
			if ( !left ) left = new node( n, 'l', _lvl + 1 );
			else
				left->insert( n );
		} else {
			if ( !right ) right = new node( n, 'r', _lvl + 1 );
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
	struct node *del( struct node *nd, const int n ) {
		if ( !nd ) return NULL;
		else if ( n == nd->_n ) {
			if ( !nd->left && !nd->right ) {
				delete nd;
				nd = NULL;
				return NULL;
			} else if ( !nd->left || !nd->right ) {
				struct node *tmp = nd->left ? nd->left : nd->right;
				tmp->_lvl--;
				delete nd;
				nd = NULL;
				return tmp;
			} else {
				struct node *tmp = nd->right;
				while ( tmp->left ) tmp = tmp->left;
				nd->_n = tmp->_n;
				tmp->_lvl--;
				nd->right = del( nd->right, nd->_n );
			}
		} else if ( n < nd->_n )
			nd->left = del( nd->left, n );
		else if ( n > nd->_n )
			nd->right = del( nd->right, n );
		return nd;
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
	void __log( node *x, const int lvl ) {
		if ( !x ) return;
		__log( x->left, lvl + 1 );
		for ( int i = 0; i < lvl; i++ ) std::cout << ' ';
		std::cout << x->_n << '\n';
		__log( x->right, lvl + 1 );
	};
	void _log( std::vector< output > &vec, node *x, const int lvl ) {
		if ( !x ) return;
		_log( vec, x->left, lvl + 1 );
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
	bst( const int n ) { root = new node( n, 'b', 0 ); };
	~bst( void ) { delete root; };
	void insert( const int n ) {
		if ( !root ) root = new node( n, 'b', 0 );
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
	void del( const int n ) {
		if ( !root ) return;
		root->del( root, n );
	};
};

int main( void ) {
	{
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
		std::cout << "x.del( 8 )\n";
		x.del( 8 );
		x.log();
		std::cout << "x.del( 5 )\n";
		x.del( 5 );
		x.log();
		for ( int i = 0; i < 15; i++ )
			std::cout << "x.find( " << i << " ) : " << x.find( i ) << '\n';
		for ( int i = 0; i < 8; i++ ) y.insert( i );
		y.log();
		y.del( 5 );
		y.log();
		y.del( 2 );
		y.log();
		for ( int i = 0; i < 15; i++ )
			std::cout << "y.find( " << i << " ) : " << y.find( i ) << '\n';
	}

	return 0;
}
