
var FB_CharacterShadow = FB_CharacterShadow||{};

FB_CharacterShadow.initialize_character = Sprite_Character.prototype.initialize;
Sprite_Character.prototype.initialize = function(character){
	FB_CharacterShadow.initialize_character.call(this,character);
	this._character.z = 1;
	if((character instanceof Game_Player)||(character instanceof Game_Follower)){
		this.createShadow();
		this._showShadow = true;
	}
	//if((character instanceof Game_Player)){
		//window.console.log(this._jumpPeak);
	//}
}

Sprite_Character.prototype.createShadow = function(){
	this._shadow = new Sprite();
	this._shadow.bitmap = ImageManager.loadSystem('Shadow1');
	this._shadow.x = 0;
	this._shadow.y = 8;
	this._shadow.z = 0;
	this._shadow.anchor.x = 0.5;
	this._shadow.anchor.y = 1;
	this.addChild(this._shadow);
}

FB_CharacterShadow.update = Sprite_Character.prototype.update;
Sprite_Character.prototype.update = function(){
	FB_CharacterShadow.update.call(this);
	if(this._showShadow){
		this.update_shadow();
	}
}

Sprite_Character.prototype.update_shadow = function(){
	var scale = 100;
	if(this._character.isJumping()){
		scale = 100-50*this._character.jumpHeight()/this._character.jumpHeightMax();
		this._shadow.y = this._character.jumpHeight()+8;
		window.console.log("%d/%d",scale,this._shadow.y);
		}
	else{
		this._shadow.y = 8;
	}	
	this._shadow.scale.x = ((this.patternWidth()*scale)/48)/90.0;
	this._shadow.scale.y = this._shadow.scale.x;
	this._shadow.opacity = 150;
	this._shadow.update();
}

Game_CharacterBase.prototype.jumpHeightMax = function() {
	return (this._jumpPeak * this._jumpPeak)/2;
	//window.console.log("%d",this._character._jumpPeak);
}