/* 
 * @requires Vector3
 */

PerspectiveCamera = function(eye, front, up, fov) { this.eye = eye; this.front = front; this.refUp = up; this.fov = fov; };

PerspectiveCamera.prototype = {
    initialize : function() {
        this.right = this.front.cross(this.refUp);
        this.up = this.right.cross(this.front);
        this.fovScale = Math.tan(this.fov * 0.5 * Math.PI / 180) * 2;
    },
    //将屏幕坐标归一化到0到1，然后转化为-1到1，然后对原来的向量进行偏转
    generateRay : function(x, y) {
        //console.log(this.right);
        var r = this.right.multiply((x - 0.5) * this.fovScale);
        var u = this.up.multiply((y - 0.5) * this.fovScale);
        return new Ray3(this.eye, this.front.add(r).add(u).normalize());
    }
};
