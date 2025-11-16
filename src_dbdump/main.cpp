/*
 * Copyright (c) 2025 Amir Czwink (amir130@hotmail.de)
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
#include <StdXX.hpp>
using namespace StdXX;
using namespace StdXX::Serialization;
#include <EDMW_DBCollection.hpp>

static String GetIdAsString(const EDMW_DBObject& object, const EDMW_ObjectSchema& schema)
{
	const auto& idProp = schema.Properties()[schema.IdPropertyIndex()];
	switch(idProp.type)
	{
		case EDMW_SchemaPropertyType::Bool:
			NOT_IMPLEMENTED_ERROR;
			break;
		case EDMW_SchemaPropertyType::Char:
			NOT_IMPLEMENTED_ERROR;
			break;
		case EDMW_SchemaPropertyType::Float32:
			NOT_IMPLEMENTED_ERROR;
			break;
		case EDMW_SchemaPropertyType::Int32:
			NOT_IMPLEMENTED_ERROR;
			break;
		case EDMW_SchemaPropertyType::UInt32:
			return String::Number(object.GetUInt32(schema.IdPropertyIndex()));
	}

	NOT_IMPLEMENTED_ERROR; //TODO: implement me
	return u8"";
}

void DumpObject(const EDMW_DBObject& object, const EDMW_ObjectSchema& schema, FlexibleFormatType targetFormat, const FileSystem::Path& destinationFolderPath)
{
	String id = GetIdAsString(object, schema);
	String fileName = id + u8"." + GetFileExtensionOfFormat(targetFormat);
	FileOutputStream fileOutputStream(destinationFolderPath / fileName, true);
	BufferedOutputStream bufferedOutputStream(fileOutputStream);

	FlexibleFormatSerializer serializer(bufferedOutputStream, targetFormat);
	serializer.EnterObject(u8"Object");

	uint8 propCounter = 0;
	for(const auto& prop : schema.Properties())
	{
		String sanitizedName = prop.name;

		if(prop.isList)
		{
			switch(prop.type)
			{
				case EDMW_SchemaPropertyType::Char:
					serializer << Binding(sanitizedName, object.GetString(propCounter));
					break;
				case EDMW_SchemaPropertyType::Float32:
				{
					const auto& array = object.GetArray(propCounter);
					DynamicArray<float32> f32s;
					for(const auto& elem : array)
						f32s.Push(elem.f32Value);
					serializer << Binding(sanitizedName, f32s);
				}
					break;
				case EDMW_SchemaPropertyType::UInt32:
				{
					const auto& array = object.GetArray(propCounter);
					DynamicArray<uint32> uint32s;
					for(const auto& elem : array)
						uint32s.Push(elem.u32Value);
					serializer << Binding(sanitizedName, uint32s);
				}
					break;
				default:
					NOT_IMPLEMENTED_ERROR; //TODO: implement me
			}
		}
		else
		{
			switch(prop.type)
			{
				case EDMW_SchemaPropertyType::Bool:
					serializer << Binding(sanitizedName, object.GetBool(propCounter));
					break;
				case EDMW_SchemaPropertyType::Char:
					NOT_IMPLEMENTED_ERROR; //TODO: implement me
					break;
				case EDMW_SchemaPropertyType::Float32:
					serializer << Binding(sanitizedName, object.GetFloat32(propCounter));
					break;
				case EDMW_SchemaPropertyType::Int32:
					serializer << Binding(sanitizedName, object.GetInt32(propCounter));
					break;
				case EDMW_SchemaPropertyType::UInt32:
					serializer << Binding(sanitizedName, object.GetUInt32(propCounter));
					break;
				default:
					NOT_IMPLEMENTED_ERROR; //TODO: implement me
			}
		}
		propCounter++;
	}

	serializer.LeaveObject();

	bufferedOutputStream.Flush();

	if(!object.Children().IsEmpty())
	{
		FileSystem::Path childPath = destinationFolderPath / id;
		FileSystem::File dir(childPath);
		dir.CreateDirectory();

		for(const auto& child : object.Children())
		{
			DumpObject(*child, schema, targetFormat, childPath);
		}
	}
}

void DumpDB(const EDMW_Database& database, const FileSystem::Path& destinationFolderPath)
{
	FlexibleFormatType targetFormat = FlexibleFormatType::YAML;
	const auto& schema = database.Schema();

	for(const auto& object : database.Objects())
	{
		DumpObject(*object, schema, targetFormat, destinationFolderPath);
	}
}

int32 Main(const String& programName, const FixedArray<String>& args)
{
	CommandLine::Parser parser(programName);

	parser.AddHelpOption();

	CommandLine::PathArgument sourcePathArg(u8"source-path", u8"Path to the source database file");
	parser.AddPositionalArgument(sourcePathArg);

	CommandLine::PathArgument schemaPathArg(u8"schema-path", u8"Path to the database schema file");
	parser.AddPositionalArgument(schemaPathArg);

	if(!parser.Parse(args))
	{
		parser.PrintHelp();
		return EXIT_FAILURE;
	}

	const CommandLine::MatchResult& result = parser.ParseResult();

	EDMW_DBCollection edmw_dbCollection;
	FileSystem::Path sourcePath = sourcePathArg.Value(result);
	const auto& db = edmw_dbCollection.LoadDatabase(sourcePath, schemaPathArg.Value(result));

	FileSystem::Path targetPath = sourcePath.GetName();
	FileSystem::File file(targetPath);
	file.CreateDirectory();

	DumpDB(db, targetPath);

	return EXIT_SUCCESS;
}