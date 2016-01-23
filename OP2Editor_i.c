/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Nov 11 16:06:01 2005
 */
/* Compiler settings for E:\op2\OP2Editor\OP2Editor.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID IID_StreamReader = {0x70AC9DEE,0xCE0F,0x4145,{0xA1,0x40,0x6A,0xE1,0xBA,0x65,0x8B,0x1E}};


const IID IID_SeekableStreamReader = {0x57B5FDD0,0x8E6E,0x4134,{0x94,0xDE,0x69,0x49,0xBD,0x2E,0xB3,0xCB}};


const IID IID_StreamWriter = {0xB83597A2,0x3471,0x48db,{0xB9,0xBC,0xEB,0x47,0x49,0xBA,0x1A,0xAA}};


const IID IID_ArchiveReader = {0xCE02B285,0xD2F4,0x4707,{0xB6,0xD3,0x39,0xCB,0x66,0x97,0x35,0x7C}};


const IID IID_ArchiveWriter = {0x98A6E750,0x10C7,0x4133,{0x9A,0x0E,0x17,0xFB,0x62,0xEC,0x6A,0xDE}};


const IID IID_TileSet = {0xC7F1E185,0x8079,0x4538,{0x96,0xCF,0x59,0x50,0x40,0x6A,0xE1,0xAA}};


const IID IID_TileSetSource = {0x153BC780,0x0FF2,0x44e4,{0x84,0x48,0x5B,0x3F,0x46,0x05,0x04,0x75}};


const IID IID_TileSetManager = {0x33A10A9E,0xA3B0,0x498f,{0xA8,0x71,0x3E,0xCC,0x78,0xB4,0x77,0xFB}};


const IID IID_TileGroup = {0x8E43C614,0x715F,0x41df,{0xB3,0x76,0xCB,0x0B,0x55,0xF2,0x90,0x90}};


const IID IID_MapFile = {0xE1C7751A,0xAA0C,0x40b7,{0x95,0xC4,0x16,0x93,0xC8,0x67,0x84,0xFC}};


const IID IID_IResourceManager = {0x2A73E1A3,0x5FAA,0x4ac8,{0xAC,0x58,0xD2,0x8C,0x77,0xE7,0x80,0xF0}};


const IID LIBID_OP2Editor = {0x53FFC417,0xDCC3,0x44C1,{0xBE,0xF2,0xAC,0xD5,0xD3,0xFD,0x74,0x12}};


const CLSID CLSID_ResourceManager = {0xC8DE4CDE,0x4554,0x4fe9,{0x86,0x88,0xA9,0x0D,0x91,0xEB,0xCA,0x0B}};


#ifdef __cplusplus
}
#endif

