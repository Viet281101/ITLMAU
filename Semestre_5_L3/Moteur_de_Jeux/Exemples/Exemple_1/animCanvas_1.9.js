
let cnv = document.getElementById("myCanvas");
let ctx = cnv.getContext("2d");

class Ball {
    constructor(ballSize = 30, vX = 2.0, hY = 200.0, persistantSize = 10) {
        this.ballSize = ballSize;
        this.vX = vX;
        this.hY = hY;
        this.updateFreq = 10;
        this.color = "#0000FF";
        this.posX = 0;
        this.posY = 400-1.0*Math.abs(this.hY*Math.sin(0.0));
        this.persistantSize = persistantSize;
        this.persistant_circles = [];
        if(this.persistantSize > 0) 
        {
            this.persistant_circles.push([this.posX,this.posY]);
        }
    }

    update_pos(cnv) 
    {
        this.posX += this.vX;
        this.posY = 400-1.0*Math.abs(this.hY*Math.sin(Math.PI*this.posX/100));
        if(this.posX >= cnv.width) {
            this.posX = 0;
            this.posY = 400-1.0*Math.abs(this.hY*Math.sin(Math.PI*this.posX/100));
        }
        if(this.persistantSize > 0) 
        {
            this.persistant_circles.push([this.posX,this.posY]);
            while(this.persistant_circles.length > this.persistantSize) 
            {
                this.persistant_circles.shift();
            }
        }
    }

    draw(ctx) 
    {
        for (let i = 0; i < this.persistant_circles.length; i++) 
        {
            ctx.beginPath();
            ctx.arc(this.persistant_circles[i][0], this.persistant_circles[i][1],
            this.ballSize, 0, 2*Math.PI);
            ctx.stroke();
            ctx.closePath();
        }
        ctx.beginPath();
        ctx.arc(this.posX, this.posY, this.ballSize, 0, 2*Math.PI);
        ctx.fillStyle = this.color;
        ctx.fill();
        ctx.closePath();
    }
}


let ball = new Ball();
let gui = new dat.gui.GUI();
gui.add(ball, 'updateFreq').min(10).max(100).step(1);
let ballFolder = gui.addFolder('Ball');
ballFolder.add(ball, 'ballSize').min(10).max(100).step(1);
ballFolder.add(ball, 'color');
ballFolder.add(ball, 'persistantSize').min(10).max(400).step(10);


function draw() {
    ctx.clearRect(0, 0, cnv.width, cnv.height);
    ball.draw(ctx);

}

let previousTimeStamp = undefined, elapsed = ball.updateFreq+1;

function update(timestamp) {
    if(previousTimeStamp != undefined) {
        elapsed = timestamp-previousTimeStamp;
    }
    if(elapsed > ball.updateFreq) {
        previousTimeStamp = timestamp;
        ball.update_pos(cnv);
    }
    draw();
    requestAnimationFrame(update);

}

requestAnimationFrame(update);


