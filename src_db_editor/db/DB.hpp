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
#pragma once
#include <Std++.hpp>
//Local
#include "DBField.hpp"
#include "../definitions.hpp"
#include "Object.hpp"
//Namespaces
using namespace StdXX;

class DB
{
public:
	//Functions
	static String LoadLanguageString(uint32 resourceId, uint8 langDllNumber);

	//Inline
	inline Path GetPath() const
	{
		return Path(g_settings.GetStringValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_EDMWPATH)) / Path(u8"Data/db") / (this->name + u8".dat");
	}
};