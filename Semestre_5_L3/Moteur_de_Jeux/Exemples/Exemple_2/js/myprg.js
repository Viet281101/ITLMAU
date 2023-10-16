let cnv = document.getElementById('myCanvas');
let ctx = cnv.getContext('2d');

ctx.font = '64pt Calibri';
ctx.fillStyle = 'blue';
ctx.fillText('Hello', cnv.width/2-100, cnv.height/2-100);


ctx.imageSmoothingEnabled= false;
var img = new Image();
img.src = './assets/mario.png';
img.onload = function() {
    ctx.drawImage(img, cnv.width/2-100, cnv.height/2-100, 200, 200);
};

console.log("Damien le nul");

//console.log(a);;
//var a = 1;

