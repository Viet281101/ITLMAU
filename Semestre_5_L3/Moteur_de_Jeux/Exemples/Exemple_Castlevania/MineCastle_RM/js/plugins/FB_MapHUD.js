//========================================================================
//Furry Bear�ĵ�ͼHUD����
//���ߣ�Furry Bear
//v1.0.0
//========================================================================


var MapHUD = MapHUD||{};

//========================================================================
//Window_MapStatus_FB
//����״̬��
//========================================================================
Window_MapStatus_FB = function(){
	this.initialize.apply(this,arguments);
}

Window_MapStatus_FB.prototype = Object.create(Window_Base.prototype);
Window_MapStatus_FB.prototype.constructor = Window_MapStatus_FB;
Window_MapStatus_FB.prototype.initialize = function(x,y,id_inParty){
	var width = 160;
	var height = 60;
	Window_Base.prototype.initialize.call(this,x,y, width, height);
	//��ȡ��ɫ
	this._actor = $gameParty.members()[id_inParty];
	//ͷ��
	this._head = new Sprite();
	this.addChild(this._head);
	//��������
	this._text = new Sprite();
	this._text.bitmap = new Bitmap(width,height);
	this._text.bitmap.fontSize = 16;
	this.addChild(this._text);
	
	this.contents.fontSize = 16;
	this.drawContent();
}

Window_MapStatus_FB.prototype.drawContent = function(){
	this.drawHead();
	this.drawLevel();
	this.drawHP();
	this.drawHPBar();
}

Window_MapStatus_FB.prototype.drawHead = function(){
	var head_x = 10;
	var head_y = this.height-100;
	var faceName = this._actor.faceName();
	var faceIndex = this._actor.faceIndex();
	this._head.bitmap = ImageManager.loadFace(faceName);
	var width = Window_Base._faceWidth;
    var height = Window_Base._faceHeight;
	var x_bm = faceIndex % 4 * width;
	var y_bm = Math.floor(faceIndex / 4) * height;
	this._head.setFrame(x_bm,y_bm,width,height);
	this._head.x = head_x;
	this._head.y = head_y;
	this._head.scale.x = 0.5;
	this._head.scale.y = 0.5;
}

Window_MapStatus_FB.prototype.drawLevel = function(){
	//�������
	var text_lv = 'Lv.';
	var num_lv = this._actor.level;
	var textWidth1 = this.textWidth(text_lv);
	var textWidth2 = this.textWidth(num_lv);
	var textHeight = 16;
	//λ��
	var offsetX = 12;
	var offsetY = 18;
	this._text.bitmap.drawText(text_lv,offsetX,offsetY,textWidth1, textHeight,'left');
	this._text.bitmap.drawText(num_lv,offsetX+textWidth1,offsetY,textWidth2, textHeight,'left');
}

Window_MapStatus_FB.prototype.drawHP = function(){
	//����
	var str_hp = this._actor.hp;
	var str_mhp = this._actor.mhp;
	//�������
	var textWidth1 = this.textWidth(str_hp);
	var textWidth2 = this.textWidth('/');
	var textWidth3 = this.textWidth(str_mhp);
	var textHeight = 16;
	//����λ��
	var x1 = 0;
	var x2 = (textWidth1)+2;
	var x3 = (textWidth1+textWidth2)+2*2;
	var y = 0;
	//����ƫ��	
	var offsetX = this._text.width-(textWidth1+textWidth2+textWidth3+2*2)-10;
	var offsetY = 10;
	//����
    this._text.bitmap.drawText(this._actor.hp, offsetX+x1, offsetY+y, textWidth1, textHeight,'right');
    this._text.bitmap.drawText('/', offsetX+x2, offsetY+y, textWidth2, textHeight,'right');
    this._text.bitmap.drawText(this._actor.mhp, offsetX+x3, offsetY+y, textWidth3, textHeight,'right');
}

Window_MapStatus_FB.prototype.drawHPBar = function(){
	this._hpBar = new FB_hpBar('hpBar','hpBar_bg',1,this.width-20);
	this._hpBar.x = 10;
	this._hpBar.y = this.height-27;
	this.addChild(this._hpBar);
	this.refreshHPBar();
}

Window_MapStatus_FB.prototype.refreshContent = function(){
	this._text.bitmap.clear();
	this.drawLevel();
	this.drawHP();
	this.refreshHPBar();
}

Window_MapStatus_FB.prototype.refreshHPBar = function(){
	var hpPercent = this._actor.hp/this._actor.mhp;
	this._hpBar.setPercent(hpPercent);
}

Window_MapStatus_FB.prototype.update = function(){
	Window_Base.prototype.update.call(this);
}

//========================================================================
//Window_QuickInventory_FB
//��ݱ�������
//������ʾ����ָ�������ʾ����
//========================================================================

Window_QuickInventory_FB = function(){
	this.initialize.apply(this,arguments);	
}

Window_QuickInventory_FB.prototype = Object.create(Window_BattleItem.prototype);
Window_QuickInventory_FB.prototype.constructor = Window_QuickInventory_FB;
Window_QuickInventory_FB.prototype.initialize = function(displayNum,x, y, width, height){
	Window_ItemList.prototype.initialize.call(this, x, y, width, height);
	this._displayNum = displayNum;
	this.refresh();
    this.show();
    this.activate();
}

Window_QuickInventory_FB.prototype.maxCols = function() {
	return 1;
}

//========================================================================
//Window_MapHUD_FB
//��ͼHUD������
//��ͼ��һֱ��ʾ��HUD���棬�����˵��������Ʒͼ��ͽ�ɫѪ����
//========================================================================
Window_MapHUD_FB = function(){
	this.initialize.apply(this,arguments);
}

Window_MapHUD_FB.prototype = Object.create(Window.prototype);
Window_MapHUD_FB.prototype.constructor = Window_MapHUD_FB;
Window_MapHUD_FB.prototype.initialize = function(){
	Window.prototype.initialize.call(this);
	this._mapStatusWindow = [];
	this.createBagIcon();
	this.createMapStatus();	
}

Window_MapHUD_FB.prototype.createBagIcon = function(){	
	//����ͼ��
	this._bagIcon = new Sprite();
	this._bagIcon.bitmap = ImageManager.loadPicture('ui_map/ui_map_bag');
	this._bagIcon.anchor.x = 0.5;
	this._bagIcon.anchor.y = 0.5;
	this._bagIcon.x = this._bagIcon.width/2+10;
	this._bagIcon.y = Graphics.boxHeight-this._bagIcon.height/2-10;
	this.addChild(this._bagIcon);
}

Window_MapHUD_FB.prototype.createMapStatus = function(){
	//��������״̬��
	var roleNum = $gameParty.members().length;
	var width_single = 160+10;
	for(i = 0;i < roleNum;i++){	
		var x = Graphics.boxWidth-width_single*(roleNum-i)+5;
		var y = Graphics.boxHeight-60-5;
		this._mapStatusWindow[i] = new Window_MapStatus_FB(x,y,i);
		this.addChild(this._mapStatusWindow[i]);
	}
}

Window_MapHUD_FB.prototype.setStatusWindowVisible = function(isVisible){
	for(i=0;i<$gameParty.members().length;i++){
		this._mapStatusWindow[i].visible = isVisible;
	}
}

Window_MapHUD_FB.prototype.refreshContent = function(){
	for(i=0;i<this._mapStatusWindow.length;i++){
		this._mapStatusWindow[i].refreshContent();
	}
}


//===============================Scene����====================================
MapHUD.initialize_map = Scene_Map.prototype.initialize;
Scene_Map.prototype.initialize = function(){
	MapHUD.initialize_map.call(this);
}

MapHUD.create_map = Scene_Map.prototype.createAllWindows;
Scene_Map.prototype.createAllWindows = function(){
	MapHUD.create_map.call(this);
	this.createMapHUDWindow();
	//this.createQuickInvWindow();
}

Scene_Map.prototype.createMapHUDWindow = function(){
	this._mapHUDWindow = new Window_MapHUD_FB();
	this.addWindow(this._mapHUDWindow);
}

MapHUD.stop_map = Scene_Map.prototype.stop;
Scene_Map.prototype.stop = function(){
	MapHUD.stop_map.call(this);
	this._mapHUDWindow.visible = false;
}

MapHUD.start_map = Scene_Map.prototype.start;
Scene_Map.prototype.start = function(){
	MapHUD.start_map.call(this);
	this._mapHUDWindow.visible = true;
}

MapHUD.update_map = Scene_Map.prototype.update;
Scene_Map.prototype.update = function(){
	MapHUD.update_map.call(this);
	//����
	if(Input.isTriggered('control')){		
		SoundManager.playOk();
		SceneManager.push(Scene_QuickInventory_FB);
	}
	else if(Input.isTriggered('shift')){
		SoundManager.playOk();
		SceneManager.push(Scene_CVMap);	
	}
}	

//===============================�����Ʒ����Scene====================================
//��ʾHUD�Ϳ������������HUD����Ҫ�ĵط�
Scene_QuickInventory_FB = function(){
	this.initialize.apply(this,arguments);
}

Scene_QuickInventory_FB.prototype = Object.create(Scene_ItemBase.prototype);
Scene_QuickInventory_FB.prototype.initialize = function()
{
	Scene_ItemBase.prototype.initialize.call(this);
}

Scene_QuickInventory_FB.prototype.create = function(){
	Scene_ItemBase.prototype.create.call(this);
	this.createHelpWindow();
	this.createMapHUDWindow();
	this.createArrowSystem();
	this.createCommandWindow();
	this._itemWindow.setHandler('ok',     this.onItemOk.bind(this));
    this._itemWindow.setHandler('cancel', this.onItemCancel.bind(this));
}

Scene_QuickInventory_FB.prototype.createMapHUDWindow = function(){
	this._mapHUDWindow = new Window_MapHUD_FB();
	this.addWindow(this._mapHUDWindow);
}

Scene_QuickInventory_FB.prototype.createArrowSystem = function(){
	this._arrowSystem = new FB_ArrowSystem_QIStatus();
	this.addChild(this._arrowSystem);
	this._arrowSystem.setHandler('ok',     this.onActorOk.bind(this));
    this._arrowSystem.setHandler('cancel', this.onActorCancel.bind(this));
}

Scene_QuickInventory_FB.prototype.createCommandWindow = function(){
	var width = 250;
	var height = 180;
	this._itemWindow = new Window_QuickInventory_FB(4,24,Graphics.boxHeight - height - 170,width,height);
	this.addWindow(this._itemWindow);
	this._itemWindow.setHelpWindow(this._helpWindow);
}

Scene_QuickInventory_FB.prototype.createMapStatus = function(){
	//��������״̬��
	var roleNum = $gameParty.members().length;
	var width_single = 160+10;
	for(i = 0;i < roleNum;i++){	
		var x = Graphics.boxWidth-width_single*(roleNum-i)+5;
		var y = Graphics.boxHeight-60-5;
		this._mapStatusWindow[i] = new Window_MapStatus_FB(x,y,i);
		this.addChild(this._mapStatusWindow[i]);
	}
}

Scene_QuickInventory_FB.prototype.activateItemWindow = function() {
    this._itemWindow.refresh();
    this._itemWindow.activate();
	this._itemWindow.setHelpWindow(this._helpWindow);
};

Scene_QuickInventory_FB.prototype.determineItem = function() {
    var action = new Game_Action(this.user());
    var item = this.item();
    action.setItemObject(item);
    if (action.isForFriend()) {
        this.showArrowSystem(action.isForAll());
    } else {
        this.useItem();
        this.activateItemWindow();
    }
};

Scene_QuickInventory_FB.prototype.showArrowSystem = function(isAll) {
	this._arrowSystem.setActive(true);
	this._arrowSystem.setHelpWindow(this._helpWindow);
	if(isAll){
		this._arrowSystem.showAllArrow();
	}else{
		this._arrowSystem.showSingleArrow();
	}	
}

Scene_QuickInventory_FB.prototype.onItemOk = function() {
    $gameParty.setLastItem(this.item());
    this.determineItem();
};

Scene_QuickInventory_FB.prototype.onItemCancel = function() {
    this._itemWindow.deselect();
	this.returnToMap();
    //this._categoryWindow.activate();
};

Scene_QuickInventory_FB.prototype.onActorCancel = function() {
    this.hideArraySystem();
};

Scene_QuickInventory_FB.prototype.onActorOk = function() {
    if (this.canUse()) {
        this.useItem();
    } else {
        SoundManager.playBuzzer();
    }
};

Scene_QuickInventory_FB.prototype.itemTargetActors = function() {
    var action = new Game_Action(this.user());
    action.setItemObject(this.item());
    if (!action.isForFriend()) {
        return [];
    } else if (action.isForAll()) {
        return $gameParty.members();
    } else {
        return [$gameParty.members()[this._arrowSystem.getIndex()]];
    }
};

Scene_QuickInventory_FB.prototype.useItem = function() {
    this.playSeForItem();
    this.user().useItem(this.item());
    this.applyItem();
    this.checkCommonEvent();
    this.checkGameover();
    this._mapHUDWindow.refreshContent();
	this._itemWindow.refresh();
};

Scene_QuickInventory_FB.prototype.hideArraySystem = function() {
	this._arrowSystem.setActive(false);
	this.activateItemWindow();
}

Scene_QuickInventory_FB.prototype.returnToMap = function() {
	SoundManager.playCancel();
	this._itemWindow.hide();
	SceneManager.pop();
}

Scene_QuickInventory_FB.prototype.update = function(){
	Scene_ItemBase.prototype.update.call(this);
	//��ť����
	if(Input.isTriggered('control')){
		this.returnToMap();
	}
}

Scene_QuickInventory_FB.prototype.user = function() {
    var members = $gameParty.movableMembers();
    var bestActor = members[0];
    var bestPha = 0;
    for (var i = 0; i < members.length; i++) {
        if (members[i].pha > bestPha) {
            bestPha = members[i].pha;
            bestActor = members[i];
        }
    }
    return bestActor;
};

Scene_QuickInventory_FB.prototype.print = function(){
	window.console.log("%d",$gameParty.allItems().length);
	for(i=0;i<$gameParty.allItems().length;i++){
		window.console.log($gameParty.allItems()[i].name);
	}
}

