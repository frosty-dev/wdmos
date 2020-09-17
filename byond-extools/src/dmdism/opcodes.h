#pragma once

#include <unordered_map>
#include "../core/byond_constants.h"

enum Bytecode
{
	UNK = -1,
	END = 0x00,
	NEW = 0x01,
	FORMAT = 0x02,
	OUTPUT = 0x03,
	OUTPUT_FORMAT = 0x04,
	STAT = 0x05,

	LINK = 0x07,

	TEST = 0x0D,
	NOT = 0x0E,
	JMP = 0x0F,
	JNZ = 0x10,
	JZ = 0x11,
	RET = 0x12,
	ISLOC = 0x13,
	ISMOB = 0x14,
	ISOBJ = 0x15,
	ISAREA = 0x16,
	ISTURF = 0x17,
	EMPTYLIST = 0x19, //TODO
	NEWLIST = 0x1A,
	VIEW = 0x1B, //TODO
	OVIEW = 0x1C, //TODO
	VIEW_TARGET = 0x1D, //TODO
	OVIEW_TARGET = 0x1E, //TODO
	BLOCK = 0x1F, //TODO

	PROB = 0x21,
	RAND = 0x22,
	RAND_RANGE = 0x23,
	SLEEP = 0x24,
	SPAWN = 0x25,

	BROWSE_RSC = 0x27,

	CALL = 0x29,
	CALLNR = 0x2A,
	CALLPATH = 0x2B,
	CALLPARENT = 0x2C,

	CALLGLOB = 0x30,
	LOG10 = 0x31,
	LOG = 0x32,
	GETVAR = 0x33,
	SETVAR = 0x34,
	SETVAR_COPY = 0x35, //TODO
	GETFLAG = 0x36,
	TEQ = 0x37,
	TNE = 0x38,
	TL = 0x39,
	TG = 0x3A,
	TLE = 0x3B,
	TGE = 0x3C,
	ANEG = 0x3D,
	ADD = 0x3E,
	SUB = 0x3F,
	MUL = 0x40,
	DIV = 0x41,
	MOD = 0x42,
	ROUND = 0x43,
	ROUNDN = 0x44,
	AUGADD = 0x45,
	AUGSUB = 0x46,
	AUGMUL = 0x47,
	AUGDIV = 0x48,
	AUGMOD = 0x49,
	AUGAND = 0x4A,
	AUGOR = 0x4B,
	AUGXOR = 0x4C,
	AUGLSHIFT = 0x4D,
	AUGRSHIFT = 0x4E,

	PUSHI = 0x50,
	POP = 0x51,
	ITERLOAD = 0x52,
	ITERNEXT = 0x53,

	LOCATE_POS = 0x5A,
	LOCATE_REF = 0x5B,

	PUSHVAL = 0x60,
	NEW_IMAGE = 0x61,
	PRE_INC = 0x62,
	POST_INC = 0x63,
	PRE_DEC = 0x64,
	POST_DEC = 0x65,
	INC = 0x66,
	DEC = 0x67,
	ABS = 0x68,
	SQRT = 0x69,
	POW = 0x6A,
	TURN = 0x6B,
	ADDTEXT = 0x6C,
	LENGTH = 0x6D,
	COPYTEXT = 0x6E,
	FINDTEXT = 0x6F,

	SWITCH = 0x78,

	SWITCH_RANGE = 0x7A,
	LISTGET = 0x7B,
	LISTSET = 0x7C,
	ISTYPE = 0x7D,
	BINARY_AND = 0x7E,
	BINARY_OR = 0x7F,
	BINARY_XOR = 0x80,
	BITWISE_NOT = 0x81,
	LSHIFT = 0x82,
	RSHIFT = 0x83,
	DBG_FILE = 0x84,
	DBG_LINENO = 0x85,

	GET_STEP = 0x90,

	LOCATE_TYPE = 0x97,

	ISNULL = 0x9E,
	ISNUM = 0x9F,

	ISTEXT = 0xA0,

	MIN = 0xA5,
	MAX = 0xA6,
	TYPESOF = 0xA7,
	CKEY = 0xA8,

	ISINLIST = 0xA9,

	BROWSE = 0xAA,
	BROWSE_OPT = 0xAB,

	JMP_OR = 0xB2,
	JMP_AND = 0xB3,

	CALLNAME = 0xB5,

	PROMPTCHECK = 0xBA,

	INPUT_ = 0xC1, //INPUT without underscore was already defined in some windows header
	SIN = 0xC2,
	COS = 0xC3,

	CRASH = 0xC7,

	CALL_GLOBAL_ARGLIST = 0xCD,

	MIN_LIST = 0xD0,
	MAX_LIST = 0xD1,
	PICK = 0xD2,

	FCOPY_RSC = 0xD7,

	ICON_NEW = 0xDE,

	ISPATH = 0xF5,
	ISSUBPATH = 0xF6,
	FEXISTS = 0xF7,
	JMP2 = 0xF8,
	JNZ2 = 0xF9,
	JZ2 = 0xFA,
	POPN = 0xFB,
	CHECKNUM = 0xFC,
	FOR_RANGE = 0xFD,

	MD5 = 0x109,
	ICON_STATES_MODE = 0x114,
	CALL_LIB = 0x116,
	CALL_LIB_ARGLIST = 0x117,
	ICON_BLEND = 0x119,
	MATRIX_NEW = 0x12A,
	REPLACETEXT = 0x130,
	REPLACETEXTEX = 0x131,
	JSON_ENCODE = 0x138,
	JSON_DECODE = 0x139,
	REGEX_NEW = 0x13A,

	LPUSH_CACHE = 0x142,
	SET_CACHE = 0x143,

	//DBG_BREAK = 0x1337,
};

enum AccessModifier
{
	SRC = 0xFFCE,
	ARGS = 0xFFCF,
	DOT = 0xFFD0,
	CACHE = 0xFFD8,
	ARG = 0xFFD9,
	LOCAL = 0xFFDA,
	GLOBAL = 0xFFDB,
	SUBVAR = 0xFFDC,

	SRC_PROC_SPEC = 0xFFDD,
	SRC_PROC = 0xFFDE,
	PROC_ = 0xFFDF,
	PROC_NO_RET = 0xFFE0,

	WORLD = 0xFFE5,
	NULL_ = 0xFFE6,
};

const std::unordered_map<AccessModifier, std::string> modifier_names = {
	{SRC, "SRC"},
	{DOT, "DOT" },
	{ARG, "ARG" },
	{ARGS, "ARGS"},
	{LOCAL, "LOCAL"},
	{GLOBAL, "GLOBAL"},
	{SUBVAR, "SUBVAR"},
	{CACHE, "CACHE"},

	{SRC_PROC_SPEC, "SRC_PROC_SPEC"},
	{SRC_PROC, "SRC_PROC"},
	{PROC_, "PROC"},
	{PROC_NO_RET, "PROC_NO_RET"},

	{WORLD, "WORLD"},
	{NULL_, "NULL"},
};

const std::unordered_map<DataType, std::string> datatype_names = {
	{ DataType::NULL_D, "NULL" },
	{ DataType::TURF, "TURF" },
	{ DataType::OBJ, "OBJ" },
	{ DataType::MOB, "MOB" },
	{ DataType::AREA, "AREA" },
	{ DataType::CLIENT, "CLIENT" },
	{ DataType::STRING, "STRING" },
	{ DataType::MOB_TYPEPATH, "MOB_TYPEPATH" },
	{ DataType::OBJ_TYPEPATH, "OBJ_TYPEPATH" },
	{ DataType::TURF_TYPEPATH, "TURF_TYPEPATH" },
	{ DataType::AREA_TYPEPATH, "AREA_TYPEPATH" },
	{ DataType::RESOURCE, "RESOURCE"},
	{ DataType::IMAGE, "IMAGE" },
	{ DataType::WORLD_D, "WORLD" },
	{ DataType::DATUM, "DATUM" },
	{ DataType::SAVEFILE, "SAVEFILE" },
	{ DataType::LIST_TYPEPATH, "LIST_TYPEPATH" },
	{ DataType::NUMBER, "NUMBER" },
	{ DataType::CLIENT_TYPEPATH, "CLIENT_TYPEPATH" },
	{ DataType::LIST, "LIST" },
	{ DataType::LIST_ARGS, "LIST_ARGS" },
	{ DataType::LIST_VERBS, "LIST_VERBS" },
	{ DataType::LIST_CONTENTS, "LIST_CONTENTS" },
	{ DataType::DATUM_TYPEPATH, "DATUM_TYPEPATH" },
	{ DataType::LIST_TURF_CONTENTS, "LIST_TURF_CONTENTS" },
};

const std::unordered_map<Bytecode, std::string> mnemonics = {
	{UNK, "???"},
	{END, "END"},
	{NEW, "NEW"},
	{FORMAT, "FORMAT"},
	{OUTPUT, "OUTPUT"},
	{OUTPUT_FORMAT, "FOUTPUT"},
	{TEST, "TEST"},
	{NOT, "NOT"},
	{JMP, "JMP"},
	{JZ, "JZ"},
	{RET, "RET"},
	{NEWLIST, "NEWLIST"},
	{SLEEP, "SLEEP"},
	{SPAWN, "SPAWN"},
	{CALL, "CALL"},
	{CALLNR, "CALLNR"},
	{CALLPATH, "CALLPATH"},
	{CALLPARENT, "CALLPARENT"},
	{CALLGLOB, "CALLGLOB"},
	{GETVAR, "GETVAR"},
	{SETVAR, "SETVAR"},
	{GETFLAG, "GETFLAG"},
	{TEQ, "TEQ"},
	{TNE, "TNE"},
	{TL, "TL"},
	{TG, "TG"},
	{TLE, "TLE"},
	{TGE, "TGE"},
	{ANEG, "ANEG"},
	{ADD, "ADD"},
	{SUB, "SUB"},
	{MUL, "MUL"},
	{DIV, "DIV"},
	{MOD, "MOD"},
	{ROUND, "ROUND"},
	{ROUNDN, "ROUNDN"},
	{AUGADD, "AUGADD"},
	{AUGSUB, "AUGSUB"},
	{AUGMUL, "AUGMUL" },
	{AUGDIV, "AUGDIV" },
	{AUGMOD, "AUGMOD"},
	{AUGAND, "AUGAND" },
	{AUGOR, "AUGOR" },
	{AUGXOR, "AUGXOR" },
	{AUGLSHIFT, "AUGLSHIFT" },
	{AUGRSHIFT, "AUGRSHIFT" },
	{PUSHI, "PUSHI"},
	{POP, "POP"},
	{ITERLOAD, "ITERLOAD"},
	{ITERNEXT, "ITERNEXT"},
	{LOCATE_POS, "LOCATE_POS"},
	{LOCATE_REF, "LOCATE_REF"},
	{PUSHVAL, "PUSHVAL"},
	{INC, "INC"},
	{DEC, "DEC"},
	{ABS, "ABS"},
	{SQRT, "SQRT"},
	{POW, "POW"},
	{COPYTEXT, "COPYTEXT"},
	{FINDTEXT, "FINDTEXT"},
	{LISTGET, "LISTGET"},
	{LISTSET, "LISTSET"},
	{ISTYPE, "ISTYPE"},
	{DBG_FILE, "DBG FILE"},
	{DBG_LINENO, "DBG LINENO"},
	{ISNULL, "ISNULL"},
	{ISINLIST, "ISINLIST"},
	{CALLNAME, "CALLNAME"},
	{PROMPTCHECK, "PROMPTCHECK"},
	{INPUT_, "INPUT"},
	{CRASH, "CRASH"},
	{CALL_GLOBAL_ARGLIST, "CALL_GLOBAL_ARGLIST"},
	{ICON_NEW, "ICON_NEW"},
	{FEXISTS, "FEXISTS"},
	{JMP2, "JMP"},
	{JNZ2, "JNZ"},
	{POPN, "POPN"},
	{CHECKNUM, "CHECKNUM"},
	{FOR_RANGE, "FOR_RANGE"},
	{MD5, "MD5"},
	{CALL_LIB, "CALL_LIB"},
	{CALL_LIB_ARGLIST, "CALL_LIB_ARGLIST"},
	{ICON_BLEND, "ICON_BLEND"},
	{MATRIX_NEW, "MATRIX_NEW"},
	{REPLACETEXT, "REPLACETEXT"},
	{REPLACETEXTEX, "REPLACETEXTEX"},
	{JSON_ENCODE, "JSON_ENCODE"},
	{JSON_DECODE, "JSON_DECODE"},
	{REGEX_NEW, "REGEX_NEW"},
	//{DBG_BREAK, "DBG BREAK"},
	{FCOPY_RSC, "FCOPY_RSC"},
	{ICON_STATES_MODE, "ICON_STATES_MODE"},
	{ISNUM, "ISNUM" },
	{JMP_OR, "JMP_OR" },
	{JMP_AND, "JMP_AND"},
	{PROB, "PROB"},
	{RAND, "RAND"},
	{RAND_RANGE, "RAND_RANGE"},
	{BLOCK, "BLOCK"},
	{JZ2, "JZ"},
	{STAT, "STAT" },
	{LOG, "LOG"},
	{LOG10, "LOG10"},
	{SIN, "SIN"},
	{COS, "COS"},
	{MIN, "MIN"},
	{MAX, "MAX"},
	{MIN_LIST, "MIN_LIST"},
	{MAX_LIST, "MAX_LIST"},
	{LOCATE_TYPE, "LOCATE_TYPE"},
	{BINARY_AND, "BINARY_AND"},
	{BINARY_OR, "BINARY_OR"},
	{BINARY_XOR, "BINARY_XOR"},
	{BITWISE_NOT, "BITWISE_NOT"},
	{LSHIFT, "LSHIFT"},
	{RSHIFT, "RSHIFT"},
	{LENGTH, "LENGTH"},
	{PICK, "PICK"},
	{ISPATH, "ISPATH" },
	{ISSUBPATH, "ISSUBPATH"},
	{TYPESOF, "TYPESOF"},
	{ NEW_IMAGE, "IMAGE" },
	{ PRE_INC, "PRE_INC" },
	{ POST_INC, "POST_INC" },
	{ PRE_DEC, "PRE_DEC" },
	{ POST_DEC, "POST_DEC" },
	{LPUSH_CACHE, "LPUSH_CACHE"},
	{ SET_CACHE, "SET_CACHE" },
	{SWITCH, "SWITCH"},
	{GET_STEP, "GET_STEP"},
	{ ISLOC, "ISLOC" },
	{ ISMOB, "ISMOB" },
	{ ISAREA, "ISAREA" },
	{ ISTURF, "ISTURF" },
	{ISOBJ, "ISOBJ"},
	{ISTEXT, "ISTEXT"},
	{CKEY, "CKEY"},
	{ BROWSE_RSC, "BROWSE_RSC" },
	{ BROWSE, "BROWSE" },
	{ BROWSE_OPT, "BROWSE_OPT" },
};