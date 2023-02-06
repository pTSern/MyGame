# MyGame

A simple clone of ddtank

#English

+ Categories: Artillery, Offline
+ Language: English
+ Programing Language: C++, SQLite
+ Gameplay: Players must sign in to enter the game. In the main menu, the player can select Battle to enter the Battle scene. In the battle scene, the player will play against the bot whose strength will be calculated based on the player's win rate. To aim at the enemy, the player has to press the Force Key. Kill the enemy to win the game.
+ Note: This game can update a lot of things: Champion, Champion's Skill, Shop. All you need to do are read the code and then follow it to create a new one.

#Download link
https://drive.google.com/file/d/1HlE-l7PCsmN37hoFOZSdzmvxE9mTJmjW/view?usp=sharing


#IOS BUILD FIX

+ Open file {your_project_name}/cocos2d/cmake/Modules/CocosConfigDepend.cmake

+ Replace: /usr/lib/libiconv.dylib/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Library/Developer/CoreSimulator/Profiles/Runtimes/iOS.simruntime/Contents/Resources/RuntimeRoot/usr/lib/libiconv.dylib

/usr/lib/libz.dylib/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Library/Developer/CoreSimulator/Profiles/Runtimes/iOS.simruntime/Contents/Resources/RuntimeRoot/usr/lib/libz.dylib
