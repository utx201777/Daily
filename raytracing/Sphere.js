/* 
 * @requires Vector3, Ray3
 */

// 球的定义，包含一个中心和半径
Sphere = function(center, radius) { this.center = center; this.radius = radius; };

Sphere.prototype = {
    copy : function() { return new Sphere(this.center.copy(), this.radius.copy()); },

    initialize : function() {
        this.sqrRadius = this.radius * this.radius;
    },

// 与一条光线求交点
    intersect : function(ray) {
        var v = ray.origin.subtract(this.center);
        var a0 = v.sqrLength() - this.sqrRadius;
        var DdotV = ray.direction.dot(v);       // v是光线与球心的连线，可以得到两者的夹角

        if (DdotV <= 0) {       // 如果夹角大于90度，肯定没有交点
            var discr = DdotV * DdotV - a0;
            if (discr >= 0) {
                var result = new IntersectResult();
                result.geometry = this;
                //距离
                result.distance = -DdotV - Math.sqrt(discr);
                //交点的位置
                result.position = ray.getPoint(result.distance);
                //交点处的方法
                result.normal = result.position.subtract(this.center).normalize();
                result.name = "Sphere";
                return result;
            }
        }
        return IntersectResult.noHit;
    }
};
