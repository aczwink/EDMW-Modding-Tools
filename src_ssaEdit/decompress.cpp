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
//Libs
#include <ACStdLib.hpp>
//Namespaces
using namespace ACStdLib;

/*
I got this algorithm through reverse engineering.
Also all the tables are from there.
Source file: Low-Level Engine.dll from Empires DMW v1.3
Root function: UDataCompression::Decompress
*/

static bool g_tablesCreated = false;

//Length tables
static const uint8 lengthBitLengthTable[16] = {3, 2, 3, 3, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 7, 7};
static const uint8 lengthExtraBitsTable[16] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 5, 6, 7, 8};
static const uint16 lengthExtraTable[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 14, 22, 38, 70, 134, 262};
static const uint8 lengthInitIdxTable[16] = {5, 3, 1, 6, 10, 2, 12, 20, 4, 24, 8, 48, 16, 32, 64, 0}; //i don't understand this table

static uint8 lengthMap[256]; //gets calculated

//Distance tables
static const uint8 distanceBitLengthTable[64] = {2, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
static const uint8 distanceInitIdxTable[64] = {3, 13, 5, 25, 9, 17, 1, 62, 30, 46, 14, 54, 22, 38, 6, 58, 26, 42, 10, 50, 18, 34, 66, 2, 124, 60, 92, 28, 108, 44, 76, 12, 116, 52, 84, 20, 100, 36, 68, 4, 120, 56, 88, 24, 104, 40, 72, 8, 240, 112, 176, 48, 208, 80, 144, 16, 224, 96, 160, 32, 192, 64, 128, 0}; //i don't understand this table

static uint8 distanceMap[256]; //gets calculated

void ConstructCodingTable(uint8 size, const uint8 *pSrcTable1, const uint8 *pSrcTable2, uint8 *pDestTable)
{
	int8 i;
	uint16 value, idx;

	for(i = size - 1; i >= 0; i--)
	{
		value = pSrcTable1[i];
		idx = pSrcTable2[i];

		while(idx < 265)
		{
			pDestTable[idx] = i;
			idx += (1 << value);
		}
	}
}

void Decompress(InputStream &refSource, AOutputStream &refOutput)
{
	byte isVariableLength;
	uint8 dictionarySizeCoding, readLength, readDistance;
	uint16 dictionaryIndex, decodedLength, decodedDistance;
	uint32 uncompressedSize, nBytesDecompressed;
	byte dictionary[10000];

	if(!g_tablesCreated)
	{
		ConstructCodingTable(sizeof(lengthBitLengthTable), lengthBitLengthTable, lengthInitIdxTable, lengthMap); //some kind of constant length shannon fano tree
		ConstructCodingTable(sizeof(distanceBitLengthTable), distanceBitLengthTable, distanceInitIdxTable, distanceMap);

		g_tablesCreated = true;
	}

	//Read header
	DataReader reader(false, refSource);
	uncompressedSize = reader.ReadUInt32();
	refSource.Skip(4); //seems to be always 0
	isVariableLength = reader.ReadByte();
	dictionarySizeCoding = reader.ReadByte();

	ASSERT(isVariableLength == 0); //1 = variable length; 0 = fixed length
	ASSERT(dictionarySizeCoding == 6); //6 indicates dictionary size of 4096

	BufferedInputStream bufferedInputStream(refSource);
	BitInputStreamBitReversed refBitInput(bufferedInputStream);

	dictionaryIndex = 0;
	nBytesDecompressed = 0;
	while(nBytesDecompressed < uncompressedSize)
	{
		if(!refBitInput.Read(1)) //opposite of zip implode-.-
		{
			//literal data
			dictionary[dictionaryIndex++] = (byte)refBitInput.Read(8);
			nBytesDecompressed++;
		}
		else
		{
			//sliding dictionary match

			//Decode the length first, also opposite of zip-.-
			readLength = lengthMap[(uint8)refBitInput.Get(8)];
			refBitInput.Skip(lengthBitLengthTable[readLength]);

			if(lengthExtraBitsTable[readLength]) //check if the length is extra long
				decodedLength = (uint16)refBitInput.Read(lengthExtraBitsTable[readLength]) + lengthExtraTable[readLength];
			else //no extra length
				decodedLength = readLength;

			//Decode the distance
			readDistance = distanceMap[(uint8)refBitInput.Get(8)];
			refBitInput.Skip(distanceBitLengthTable[readDistance]);

			if(decodedLength == 0) //2bit extra distance
				decodedDistance = (uint16)refBitInput.Read(2) | ((uint16)readDistance << 2);
			else //'dictionarySizeCoding' extra bits, this time they are lower bits
				decodedDistance = (readDistance << dictionarySizeCoding) | (uint8)refBitInput.Read(dictionarySizeCoding);

			decodedLength += 2; //minimum match length

			//Write into dictionary
			//stdOut << decodedLength << endl;
			MemCopy(&dictionary[dictionaryIndex], &dictionary[dictionaryIndex - (decodedDistance + 1)], decodedLength);
			dictionaryIndex += decodedLength;
			nBytesDecompressed += decodedLength;
		}

		ASSERT(dictionaryIndex < sizeof(dictionary));

		if(dictionaryIndex >= 8192)
		{
			refOutput.WriteBytes(dictionary, 4096);
			MemCopy(dictionary, &dictionary[4096], dictionaryIndex - 4096);
			dictionaryIndex -= 4096;
		}
	}

	refOutput.WriteBytes(dictionary, dictionaryIndex);
}