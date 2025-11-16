/*
 * Copyright (c) 2017-2025 Amir Czwink (amir130@hotmail.de)
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

struct EDMW_DBObjectValue
{
	union
	{
		bool boolValue;
		float32 f32Value;
		int32 i32Value;
		uint32 u32Value;
	};
	StdXX::String stringValue;
};

class EDMW_DBObject
{
	struct Entry
	{
		EDMW_DBObjectValue value;
		StdXX::DynamicArray<EDMW_DBObjectValue> array;
	};
public:
	//Properties
	inline const StdXX::DynamicArray<StdXX::UniquePointer<EDMW_DBObject>>& Children() const
	{
		return this->children;
	}

	//Inline
	inline void Add(bool value)
	{
		Entry v;
		v.value.boolValue = value;
		this->values.Push(v);
	}

	inline void Add(StdXX::DynamicArray<EDMW_DBObjectValue>&& value)
	{
		Entry v;
		v.array = StdXX::Move(value);
		this->values.Push(StdXX::Move(v));
	}

	inline void Add(float32 value)
	{
		Entry v;
		v.value.f32Value = value;
		this->values.Push(v);
	}

	inline void Add(int32 value)
	{
		Entry v;
		v.value.i32Value = value;
		this->values.Push(v);
	}

	inline void Add(const StdXX::String& value)
	{
		Entry v;
		v.value.stringValue = value;
		this->values.Push(v);
	}

	inline void Add(uint32 value)
	{
		Entry v;
		v.value.u32Value = value;
		this->values.Push(v);
	}

	inline void AddChild(StdXX::UniquePointer<EDMW_DBObject>&& object)
	{
		this->children.Push(Move(object));
	}

	inline const StdXX::DynamicArray<EDMW_DBObjectValue>& GetArray(uint8 propertyIndex) const
	{
		return this->values[propertyIndex].array;
	}

	inline bool GetBool(uint8 propertyIndex) const
	{
		return this->values[propertyIndex].value.boolValue;
	}

	inline float32 GetFloat32(uint8 propertyIndex) const
	{
		return this->values[propertyIndex].value.f32Value;
	}

	inline int32 GetInt32(uint8 propertyIndex) const
	{
		return this->values[propertyIndex].value.i32Value;
	}

	inline const StdXX::String& GetString(uint8 propertyIndex) const
	{
		return this->values[propertyIndex].value.stringValue;
	}

	inline uint32 GetUInt32(uint8 propertyIndex) const
	{
		return this->values[propertyIndex].value.u32Value;
	}

private:
	//State
	StdXX::DynamicArray<Entry> values;
	StdXX::DynamicArray<StdXX::UniquePointer<EDMW_DBObject>> children;
};