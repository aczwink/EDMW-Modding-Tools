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
#include "../db/DB.hpp"
//Namespaces
using namespace StdXX;
using namespace StdXX::UI;

//Forward declarations
class MainWindow;

class ObjectEditorController : public TreeController
{
public:
	//Members
	ControllerIndex activeItemIndex;

	//Constructor
	ObjectEditorController(const MainWindow &mainWindow);

	//Methods
	ControllerIndex GetChildIndex(uint32 row, uint32 column, const ControllerIndex &parent) const override;
	String GetColumnText(uint32 column) const;
	uint32 GetNumberOfChildren(const ControllerIndex &parent) const override;
	uint32 GetNumberOfColumns() const;
	ControllerIndex GetParentIndex(const ControllerIndex &index) const override;
	String GetText(const ControllerIndex &index) const override;

private:
	//Members
	const MainWindow &mainWindow;
};