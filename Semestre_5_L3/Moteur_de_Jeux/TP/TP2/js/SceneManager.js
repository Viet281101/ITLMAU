

class SceneManager {
    constructor(canvas) {

        const screenDimensions = {
            width: canvas.width,
            height: canvas.height
        };

        // INITIALISATION
        const scene = buildScene();
        const renderer = buildRender(screenDimensions);
        const camera = buildCamera(screenDimensions);

        var keyMap = [];

        var spaceShip, theSkybox, enemies;
        const dynamicSubjects = createSceneSubjects(scene);
        var bullets = [];


        // AMBIENT LIGHTING
        var ambientLight = new THREE.AmbientLight('#ffffff', 1.5);
        scene.add(ambientLight);


        var gameEnded = false;


        function buildScene() {
            const scene = new THREE.Scene();
            return scene;
        }


        function buildRender({ width, height }) {
            const renderer = new THREE.WebGLRenderer({ canvas: canvas, antialias: true, alpha: true });

            renderer.setClearColor("#222222");
            renderer.setSize(width, height);

            return renderer;
        }


        function buildCamera({ width, height }) {
            const aspectRatio = width / height;
            const fieldOfView = 30;
            const nearPlane = 0.1;
            const farPlane = 3000;
            const camera = new THREE.PerspectiveCamera(fieldOfView, aspectRatio, nearPlane, farPlane);

            camera.position.y = 0.65;
            return camera;
        }


        function createSceneSubjects(scene) {
            theSkybox = new BackgroundSpace(scene, 3000);
            spaceShip = new SpaceShip(scene);
            enemies = placeEnemies(scene);

            const dynSubjs = [spaceShip];

            return dynSubjs;
        }

        //// UPDATE
        this.update = function () {

            if (camera.position.z > -2400) {

                camera.position.z -= spaceShip.shipSpeed;

                for (let i = 0; i < dynamicSubjects.length; i++)
                    if (dynamicSubjects[i].model) {
                        dynamicSubjects[i].update();
                    }

                [enemies, bullets] = checkCollision(spaceShip, enemies, bullets);

                bullets = freeBullets(bullets);

                // RENDERING
                renderer.render(scene, camera);

                // EXECUTING INPUT MOVEMENT
                if (spaceShip.model) {
                    spaceShip.handleInput(keyMap, camera);

                    //// space key shooting
                    if (keyMap[32]) {
                        const m = spaceShip.shooting();

                        //// shooting sound
                        const listener = new THREE.AudioListener();
                        camera.add(listener);
                        const sound = new THREE.Audio(listener);
                        const audioLoader = new THREE.AudioLoader();
                        audioLoader.load('../assets/sound/shoot.wav', function (buffer) {
                            sound.setBuffer(buffer);
                            sound.setLoop(false);
                            sound.setVolume(0.5);
                            sound.play();
                        });

                        dynamicSubjects.push(m);
                        bullets.push(m);
                        keyMap[32] = false;
                    }
                }


            };
        };


        this.onWindowResize = function () {
            const { width, height } = canvas;

            screenDimensions.width = width;
            screenDimensions.height = height;

            renderer.setSize(width, height);

            camera.aspect = width / height;
            camera.updateProjectionMatrix();
        };


        this.handleInput = function (keyCode, isDown) {

            keyMap[keyCode] = isDown;
        };
    };
};


function freeBullets(bullets) {

    var j = bullets.length;
    while (j--) {
        if (bullets[j].model && bullets[j].model.position.z < -2400) {
            bullets[j].destroy();
            bullets.splice(j, 1);
        }
    };

    return bullets;
};

