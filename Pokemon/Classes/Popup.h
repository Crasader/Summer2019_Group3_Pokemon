

#ifndef Popup_h
#define Popup_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"


namespace UICustom {
    
    
    class PopupDelegates : public cocos2d::LayerRadialGradient
    {
        
    public:
        static PopupDelegates *create();
        
    protected:
        virtual bool init();
        virtual void setUpTouches();
        
        virtual void show(const bool animated = true);
        virtual void dismiss(const bool animated = true);
        void setAnimated(const bool animated){_isAnimated = animated;};
        
        cocos2d::ui::ImageView *_bg = nullptr;
    private:
        bool _isAnimated = false;
    };
    
    
    
    class Popup : public PopupDelegates
    {
        
    public:
        static Popup * createAsMessage(const std::string &title, const std::string &msg);
        static Popup * createAsConfirmDialogue(const std::string &title, const std::string &msg ,const std::function<void ()> &YesFunc);
        static Popup * create(const std::string &title, const std::string &msg, cocos2d::Label *lbl, const std::function<void ()> &YesFunc);
		static Popup * createSetting(const std::string & title);
		static Popup * createBag(const std::string &title);
		static Popup * ChoosePokemon();
		static Popup * CreateBagItemInBattle();
		static Popup * CreateBagInBattle();
		static Popup * CreateShop();
		void SelectedShopItemEvent(Ref *sender, cocos2d::ui::ListView::EventType type);
		static Popup * CreateItemShop(int index);
	private:
        void initBg(const cocos2d::Size size,const std::string &title);
    };
}

#endif /* Popup_h */

