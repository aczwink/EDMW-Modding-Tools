/*
 * Copyright (c) 2017-2018 Amir Czwink (amir130@hotmail.de)
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
#include <Std++.hpp>
using namespace StdXX;
//Local
#include "db/DBManager.hpp"
#include "ui/MainWindow.hpp"

//Global Variables
ConfigurationFile g_settings(SETTINGS_FILENAME, false);

int32 Main(const String &programName, const FixedArray<String> &args)
{
	StandardEventQueue eventQueue;
	MainWindow* mainWindow = new MainWindow(eventQueue);
	mainWindow->Show();

	eventQueue.ProcessEvents();
	DBManager::Get().ReleaseAll();

	return EXIT_SUCCESS;
}

/*
//Local
#include "definitions.hpp"

MainWindow *g_mainWindow;

void RunFindEDMWPathDialog()
{
	auto callback = [](const Path &refPath)
	{
		return (refPath / Path(EMPIRES_EXENAME)).Exists();
	};

	Path path = g_mainWindow->SelectExistingDirectory(u8"Select Empires installation directory", callback);
	if(path.GetString().IsEmpty())
		throw false; //error

	g_settings.SetValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_EDMWPATH, path.GetString());
	g_settings.SetValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_SHOWUNKNOWNVALUES, false);
	g_settings.SetValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_SHOWCONSTANTVALUES, false);
}

void Init()
{
	if(!g_settings.ContainsValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_EDMWPATH))
	{
		g_mainWindow->ShowInformationBox("Missing Settings", "Please select path to Empires");
		RunFindEDMWPathDialog();
	}

	Path exePath = g_settings.GetStringValue(SETTINGS_SECTION_GENERAL, SETTINGS_KEY_EDMWPATH);
	exePath /= Path(EMPIRES_EXENAME);

	if(!exePath.Exists())
	{
		g_mainWindow->ShowErrorBox("Invalid Settings", "Path to Empires is invalid, please select the correct one.");
		RunFindEDMWPathDialog();
	}
}

int32 Main(const String &programName, const FixedArray<String> &args)
{
try
	{
		Init();
	}
	catch(...)
	{
		delete g_mainWindow;
		return EXIT_FAILURE;
	}
}*/