#ifndef __UTIL_H__
#define __UTIL_H__

#include "cocos2d.h"
#include "LanguageString.h"
#include "ConstUtil.h"
#include "audio/include/SimpleAudioEngine.h"

USING_NS_CC;

class Util
{
public:
	static Vector<String*> splitString(const char* srcStr, const char* sSep);
	static Point map2GL(const Point& ptMap, TMXTiledMap* map);
	static Point GL2map(const Point& ptGL, TMXTiledMap* map);
	static void sendCustomEvent(const std::string messageType, String* message);
	static void playBgMusic(char* musicName, bool isLoop);
	static void playAudioEffect(const char* effectName, bool isLoop);
	static void playAudioEffectRandom(Vector<String*> effectVec, bool isLoop);
	static void stopAudioPlay();
};


#endif