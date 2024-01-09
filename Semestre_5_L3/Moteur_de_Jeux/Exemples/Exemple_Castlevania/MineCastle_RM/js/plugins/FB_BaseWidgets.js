//========================================================================
//Furry Bear的基础控件
//作者：Furry Bear
//v1.0.0
//========================================================================

//========================================================================
//FB_HPBar 生命条
//可自行指定血条图片和底板，放入system文件夹，创建时指定
//可调整生命百分率(取值0~1)
//可指定长宽
//========================================================================

function FB_hpBar(){
	this.initialize.apply(this,arguments);
}

FB_hpBar.prototype = Object.create(Sprite.prototype);
FB_hpBar.prototype.constructor = FB_hpBar;

FB_hpBar.prototype.initialize = function(tex_bar,tex_barBg,percent,width,height){
	Sprite.prototype.initialize.call(this);
	this._percent = percent||1;
	if(width){
		this._realWidth = width;
	}
	if(height){
		this._realHeight = height;
	}
	//底板
	this.bitmap = ImageManager.loadSystem(tex_barBg);
	//进度条
	this._bar = new Sprite();
	this._bar.bitmap = new Bitmap(0,0);
	this._bar.move(0,0);
	this.addChild(this._bar);
	this.setBar(tex_bar);
}

FB_hpBar.prototype.setBar = function(tex_bar){
	this._bar.bitmap = ImageManager.loadSystem(tex_bar);
	this._bar.bitmap.addLoadListener(function(){
		this._width = this._bar.bitmap.width;
		this._height = this._bar.bitmap.height;
		//缩放
		if(this._realWidth){
			this.scale.x = this._realWidth/this._bar.bitmap.width;
		}
		if(this._realHeight){
			this.scale.y = this._realHeight/this._bar.bitmap.height;
		}
		//this._bar.bitmap.resize(this._width,this._height);
		this.setPercent(this._percent);	
	}.bind(this));
}

FB_hpBar.prototype.setPercent = function(per){
	this._percent = per;
	this._bar.width = this._width*per;
	//window.console.log("%d",this._bar.bitmap.width);
}

FB_hpBar.prototype.getPercent = function(){
	return this._percent;
}

//========================================================================
//FB_Arrow 光标
//一个手型光标，会左右摇摆
//========================================================================

function FB_Arrow(){
	this.initialize.apply(this,arguments);
}

FB_Arrow.prototype = Object.create(Sprite.prototype);
FB_Arrow.prototype.constructor = FB_Arrow;

FB_Arrow._handCursorDisMax = 20;
FB_Arrow.prototype.initialize = function(){
	Sprite.prototype.initialize.call(this);
	this._handBitmap = new Sprite();
	this._handBitmap.bitmap = ImageManager.loadSystem('Arrow');
	this.addChild(this._handBitmap);
	this.width = this._handBitmap.width;
	this.height = this._handBitmap.height;
	this._active = true;
	this._handCursorSpeed = 1.5;
	this._handCursorOffsetX = 0;	
	this._handCursorOriginalX = 0;
	this._handCursorOffsetX = this._handCursorOriginalX;
}

FB_Arrow.prototype.getCenterPoint = function(){
	var x = this.x + this.bitmap.width/2;
	var y = this.y + this.bitmap.height/2;
	return {x,y};
}

FB_Arrow.prototype.setCenterPoint = function(x,y){
	this.x = x-this.bitmap.width/2;
	this.y = x-this.bitmap.height/2;
}

FB_Arrow.prototype.setOffset = function(x,y){
	this._handBitmap.x = x;
	this._handCursorOriginalX = x;
	this._handBitmap.y = y;
}

FB_Arrow.prototype.setActive = function(isActive){
	this._active = isActive;
}

FB_Arrow.prototype.update = function(){
	Sprite.prototype.update.call(this);
	this.updateHandCursor();
}

FB_Arrow.prototype.updateHandCursor = function(){
	if(this._active){
		this._handCursorOffsetX += this._handCursorSpeed;	
		if(Math.abs(this._handCursorOffsetX-this._handCursorOriginalX)>FB_Arrow._handCursorDisMax/2){
			this._handCursorSpeed = -this._handCursorSpeed;		
		}
		this._handBitmap.x = this._handCursorOffsetX;
	}
	else{
		this._handBitmap.x = this._handCursorOriginalX;
	}
}

//========================================================================
//FB_ArrowSystem 光标系统的基础类
//生成一组光标并根据情况调用，可应用于菜单及角色、敌人等对象的选择
//_isAll为是否开启全选状态，通过showAllArrow/showSingleArrow切换。
//_isActive为是否激活状态，只有激活才会显示光标
//_index为当前选择项编号，只有_isAll为false时有效
//========================================================================

function FB_ArrowSystem(){
	this.initialize.apply(this,arguments);
}

FB_ArrowSystem.prototype = Object.create(Sprite.prototype);
FB_ArrowSystem.prototype.constructor = FB_ArrowSystem;

FB_ArrowSystem.prototype.initialize = function(){
	Sprite.prototype.initialize.call(this);
	this._arrow = [];
	this._arrowMax = this.initArrowMax();
	this._handlers = {};
	this._isAll = false;
	this._isActive = true;
	this._index = 0;
	this._isArrowChanged = false;
	this._helpWindow = null;
	this.initArrow();
	this._arrowHeight = this._arrow[0].height||0;
	this._arrowWidth = this._arrow[0].width||0;
}

FB_ArrowSystem.prototype.initArrow = function(){
	for(i=0;i<this._arrowMax;i++){
		this._arrow[i] = new FB_Arrow();
		this.addChild(this._arrow[i]);
		this._arrow[i].visible = false;
	}
}

FB_ArrowSystem.prototype.callHandler = function(symbol) {
    if (this.isHandled(symbol)) {
        this._handlers[symbol]();
    }
}

FB_ArrowSystem.prototype.isHandled = function(symbol) {
    return !!this._handlers[symbol];
}

FB_ArrowSystem.prototype.setHelpWindow = function(helpWindow){
	this._helpWindow = helpWindow;
}

FB_ArrowSystem.prototype.initArrowMax = function(){
	return 1;
}

FB_ArrowSystem.prototype.setArrowMax = function(max){
	this._arrowMax = max;
}

FB_ArrowSystem.prototype.getArrowMax = function(){
	return this._arrowMax;
}

FB_ArrowSystem.prototype.isAll = function(){
	return this._isAll;
}

FB_ArrowSystem.prototype.setAll = function(){
	this._isAll = true;
}

FB_ArrowSystem.prototype.setSingle = function(){
	this._isAll = false;
}

FB_ArrowSystem.prototype.showSingleArrow = function(){
	this.setSingle();
	this.hideAllArrow();
	this._arrow[0].visible = true;
}

FB_ArrowSystem.prototype.showAllArrow = function(){
	this.setAll();
	for(i=0;i<this._arrowMax;i++){
		this._arrow[i].visible = true;		
	}
}

FB_ArrowSystem.prototype.hideAllArrow  = function(){
	for(i=0;i<this._arrowMax;i++){
		this._arrow[i].visible = false;
	}
}

FB_ArrowSystem.prototype.isActive = function(){
	return this._isActive;
}

FB_ArrowSystem.prototype.setActive = function(isActive){
	this._isActive = isActive;
	for(i=0;i<this._arrowMax;i++){
		this._arrow[i].visible = isActive&&(this._isAll||i==0);
	}
	this._isArrowChanged = true;
	//this.updateArrow();
}

FB_ArrowSystem.prototype.deactivate = function(){
	this.setActive(false);
	//this.setIndex(false);
}

FB_ArrowSystem.prototype.getIndex = function(){
	return this._index;
}

FB_ArrowSystem.prototype.setIndex = function(index){
	this._index = index;
}

FB_ArrowSystem.prototype.addIndex = function(value){
	this._isArrowChanged = true;
	this._index += value;
	if(this._index >= this._arrowMax){
		this._index = 0;
	}
	else if(this._index < 0){
		this._index = this._arrowMax - 1;
	}
}
	
FB_ArrowSystem.prototype.cursorDown = function(index){
	this.addIndex(-1);
}
	
FB_ArrowSystem.prototype.cursorUp = function(index){
	this.addIndex(1);
}

FB_ArrowSystem.prototype.getArrow = function(index){
	return this._arrow[index];
}

FB_ArrowSystem.prototype.setHandler = function(symbol, method){
    this._handlers[symbol] = method;
}

FB_ArrowSystem.prototype.setArrowPosition = function(id){

}

FB_ArrowSystem.prototype.isCurrentItemEnabled = function() {
	return true;
}

FB_ArrowSystem.prototype.processCancel = function() {
    SoundManager.playCancel();
    this.updateInputData();
    this.deactivate();
    this.callHandler('cancel');
};

FB_ArrowSystem.prototype.processOk = function() {
    if (this.isCurrentItemEnabled()) {
        //this.playOkSound();
        this.updateInputData();
        //this.deactivate();
        this.callHandler('ok');
    } else {
        this.playBuzzerSound();
    }
};

FB_ArrowSystem.prototype.processHandling = function() {
    if (this.isActive()) {
        if (Input.isTriggered('ok')) {
            this.processOk();
        } else if (Input.isTriggered('cancel')) {
            this.processCancel();
        }
    }
};

FB_ArrowSystem.prototype.playOkSound = function() {
    SoundManager.playOk();
};

FB_ArrowSystem.prototype.playBuzzerSound = function() {
    SoundManager.playBuzzer();
};

FB_ArrowSystem.prototype.update = function(){
	Sprite.prototype.update.call(this);
	this.processHandling();
	this.updateArrow();
}

FB_ArrowSystem.prototype.updateArrow = function(){
	if(!this._isArrowChanged){
		return;
	}
	this._isArrowChanged = false;
	if(this._isAll){
		for(i=0;i<this.getArrowMax();i++){
			this.setArrowPosition(i);			
		}
	}
	else{
		this.setArrowPosition();
	}
}

FB_ArrowSystem.prototype.updateHelpWindow = function(){
	this._helpWindow.clear();
}

FB_ArrowSystem.prototype.updateInputData = function() {
    Input.update();
    TouchInput.update();
};


//========================================================================
//FB_ArrowSystem_QIStatus 快捷背包角色选择的光标系统
//========================================================================

function FB_ArrowSystem_QIStatus(){
	this.initialize.apply(this,arguments);
}

FB_ArrowSystem_QIStatus.prototype = Object.create(FB_ArrowSystem.prototype);
FB_ArrowSystem_QIStatus.prototype.constructor = FB_ArrowSystem_QIStatus;

FB_ArrowSystem_QIStatus.prototype.initialize = function(){
	FB_ArrowSystem.prototype.initialize.call(this);	
	this.setActive(false);
}

FB_ArrowSystem.prototype.initArrowMax = function(){
	return $gameParty.members().length;
}

FB_ArrowSystem_QIStatus.prototype.getArrowPosition = function(id){
	var roleNum = $gameParty.members().length;
	var width_single = 160+10;
	var x = Graphics.boxWidth-width_single*(roleNum-id)-this._arrowWidth/2+5;
	var y = Graphics.boxHeight-this._arrowHeight/2-30-5;
	return {x,y};
}

FB_ArrowSystem_QIStatus.prototype.setArrowPosition = function(id){
	var index = id||0;
	var pos = this.getArrowPosition(this._isAll?index:this.getIndex());
	this._arrow[index].x = pos.x;
	this._arrow[index].y = pos.y;
}

FB_ArrowSystem_QIStatus.prototype.update = function(){
	if(!this.isActive()){
		return;
	}
	FB_ArrowSystem.prototype.update.call(this);
	this.processCursorMove();
	this.updateHelpWindow();
}

FB_ArrowSystem_QIStatus.prototype.updateHelpWindow = function(){
	FB_ArrowSystem.prototype.updateHelpWindow.call(this);
	var actor =  $gameParty.members()[this._index];
	var text_name = actor.name();
	var text_hp = actor.hp+"/"+actor.mhp;
	this._helpWindow.setText(text_name+"  "+text_hp);
}

FB_ArrowSystem_QIStatus.prototype.processCursorMove = function() {
    if (this.isActive()&&(!this._isAll)) {
		var lastIndex = this.getIndex();
		if (Input.isRepeated('right')) {
			this.cursorUp();
		}
		else if (Input.isRepeated('left')) {
			this.cursorDown();
		}
		if (this.getIndex() !== lastIndex) {
            SoundManager.playCursor();
        }
	}
}


