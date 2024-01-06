
//========================================================================
//Window_Selectable窗口改造

//1、增加手指光标。窗口激活时将左右匀速位移
//x轴范围：10~40（指尖位置）

//========================================================================


var FB_WindowReform = FB_WindowReform||{};

//图形预加载
FB_WindowReform.loadSystemImages_sceneBoot = Scene_Boot.prototype.loadSystemImages;
Scene_Boot.prototype.loadSystemImages = function(){
	FB_WindowReform.loadSystemImages_sceneBoot.call(this);	
    ImageManager.loadSystem('Arrow');
}

Window_Selectable._num_backupHandCursor = 3;//备用光标数

FB_WindowReform.initialize = Window_Selectable.prototype.initialize;
Window_Selectable.prototype.initialize = function(x, y, width, height){
	FB_WindowReform.initialize.call(this,x, y, width, height);
	this.createHandCursor();
}

Window_Selectable.prototype.createHandCursor = function(){
	this._handCursor = new Array();
	for(i=0;i<Window_Selectable._num_backupHandCursor+1;i++){
		this._handCursor[i] = new FB_Arrow();
		this._handCursor[i].visible = false;
		this._handCursor[i].setOffset(0,(this.itemHeight()-this._handCursor[i].height)/2+this._padding);
		this.addChild(this._handCursor[i]);
	}
	//标准光标矩形
	this._rect = new Bitmap();
}
	
FB_WindowReform.update = Window_Selectable.prototype.update;
Window_Selectable.prototype.update = function(){
	FB_WindowReform.update.call(this);
	this.updateStandardCursorRect();
	this.updateHandCursor();
}

//每帧生成一个标准光标矩形，便于反复利用
Window_Selectable.prototype.updateStandardCursorRect = function(){
	this._rect = this.itemRect(this.index());
}

Window_Selectable.prototype.updateHandCursor = function(){
	if(this.active&&this.visible&&this.isCursorVisible()){
		var count = this._cursorAll?Math.min(this.maxRows(),Window_Selectable._num_backupHandCursor+1):1;
		for(i=0;i<count;i++){
			this._handCursor[i].visible = true;
			this._handCursor[i].x = this._rect.x;
			var d = this.itemHeight() - this._handCursor[i].height;
			this._handCursor[i].y = this._rect.y+ this._rect.height*i;
		}
	}
	else{
		for(i=0;i<Window_Selectable._num_backupHandCursor+1;i++){
			this._handCursor[i].visible = false;
		}
	}
}