//================================================
//中文词典类
//================================================
var dictionary = dictionary||{};
var $gameDictionary        = null;

//DataManager
//字典预加载
DataManager._dictionaryDataFiles = [
	{name: '$gameDictionary',       src: 'StringDictionary.json'}
];
	
DataManager.loadCVMapData = function() {
    for (var i = 0; i < this._dictionaryDataFiles.length; i++) {
        var name = this._dictionaryDataFiles[i].name;
        var src = this._dictionaryDataFiles[i].src;
        this.loadDataFile(name, src);
    }
};

//Scene_Boot
dictionary.createSceneBoot = Scene_Boot.prototype.create;
Scene_Boot.prototype.create = function(){
	dictionary.createSceneBoot.call(this);
	DataManager.loadCVMapData();
};

//DictManager
DictManager = function(){
	throw new Error('This is a static class');
}

DictManager.prototype.getString = function(key) {
	re
}
