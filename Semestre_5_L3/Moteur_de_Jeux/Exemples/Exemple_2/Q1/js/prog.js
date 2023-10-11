

let cnv = document.getElementById("myCanvas");
let ctx = cnv.getContext("2d");


ctx.imageSmoothingEnabled = false;




class myImg {
    constructor(imgSrc, w = 25, h = 25) {
    this.defaultW = w;
    this.defaultH = h
    this.w = w;
    this.h = h;
    this.imgSrc = imgSrc;

    this.x = (cnv.width / 2) - (this.w / 2);
    this.y = (cnv.height / 2) - (this.h / 2);

    this.img = new Image();
    this.img.src = this.imgSrc;
    }

    reset() {
        this.w = this.defaultW;
        this.h = this.defaultH;
        this.x = (cnv.width / 2) - (this.w / 2);
        this.y = (cnv.height / 2) - (this.h / 2);
        this.img.src = this.img;
    }

    draw(ctx) {
        ctx.drawImage(this.img, this.x, this.y, this.w, this.h);
    }
}

class myAnimatedImg extends myImg {
    constructor(sprites = [], w = 25, h = 25) {
        super(sprites[0], w, h);
        this.sprites = sprites;
    }

    next_frame() {
        let next = this.sprites.shift();
        this.sprites.push(next);
        this.img.src = next;
    }
}


// let img = new myImg();
let imgName = "pp-a_pp_walking_";
let ext = ".png";
let sprites = [];
for (let i = 0; i < 8; i++) {
    sprites.push("assets/" + imgName + (i+1) + ext);
}

// console.log(sprites)


let imgAnimated = new myAnimatedImg(sprites, 100, 100)
let gui = new dat.gui.GUI();

let imgFolder = gui.addFolder("Perso");
imgFolder.open()


imgFolder.add(imgAnimated, "x", 0, cnv.width - imgAnimated.w, 1);
imgFolder.add(imgAnimated, "y", 0, cnv.height - imgAnimated.h, 1);
imgFolder.add(imgAnimated, "w", 10, cnv.width, 1);
imgFolder.add(imgAnimated, "h", 10, cnv.height, 1);
imgFolder.add(imgAnimated, "reset");



function updateGui() {
    imgFolder.updateDisplay();
}



function updates() {
    imgAnimated.next_frame();
}


function draw() {
    ctx.clearRect(0, 0, cnv.width, cnv.height);
    imgAnimated.draw(ctx);
}


function update() {
    updates()
    draw();
    updateGui();
}


// requestAnimationFrame(update);
setInterval(update, 100);
