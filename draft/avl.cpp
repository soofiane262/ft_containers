#include <cstdlib>
#include <ios>
#include <iostream>
#include <sstream>
#include <vector>

struct node {
	int _n;
	int _lvl;
	node( void ) {
		left  = NULL;
		right = NULL;
	};
	node( const int n ) {
		_n	  = n;
		_lvl  = 0;
		left  = NULL;
		right = NULL;
	};
	int lvl( node *nd ) {
		if ( !nd ) return 0;
		return nd->_lvl;
	};
	struct node *left, *right;
};

struct output {
	node	  *_nd;
	int		   _lvl;
	static int lvls;
	output( node *nd, const int lvl ) {
		_nd	 = nd;
		_lvl = lvl;
		if ( _nd->_lvl > lvls ) lvls = _nd->_lvl;
	};
};

int output::lvls = 0;

class avl {
  private:
	int lvl( node *nd ) {
		if ( !nd ) return -1;
		return nd->_lvl;
	};
	bool find( node &nd, const int n ) {
		if ( n == nd._n ) return true;
		else if ( n < nd._n ) {
			if ( !nd.left ) return false;
			else
				return find( *( nd.left ), n );
		} else {
			if ( !nd.right ) return false;
			else
				return find( *( nd.right ), n );
		}
	};
	int getBalance( node *nd ) {
		if ( !nd ) return 0;
		return lvl( nd->left ) - lvl( nd->right );
	};
	void rightRotation( node *&nd ) {
		struct node *l = nd->left, *lr = l->right;
		l->right = nd;
		nd->left = lr;
		nd->_lvl = std::max( lvl( nd->left ), lvl( nd->right ) ) + 1;
		l->_lvl	 = std::max( lvl( l->left ), lvl( l->right ) ) + 1;
		nd		 = l;
	};
	void leftRotation( node *&nd ) {
		struct node *r = nd->right, *rl = r->left;
		r->left	  = nd;
		nd->right = rl;
		nd->_lvl  = std::max( lvl( nd->left ), lvl( nd->right ) ) + 1;
		r->_lvl	  = std::max( lvl( r->left ), lvl( r->right ) ) + 1;
		nd		  = r;
	};
	void _insert( struct node *&nd, const int n ) {
		if ( !nd ) {
			nd = new node( n );
			std::cout << "before balance :\n";
			log();
			return;
		} else if ( n < nd->_n )
			_insert( nd->left, n );
		else if ( n > nd->_n )
			_insert( nd->right, n );
		else
			return;
		nd->_lvl = std::max( lvl( nd->left ), lvl( nd->right ) ) + 1;
		int bal	 = getBalance( nd );
		if ( bal > 1 && nd->left->left ) rightRotation( nd );
		else if ( bal > 1 && nd->left->right ) {
			std::cout << "\n" << nd->_n << "\n\n";
			leftRotation( nd->left );
			rightRotation( nd );
		} else if ( bal < -1 && nd->right->left ) {
			std::cout << "\nright left " << nd->_n << "\n\n";
			rightRotation( nd->right );
			leftRotation( nd );
		} else if ( bal < -1 && nd->right->right )
			leftRotation( nd );
	};
	void _del( struct node *&nd, const int n ) {
		if ( !nd ) return;
		else if ( n == nd->_n ) {
			if ( !nd->left && !nd->right ) {
				delete nd;
				nd = NULL;
			} else if ( !nd->left || !nd->right ) {
				struct node *tmp = nd->left ? nd->left : nd->right;
				tmp->_lvl--;
				delete nd;
				nd = tmp;
			} else {
				struct node *tmp = nd->right;
				while ( tmp->left ) tmp = tmp->left;
				nd->_n = tmp->_n;
				tmp->_lvl--;
				_del( nd->right, nd->_n );
			}
		} else if ( n < nd->_n )
			_del( nd->left, n );
		else if ( n > nd->_n )
			_del( nd->right, n );
	};
	void _log( std::vector< output > &vec, node *x, const int lvl ) {
		if ( !x ) return;
		_log( vec, x->left, lvl + 1 );
		vec.push_back( output( x, lvl ) );
		_log( vec, x->right, lvl + 1 );
	};
	void logTree( std::vector< output > &vec ) {
		for ( int lvl = 0, i = -1, lsl = -1; lvl <= output::lvls; lvl++, i = -1, lsl = -1 ) {
			while ( ++i < vec.size() ) {
				if ( vec[ i ]._lvl != lvl ) continue;
				for ( int j = 0; j < i - lsl - 1; j++ ) std::cout << "  ";
				std::cout << vec[ i ]._nd->_n;
				lsl = i;
			}
			std::cout << '\n';
			i	= -1;
			lsl = -1;
			while ( ++i < vec.size() ) {
				if ( vec[ i ]._lvl != lvl ) continue;
				for ( int j = 0; j < i - lsl - 1; j++ ) std::cout << "  ";
				if ( vec[ i ]._nd->left ) std::cout << '/';
				if ( vec[ i ]._nd->right ) std::cout << " \\";
				lsl = i;
			}
			std::cout << '\n';
		}
	};
	node *root;

  public:
	avl( void ) { root = NULL; };
	avl( const int n ) { root = new node( n /*, 'b'*/ ); };
	~avl( void ) { delete root; };
	void insert( const int n ) {
		_insert( root, n );
		std::cout << "after balance :\n";
		log();
	};
	bool find( const int n ) {
		if ( !root ) return false;
		else
			return find( *root, n );
	};
	void log( void ) {
		if ( !root ) return;
		std::vector< output > vec;
		_log( vec, root, 0 );
		logTree( vec );
		std::cout << "\n";
	};
	void del( const int n ) {
		if ( !root ) return;
		_del( root, n );
	};
};

int main( void ) {
	{
		avl x;
		avl y;
		std::cout << std::boolalpha;
		x.insert( 8 );
		x.insert( 6 );
		x.insert( 1 );
		x.insert( 4 );
		x.insert( 2 );
		x.insert( 7 );
		x.insert( 3 );
		x.insert( 5 );

		// std::cout << "x.del( 8 )\n";
		// x.del( 8 );
		// x.log();
		// std::cout << "x.del( 5 )\n";
		// x.del( 5 );
		// x.log();
		// for ( int i = 0; i < 15; i++ )
		// 	std::cout << "x.find( " << i << " ) : " << x.find( i ) << '\n';
		// for ( int i = 0; i < 8; i++ ) {
		// 	y.insert( i );
		// 	y.log();
		// }
		// for ( int i = 8; i; i-- ) {
		// 	y.insert( i );
		// 	y.log();
		// }
		// for ( int i = 0; i < 15; i++ )
		// std::cout << "y.find( " << i << " ) : " << y.find( i ) << '\n';
	}

	return 0;
}
