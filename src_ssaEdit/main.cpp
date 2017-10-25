/*
 * Copyright (c) 2017 Amir Czwink (amir130@hotmail.de)
 *
 * This file is part of EDMW-Modding-Tools.
 *
 * EDMW-Modding-Tools is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * EDMW-Modding-Tools is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with EDMW-Modding-Tools.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <ACStdLib.hpp>
//Namespaces
using namespace ACStdLib;
//Definitions
#define PROGRAM_ARG_PACK "pack"
#define PROGRAM_ARG_EXTRACT "extract"
#define PROGRAM_ARG_DECOMPRESS "decompress"
//Enums
enum ECommand
{
	COMMAND_ILLEGAL,
	COMMAND_PACK,
	COMMAND_EXTRACT,
	COMMAND_DECOMPRESS,
};

//Global Variables
ECommand g_Command;
Path g_Input;
Path g_Output;


//Prototypes
bool CheckArguments();
void Decompress(InputStream &refSource, AOutputStream &refOutput);
bool EvaluateArguments(const LinkedList<String> &args);
void PrintManual();
bool Extract(Path input, Path output);
bool Pack(Path input, Path output);

bool DecompressFile()
{
	FileInputStream input(g_Input);
	DataReader reader(false, input);

	if(reader.ReadUInt32() != 0x31304B50)
	{
		stdErr << "Input is not compressed" << endl;
		return false;
	}

	if(g_Output.GetString().IsEmpty())
	{
		g_Output = g_Input.GetParent() / ("decompressed_" + g_Input.GetName());
	}
	FileOutputStream output(g_Output);

	Decompress(input, output);

	return true;
}

int32 Main(const String &programName, const LinkedList<String> &args)
{
	if(EvaluateArguments(args))
	{
		bool ok = false;

		switch(g_Command)
		{
			case COMMAND_PACK:
				ok = Pack(g_Input, g_Output);
				break;
			case COMMAND_EXTRACT:
				ok = Extract(g_Input, g_Output);
				break;
			case COMMAND_DECOMPRESS:
				ok = DecompressFile();
				break;
		}

		if(ok)
		{
			stdOut << endl << "Done." << endl;
			return EXIT_SUCCESS;
		}
		return EXIT_FAILURE;
	}
	else
	{
		PrintManual();
		return EXIT_FAILURE;
	}

	PrintManual();
	return EXIT_SUCCESS;
}

bool EvaluateArguments(const LinkedList<String> &args)
{
	//At least 2 args must exist
	if(args.GetNumberOfElements() < 2)
		return false;

	//First Arg is the command
	if(args[0] == PROGRAM_ARG_PACK)
	{
		g_Command = COMMAND_PACK;
	}
	else if(args[0] == PROGRAM_ARG_EXTRACT)
	{
		g_Command = COMMAND_EXTRACT;
	}
	else if(args[0] == PROGRAM_ARG_DECOMPRESS)
	{
		g_Command = COMMAND_DECOMPRESS;
	}
	else
	{
		return false;
	}

	for(uint32 i = 1; i < args.GetNumberOfElements(); i++)
	{
		if(args[i][0] == '-' && g_Input.GetString().IsEmpty()) //An option
		{
			return false;
		}
		else //Either input or output
		{
			if(g_Input.GetString().IsEmpty())
			{
				g_Input = args[i];
			}
			else
			{
				if(g_Output.GetString().IsEmpty())
					g_Output = args[i];
				else
					return false;
			}
		}
	}

	return CheckArguments();
}

bool CheckArguments()
{
	return true;
}

void PrintManual()
{
	stdOut
		<< "Usage: " << endl
		<< "  " << "ssaEdit command input [output]" << endl << endl
		<< "  Note: SSSI uses an own created compression method (PK01). This file supports decoding, but will not compress again." << endl << endl
		<< "   command" << endl
		<< "     " << PROGRAM_ARG_PACK << "      pack a directory to a ssa file" << endl
		<< "     " << PROGRAM_ARG_EXTRACT << "   extract a ssa file" << endl
		<< "     " << PROGRAM_ARG_DECOMPRESS << "   decompress a compressed file" << endl
		<< "   input      a input file depending on command" << endl
		<< "   output     optionally a output name, is chosen automatically if not specified" << endl;
}