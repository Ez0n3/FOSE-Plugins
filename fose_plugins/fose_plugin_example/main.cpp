#include "fose/PluginAPI.h"
#include "fose/CommandTable.h"
#include "fose/GameAPI.h"
#include "fose/ParamInfos.h"
#include "fose/GameObjects.h"
#include <string>

IDebugLog		gLog("fose_plugin_example.log");

PluginHandle	g_pluginHandle = kPluginHandle_Invalid;

#ifdef RUNTIME

bool Cmd_ExamplePlugin_PluginTest_Execute(COMMAND_ARGS)
{
	_MESSAGE("plugintest");

	*result = 42;

	Console_Print("plugintest running");

	return true;
}

#endif

DEFINE_COMMAND_PLUGIN(ExamplePlugin_PluginTest, "prints a string", 0, 0, NULL)

extern "C" {

bool FOSEPlugin_Query(const FOSEInterface * fose, PluginInfo * info)
{
	_MESSAGE("query");

	// fill out the info structure
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "fose_plugin_example";
	info->version = 1;

	// version checks
	if(!fose->isEditor)
	{
		if(fose->foseVersion < FOSE_VERSION_INTEGER)
		{
			_ERROR("FOSE version too old (got %08X expected at least %08X)", fose->foseVersion, FOSE_VERSION_INTEGER);
			return false;
		}

		if(fose->runtimeVersion != FALLOUT_VERSION)
		{
			_ERROR("incorrect runtime version (got %08X need %08X)", fose->runtimeVersion, FALLOUT_VERSION);
			return false;
		}
	}
	else
	{
		// no version checks needed for editor
	}

	// version checks pass

	return true;
}

bool FOSEPlugin_Load(const FOSEInterface * fose)
{
	_MESSAGE("load");

	g_pluginHandle = fose->GetPluginHandle();

	/***************************************************************************
	 *	
	 *	READ THIS!
	 *	
	 *	Before releasing your plugin, you need to request an opcode range from
	 *	the FOSE team and set it in your first SetOpcodeBase call. If you do not
	 *	do this, your plugin will create major compatibility issues with other
	 *	plugins, and will not load in release versions of FOSE. See
	 *	fose_readme.txt for more information.
	 *	
	 **************************************************************************/

	// register commands
	fose->SetOpcodeBase(0x2000);
	fose->RegisterCommand(&kCommandInfo_ExamplePlugin_PluginTest);

	return true;
}

};
