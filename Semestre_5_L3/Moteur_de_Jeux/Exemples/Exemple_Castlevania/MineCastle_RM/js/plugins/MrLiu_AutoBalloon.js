//=============================================================================
// MrLiu_AutoBalloon.js
//=============================================================================
 
/*:
 * @plugindesc 在RMMV游戏中地图界面的人物头顶自动显示气球
 * @author MrLiu-过眼云烟
 *
 * @help 事件页的说明下加入“autoballoon_11”，即显示第11行的表情，需将Balloon_1.png
 * 文件放在\img\system目录下，该文件默认大小为96*352，默认每格表情大小为32，每行3格
 * 后续版本将提供修改格式，显示速度等功能，敬请期待，如有问题欢迎给我留言。
 */
//-----------------------------------------------------------------------------
var Imported = Imported || {};
Imported.MrLiu_AutoBalloon = true;
 
var Lmd = Lmd || {};
Lmd.MrLiu_AutoBalloon = Lmd.MrLiu_AutoBalloon || {};
 
 
 
  var parameters = PluginManager.parameters('MrLiu_Shadow');
  var displayAutoBalloon = String(parameters['displayAutoBalloon']);
  var shadowOpacity = Number(parameters['shadowOpacity']);
  displayAutoBalloon = false;
 
Lmd.MrLiu_AutoBalloon.Game_Character_initialize = Game_Character.prototype.initialize;
  Game_Character.prototype.initialize = function() {
    Lmd.MrLiu_AutoBalloon.Game_Character_initialize.call(this);
    this._auto_balloon = 0;
};
 
Game_Character.prototype._auto_balloon = function() {
        return this._auto_balloon;
};
 
 
Lmd.MrLiu_AutoBalloon.Game_Event_refresh = Game_Event.prototype.refresh;
Game_Event.prototype.refresh = function() {
        Lmd.MrLiu_AutoBalloon.Game_Event_refresh.call(this);
        if((this._erased == false)&&(this._trigger == 0)){
        var list = this.list();
        for(var i=0 ;i<list.length;i++){
                if (list[i].code == 108){
                        var num =list[i].parameters[0].match(/autoballoon_(\d+)/g);
                        if (num){
                                var num1 = Number((String(num)).match(/\d+(\.\d+)?/g));
                                this._auto_balloon = num1;
                        }
                }
        }
        }
};
 
Game_Event.prototype.setupPage = function() {
    if (this._pageIndex >= 0) {
                this._auto_balloon = 0;
        this.setupPageSettings();
    } else {
                this._auto_balloon = 0;
        this.clearPageSettings();
    }
    this.refreshBushDepth();
    this.clearStartingFlag();
    this.checkEventTriggerAuto();
};
 
 
 
 
 
 
Lmd.MrLiu_AutoBalloon.Sprite_Character_initialize = Sprite_Character.prototype.initialize;
Sprite_Character.prototype.initialize = function(character) {
    Lmd.MrLiu_AutoBalloon.Sprite_Character_initialize.call(this,character);
        this.createAutoBalloon();
        this._dis_flag = 0;
        this._flag = 0;
        this._bx = 0
        this.character = character;
};
Sprite_Character.prototype.createAutoBalloon = function() {
    this._auto_balloon_sprite = new Sprite();
    this._auto_balloon_sprite.bitmap = ImageManager.loadSystem('Balloon_1');
        this._auto_balloon_sprite.opacity = 0;
        this._auto_balloon_sprite.z = 7;
        this._auto_balloon_sprite.x = this.x;
    this._auto_balloon_sprite.y = this.y-40;//-this.patternHeight();// ;//- this.height*2;
        this._auto_balloon_sprite.anchor.x = 0.5;
    this._auto_balloon_sprite.anchor.y = 1;
        //this.addChild(this._auto_balloon_sprite);
    this.addChild(this._auto_balloon_sprite);
        if (displayAutoBalloon){
                this._p_balloon_sprite = new Sprite();
                this._p_balloon_sprite.bitmap = ImageManager.loadSystem('Balloon_1');
                this._p_balloon_sprite.opacity = 0;
                this._p_balloon_sprite.z = 7;
                this.parent.addChild(this._p_balloon_sprite);//this.addChild(this._p_balloon_sprite);
        }
}        
 
Lmd.MrLiu_AutoBalloon.Sprite_Character_update = Sprite_Character.prototype.update;
Sprite_Character.prototype.update = function() {
        Lmd.MrLiu_AutoBalloon.Sprite_Character_update.call(this);
        if ((this.character._auto_balloon == 0)  || ! (this._balloonDuration == 0 ) || ($gameMap._interpreter.isRunning()) || ($gameSwitches[212] == true)){
      this.clear_auto_balloon();
        }
    else{
      this.update_auto_balloon();
        }
}
 
 
Sprite_Character.prototype.face_to_event = function() {
    var data = new Array();
    var w = 1;
    var h = 1 * 2;
        for (var i=0;i<(h+1);i++)
        {
                for (var j=0;j<(h+1);j++)
                        {
                            data.push([(this.character.x-w)+i,(this.character.y-w)+j]);
                        }
        }
         for(var i =0;i<data.length;i++) {
     if((String(data[i])) == (String([$gamePlayer.x , $gamePlayer.y]))) {
      return true;
     }
    }
        return false;
}
 
 
Sprite_Character.prototype.distance_balloom_opacity = function() {
   this._auto_balloon_sprite.opacity += 70;
    if (displayAutoBalloon){
      this._p_balloon_sprite.opacity += 70;
        }
}
 
 
Sprite_Character.prototype.clear_auto_balloon = function() {
        if (this._auto_balloon_sprite.opacity == 0){
      this._dis_flag = 255;
      return;
        }
    this._auto_balloon_sprite.opacity = this._dis_flag;
    if (displayAutoBalloon){
      this._p_balloon_sprite.opacity = this._dis_flag;
        }
    this._dis_flag -= 35;
}
 
 
 
Sprite_Character.prototype.start_auto_balloon = function() {
    this._flag = 1;
    this._balloon_id = this.character._auto_balloon;
    this._ry = (this.character._auto_balloon - 1) * 32;
}
 
Sprite_Character.prototype.set_rect = function(index) {
    this._auto_balloon_sprite.setFrame(32 * index, this._ry, 32, 32);
    if (displayAutoBalloon){
      this._p_balloon_sprite.setFrame(32 * index, this._ry, 32, 32);
        }
}
 
 
 
Sprite_Character.prototype.update_auto_balloon = function() {
    if ((!this._auto_balloon_sprite) ||  (this._balloon_id != this._character._auto_balloon) || (this._flag == 0)){ 
          this.start_auto_balloon();
    }
        //console.log(this.height);
        //console.log(this.character.y);
        //this._auto_balloon_sprite.y = this.character.y - this.height;
        //console.log(this._auto_balloon_sprite.y);
    if (displayAutoBalloon){
                this._p_balloon_sprite.x = $gamePlayer.x;
        this._p_balloon_sprite.y = $gamePlayer.y;
        }
    if (this.face_to_event()){
      this.distance_balloom_opacity();
        }else{
      this.clear_auto_balloon();
        }
    if (this._flag == 10){
      this._flag = 0; 
          if(this._bx == 2){
                  this._bx = 0;
          }
          else{
                  this._bx++;
          }
        }
    else{
      this._flag++;
        }
        this.set_rect(this._bx);
}
