node *getDBSibling( node *nd ) {
	if ( nd->_color == DOUBLE_BLACK ) return getSibling( nd );
	else if ( nd->_nil == LEFT )
		return nd->_right;
	return nd->_left;
};
void fixDBRotate( node *&nd, bool colorSwap ) {
	if ( !nd->_rotate ) return;
	node *parent = nd->_parent;
	int	  dir	 = 0;
	if ( !parent )
		;
	else if ( nd == parent->_left )
		dir = -1;
	else
		dir = 1;
	std::cout << "rotate\n";
	std::cout << "i am " << nd->_elt << '\n'; // 66
	std::cout << "right is " << nd->_right->_elt << ", r's p " << nd->_right->_parent->_elt
			  << '\n'; // 78 -> 66
	rotate( nd, colorSwap );
	std::cout << "i am " << nd->_elt << '\n'; // 55
	std::cout << "right is " << nd->_right->_elt << ", r's p " << nd->_right->_parent->_elt
			  << '\n'; // 66 -> 55
	std::cout << "right right is " << nd->_right->_right->_elt << ", r r's p "
			  << nd->_right->_right->_parent->_elt << '\n'; // 78 -> 66
	_log( nd, 0 );
	log();
	if ( dir == -1 ) parent->_left = nd;
	else if ( dir == 1 )
		parent->_right = nd;
	else
		root = nd;
};
void fixNephewRotate( node *&nd, bool colorSwap ) {
	int dir = nd->_rotate;
	// std::cout << "parent is " << parent->_elt << " ( " << parent << " )" << '\n';
	fixDBRotate( nd, colorSwap );
	_log( nd, 0 );
	std::cout << "i am " << nd->_right->_right->_elt << ", my parent is "
			  << nd->_right->_right->_parent->_elt << '\n';
	// std::cout << "parent is " << parent->_elt << " ( " << parent << " )" << '\n';
	if ( dir == 2 ) nd->_right->_right->_parent = nd->_right;
	// std::cout << "here\n";
	// std::cout << "i am " << nd->_right->_right->_elt << ", my parent is "
	// 		  << nd->_right->_right->_parent->_elt << '\n';
};
void fixNieceRotate( node *&nd, node *parent, bool colorSwap ) {
	if ( !nd->_rotate ) return;
	int dir = 0;
	if ( nd == parent->_left ) dir = -1;
	else
		dir = 1;
	rotate( nd, colorSwap );
	if ( dir == -1 ) parent->_left = nd;
	else if ( dir == 1 )
		parent->_right = nd;
};
void fixDB( node *&nd ) {
	std::cout << "\e[1;34mfixDB\e[0m\n";
	std::cout << "i am " << nd->_elt << ", baba is " << nd->_parent->_elt << " ( " << nd->_parent
			  << " )" << '\n';
	log();
	std::cout << "\e[1;34m// fixDB\e[0m\n";
	fixDBRotate( nd, false );
	if ( !nd->_parent ) nd->_color = BLACK;
	if ( nd->_color != DOUBLE_BLACK && !nd->_nil ) return;
	else {
		node *DBsibling = getDBSibling( nd );
		int	  DBdir		= ( nd->_nil ? nd->_nil : ( nd == nd->_parent->_left ? LEFT : RIGHT ) );
		if ( !DBsibling || DBsibling->_color == BLACK ) {
			if ( DBsibling && DBsibling->hasThisChild( RED ) ) {
				int tmpColor = ( nd->_color == DOUBLE_BLACK ? nd->_parent->_color : nd->_color );
				if ( DBsibling->hasThisNiece( DBdir, RED ) ) {
					node *niece = DBsibling->getThisNiece( DBdir, RED );
					// std::cout << "i am " << nd->_elt
					// 		  << ( nd->_parent ? ", my parent is " : ", i am root" )
					// 		  << ( nd->_parent ? nd->_parent->_elt : 0 ) << '\n';
					// std::cout << "niece is " << niece->_elt << ", its parent is "
					// 		  << niece->_parent->_elt << '\n';
					niece->_color	   = tmpColor;
					DBsibling->_rotate = ( DBdir == LEFT ? RIGHT : LEFT );
					// std::cout << "before " << DBsibling->_elt << ' '
					// 		  << ( DBsibling->_rotate == LEFT ? "left" : "right" )
					// 		  << " rotation\n";
					// _log( nd, 0 );
					fixNieceRotate( DBsibling, ( nd->_nil ? nd : nd->_parent ), false );
					// std::cout << "after\n";
					// _log( nd, 0 );
					if ( nd->_color == DOUBLE_BLACK ) {
						nd->_color			 = BLACK;
						nd->_parent->_color	 = BLACK;
						nd->_parent->_rotate = DBdir;
						// std::cout << DBdir << '\n';
						fixDBRotate( nd->_parent, false );
						// _log( nd, 0 );
					} else {
						nd->_color	= BLACK;
						nd->_nil	= 0;
						nd->_rotate = DBdir;
						fixDBRotate( nd, false );
					}
				} else if ( DBsibling->hasThisNephew( DBdir, RED ) ) {
					std::cout << "\e[0;33mnephew\e[0m\n";
					node *nephew	  = DBsibling->getThisNephew( DBdir, RED );
					nephew->_color	  = BLACK;
					DBsibling->_color = tmpColor;
					if ( nd->_color == DOUBLE_BLACK ) {
						nd->_color			 = BLACK;
						nd->_parent->_color	 = BLACK;
						nd->_parent->_rotate = DBdir;
						fixDBRotate( nd->_parent, false );
					} else {
						nd->_color	= BLACK;
						nd->_nil	= 0;
						nd->_rotate = DBdir;
						fixDBRotate( nd, false );
					}
				}
			} else {
				if ( DBsibling ) DBsibling->_color = RED;
				if ( nd->_color == DOUBLE_BLACK ) {
					nd->_color = BLACK;
					nd->_parent->_color++;
					fixDB( nd->_parent );
				} else {
					nd->_nil = 0;
					nd->_color++;
					fixDB( nd );
				}
			}
		} else {
			node *DB = nd, *parent = DB->_parent;
			if ( nd->_color == DOUBLE_BLACK ) {
				nd->_parent->_rotate = DBdir;
				fixDBRotate( nd->_parent, true );
				DB->_parent = parent;
			} else {
				nd->_rotate = DBdir;
				fixDBRotate( nd, true );
			}
			fixDB( DB );
		}
	}
};