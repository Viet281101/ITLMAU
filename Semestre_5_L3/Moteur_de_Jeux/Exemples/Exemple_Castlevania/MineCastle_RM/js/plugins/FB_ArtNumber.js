//========================================================================
//Furry Bear的美术字
//作者：Furry Bear
//v1.0.0
//数字图片存放在img/art_number文件夹中
//数字图片必须是由[./0123456789]12个字符组成
//========================================================================

(Function(){

function FB_ArtNumber(){
     this.initialize.apply(this,arguments);
}

FB_ArtNumber._elementNum = 12;
FB_ArtNumber._specialElementNum = 2;

FB_ArtNumber.prototype = Object.create(Sprite.prototype);
FB_ArtNumber.prototype.initialize = function(textureName,value){
     Sprite.prototype.initialize.call(this);
     this._textureName = textureName;
     this._value = value;
     //this._texture = ImageManager.loadBitmap('img/art_number/',textureName);
     this.bitmap = ImageManager.loadBitmap('img/art_number/',textureName);
     //this._texture.addLoadListener(this.drawNumber.bind(this));
}

FB_ArtNumber.prototype.drawNumber = function(){
     this._cellWidth = _texture.width/FB_ArtNumber._elementNum;
     this._cellHeight = _texture.height;
     var vNumMenber = new Array();
     var tempNum = this._value;
     var count = 0;
     //从个位到高位
     while(true){
          vNumMenber[count] = tempNum%10;
          tempNum = tempNum/10;
          if(tempNum<10){
               break;
          }
     }
     //分析生成图片长宽
     var width_targetPic = this._cellWidth*vNumMenber.length;
     var height_targetPic = this._cellHeight;
     for(i=0;i<vNumMenber.length;i++){
          var num = vNumMenber[i];
          var numX = width_targetPic-this._cellWidth*i;
          var numY = 0;
          var resX = _cellWidth*(num+FB_ArtNumber._specialElementNum);
          var resY = 0;
          this.bitmap.blt(this._texture,resX,resY,this._cellWidth,this._cellHeight,numX,numY);
     }   
}


})();
