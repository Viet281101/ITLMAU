
class BackgroundSpace {
	constructor(scene, height) {
	
		const textureLoader = new THREE.TextureLoader();
		
		var geometry = new THREE.CubeGeometry(height, height, height);

		var cubeMaterials = 
		[
			new THREE.MeshBasicMaterial({ map: textureLoader.load("../../assets/textures/space/space-negx.jpg"), side: THREE.DoubleSide }),
			new THREE.MeshBasicMaterial({ map: textureLoader.load("../../assets/textures/space/space-negy.jpg"), side: THREE.DoubleSide }),
			new THREE.MeshBasicMaterial({ map: textureLoader.load("../../assets/textures/space/space-negz.jpg"), side: THREE.DoubleSide }),
			new THREE.MeshBasicMaterial({ map: textureLoader.load("../../assets/textures/space/space-posx.jpg"), side: THREE.DoubleSide }),
			new THREE.MeshBasicMaterial({ map: textureLoader.load("../../assets/textures/space/space-posy.jpg"), side: THREE.DoubleSide }),
			new THREE.MeshBasicMaterial({ map: textureLoader.load("../../assets/textures/space/space-posz.jpg"), side: THREE.DoubleSide }),
		];
		var material = new THREE.MeshFaceMaterial(cubeMaterials);

		var cube = new THREE.Mesh(geometry, material);

		cube.rotation.x = Math.PI / 2;
		cube.position.z = -1490;
		// bg.position.y = 1000;

		scene.add(cube);

	};
};

