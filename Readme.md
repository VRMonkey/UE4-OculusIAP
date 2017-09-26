
Installation
-------------
All files must be placed in \Plugins\OculusIAP folder inside your project. Simply build the project, and later enable the plugin. The current version only has 4.16 official support, but should be compatible with future versions as well, despite the warning.

Usage
-----------
Adds via blueprint the ability to open the Oculus Android/Windows Store's checkout page of any given IAP item, and verify wether or not user is entitled to any given IAP item. Developer must verify user entitlement through Oculus's blueprint exposed function BEFORE any calls to this plugin. Success, Failure or Timeout verification is done through Event Dispatchers. Price check has not been fully implemented as of yet.


Contact
-------------
If you have any Questions, Comments, Bug reports or feature requests for this plugin, or you wish to contact us you can and should email contato@vrmonkey.com.br