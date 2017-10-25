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
//Local
#include "SSA.h"
//Namespaces
using namespace ACStdLib;

struct SFileHeader
{
	ByteString fileName;
	uint32 offset;
	uint32 size;
};

//Forward declarations
void Decompress(InputStream &refSource, AOutputStream &refOutput);

bool ReadFileHeaders(SeekableInputStream &refInput, LinkedList<SFileHeader> &refFileHeaders, uint32 fileHeadersSize)
{
	uint32 nameLength;
	char buffer[1000];
	SFileHeader fileHeader;

	MemZero(buffer, sizeof(buffer));

	while(refInput.GetCurrentOffset() < fileHeadersSize + SSA_HEADER_SIZE)
	{
		DataReader reader(false, refInput);
		nameLength = reader.ReadUInt32();
		if(nameLength > sizeof(buffer))
			return false;
		refInput.ReadBytes(buffer, nameLength);
		buffer[nameLength] = 0;

		fileHeader.fileName = buffer;

		fileHeader.offset = reader.ReadUInt32();
		refInput.Skip(4); //seems to be: offset + size -1
		fileHeader.size = reader.ReadUInt32();

		refFileHeaders.InsertTail(fileHeader);
	}

	return true;
}

void ExtractFile(InputStream &refSource, AOutputStream &refSink, uint32 size)
{
	if(size > 4)
	{
		DataReader reader(false, refSource);

		uint32 signature = reader.ReadUInt32();
		if(signature == 0x31304B50)
		{
			Decompress(refSource, refSink);
			return;
		}
		else
		{
			refSink.WriteUInt32LE(signature);
			size -= 4;
		}
	}
	refSource.FlushTo(refSink, size);
}

bool Extract(Path input, Path output)
{
	uint8 percentage, lastPercentage;
	uint32 i, signature, versionMajor, versionMinor, fileHeadersSize;
	FileInputStream file(input);
	LinkedList<SFileHeader> fileHeaders;

	if(output.GetString().IsEmpty())
	{
		output = input.GetParent();
		if(output.IsRoot())
			output = input.GetTitle();
		else
			output /= input.GetTitle();
	}

	DataReader reader(false, file);
	signature = reader.ReadUInt32();
	versionMajor = reader.ReadUInt32();
	versionMinor = reader.ReadUInt32();
	if(signature != SSA_SIGNATURE || versionMajor != SSA_VERSION_MAJOR || versionMinor != SSA_VERSION_MINOR)
	{
		stdErr << "This is not a ssa file." << endl;
		return false;
	}

	fileHeadersSize = reader.ReadUInt32();
	if(!ReadFileHeaders(file, fileHeaders, fileHeadersSize))
	{
		stdErr << "An error occured while reading the file headers of the archive." << endl;
		return false;
	}

	stdOut << "Files to extract: " << fileHeaders.GetNumberOfElements() << endl << endl;

	//Extract files
	lastPercentage = -1;
	i = 0;

	for(const SFileHeader &currentHeader : fileHeaders)
	{
		percentage = (uint8)(i * 100 / fileHeaders.GetNumberOfElements());
		if(percentage != lastPercentage)
		{
			lastPercentage = percentage;

			stdOut << "progress:" << percentage << "%    ";
			stdOut << "files left: " << fileHeaders.GetNumberOfElements() - i << endl;
		}

		Path currentPath = output / String(UTF8String(currentHeader.fileName));
		Path currentDir = currentPath.GetParent();
		if(!currentDir.CreateDirectoryTree())
		{
			stdErr << "Couldn't create directory '" << currentHeader.fileName << "'." << endl;
			return false;
		}

		file.SetCurrentOffset(currentHeader.offset);
		FileOutputStream currentOutFile(currentPath);
		ExtractFile(file, currentOutFile, currentHeader.size);

		i++;
	}

	return true;
}