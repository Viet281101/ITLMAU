

function checkCollision(spaceShip, enemies, bullets) {

    if (spaceShip.model) {

        this.spaceShipBB = new THREE.Box3().setFromObject(spaceShip.model);

        // HANDLING COLLISION 

        var i = enemies.length;
        while (i--) {
            if (enemies[i]) {
                enemyBB = new THREE.Box3().setFromObject(enemies[i].model);

                if (this.spaceShipBB.intersectsBox(enemyBB)) {
                    enemies[i].destroy();
                    enemies.splice(i, 1);
                };
            };

            var j = bullets.length;
            while (j--) {
                if (bullets[j]) {
                    this.bulletBB = new THREE.Box3().setFromObject(bullets[j].model);
                    if (this.bulletBB.intersectsBox(enemyBB)) {
                        var blast_sound = new Audio('../assets/sound/blast.wav');
                        blast_sound.volume = 0.5;
                        blast_sound.play();
                        enemies[i].destroy();
                        enemies.splice(i, 1);
                        bullets[j].destroy();
                        bullets.splice(j, 1);
                    };
                };
            };
        };
    };

    return [enemies, bullets];

};

