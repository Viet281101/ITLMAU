

class SpaceShip {
	constructor(scene) {

		var modelLoader = new THREE.GLTFLoader();

		this.model;
		this.spaceShipBndBox;
		this.shipSpeed = 0.4;
		this.limit = 15;
		this.scale = 0.03;

		modelLoader.load('../../assets/models/spaceship_cb1/scene.gltf', ((obj) => {

			const newModel = obj.scene.children[0];

			newModel.rotation.x = (Math.PI / 2);
			newModel.rotation.z = -(Math.PI / 2);
			newModel.position.z = -10;
			newModel.position.x = 0;
			newModel.position.y = 0;
			newModel.scale.set(this.scale, this.scale, this.scale);

			scene.remove(this.model);

			this.model = newModel;

			scene.add(this.model);

			this.spaceShipBndBox = new THREE.Box3().setFromObject(this.model);
		}).bind(this)
		);

		this.update = function() {
			this.model.position.z -= this.shipSpeed;
		};

		this.handleInput = function (keyMap, camera) {

			if ((keyMap[87] || keyMap[38])) {
				if (keyMap[16]) {
					this.model.position.z -= (this.shipSpeed + 1.1);
					camera.position.z -= (this.shipSpeed + 1.1);
				}
				else {
					this.model.position.z -= (this.shipSpeed + 0.6);
					camera.position.z -= (this.shipSpeed + 0.6);
				}
			}
			if ((keyMap[83] || keyMap[40]) && this.model.position.z < -1) {
				this.model.position.z += (this.shipSpeed + 0.6);
				camera.position.z += (this.shipSpeed + 0.6);
			}
			if ((keyMap[68] || keyMap[39]) && this.model.position.x < this.limit) {
				this.model.position.x += (this.shipSpeed / 2);
				camera.position.x += (this.shipSpeed / 2);
			}
			if ((keyMap[65] || keyMap[37]) && this.model.position.x > -this.limit) {
				this.model.position.x -= (this.shipSpeed / 2);
				camera.position.x -= (this.shipSpeed / 2);
			}
		};

		this.shooting = function () {

			var x = this.model.position.x;
			var z = this.model.position.z - this.spaceShipBndBox.getSize().z;

			const m = new FireBullet(scene, x, z);

			return m;
		};

		const gui = new dat.GUI();
		gui.add(this, 'shipSpeed', 0.1, 1.0);
		gui.add(this, 'limit', 10, 20);
		gui.add(this, 'scale', 0.01, 0.1);
	};
};

