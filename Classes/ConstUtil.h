#ifndef __CONSTUTIL_H__
#define __CONSTUTIL_H__


#define FU1_IMAGE     "fu1.png"
#define WENG_IMAGE     "weng.png"
#define FU2_IMAGE      "fu2.png"
#define PO_IMAGE      "po.png"

#define NORMAL_MENU   "normal_menu.png"
#define PRESS_MENU    "press_menu.png"
#define MENU_LOGO     "menuLogo.png"
#define RAINBOW       "rainbow.png"

#define FONT_MENU     "Marker Felt"

#define SINGLE_GAME   "single_game"
#define MULTI_GAME    "multi_game"
#define MUSIC_ON      "music_on"
#define MUSIC_OFF     "music_off"
#define LOAD_GAME     "load_game"
#define QUIT_GAME     "quit_game"

#define MUSIC_ON_KEY  "music_on_key"

#define  BUY_LAND_MSG "buy_land_msg"

#define  DIALOG_BG "popuplayer/dialog_bg.png"
#define  BUTTON_BG1 "popuplayer/button_bg1.png"
#define  BUTTON_BG2 "popuplayer/button_bg2.png"
#define  BUTTON_BG3 "popuplayer/button_bg3.png"

#define DIALOG_TITLE  "dialog_title"
#define DIALOG_CONTENT "dialog_content"
#define OK "ok"
#define CANCEL "cancel"

const int Dialog_Size_Width = 400;
const int Dialog_Size_Height = 220;

const int Btn_OK_TAG = 1;
const int Btn_Cancel_TAG = 0;

#define STAGE_BACKGROUND "map/stage_background2.png"
#define MAP_1 "map/map_1.png"
#define MAP_2 "map/map_2.png"
#define MAP_3 "map/map_3.png"

#define RIGHT_BANNER "map/right_banner.png"
#define PLAYER_1 "map/player1.png"
#define PLAYER_2 "map/player2.png"

#define PLAYER1_ANIM_PLIST   "images/player1_anim.plist"
#define PLAYER1_ANIM_PNG "images/player1_anim.png"

#define PLAYER2_ANIM_PLIST "images/player2_anim.plist"
#define PLAYER2_ANIM_PNG "images/player2_anim.png"

#define PLAYER_1_NAME "player1"
const int PLAYER_1_TAG = 1;
#define PLAYER_2_NAME "player2"
const int PLAYER_2_TAG = 2;

#define RICHER_MSG "richer_msg"
#define RICHER_CONTROLLER_MSG "richer_controller_msg"

const int MSG_GO_HIDE_TAG = 0;
const int MSG_GO_SHOW_TAG = 1;
const int MSG_BUY_BLANK_TAG = 2;
const int MSG_BUY_LAND_1_TAG = 3;
const int MSG_BUY_LAND_2_TAG = 4;
const int MSG_PICKONE_TOGO_TAG = 5;
const int MSG_PAY_TOLLS_1_TAG = 6;
const int MSG_PAY_TOLLS_2_TAG = 7;
const int MSG_PAY_TOLLS_3_TAG = 8;
const int MSG_AROUND_LAND_TAG = 9;
const int MSG_RANDOM_ASK_EVENT_TAG = 10;
const int MSG_BLOCK_WAY_EVENT_TAG = 11;
const int MSG_HANDLE_PROP_EVENT_TAG = 12;
const int MSG_ROUND_COUNT_TAG = 13;
const int MSG_REST_TAG = 14;
const int MSG_STRENGTH_UP30_TAG = 15;
const int MSG_STRENGTH_UP50_TAG = 16;
const int MSG_STRENGTH_UP80_TAG = 17;
const int MSG_LOTTERY_TAG = 18;
const int MSG_MOVE_ONE_STEP_TAG = 19;
const int MSG_DIMISS_DIALOG_PUBLISH_LOTTERY_TAG = 20;
const int MSG_STOCK_TAG = 21;
const int MSG_STOCK_LAYER_DISMISS_TAG = 22;
const int MSG_USE_SKILL_TAG = 23;
const int MSG_GAME_OVER_TAG = 24;
const int MSG_LOAD_GAME_TAG = 25;

const int LAND_BLANK_MONEY = 1000;
const int LAND_LEVEL_1_MONEY = 2000;
const int LAND_LEVEL_2_MONEY = 3000;

#define DIGITAL_0 "digital_0.png"
#define DIGITAL_1 "digital_1.png"
#define DIGITAL_2 "digital_2.png"
#define DIGITAL_3 "digital_3.png"
#define DIGITAL_4 "digital_4.png"
#define DIGITAL_5 "digital_5.png"
#define DIGITAL_6 "digital_6.png"
#define DIGITAL_7 "digital_7.png"
#define DIGITAL_8 "digital_8.png"
#define DIGITAL_9 "digital_9.png"

#define PATH_MARK_1 "images/mark1.png"
#define PATH_MARK_2 "images/mark2.png"
#define PATH_MARK_3 "images/mark3.png"
#define PATH_MARK_4 "images/mark4.png"
#define PATH_MARK_5 "images/mark5.png"
#define PATH_MARK_6 "images/mark6.png"

#define PLAYER1_1_PARTICLE_PNG "images/foot1.png"
#define PLAYER2_1_PARTICLE_PNG "images/foot2.png"

#define PLAYER1_2_PARTICLE_PNG "images/starfish1.png"
#define PLAYER2_2_PARTICLE_PNG "images/starfish2.png"

#define PLAYER1_3_PARTICLE_PNG "images/heart1.png"
#define PLAYER2_3_PARTICLE_PNG "images/heart2.png"

#define PLAYER1_1_PARTICLE_PLIST "images/showClick.plist"
#define PLAYER2_1_PARTICLE_PLIST "images/fire.plist"

const float TOAST_SHOW_TIME = 2.0f;

const int TAX_REBATES_KEY = 1;			//政府鼓励投资，返还税金10000
const int PAY_TAXES_KEY = 2;			//政府严查账务，补交税金20000
const int LOSS_STRENGTH_KEY = 3;		//喝到假酒，上吐下泻，体力耗光
const int PHYSICAL_RECOVERY_KEY = 4;	//吃了大补丸，体力恢复
const int INVESTMENT_DIVIDENDS_KEY = 5;	//投资获利，分红20000
const int INVESTMENT_LOSS_KEY = 6;		//投资失败，亏损30000
const int STORM_UP_KEY = 7;				//暴风骤雨技能升级
const int STEP_UP_KEY = 8;				 //随心步技能升级
const int TRANSFER_UP_KEY = 9;			 //巧取豪夺技能升级

#define  TAX_REBATES  "tax_rebates"						//政府鼓励投资，返还税金10000
#define  PAY_TAXES "pay_taxes"							//政府严查账务，补交税金20000
#define  LOSS_STRENGTH "loss_strength"					//喝到假酒，上吐下泻，体力耗光
#define  PHYSICAL_RECOVERY "physical_recovery"			//吃了大补丸，体力恢复
#define  INVESTMENT_DIVIDENDS "investment_dividends"	//投资获利，分红20000
#define  INVESTMENT_LOSS "investment_loss"				//投资失败，亏损30000
#define STORM_SKILL_UP "storm_skill_up"
#define STEP_SKILL_UP "step_skill_up"
#define TRANSFER_SKILL_UP "transfer_skill_up"

#define STRENGTH_UP "strength_up"
#define PLAYER_HURT "player_hurt"
#define RICH_DAY "rich_day"
#define IN_HOSPITAL_REMAIN "in_hospital_remain"
#define IN_HOSPITAL "in_hospital"
#define PICK_BALL "pick_ball"
const int GOEND = 1;
const int MOVEPASS = 0;
#define BUY_OK "buy_ok"
#define SELECT_LOTTERY_TITLE "select_lottery_title"
const int BUY_LOTTERY_MONEY = 1000;
#define BUY_LOTTERY "buy_lottery"
const int LOTTERY_BALL_COUNT = 18;
const int PUBLISH_LOTTERY_FREQUENTLY =10;
#define PUBLISH_LOTTERY "publish_lottery"
const int LOTTERY_WIN_MONEY = 50000;

#define POOL_FUNDS "pool_funds"

#define STOCK_CODE "stock_code"
#define STOCK_NAME "stock_name"
#define STOCK_NOWPRICE "stock_nowprice"
#define STOCK_DEALPRICE "stock_dealprice"
#define STOCK_PERCENT "stock_percent"
#define STOCK_STORE "stock_store"
#define PLAYER_MONEY "player_money"
#define NO_MONEY_BUY_STOCK "no_money_buy_stock"

#define BUY "buy"
#define SELL "sell"
#define SHARES "shares"
#define RICH_TECHNOLOGY "rich_technology"
#define RICH_OIL "rich_oil"
#define ICBC "icbc"
#define HUATUO_MEDICINE "huatuo_medicine"
#define DEMOLITION_CONSTRUCTION "demolition_construction"
#define GRADE "grade"
#define LOST_STRENGTH "lost_strength"

#define RAIN "rain"
#define YOURS_IS_MINE  "yours_is_mine"
#define GOBY_HEART "goby_heart"
#define GRADE "grade"
#define LOST_STRENGTH "lost_strength"
#define DOWN_GRADE "down_grade"
#define GOBY_HEART_INFO "goby_heart_info"
#define YOURS_IS_MINE_INFO "yours_is_mine_info"
#define YOUR_STRENGTH_IS_LOW "your_strength_is_low"

#define SAVE_SUCESS "save_sucess"
#define SAVE_FAIL "save_fail"

#define SAVE_MAP1_JSON  "map1_save.json"
#define SAVE_MAP2_JSON  "map2_save.json"
#define SAVE_MAP3_JSON  "map3_save.json"

#define MSG_LOAD_GAME "msg_load_game"

#define BG01_MP3 "sound/bg01.mp3" 
#define BG02_MP3 "sound/bg02.mp3" 
#define BG03_MP3 "sound/bg03.mp3" 

//交过路费声音
#define p1_fangpi  			"sound/p1_fangpi.wav"			//倒霉时放屁都砸脚跟
#define p1_goushiyun  		"sound/p1_goushiyun.wav"		//狗屎运而已
#define p1_lehun  			"sound/p1_lehun.wav"			//别乐昏了
#define p1_nothing  		"sound/p1_nothing.wav"			//哼，没什么了不起
#define p1_shebude  		"sound/p1_shebude.wav"			//真舍不得
#define p1_smiletolast  	"sound/p1_smiletolast.wav"		//有本事笑到最后啊
#define p1_jianfei  		"sound/p1_jianfei.wav"			//比减肥更让我痛苦
#define p1_xiaodaxiaonao  	"sound/p1_xiaodaxiaonao.wav"	//小打小闹


//抢夺别人地块	
#define p1_huanyibao  		"sound/p1_huanyibao.wav"		//一报还一报

//房屋被抢夺
#define p1_buruyi89  		"sound/p1_buruyi89.wav"			//人生不如意
#define p1_pei  			"sound/p1_pei.wav"				//做生意哪有不赔的
#define p1_zhenbuganxin  	"sound/p1_zhenbuganxin.wav"		//真不甘心

//房屋被摧毁
#define p1_doufu  			"sound/p1_doufu.wav"			//买块豆腐撞死吧
#define p1_xinzangbing  	"sound/p1_xinzangbing.wav"		//我的心脏病要发作了
//摧毁别人房屋
#define p1_chaidiao  		"sound/p1_chaidiao.wav"			//给我拆掉它

//蜜蜂伤人
#define p1_aiyouwai  		"sound/p1_aiyouwai.wav"			//哎呦歪啊
//看到别人住院
#define p1_daomeishiba  	"sound/p1_daomeishiba.wav"		//倒霉是吧
#define p1_jintian  		"sound/p1_jintian.wav"			//你也有今天那
#define p1_kaixin  			"sound/p1_kaixin.wav"			//看到别人倒霉就是开心
#define p1_gouyancanchuan  	"sound/p1_gouyancanchuan.wav"	//苟延残喘
//收取过路费
#define p1_zhushang  		"sound/p1_zhushang.wav"			//又有人装猪上了
#define p1_goddesign  		"sound/p1_goddesign.wav"		//这是真主的决定
#define p1_pigtree  		"sound/p1_pigtree.wav"			//猪撞上树了
//升级房子
#define p1_buyaoxianmuwo  	"sound/p1_buyaoxianmuwo.wav"	//不要羡慕我
#define p1_zoushenmeyun  	"sound/p1_zoushenmeyun.wav"		//什么人走什么运
#define p1_quickup  		"sound/p1_quickup.wav"			//加快建设
//不交过路费
#define p1_bugeini  		"p1_bugeini.wav"				//就是不给你
#define	p1_sheng     		"p1_sheng.wav"		    		//能省则省
//买地
#define p1_likebuy  		"sound/p1_likebuy.wav"			//喜欢就买
#define p1_zanmeigod  		"sound/p1_zanmeigod.wav"		//真主我赞美你
//捡到珍珠
#define p1_huanjue  		"sound/p1_huanjue.wav"			//这都是幻觉
#define p1_thanksgod  		"sound/p1_thanksgod.wav"		//感谢真主 
//对方被罚收税
#define p1_closedoor  		"sound/p1_closedoor.wav"		//趁早关门吧
#define p1_baoying  		"sound/p1_baoying.wav"			//哈哈哈，报应
#define p1_dakuairenxin  	"sound/p1_dakuairenxin.wav"		//真是大快人心啊


//交过路费声音
#define p2_buyongzhaole    "sound/p2_buyongzhaole.wav"  //不用找了
#define p2_dazhema   		"sound/p2_dazhema.wav"         //不能打折吗
#define p2_kanbushang    	"sound/p2_kanbushang.wav"         //这点小利 我都看不上
#define p2_qionggui    	"sound/p2_qionggui.wav"         //穷鬼终于有些小钱了吗
#define p2_xiangnaier    	"sound/p2_xiangnaier.wav"         //我的香奈儿
#define p2_tianna   	 	"sound/p2_tianna.wav"         //天哪
//抢夺别人地块	
#define p2_bingmao    		"sound/p2_bingmao.wav"         //老虎不发威当病猫
#define p2_bufangguo    	"sound/p2_bufangguo.wav"      //好东西不能放过
#define p2_huanfang    	"sound/p2_huanfang.wav"         //交换房屋
#define p2_landisgood    	"sound/p2_landisgood.wav"         //这块地段不错嘛
#define p2_shouduan    	"sound/p2_shouduan.wav"         //看老娘的手段
//房屋被抢夺
#define p2_lihai    		"sound/p2_lihai.wav"         //哎呦 好像挺厉害的嘛
#define p2_pricelow    	"sound/p2_pricelow.wav"         //价格太低了吧
#define p2_smiletolast   	 "sound/p2_smiletolast.wav"         //看谁笑到最后
//房屋被摧毁
#define p2_rangnideyi    	"sound/p2_rangnideyi.wav"         //先让你得意几天
#define p2_zheyoushenme    "sound/p2_zheyoushenme.wav"         //这有什么
#define p2_yingwo    		"sound/p2_yingwo.wav"         //别以为这样就能赢我
//摧毁别人房屋
#define p2_bieguaiwo   	 "sound/p2_bieguaiwo.wav"         //别怪我
#define p2_buhaore    		"sound/p2_buhaore.wav"       //老娘可不是好惹的
#define p2_chaichu    		"sound/p2_chaichu.wav"        //拆除违章建筑
#define p2_kanwode    		"sound/p2_kanwode.wav"         //看我的
#define p2_youiquaile   	 "sound/p2_youiquaile.wav"         //你的痛苦就是我的快乐
//蜜蜂伤人
#define p2_daomei    		"sound/p2_daomei.wav"         //真倒霉
#define p2_hongyan    		"sound/p2_hongyan.wav"         //天妒红颜
#define p2_mamaya    		"sound/p2_mamaya.wav"         //我的妈妈呀
#define p2_minga    		"sound/p2_minga.wav"         //一切都是命啊
//看到别人住院
#define p2_jintian    		"sound/p2_jintian.wav"         //你也有今天那
//收取过路费
#define p2_chabuduo   		 "sound/p2_chabuduo.wav"     //这还差不多
#define p2_saiyafeng  	 	 "sound/p2_saiyafeng.wav"         //塞牙缝都不够
#define p2_zhuandaole   	 "sound/p2_zhuandaole.wav"         //赚到了
//升级房子
#define p2_gougaoba   	 	"sound/p2_gougaoba.wav"         //够高吧

//不交过路费
#define p2_bugei    		"sound/p2_bugei.wav"         //老娘就是不想给
//买地
#define p2_budongchan    	"sound/p2_budongchan.wav"     //积极投资不动产
#define p2_meili    		"sound/p2_meili.wav"         //难道是我太有魅力了
#define p2_shuaidaile   	 "sound/p2_shuaidaile.wav"         //帅呆了
#define p2_xinqinghao    	"sound/p2_xinqinghao.wav"         //真是让人心情舒畅啊
//捡到珍珠
#define p2_bulaima    		"sound/p2_bulaima.wav"       //不赖嘛
#define p2_zuomeismile    "sound/p2_zuomeismile.wav"         //今夜做梦也会笑
#define p2_xingyungirl   	 "sound/p2_xingyungirl.wav"         //我是幸运女神
//对方被罚收税
#define p2_diuren   	 	"sound/p2_diuren.wav"         //丢人现眼啊
#define p2_jiaoshui    	"sound/p2_jiaoshui.wav"         //不要忘记缴税啊

#define walk_effect "sound/walk.wav" 
#define click_effect "sound/click.wav"
#define block_effect "sound/block.wav"

const int NEXT_EFFECT_DELAY = 2;
#define STORM_EFFECT "sound/storm.wav"
#define PARTICLE_EFFECT "sound/particle.mp3"
#define LOTTERY_EFFECT "sound/lottery.wav"

#define P1_DEYIDEYITIAN  "sound/byelottery.wav"//拜拜 祝您中奖
#define P1_need1000  "sound/need1000.wav"//只要1000元
#define P1_select_lottery  "sound/select_lottery.wav"//请圈选你要购买的彩票
#define P1_meirendejiang "sound/meirendejiang.wav"//sorry 本月份没有人得奖
#define MASHANGKAIJIANG  "sound/mashangkaijiang.wav" //现在马上开出这期的号码
#define M120  "sound/m120.mp3"
#define youismine "sound/youismine.wav"

#define AUDIO_ON "images/audio_on.png"
#define AUDIO_OFF "images/audio_off.png"

const int Quit_OK_TAG = 801;
const int Quit_Cancel_TAG = 802;
const int RAISE_PRICE_INDEX_MONEY = 200000;
const int RAISE_PRICE_INDEX_FREN = 28;
#define PRICE_INDEX "price_index"

const int MAX_NUMBER_STORE_STOCK = 500;
#define max_store_stock "max_store_stock"
#endif
