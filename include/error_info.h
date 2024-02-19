#pragma once

typedef enum
{
	CMD_MISPARAM = -11,	// inimissing paramt file 
	CMD_MEMERR = -10,
	CMD_INITNF = -9,   // initialization file not found
	CMD_HELPERR = -8,   // problem with help subsystem
	CMD_QUOTES = -7,   // argument not enclosed in quotes
	CMD_IOERR = -6,   // io error
	CMD_BANNERPTH = -5,   //
	CMD_FILEEXST = -4,   // file exists
	CMD_FILENF = -3,   // file not found
	CMD_ARGS = -2,   // error with command arguments
	CMD_ERR = -1,   // non-specific error
	CMD_OK = 0,    // command completed successfully
	CMD_QUIT = 1,    // exit application
	CMD_NOOP = 2     // no operation
} RET_CODE;
