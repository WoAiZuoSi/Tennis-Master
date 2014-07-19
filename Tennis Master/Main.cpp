#include "DarkGDK.h"

float aga, agb;
float radius;

float cx, cy, cz;

DWORD white = RGB ( 255, 255, 255 );
DWORD gray = RGB ( 120, 120, 120 );
DWORD red = RGB ( 255, 0, 0 );

bool doControl;

void setup ( )
{
	aga = 270;
	agb = 45;
	radius = 2.0f;
	doControl = false;
}

void DarkGDK ( void )
{
	setup ( );

	int i, j, k, lx, ly;
	float ls;

	dbLoadImage ( "123.bmp", 1 );
	dbSprite ( 1, 0, 0, 1 );

	dbLoadObject		( "media\\H-USA-Idle.x" , 1 );
	dbPositionObject	( 1 , 0 , -1 , 0 );
	dbSetObjectSpeed ( 1, 50 );
	dbLoopObject ( 1 );

	dbMakeObjectBox ( 2, 1, 1, 1 );
	dbPositionObject ( 2, 3, 0, 0 );

	dbPositionCamera ( 100, 100, 100 );
	dbPointCamera ( 0, 0, 0 );

	dbSyncOn   ( );
	dbSyncRate ( 60 );

	dbRandomize ( dbTimer ( ) );

	while ( LoopGDK ( ) )
	{
		
		if ( dbUpKey ( ) )
			radius -= 0.1f;
		else if ( dbDownKey ( ) )
			radius += 0.1f;

		if ( doControl == false && dbMouseClick ( ) == 1 )
		{
			doControl = true;
			lx = dbMouseX ( );
			ly = dbMouseY ( );
		}
		else if ( doControl == true )
		{
			aga = aga + lx - dbMouseX ( );
			agb = agb + dbMouseY ( ) - ly;

			if ( aga > 360 )
				aga -= 360;
			else if ( aga < 0 )
				aga += 360;
			if ( agb > 89 )
				agb = 89;
			else if ( agb < -89 )
				agb = -89;
			
			lx = dbMouseX ( );
			ly = dbMouseY ( );

			if ( dbMouseClick ( ) == 0 )
				doControl = false;
		}

		ls = radius * dbCos ( agb );
		cx = ls * dbCos ( aga );
		cy = radius * dbSin ( agb );
		cz = ls * dbSin ( aga );

		dbPositionCamera ( cx, cy, cz );
		dbPointCamera ( 0, 0, 0 );
		dbSync ( );
	}

	return;
}

