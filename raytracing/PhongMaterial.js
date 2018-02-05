/* 
 * @requires Vector3
 * @requires Color
 */

PhongMaterial = function(diffuse, specular, shininess, reflectiveness) {
    this.diffuse = diffuse;
    this.specular = specular;
    this.shininess = shininess;
    // 反射占的比重 0-1之间
    this.reflectiveness = reflectiveness;
};

// global temp  假设的全局光线方向，光线的强度
var lightDir = new Vector3(1, 0.5, 1).normalize();
var lightColor = Color.white;

PhongMaterial.prototype = {
    sample: function(ray, position, normal) {
            
        //return new Color(1,1,0);     
        var NdotL = normal.dot(lightDir);       // 计算漫反射的值
        var H = (lightDir.subtract(ray.direction)).normalize();
        var NdotH = normal.dot(H);              // 计算镜面反射
        var diffuseTerm = this.diffuse.multiply(Math.max(NdotL, 0));
        var specularTerm = this.specular.multiply(Math.pow(Math.max(NdotH, 0), this.shininess));
        return lightColor.modulate(diffuseTerm.add(specularTerm).convert());            
    }
};


/*
if (result.geometry) {

                var color = result.geometry.material.sample(ray, result.position, result.normal);

                pixels[i] = color.r * 255;

                pixels[i + 1] = color.g * 255;

                pixels[i + 2] = color.b * 255;

                pixels[i + 3] = 255;

            }
*/