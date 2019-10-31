/*
 * Copyright (c) 2017-2019 Amir Czwink (amir130@hotmail.de)
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
#include "DB.hpp"

//Public methods
void DB::Load()
{
	FileInputStream file(this->GetPath());
	BufferedInputStream bufferedInput(file);
	DataReader reader = DataReader(false, bufferedInput);
	TextReader textReader = TextReader(bufferedInput, TextCodecType::Latin1);

	while (true)
	{
		if (this->repeating && file.IsAtEnd())
			break;

		Map<String, uint32> virtuals;
		this->LoadFields(this->root, this->fields, virtuals, reader, textReader);

		if(!this->repeating)
			break;
	}

	//ASSERT(file.IsAtEnd(), u8"File should have been read to the end!");
	
	this->isLoaded = true;
}

//Class functions
#ifdef XPC_OS_WINDOWS
#include <Windows.h>
String DB::LoadLanguageString(uint32 resourceId, uint8 langDllNumber)
{
	const static String langDllPath = OSFileSystem::GetInstance().ToNativePath(Path(g_settings.GetStringValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_EDMWPATH)) / String(EMPIRES_LANGDLL));
	const static String lang2DllPath = OSFileSystem::GetInstance().ToNativePath(Path(g_settings.GetStringValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_EDMWPATH)) / String(EMPIRES_LANG2DLL));
	
	const static HMODULE langDllModule = LoadLibraryW((LPCWSTR)langDllPath.ToUTF16().GetRawZeroTerminatedData());
	const static HMODULE lang2DllModule = LoadLibraryW((LPCWSTR)lang2DllPath.ToUTF16().GetRawZeroTerminatedData());
	const static HMODULE langs[] = { nullptr, langDllModule, lang2DllModule };

	ASSERT(Math::IsValueInInterval(langDllNumber, uint8(1), uint8(2)), u8"Invalid langdll number");
	LPWSTR resource;
	int res = LoadStringW(langs[langDllNumber], resourceId, (LPWSTR)&resource, 0);
	if (res)
		return String::CopyRawString((uint16*)resource, res);
	return String();
}
#else
String DB::LoadLanguageString(uint32 resourceId, uint8 langDllNumber)
{
	return u8"Loading language is only supported on Windows currently.";
}
#endif

//Private methods
DynamicArray<const DBField*> DB::FlattenFields(const DynamicArray<DBField>& fields) const
{
	DynamicArray<const DBField*> flattened;

	for (const DBField& field : fields)
	{
		uint32 count;

		if (!field.virt.IsEmpty())
			continue; //virtuals are not editable
		
		switch (field.type)
		{
		case DBType::CharType:
			count = 1;
			break;
		default:
			if (field.count.IsEmpty())
				count = 1;
			else if (field.count.StartsWith(u8"#"))
				count = 1; //its a list
			else
				count = field.count.ToUInt32();
		}

		for (uint32 i = 0; i < count; i++)
			flattened.Push(&field);
	}

	return flattened;
}

void DB::LoadFields(Object& object, const DynamicArray<DBField>& fields, Map<String, uint32>& virtuals, DataReader& reader, TextReader& textReader)
{
	for (const DBField& field : fields)
	{
		//check for virtual
		if (!field.virt.IsEmpty())
		{
			ASSERT((field.type == DBType::UInt32) && (field.count.IsEmpty()), u8"Report this please!");

			if (field.virt.StartsWith(u8"#"))
			{
				virtuals[field.virt] = reader.ReadUInt32();
			}
			else
				NOT_IMPLEMENTED_ERROR;
			continue;
		}

		//eval count
		uint32 count = 1;
		if (!field.count.IsEmpty())
		{
			if (virtuals.Contains(field.count))
				count = virtuals[field.count];
			else
				count = field.count.ToUInt32();
		}
		
		switch (field.type)
		{
		case DBType::Bool:
		{
			for (uint32 i = 0; i < count; i++)
				object.AddBool(reader.ReadByte() != 0);
		}
		break;
		case DBType::CharType:
		{
			object.AddString(textReader.ReadString(count), count);
		}
		break;
		case DBType::Float32:
		{
			for (uint32 i = 0; i < count; i++)
				object.AddFloat32(reader.ReadFloat32());
		}
		break;
		case DBType::NamedType:
		{
			for (uint32 i = 0; i < count; i++)
			{
				Object* child = new Object;

				//read type
				if (!field.name.IsEmpty())
					this->LoadFields(*child, this->types[field.name], virtuals, reader, textReader);

				//read children
				this->LoadFields(*child, field.childrenFields, virtuals, reader, textReader);

				object.AddChildObject(child);
			}
		}
		break;
		case DBType::UInt32:
		{
			for (uint32 i = 0; i < count; i++)
				object.AddUInt32(reader.ReadUInt32());
		}
		break;
		default:
			NOT_IMPLEMENTED_ERROR;
		}
	}
}

DynamicArray<DBField> DB::ParseFields(const XML::Element& element)
{
	DynamicArray<DBField> result;

	uint32 index = 0;
	for (const XML::Node *const& node : element)
	{
		ASSERT(node->GetType() == XML::NodeType::Element, u8"If you see this, please report");
		XML::Element const& fieldElement = *(XML::Element *)node;

		DBField dbEntry;
		
		if (fieldElement.GetName() == u8"Field")
		{
			//type
			if (fieldElement.GetAttribute("type") == "bool")
				dbEntry.type = DBType::Bool;
			else if (fieldElement.GetAttribute("type") == "byte")
				dbEntry.type = DBType::ByteType;
			else if (fieldElement.GetAttribute("type") == "char")
				dbEntry.type = DBType::CharType;
			else if (fieldElement.GetAttribute("type") == "float32")
				dbEntry.type = DBType::Float32;
			else if (fieldElement.GetAttribute("type") == "uint32")
				dbEntry.type = DBType::UInt32;
			else
				NOT_IMPLEMENTED_ERROR;

			//name
			if (fieldElement.HasAttribute(u8"name"))
				dbEntry.name = fieldElement.GetAttribute("name");

			//language
			if (fieldElement.HasAttribute(u8"language"))
				dbEntry.language = (uint8)fieldElement.GetAttribute(u8"language").ToUInt32();

			//comment
			if (fieldElement.HasAttribute("comment"))
				dbEntry.comment = fieldElement.GetAttribute("comment");

			//filterable
			if (fieldElement.HasAttribute("filterable"))
				this->filterableFields.Push(index);
		}
		else
		{
			ASSERT(this->types.Contains(fieldElement.GetName()), u8"Report this please!");

			dbEntry.type = DBType::NamedType;
			dbEntry.name = fieldElement.GetName();

			dbEntry.childrenFields = this->ParseFields(fieldElement);
		}

		//virtuality
		if(fieldElement.HasAttribute(u8"virtual"))
			dbEntry.virt = fieldElement.GetAttribute(u8"virtual");
			
		//count
		if (fieldElement.HasAttribute("count"))
			dbEntry.count = fieldElement.GetAttribute("count");

		result.Push( Move(dbEntry) );
		index++;
	}

	return result;
}

void DB::ParseXML(const XML::Element& dbElement)
{
	for (const XML::Node *const& node : dbElement)
	{
		ASSERT(node->GetType() == XML::NodeType::Element, u8"If you see this, please report");
		XML::Element const& topLevel = *(XML::Element *)node;

		if (topLevel.GetName() == u8"Define")
		{
			this->types.Insert(topLevel.GetAttribute(u8"type"), this->ParseFields(topLevel));
			this->objectScheme = &this->types[topLevel.GetAttribute(u8"type")];
		}
		else if(topLevel.GetName() == u8"Structure")
		{
			if (topLevel.HasAttribute(u8"repeating") && topLevel.GetAttribute(u8"repeating") == u8"true")
				this->repeating = true;
			this->fields = this->ParseFields(topLevel);
		}
		else
		{
			NOT_IMPLEMENTED_ERROR;
		}
	}

	if(this->objectScheme)
		this->flattenedFields = this->FlattenFields(*this->objectScheme);
	else
		this->flattenedFields = this->FlattenFields(this->fields);
}


/*
//Local
#include "Object.hpp"

//Destructor
DB::~DB()
{
	for(const auto &object : this->objects)
		delete object;
}

//Protected methods
Object *DB::LoadObject(InputStream &inputStream)
{
	Object *row = new Object(*this);

	uint32 i = 0;
	for(const auto &field : this->fields)
	{
		switch(field.type)
		{
			case DBType::CharType:
			{
				TextReader textReader(inputStream, TextCodecType::ASCII);

				String string = textReader.ReadString(100);
				row->SetValue(i, string);
			}
				break;
			case DBType::Bool:
			NOT_IMPLEMENTED_ERROR;
				break;
			case DBType::ByteType:
			NOT_IMPLEMENTED_ERROR;
				break;
			case DBType::Float32:
			NOT_IMPLEMENTED_ERROR;
				break;
			case DBType::UInt32:
			NOT_IMPLEMENTED_ERROR;
				break;
		}

		i++;
	}

	return row;
}*/