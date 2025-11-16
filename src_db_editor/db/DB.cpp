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
DynamicArray<DBField> DB::ParseFields(const XML::Element& element)
{
	DynamicArray<DBField> result;

	uint32 index = 0;
	for (const XML::Node *const& node : element)
	{
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