/************************************************************
description
	ofxArtnetにて、common.hが使用されている。
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/************************************************************
************************************************************/

enum{
	BUF_SIZE = 512,
};
enum COLORPATTERNS{
	COLPATTERN_AQUA,
	COLPATTERN_MAGMA,
	COLPATTERN_DIGITAL,
	COLPATTERN_SEXY,
	
	COLPATTERN_TRIP,
	COLPATTERN_REGGAE,
	COLPATTERN_SAMBA,
	COLPATTERN_SWEETS,
	// ↑以上:Autoで使用
	
	/*
	COLPATTERN_RAINBOW,
	COLPATTERN_BLIZZARD,
	
	
	COLPATTERN_AUTO,
	*/
	
	
	NUM_COLORPATTERNS,
};


/************************************************************
************************************************************/
#define ERROR_MSG(); printf("Error in %s:%d\n", __FILE__, __LINE__);

/************************************************************
************************************************************/
extern void printMessage(const char* message);
