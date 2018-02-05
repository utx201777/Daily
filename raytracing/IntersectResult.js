/* 
 * @requires Vector3
 */

IntersectResult = function() {
    this.geometry = null;
    this.distance = 0;
    this.position = Vector3.zero;
    this.normal = Vector3.zero;
    this.name ="";
};

IntersectResult.noHit = new IntersectResult();
