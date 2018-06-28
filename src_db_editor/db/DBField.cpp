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
//Class header
#include "DBField.hpp"

//Public methods
String DBField::ValueToString(const void *p) const
{
	if(this->type == DBType::CharType)
	{
		char buffer[101];
		MemCopy(buffer, p, this->count);
		buffer[100] = 0;

		return buffer;
	}

	String result;
	for(uint32 i = 0; i < this->count; i++)
	{
		const byte *p_offseted = static_cast<const byte *>(p) + i * 4;
		BufferInputStream inputStream(p_offseted, 4);
		DataReader reader(false, inputStream);

		switch (this->type)
		{
			case DBType::Bool:
			{
				if(reader.ReadByte())
					result += "True";
				else
					result += "False";
			}
			break;
			case DBType::ByteType:
			{
				uint64 v = ((byte *) p)[i];
				result += String::HexNumber(v, 2, false);
			}
			break;
			case DBType::Float32:
				result += String::Number(reader.ReadFloat32());
			break;
			case DBType::UInt32:
				result += String::Number(reader.ReadUInt32());
				break;
		}

		result += " ";
	}

	return result;
}

//Private methods
uint32 DBField::GetTypeSize() const
{
	switch(this->type)
	{
		case DBType::Bool:
		case DBType::CharType:
		case DBType::ByteType:
			return 1;
		case DBType::Float32:
		case DBType::UInt32:
			return 4;
	}
}