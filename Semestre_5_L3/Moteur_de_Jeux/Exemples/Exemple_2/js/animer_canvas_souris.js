let cnv = document.getElementById("myCanvas");
let ctx = cnv.getContext("2d");
let ballSize = 30, posX = 0, posY = 0;
function draw() {
    ctx.clearRect(0, 0, cnv.width, cnv.height);
    ctx.beginPath();
    ctx.arc(posX, posY, ballSize, 0, 2*Math.PI);
    ctx.fillStyle = "#0000FF";
    ctx.fill();
    ctx.closePath();
}
function update() {
    draw();
    requestAnimationFrame(update);
}
document.addEventListener("mousemove", mousemove_fun);
function mousemove_fun(e) { posX = e.clientX; posY = e.clientY; }
requestAnimationFrame(update);
