/* 
 * @requires Vector3
 * @requires Color
 * 格子材质
 */
// scale代表单位长度内有多少个格子
CheckerMaterial = function(scale, reflectiveness) { this.scale = scale; this.reflectiveness = reflectiveness; };

CheckerMaterial.prototype = {
	// ray代表光线，Position代表材质的位置，normal是所在位置的法线，这里仅需要位置一个属性。
    sample : function(ray, position, normal) {
        return Math.abs((Math.floor(position.x * this.scale) + Math.floor(position.z * this.scale)) % 2) < 1 ? Color.black : Color.white;
    }
};

CheckerMaterialy = function(scale, reflectiveness) { this.scale = scale; this.reflectiveness = reflectiveness; };

CheckerMaterialy.prototype = {
	// ray代表光线，Position代表材质的位置，normal是所在位置的法线，这里仅需要位置一个属性。
    sample : function(ray, position, normal) {
        return Math.abs((Math.floor(position.z * this.scale) + Math.floor(position.y * this.scale)) % 2) < 1 ? Color.black : Color.white;
    }
};
