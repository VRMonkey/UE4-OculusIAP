Building
-----------------
Open the .sln file and build the solution. Create a zip or 7z file containing the following:
Plugins/OculusIAP/...

Binaries/Win64/UE4Editor-OculusIAP.dll
Resources/Icon128.png
OculusIAP.uplugin


Installation
-------------
Unzip the package into the Plugins directory of your game. To add it as an engine plugin you will need to unzip the module into the plugin directory under where you installed UE4.


Usage
-----------
Adds via blueprint the ability to open the Oculus Android/Windows Store's checkout page of any given IAP item, and verify wether or not user is entitled to any given IAP item. Developer must verify user entitlement through Oculus's blueprint exposed function BEFORE any calls to this plugin.


Contact
-------------
If you have any Questions, Comments, Bug reports or feature requests for this plugin, or you wish to contact me you can and should email me - contato@vrmonkey.com.br