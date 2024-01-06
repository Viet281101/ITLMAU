Window_FBCommand = function(){
	this.initialize.apply(this,arguments);
}

Window_FBCommand.prototype = Object.create(Window_Command.prototype);
Window_FBCommand.prototype.initialize = function(x,y)
{
	Window_Command.prototype.initialize.call(this,x,y);
}

Scene_FBCommand = function(){
	this.initialize.apply(this,arguments);
}

Scene_FBCommand.prototype = Object.create(Scene_MenuBase.prototype);
Scene_FBCommand.prototype.initialize = function()
{
	Scene_MenuBase.prototype.initialize.call(this);
}

Scene_FBCommand.prototype.create = function(){
	Scene_MenuBase.prototype.create.call(this);
	this._commandWindow = new Window_FBCommand(300,200);
	this.addWindow(this._commandWindow);
}

Scene_FBCommand.prototype.update = function(){
	if(Input.isTriggered('escape')||Input.isTriggered('cancel')){
		this._commandWindow.hide();
		SceneManager.goto(Scene_Map);
	}
}