/* 
 * @requires Vector3
 * @requires Color
 */
// 射线包括一个起点和方向
Ray3 = function(origin, direction) { this.origin = origin; this.direction = direction; }

// 获得一定长度后的点，将起点加上方向乘以一定的倍数
Ray3.prototype = {
    getPoint : function(t) { return this.origin.add(this.direction.multiply(t)); }
};