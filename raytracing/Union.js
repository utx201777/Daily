/* 
* @requires Vector3
* @requires Ray3
* @requires IntersectResult
*/

Union = function(geometries) { this.geometries = geometries; };

Union.prototype = {
    initialize: function() {
        for (var i in this.geometries)
        {
            //console.log(this.geometries.toString());
            this.geometries[i].initialize();
        }            
    },
    
    intersect: function(ray) {
        var minDistance = Infinity;
        var minResult = IntersectResult.noHit;
        for (var i in this.geometries) {
            var result = this.geometries[i].intersect(ray);
            if (result.geometry && result.distance < minDistance) {
                //console.log(result.distance);
                minDistance = result.distance;
                minResult = result;
            }
        }
        return minResult;
    }
};
