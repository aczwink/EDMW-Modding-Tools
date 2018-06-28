/*
 * Copyright (c) 2018 Amir Czwink (amir130@hotmail.de)
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
#include "DB.hpp"

struct FieldValue
{
	String string;
};

class Object
{
public:
	//Constructor
	inline Object(DB &db) : db(db), values(db.GetFields().GetNumberOfElements())
	{
	}

	//Inline
	inline const FieldValue &GetValue(uint32 index) const
	{
		return this->values[index];
	}

	inline void SetValue(uint32 index, const String &value)
	{
		const DBField &field = this->db.GetFields()[index];
		ASSERT(field.type == DBType::CharType, "If you see this, report this");
		this->values[index].string = value;
	}

private:
	//Members
	DB &db;
	FixedArray<FieldValue> values;
};