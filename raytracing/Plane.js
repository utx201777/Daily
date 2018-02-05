/* 
 * @requires Vector3
 * @requires IntersectResult
 */

 // 平面的类包括一个法线和到原点的距离
 // Ax+By+Cz+D=0
 

Plane = function(normal, d) { this.normal = normal; this.d = d; };

Plane.prototype = {
    copy : function() { return new plane(this.normal.copy(), this.d); },

    // 交点的位置
    initialize : function() {
        this.position = this.normal.multiply(this.d);
    },
    
    // 给定一条射线，求交点
    intersect : function(ray) {
        var a = ray.direction.dot(this.normal);
        if (a >= 0)
            return IntersectResult.noHit;

        var b = this.normal.dot(ray.origin.subtract(this.position));
        var result = new IntersectResult();
        result.geometry = this;
        result.distance = -b / a;
        result.position = ray.getPoint(result.distance);
        result.normal = this.normal;
        result.name = "Plane";
        return result;
    }
};
