function Window_FB(){
	this.initialize.apply(this,arguments);
}

Window_FB.prototype = Object.create(Window_Selectable.prototype);
Window_FB.prototype.initialize = function(x,y,width,height){
    Window_Selectable.prototype.initialize.call(this,x,y,width,height);
}

function Scene_FB(){
	this.initialize.apply(this,arguments);
}

Scene_FB.prototype = Object.create(Scene_MenuBase.prototype);
Scene_FB.prototype.initialize = function(){
    Scene_MenuBase.prototype.initialize.call(this);
}

Scene_FB.prototype.create = function(){
	Scene_MenuBase.prototype.create.call(this);
	this._commandWindow = new Window_FB(0,0,300,200);
	this.addWindow(this._commandWindow);
}

Scene_FB.prototype.update = function(){
	if(Input.isTriggered('escape')||Input.isTriggered('cancel')){
		this._commandWindow.hide();
		SceneManager.goto(Scene_Map);
	}
}
