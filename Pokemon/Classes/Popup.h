#pragma once
#ifndef Popup_h
#define Popup_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

/*
-Displays a popup
-Resizes itself
-Automatically swallows rest of the touches
-Exit is called if touch is outside Bg
*/

namespace UICustom 
{
	class PopupDelegates : public cocos2d::LayerRadialGradient
	{
	public:
		static PopupDelegates *create();

	protected:
		virtual bool init();
		virtual void setUpTouches();

		virtual void show(const bool animated = true);
		virtual void dismiss(const bool animated = true);
		void setAnimated(const bool animated) { _isAnimated = animated; };

		cocos2d::ui::ImageView *_bg = nullptr;
	private:
		bool _isAnimated = false;
	};
	class Popup : public PopupDelegates
	{
	public:
		static Popup* createAbout();
		static Popup* createSetting();
		static Popup* createShop();
	private:
		void initBg(const cocos2d::Size size);
	};
}

#endif /* Popup_h */