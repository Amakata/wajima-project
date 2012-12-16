#pragma once
#include <d3d8.h>
#include "std/COMObject.h"

#define D3DFVF_CUSTOMVERTEX	( D3DFVF_XYZRHW|D3DFVF_TEX1)

namespace zefiro{
namespace graphics{

typedef struct CUSTOMVERTEX_ {
	float x,y,z,rhw;
	float tu,tv;
}CUSTOMVERTEX;

}
}