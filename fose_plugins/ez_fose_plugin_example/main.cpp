// User Defines
#include "config.h"
// FOSE
#include "fose/GameAPI.h"
#include "fose/PluginAPI.h"
#include "fose_common/SafeWrite.h"
// Legacy SDK
#include "fose/CommandTable.h" // Required for new functions
#include "fose/ParamInfos.h"
#include "fose/GameObjects.h"
#include "fose/GameOSDepend.h"
#include <string>
// Windows
#include <shlobj.h>	// CSIDL_MYCODUMENTS

// ================================
// Handles
// ================================

// Handle for the plugin
PluginHandle g_pluginHandle = kPluginHandle_Invalid;

// Handle for other things...

/* // Uncomment to use the FOSE interface
// Handle for the interface
FOSEInterface* g_interface;
*/

/*
// FOSE does not use this
FOSEScriptInterface* g_script;
*/

/* // Uncomment to use the command table interface
// Handle for the command table interface
FOSECommandTableInterface* g_cmdTable;
const CommandInfo* g_TFC;
*/

/* // Uncomment to use messaging
// Handle for the messaging interface
static FOSEMessagingInterface* g_messaging = NULL;
*/

// ================================
// User Code
// ================================

// If is RUNTIME PreProc, not in the Editor
#ifdef RUNTIME

// Example test bool function to print Hello World! to the plugin log and console
// Note: New functions are prepended with "Cmd_" and appended with "_Execute"
// And are enclosed within the #ifdef RUNTIME preprocessor definition
bool Cmd_PluginExampleFunctionsTest_Execute(COMMAND_ARGS)
{
	_MESSAGE("Hello World!"); // print to the plugin log
	Console_Print("Hello Console!"); // print to the in-game console

	//*result = 42;

	return true;
}

#endif // RUNTIME

// Define the example test bool function, including a description of what it does
// Note: Outside of the RUNTIME def, for the editor also
DEFINE_COMMAND_PLUGIN(PluginExampleFunctionsTest, "Prints Hello to the Log and Console", 0, 0, NULL)

// ================================
// Plugin Listener
// ================================

/* // Uncomment to use messaging
// Listener for the plugin
static void PluginListener(FOSEMessagingInterface::Message* msg) noexcept
{
	switch (msg->type) {
		// case FOSEMessagingInterface::kMessage_PostLoad:
		case FOSEMessagingInterface::kMessage_PostPostLoad:
		{
			_MESSAGE("PluginListener: kMessage_PostPostLoad");
			break;
		}
		// case FOSEMessagingInterface::kMessage_ExitGame:
		// case FOSEMessagingInterface::kMessage_ExitToMainMenu:
		// case FOSEMessagingInterface::kMessage_LoadGame:
		// case FOSEMessagingInterface::kMessage_SaveGame:
		// case FOSEMessagingInterface::kMessage_Precompile:
		// case FOSEMessagingInterface::kMessage_ExitGame_Console:
		// case FOSEMessagingInterface::kMessage_RuntimeScriptError:
		// case FOSEMessagingInterface::kMessage_DeleteGame: 		// kV2
		// case FOSEMessagingInterface::kMessage_RenameGame: 		// kV2
		// case FOSEMessagingInterface::kMessage_RenameNewGame:		// kV2
		// case FOSEMessagingInterface::kMessage_NewGame: 			// kV2
		// case FOSEMessagingInterface::kMessage_DeleteGameName:	// kV3
		// case FOSEMessagingInterface::kMessage_RenameGameName:	// kV3
		// case FOSEMessagingInterface::kMessage_RenameNewGameName:	// kV3
		// case FOSEMessagingInterface::kMessage_PreLoadGame:
		// case FOSEMessagingInterface::kMessage_PostLoadGame:
	}
}
*/

// ================================
// Plugin Compatibility Check
// ================================

// Check that the runtime and plugin versions are compatible
const bool IsCompatible(const FOSEInterface* fose)
{
	// check if it's being loaded into the editor
	if(fose->isEditor)
	{
		_MESSAGE("IsCompatible: isEditor");
		
		// FIXME - can i use the prop global variable here? it's only set for the editor which plugins don't need?
		// check that it's the supported editor
		if(fose->editorVersion < SUPPORTED_RUNTIME_VERSION_CS) { // CS_VERSION_1_4_0_518
			_MESSAGE("ERROR::IsCompatible: Editor incorrect editor version (got %08X need at least %08X)", fose->editorVersion, SUPPORTED_RUNTIME_VERSION_CS); // CS_VERSION_1_4_0_518
			_ERROR("ERROR::IsCompatible: Editor incorrect editor version (got %08X need at least %08X)", fose->editorVersion, SUPPORTED_RUNTIME_VERSION_CS); // CS_VERSION_1_4_0_518
			return false;
		}
#ifdef NOGORE
		_ERROR("Editor only uses standard edition, closing.");
		return false;
#endif // NOGORE
	}
	// check for compatible version. if strict=true, runtime and supported versions must match. if strict=false, runtime version must be above the minimum
	else if (!IVersionCheck::IsCompatibleVersion(fose->runtimeVersion, MINIMUM_RUNTIME_VERSION, SUPPORTED_RUNTIME_VERSION, SUPPORTED_RUNTIME_VERSION_STRICT)) { // not strict
		_MESSAGE("ERROR::IsCompatible: Plugin is not compatible with runtime version, disabling");
		_FATALERROR("ERROR::IsCompatible: Plugin is not compatible with runtime version, disabling");
		
#ifdef NOGORE
		if(!fose->isNogore) { // if is no gore, but gore is set
			_MESSAGE("ERROR::IsCompatible: Incorrect runtime edition (got %08X need %08X (nogore))", fose->isNogore, 1);
			_ERROR("ERROR::IsCompatible: Incorrect runtime edition (got %08X need %08X (nogore))", fose->isNogore, 1);
			return false;
		}
#else
		if(fose->isNogore) { // if is gore, but no gore is set
			_MESSAGE("ERROR::IsCompatible: Incorrect runtime edition (got %08X need %08X (standard))", fose->isNogore, 0);
			_ERROR("ERROR::IsCompatible: Incorrect runtime edition (got %08X need %08X (standard))", fose->isNogore, 0);
			return false;
		}
#endif // NOGORE
		
		// not compatible
		return false;
	}
	
	// compatible
	return true;
}

// ================================
// Plugin Export, Query and Load - Start Extern-C
// ================================

extern "C" { // Start: extern "C"

// ================================
// Plugin Version Data - Not Used In All SE SDK's
// ================================

/*
// FOSE does not use this
__declspec(dllexport) FOSEPluginVersionData FOSEPlugin_Version =
{
};
*/

// ================================
// Plugin Query - Not Used In All SE SDK's
// ================================

// FOSE Plugin Query - Called when the plugin is queried
bool FOSEPlugin_Query(const FOSEInterface* fose, PluginInfo* info)
{
	// open the plugin log file
	// gLog.Open(CSIDL_MYDOCUMENTS, PLUGIN_LOG_FILE); // vc9_fose
	gLog.OpenRelative(CSIDL_MYDOCUMENTS, PLUGIN_LOG_FILE); // Added OpenRelative for uniformity
	
	_MESSAGE(PLUGIN_VERSION_INFO); // write the plugin version to the log
	_MESSAGE("Plugin_Query: Querying");

	// populate info structure
	info->infoVersion =	PluginInfo::kInfoVersion;
	info->name =		PLUGIN_NAME_LONG;		// set in config.h
	info->version =		PLUGIN_VERSION_DLL;		// set in config.h
	
	// check for compatible versions
	if (!IsCompatible(fose)) {
		_MESSAGE("ERROR::Plugin_Query: Incompatible | Disabling Plugin");
		_FATALERROR("ERROR::Plugin_Query: Incompatible | Disabling Plugin");
		// incompatible
		return false;
	}
	
	// ######################################################
	// Note: Nothing should be assigned below this point
	// Get the necessary info about the plugin and return
	// ######################################################
	
	_MESSAGE("Plugin_Query: Queried Successfully"); // log the successful query

	// supported runtime version
	return true;
}

// ================================
// Plugin Preload - Not Used In All SE SDK's
// ================================

/*
// FOSE does not use this
bool FOSEPlugin_Preload(const FOSEInterface* fose)
{
}
*/

// ================================
// Plugin Load - Used In All SE SDK's
// ================================

// FOSE Plugin Load - Called when the plugin loads everytime
bool FOSEPlugin_Load(const FOSEInterface* fose)
{
	// open the plugin log file
	//  gLog.Open(PLUGIN_LOG_FILE); // vc9_fose
	gLog.OpenRelative(CSIDL_MYDOCUMENTS, PLUGIN_LOG_FILE); // Added OpenRelative for uniformity
	
	_MESSAGE(PLUGIN_VERSION_INFO); // write the plugin version to the log
	_MESSAGE("Plugin_Load: Loading");
	
	// check for compatible versions
	if (!IsCompatible(fose)) {
		_MESSAGE("ERROR::Plugin_Load: Incompatible | Disabling Plugin");
		_FATALERROR("ERROR::Plugin_Load: Incompatible | Disabling Plugin");
		// incompatible
		return false;
	}
	
	// store plugin handle for later
	g_pluginHandle = fose->GetPluginHandle();
	
	/* // Uncomment to use the FOSE interface
	// save the FOSEinterface in case we need it later
	g_interface = (FOSEInterface *)fose;
	*/
	
	/* // Uncomment to use messaging
	// register the listener
	g_messaging = (FOSEMessagingInterface*)fose->QueryInterface(kInterface_Messaging);
	if (g_messaging) {
		if (g_messaging->RegisterListener(g_pluginHandle, "FOSE", PluginListener)) {
			_MESSAGE("Plugin_Load: Listener Registered");
		}
	}
	*/
	
	/***************************************************************************
	 *	
	 *	IMPORTANT::READ THIS!
	 *	
	 *	Before releasing your plugin, you need to request an opcode range from
	 *	the FOSE team and set it in your first SetOpcodeBase call. If you do not
	 *	do this, your plugin will create major compatibility issues with other
	 *	plugins, and will not load in release versions of FOSE. See
	 *	fose_readme.txt for more information.
	 *	
	 **************************************************************************/
	 
	// register the new functions
	fose->SetOpcodeBase(0x2000);
	if (fose->RegisterCommand(&kCommandInfo_PluginExampleFunctionsTest)) {
		_MESSAGE("Plugin_Load: Functions Registered");
	}
	
	_MESSAGE("Plugin_Load: Loaded Successfully"); // log the successful load

	// initialized
	return true;
}

}; // Stop: extern "C"

// ================================
