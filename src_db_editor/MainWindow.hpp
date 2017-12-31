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
//Local
#include "ItemFieldsController.hpp"

class MainWindow : public MainAppWindow
{
public:
	//Constructor
	MainWindow();

	//Inline
	inline uint32 GetActiveDBIndex() const
	{
		return this->activeDBIndex;
	}

	inline void SetCurrentItem(const ControllerIndex &index)
	{
		this->itemFieldsController.activeItemIndex = index;
		this->itemFieldsController.ModelChanged();
	}

private:
	//Members
	uint32 activeDBIndex;

	//UI
	TreeView *itemView;
	ItemFieldsController itemFieldsController;

	//Methods
	void SetupChildren();
	void SetupSelectionPanel();
};