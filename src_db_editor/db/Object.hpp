/*
 * Copyright (c) 2018-2019 Amir Czwink (amir130@hotmail.de)
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
#pragma once
//Local
#include "DBField.hpp"

struct ObjectProperty
{
	DBType type;
	union
	{
		bool b;
		String* string;
		float32 f;
		uint32 ui;
	};
	uint32 maxChars;

	//Inline
	inline String ToString() const
	{
		switch (this->type)
		{
		case DBType::Bool:
		{
			if (this->b)
				return u8"true";
			return u8"false";
		}
		break;
		case DBType::CharType:
			return *this->string;
		case DBType::Float32:
			return String::Number(this->f);
		case DBType::UInt32:
			return String::Number(this->ui);
		default:
			NOT_IMPLEMENTED_ERROR;
		}
	}
};

class Object
{
public:
	//Constructors
	Object() = default;
	Object(const Object&) = default;
	Object(Object&&) = default;

	//Destructor
	~Object();

	//Operators
	Object& operator=(const Object&) = default;
	Object& operator=(Object&&) = default;

	//Inline
	inline void AddBool(bool value)
	{
		ObjectProperty v{ DBType::Bool };
		v.b = value;
		this->properties.Push(v);
	}

	inline void AddString(String&& value, uint32 maxChars)
	{
		ObjectProperty v{ DBType::CharType };
		v.string = new String(Move(value));
		v.maxChars = maxChars;
		this->properties.Push(v);
	}

	inline void AddFloat32(float32 value)
	{
		ObjectProperty v{ DBType::Float32 };
		v.f = value;
		this->properties.Push(v);
	}

	inline void AddChildObject(Object* obj)
	{
		this->children.Push(obj);
	}

	inline void AddUInt32(uint32 value)
	{
		ObjectProperty v{ DBType::UInt32 };
		v.ui = value;
		this->properties.Push(v);
	}

	inline const Object& GetChild(uint32 index) const
	{
		return *this->children[index];
	}

	inline uint32 GetNumberOfChildren() const
	{
		return this->children.GetNumberOfElements();
	}

	inline uint32 GetNumberOfProperties() const
	{
		return this->properties.GetNumberOfElements();
	}

	inline const ObjectProperty& GetProperty(uint32 index) const
	{
		return this->properties[index];
	}

private:
	//Members
	DynamicArray<ObjectProperty> properties;
	DynamicArray<Object*> children;
};