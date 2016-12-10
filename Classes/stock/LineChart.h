#ifndef __LINECHART__
#define __LINECHART__


#include "cocos2d.h"
#include "VisibleRect.h"
#include "stock/StockCellCard.h"
#include "stock/Stock.h"
#include "ConstUtil.h"
#include "Util.h"
#include "RicherPlayer.h"
#include "extensions/cocos-ext.h"

#include "PopupLayer/CocosToast.h"

using namespace std;

USING_NS_CC;
USING_NS_CC_EXT;



const int stockCellWidth = 100;
const int stockCellHeight = 30;
const int buy_button = 801;
const int sell_button = 802;
const int back_button =803;
const float spaceRatio = 0.08;
const float leftRatioX = 0.1;


class LineChart:public LayerColor ,TableViewDataSource,TableViewDelegate {
    
public:
	LineChart();
	~LineChart();

	RicherPlayer* richerPlayer;
	int selectedTag;
    DrawNode* drawNode ;
    TableView * tv;
	static LineChart* createChart(RicherPlayer* player, vector<int> stock_pointvec1, vector<int> stock_pointvec2, vector<int> stock_pointvec3, vector<int> stock_pointvec4, vector<int> stock_pointvec5);
	void drawCoordinates();
	void drawTrend();
	void drawLine(vector<Point> vec, Color4B lineColor, Color4B dotColor);

	vector<int> stock_pointvec1;
	vector<int> stock_pointvec2;
	vector<int> stock_pointvec3;
	vector<int> stock_pointvec4;
	vector<int> stock_pointvec5;
	Vector<Stock*> stockVector;
	Map<int,Stock*> playerStockMap ;
	void initStockVector(Map<int,Stock*> stockMap);
    CREATE_FUNC(LineChart);
    
	bool initChart(RicherPlayer* player, vector<int> stock_pointvec1, vector<int> stock_pointvec2, vector<int> stock_pointvec3, vector<int> stock_pointvec4, vector<int> stock_pointvec5);
    CC_SYNTHESIZE(int, _hInterval, HInterval);
    CC_SYNTHESIZE(int, _vInterval, VInterval);
	Vector<int>* firstVec;
    double  getMaxValue(std::vector<Point>  vec);   
    std::vector<Point> pointvec;  
	void setData(vector<int> data);
    int spaceValue;    
	int  bottomSpace;
	virtual Size cellSizeForTable(TableView *table);
	virtual TableViewCell* tableCellAtIndex(TableView *table, ssize_t idx);
	virtual ssize_t numberOfCellsInTableView(TableView *table);
	virtual void tableCellTouched(TableView* table, TableViewCell* cell);   
    virtual void scrollViewDidScroll(ScrollView* view){};
    virtual void scrollViewDidZoom(ScrollView* view){};
	Sprite* arrowSprite_left ;
	Sprite* arrowSprite_right ;
	void initMenu();
	CC_SYNTHESIZE(Menu*, _menu, Menu);
	void buttonCallback(CCObject* pSender);
	int moveTag ;
	void sendMSGDealAroundLand();
	void sendMSGMoveOneStep();
	vector<int> getsock_pointVec(int id);
	Label* playerMoneyLabel ;   
};

#endif 
