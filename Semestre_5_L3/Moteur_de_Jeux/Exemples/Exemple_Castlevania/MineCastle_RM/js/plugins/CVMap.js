//==============================================================
//仿恶魔城地图
//
//==============================================================

var CVMap = CVMap||{};
CVMap.realWidth_perCell = 17;
CVMap.realHeight_perCell = 13;
//====DataManager====

//地图状态数据
DataManager.num_CVMap = 2;
var $CVMapData       	 = null;
var $gameCVMapStatus        = null;
//地图预加载
DataManager._CVMapDataFiles = [
	{name: '$CVMapData',       src: 'CVMapData/CVMapData.json'}
];
	
DataManager.loadCVMapData = function() {
    for (var i = 0; i < this._CVMapDataFiles.length; i++) {
        var name = this._CVMapDataFiles[i].name;
        var src = this._CVMapDataFiles[i].src;
        this.loadDataFile(name, src);
    }
};

DataManager.isCVMapDatabaseLoaded = function() {
    this.checkError();
    for (var i = 0; i < this._CVMapDataFiles.length; i++) {
        if (!window[this._CVMapDataFiles[i].name]) {
            return false;
        }
    }	
	console.log("CVMap init!");
    return true;
};

CVMap.createGameObjects_original = DataManager.createGameObjects;
DataManager.createGameObjects = function() {
	CVMap.createGameObjects_original.call(this);
	$gameCVMapStatus = new Game_CVMapStatus();
};

//====Game_Player====
Game_Player.prototype.getCurrentCVMapPos = function(){
	var x_CVMapCell_temp = Math.floor(this._x/CVMap.realWidth_perCell);
	var y_CVMapCell_temp = Math.floor(this._y/CVMap.realHeight_perCell);
	var x_CVMapCell = x_CVMapCell_temp + $gameMap.posStart_singleMap.x - $CVMapData[$gameMap.id_CVMap].startPos_x;
	var y_CVMapCell = y_CVMapCell_temp + $gameMap.posStart_singleMap.y - $CVMapData[$gameMap.id_CVMap].startPos_y;
	return {x:x_CVMapCell,y:y_CVMapCell};
}

CVMap.update_gamePlayerBase = Game_Player.prototype.update;
Game_Player.prototype.update = function(sceneActive){
	CVMap.update_gamePlayerBase.call(this,sceneActive);
	this.updateCVMapStatus();
}

Game_Player.prototype.updateCVMapStatus = function(){
	/*var x_CVMapCell_temp = Math.floor(this._x/CVMap.realWidth_perCell);
	var y_CVMapCell_temp = Math.floor(this._y/CVMap.realHeight_perCell);
	var x_CVMapCell = x_CVMapCell_temp + $gameMap.posStart_singleMap.x - $CVMapData[$gameMap.id_CVMap].startPos_x;
	var y_CVMapCell = y_CVMapCell_temp + $gameMap.posStart_singleMap.y - $CVMapData[$gameMap.id_CVMap].startPos_y;
	*/
	var pos_CVMapCell = this.getCurrentCVMapPos();
	if($gameCVMapStatus.getCellStatus($gameMap.id_CVMap,pos_CVMapCell.x,pos_CVMapCell.y) != Game_CVMapStatus.EXPLORED){
		$gameCVMapStatus.setExplored($gameMap.id_CVMap,pos_CVMapCell.x,pos_CVMapCell.y);		
	}
}
		
//====Game_Map====
CVMap.initialize_gameMap = Game_Map.prototype.initialize;
Game_Map.prototype.initialize = function() {
	CVMap.initialize_gameMap.call(this);
	this.id_CVMap = 0;
	this.posStart_singleMap = {x:0,y:0};
	this.posEnd_singleMap = {x:0,y:0};
	this.size_CVMap = {width:0,height:0};
	this.customAttr = null;
};

CVMap.setupGameMap = Game_Map.prototype.setup;
Game_Map.prototype.setup = function(mapId){
	CVMap.setupGameMap.call(this,mapId);
	var str_note = $dataMap.note;
	var customAttr = JSON.parse(str_note);
	this.setupCustomAttr(customAttr);
};

Game_Map.prototype.setupCustomAttr = function(customAttr){
	if(customAttr == null){
		console.log("Warning:customAttr string is empty!");
		return;
	}
	this.id_CVMap = customAttr.id_CVMap;
	if($gameCVMapStatus.getGlobalMapStatus(this.id_CVMap) == Game_CVMapStatus.UNEXPLORED){
		$gameCVMapStatus.setGlobalMapExplored(this.id_CVMap);
	}
	this.parseRange(customAttr.range);
};

//解析AA00:BB11格式的区域信息
Game_Map.prototype.parseRange = function(str_range){
	var range = str_range.split(':');
	if(range.length <2){
		console.log("Warning:string of range error!");
		return;
	}
	this.posStart_singleMap = this.parsePosition(range[0]);
	this.posEnd_singleMap = this.parsePosition(range[1]);
	this.size_CVMap.width = this.posEnd_singleMap.x - this.posStart_singleMap.x + 1;
	this.size_CVMap.height = this.posEnd_singleMap.y - this.posStart_singleMap.y + 1;
};

//解析AA00格式的坐标信息
Game_Map.prototype.parsePosition = function(str_pos){
	var id_slice = 0;
	for(var i=0;i<str_pos.length;i++){
		var asciiCode = str_pos.charCodeAt(i);
		if(asciiCode>=48&&asciiCode<=57){
			id_slice = i;
			break;
		}
	}
	var tempStrX = str_pos.slice(0,i);
	var str_x = this.parseSymbolToNum(tempStrX) - 1;
	var str_y = str_pos.slice(i) - 1;
	return {x:str_x,y:str_y};
};

//将坐标信息中的字母转化为数字
Game_Map.prototype.parseSymbolToNum = function(str_symbol){
	var result = 0;
	for(var i = 0;i<str_symbol.length;i++){
		result += (str_symbol.charCodeAt(i) - 64)*Math.pow(26,str_symbol.length-i-1);
	}
	return result;
};

//====Scene_Boot====
CVMap.createSceneBoot = Scene_Boot.prototype.create;
Scene_Boot.prototype.create = function(){
	CVMap.createSceneBoot.call(this);
	DataManager.loadCVMapData();
};

//图形预加载
CVMap.loadSystemImages_sceneBoot = Scene_Boot.prototype.loadSystemImages;
Scene_Boot.prototype.loadSystemImages = function(){
	CVMap.loadSystemImages_sceneBoot.call(this);	
    ImageManager.loadSystem('Window_blank');	
    ImageManager.loadSystem('Arrow_CVMap');		
    ImageManager.loadSystem('CVMapName_bg');	
    ImageManager.loadSystem('map_cell_0');
    ImageManager.loadSystem('map_cell_1');
    ImageManager.loadSystem('map_cell_2');
    ImageManager.loadSystem('map_cell_3');
    ImageManager.loadSystem('map_cell_4');
    ImageManager.loadSystem('map_borderH_0');
    ImageManager.loadSystem('map_borderH_1');
    ImageManager.loadSystem('map_borderH_2');
    ImageManager.loadSystem('map_borderH_3');
    ImageManager.loadSystem('map_borderV_0');
    ImageManager.loadSystem('map_borderV_1');
    ImageManager.loadSystem('map_borderV_2');
    ImageManager.loadSystem('map_borderV_3');
}

Scene_Boot.prototype.isReady = function() {
    if (Scene_Base.prototype.isReady.call(this)) {
        return DataManager.isDatabaseLoaded() /*&& DataManager.isCVMapDatabaseLoaded()*/ && this.isGameFontLoaded();
    } else {
        return false;
    }
};
//==============================================================
//Game_CVMapStatus 地图状态数据类
//0：未探索 1：已获知 2：已探索
//==============================================================

function Game_CVMapStatus(){
	this.initialize.apply(this, arguments);
}

Game_CVMapStatus.NULL = 0;
Game_CVMapStatus.UNEXPLORED = 1;
Game_CVMapStatus.KNOWN = 2;
Game_CVMapStatus.EXPLORED = 3;
Game_CVMapStatus.prototype.initialize = function() {
	this._CVMapStatusData = new Array();
	this._CVMapStatusGlobalData = new Array();
	this.initCVMapData();
	this.initCVMapGlobalData();
}

Game_CVMapStatus.prototype.initCVMapData = function(){
	for(var i=0;i<$CVMapData.length;i++){
		var mapData = $CVMapData[i].room;
		var mapStatusData = new Array();
		for(var y=0;y<mapData.length;y++){
			mapStatusData[y] = new Array();
			for(var x=0;x<mapData[y].length;x++){
				mapStatusData[y][x] = mapData[y][x].type == 0?Game_CVMapStatus.NULL:Game_CVMapStatus.UNEXPLORED;
			}
		}
		this._CVMapStatusData.push(mapStatusData);
	}
}

Game_CVMapStatus.prototype.initCVMapGlobalData = function(){
	for(var i=0;i<$CVMapData.length;i++){
		this._CVMapStatusGlobalData.push(Game_CVMapStatus.UNEXPLORED);
	}
}

Game_CVMapStatus.prototype.getGlobalMapStatus = function(id_map){
	return this._CVMapStatusGlobalData[id_map];
}

Game_CVMapStatus.prototype.setGlobalMapExplored = function(id_map){
	this._CVMapStatusGlobalData[id_map] = Game_CVMapStatus.EXPLORED;
}

Game_CVMapStatus.prototype.getCellStatus = function(id_map,x,y){
	return this._CVMapStatusData[id_map][y][x];
}

Game_CVMapStatus.prototype.getAllCellNum = function(id_map){	
	var num_room = 0;
	for(var y = 0;y<this._CVMapStatusData[id_map].length;y++){
		for(var x = 0;x<this._CVMapStatusData[id_map][y].length;x++){
			if(this._CVMapStatusData[id_map][y][x] != Game_CVMapStatus.NULL){
				num_room++;
			}
		}
	}
	return num_room;
}

Game_CVMapStatus.prototype.getExploredCellNum = function(id_map){	
	var num_exploredRoom = 0;
	for(var y = 0;y<this._CVMapStatusData[id_map].length;y++){
		for(var x = 0;x<this._CVMapStatusData[id_map][y].length;x++){
			if(this._CVMapStatusData[id_map][y][x] == Game_CVMapStatus.EXPLORED){
				num_exploredRoom++;
			}
		}
	}
	return num_exploredRoom;
}

Game_CVMapStatus.prototype.setKnown = function(id_map,x,y){
	this._CVMapStatusData[id_map][y][x] = Game_CVMapStatus.KNOWN;
}

Game_CVMapStatus.prototype.setExplored = function(id_map,x,y){
	this._CVMapStatusData[id_map][y][x] = Game_CVMapStatus.EXPLORED;
}
//==============================================================
//Arrow_CVMap 地图光标类
//==============================================================
function Arrow_CVMap(){
	this.initialize.apply(this,arguments);
}

Arrow_CVMap.prototype = Object.create(Sprite.prototype);
Arrow_CVMap.prototype.constructor = Arrow_CVMap;

Arrow_CVMap.scaleBegin = 1;
Arrow_CVMap.scaleEnd = 0.05;
Arrow_CVMap.scaleSpeed = -0.02;
Arrow_CVMap.prototype.initialize = function(bitmap){
	Sprite.prototype.initialize.call(this,bitmap);
	this._Arrow = new Sprite();
	this._Arrow.bitmap = ImageManager.loadSystem('Arrow_CVMap');
	this._Arrow.opacity = 200;
	this._Arrow.anchor.x = 0.5;
	this._Arrow.anchor.y= 0.5;
	this.addChild(this._Arrow);
	this._arrowScale = Arrow_CVMap.scaleBegin;
}

Arrow_CVMap.prototype.update = function(){
	Sprite.prototype.update.call(this);
	this.updateArrowScale();
}

Arrow_CVMap.prototype.updateArrowScale = function(){
	this._arrowScale += Arrow_CVMap.scaleSpeed;
	if(this._arrowScale < Arrow_CVMap.scaleEnd){
		this._arrowScale = Arrow_CVMap.scaleBegin;
	}
	this._Arrow.scale.x = this._arrowScale;
	this._Arrow.scale.y = this._arrowScale;
}
//==============================================================
//CVMap 地图类
//==============================================================
function CVMap(){
	this.initialize.apply(this,arguments);
}

CVMap.prototype = Object.create(Sprite.prototype);
CVMap.prototype.constructor = CVMap;

CVMap.cellWidth = 16;
CVMap.cellHeight = 16;
CVMap.borderHWidth = 16+2;
CVMap.borderHHeight = 2;
CVMap.borderVWidth = 2;
CVMap.borderVHeight = 16+2;
CVMap.coordinateX = Graphics.width/CVMap.cellWidth-1;
CVMap.coordinateY = Graphics.height/CVMap.cellHeight-1;

CVMap.prototype.initialize = function(id_map){
	Sprite.prototype.initialize.call(this);
	this.bitmap = new Bitmap();
	this.id_map = 0;
	this.posStart_x = 0;
	this.posStart_y = 0;
	this.initResource();
	this.addMapNameBG();
	this.resetMap(id_map);
}

CVMap.prototype.initResource = function(){
	this.cell = new Array();
	this.cell[0] = ImageManager.loadSystem('map_cell_0');
	this.cell[1] = ImageManager.loadSystem('map_cell_1');
	this.cell[2] = ImageManager.loadSystem('map_cell_2');
	this.cell[3] = ImageManager.loadSystem('map_cell_3');
	this.cell[4] = ImageManager.loadSystem('map_cell_4');
	
	this.borderH = new Array();
	this.borderH[0] = ImageManager.loadSystem('map_borderH_0');
	this.borderH[1] = ImageManager.loadSystem('map_borderH_1');
	this.borderH[2] = ImageManager.loadSystem('map_borderH_2');
	this.borderH[3] = ImageManager.loadSystem('map_borderH_3');
	
	this.borderV = new Array();
	this.borderV[0] = ImageManager.loadSystem('map_borderV_0');
	this.borderV[1] = ImageManager.loadSystem('map_borderV_1');
	this.borderV[2] = ImageManager.loadSystem('map_borderV_2');
	this.borderV[3] = ImageManager.loadSystem('map_borderV_3');
}

CVMap.prototype.setBackground = function(){
	this.bitmap = ImageManager.loadSystem('Window_blank');
	this.bitmap.fillAll('black');
	//this.bitmap = new Bitmap(0,0,Graphics.boxWidth,Graphics.boxHeight);
	//this.bitmap.fillRect(0,0,Graphics.boxWidth,Graphics.boxHeight,'black');
}

CVMap.prototype.getCellStatus = function(id_map,x,y){
	return $gameCVMapStatus.getCellStatus(id_map,x,y);
}

CVMap.prototype.addMapNameBG= function(){
	this.mapNameBG = new Sprite();
	this.mapNameBG.x = 10;
	this.mapNameBG.y = 10;
	this.mapNameBG.bitmap = ImageManager.loadSystem('CVMapName_bg');
	this.addChild(this.mapNameBG);
}

CVMap.prototype.resetMap = function(id_map){
	this.id_map = id_map;
	this.bitmap.clear();
	this.setBackground();
	this.drawMap();
	this.drawRate();
	this.drawMapName();
	this.resetArrow();
}

CVMap.prototype.drawMap = function(){
	this.posStart_x = $CVMapData[this.id_map].startPos_x;
	this.posStart_y = $CVMapData[this.id_map].startPos_y;
	for(y=0;y<$CVMapData[this.id_map].room.length;y++){
		for(x=0;x<$CVMapData[this.id_map].room[y].length;x++){
			if(this.getCellStatus(this.id_map,x,y) == Game_CVMapStatus.NULL
			||this.getCellStatus(this.id_map,x,y) == Game_CVMapStatus.UNEXPLORED){
				continue;
			}
			var pos_x = x+this.posStart_x;
			var pos_y = y+this.posStart_y;
			//画房间
			this.drawCell(pos_x,pos_y,$CVMapData[this.id_map].room[y][x].type);
			
			//画边界
			this.drawBorderH(pos_x,pos_y,$CVMapData[this.id_map].border_h[y][x].type);
			this.drawBorderH(pos_x,pos_y+1,$CVMapData[this.id_map].border_h[y+1][x].type);	
			this.drawBorderV(pos_x,pos_y,$CVMapData[this.id_map].border_v[y][x].type);
			this.drawBorderV(pos_x+1,pos_y,$CVMapData[this.id_map].border_v[y][x+1].type);
		}
	}
}

CVMap.prototype.resetArrow = function(){
	if(this._arrow == null){
		this._arrow = new Arrow_CVMap();
		this.addChild(this._arrow);	
	}
	if($gameCVMapStatus.getGlobalMapStatus(this.id_map) == Game_CVMapStatus.EXPLORED){
		this._arrow.visible = true;
		var CVMapPos = $gamePlayer.getCurrentCVMapPos();
		this.setArrowPos(CVMapPos.x,CVMapPos.y);
	}
	else{
		this._arrow.visible = false;
	}
}

CVMap.prototype.drawRate = function(){
	if(this.rateArea == null){
		this.rateArea = new Sprite();
		this.rateArea.x = Graphics.boxWidth - 92;
		this.rateArea.y = 30;
		this.rateArea.bitmap = new Bitmap(160,60);
		this.rateArea.bitmap.fontSize = 24;
		this.addChild(this.rateArea);
	}
	this.rateArea.bitmap.clear();
	var num_allRoom = $gameCVMapStatus.getAllCellNum(this.id_map);
	var num_exploredRoom = $gameCVMapStatus.getExploredCellNum(this.id_map);
	var rate = num_exploredRoom*100/num_allRoom;
	rate = rate.toFixed(1);
	var text_rate = rate+"%";
	var textWidth = this.rateArea.bitmap.measureTextWidth(text_rate);
	this.rateArea.bitmap.drawText(text_rate, 0, 0, textWidth, 24,'right');
}

CVMap.prototype.drawMapName = function(){
	if(this.mapName == null){
		this.mapName = new Sprite();
		this.mapName.bitmap = new Bitmap(200,60);
		this.mapName.bitmap.fontSize = 20;
		this.mapNameBG.addChild(this.mapName);
	}
	this.mapName.bitmap.clear();
	var name = $CVMapData[this.id_map].name;
	var textWidth = this.mapName.bitmap.measureTextWidth(name);
	this.mapName.bitmap.drawText(name,64,30,textWidth,20,'center');
}

CVMap.prototype.changeToLastMap = function(){
	var newID = this.id_map-1;
	if(newID<0){
		newID = $CVMapData.length-1;
	}
	this.resetMap(newID);
}

CVMap.prototype.changeToNextMap = function(){
	var newID = this.id_map+1;
	if(newID>=$CVMapData.length){
		newID = 0;
	}
	this.resetMap(newID);
}

CVMap.prototype.setArrowPos = function(CVMap_x,CVMap_y){
	if(this._arrow == null){
		return;
	}
	this._arrow.x = (CVMap_x+this.posStart_x+0.5)*CVMap.cellWidth;
	this._arrow.y = (CVMap_y+this.posStart_y+0.5)*CVMap.cellHeight;
}

CVMap.prototype.drawCell = function(x,y,type){
	if(type<=0){
		return;
	}
	if(!this.cell[type]){
		return;
	}
	if(x>CVMap.coordinateX||y>CVMap.coordinateY){
		return;
	}
	this.bitmap.blt(this.cell[type],0,0,CVMap.cellWidth,CVMap.cellHeight,CVMap.cellWidth*x,CVMap.cellHeight*y,CVMap.cellWidth,CVMap.cellHeight);
}

CVMap.prototype.drawBorderH = function(x,y,type){
	if(type<=0){
		return;
	}
	if(!this.borderH[type]){
		return;
	}
	if(x>CVMap.coordinateX||y>CVMap.coordinateY+1){
		return;
	}
	this.bitmap.blt(this.borderH[type],0,0,CVMap.borderHWidth,CVMap.borderHHeight,
	CVMap.cellWidth*x-1,CVMap.cellHeight*y-1,CVMap.borderHWidth,CVMap.borderHHeight);
}

CVMap.prototype.drawBorderV = function(x,y,type){
	if(type<=0){
		return;
	}
	if(!this.borderV[type]){
		return;
	}
	if(x>CVMap.coordinateX+1||y>CVMap.coordinateY){
		return;
	}
	this.bitmap.blt(this.borderV[type],0,0,CVMap.borderVWidth,CVMap.borderVHeight,
	CVMap.cellWidth*x-1,CVMap.cellHeight*y-1,CVMap.borderVWidth,CVMap.borderVHeight);
}

//Map的Scene
function Scene_CVMap(){
	this.initialize.apply(this,arguments);
}

Scene_CVMap.prototype = Object.create(Scene_MenuBase.prototype);
Scene_CVMap.prototype.constructor = Scene_CVMap;

Scene_CVMap.prototype.initialize = function(){
	Scene_MenuBase.prototype.initialize.call(this);
	
}

Scene_CVMap.prototype.create = function(){
	Scene_MenuBase.prototype.create.call(this);
	this.addCVMap();
}

Scene_CVMap.prototype.addCVMap = function(){
	this._CVMap = new CVMap($gameMap.id_CVMap);
	this.addChild(this._CVMap);
}

Scene_CVMap.prototype.returnToMap = function(){
	SoundManager.playCancel();
	SceneManager.pop();	
}

Scene_CVMap.prototype.update = function(){
	Scene_MenuBase.prototype.update.call(this);
	//输入
	if(Input.isTriggered('shift')||Input.isTriggered('escape')){		
		this.returnToMap();
	}
	else if(Input.isTriggered('left')){
		SoundManager.playCursor();
		this._CVMap.changeToLastMap();
	}
	else if(Input.isTriggered('right')){
		SoundManager.playCursor();
		this._CVMap.changeToNextMap();
	}
}
