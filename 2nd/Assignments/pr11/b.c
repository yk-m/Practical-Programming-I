
	int root[MAX_SIZE]
	  , num
	  , i = 0
	;
	
	root[i] = q;

	do {
		i++;
		root[i] = pre_vertex[p][ root[i-1] ];
	} while( root[i] != p );

	for ( ; i >= 0; i-- ) {
		printf("-|%s|-",graph_data[ root[i] ]);
	}

	